#include "rendering_thread_manager.h"


RenderManager::RenderManager(int w, int h, int n)
: width(w), height(h), maxDepth(10), threshold(Vec3(0.01)), numOfThreads(n) {
    camera = new Camera(Vec3(15, 10, 16), Vec3(0, 0, 0), Vec3(0, 1, 0));
    camera->setSize(w, h);
    
    frontBuffer = new QImage(w, h, QImage::Format_RGB32);
    backBuffer = new QImage(w, h, QImage::Format_RGB32);
    
    rendering = false;
    
    colorBuffer = NULL;
}

RenderManager::~RenderManager() {
    delete [] tracers;
}

void RenderManager::addTask(RenderNode *n) {
    taskQueueMutex.lock();
    if (n == NULL) {
        printf("fuck\n");
    }
    tasks.push(n);
    taskQueueMutex.unlock();
}

RenderNode* RenderManager::getTask() {
    taskQueueMutex.lock();
    RenderNode* task = tasks.front();
    tasks.pop();
    taskQueueMutex.unlock();
    return task;
}

bool RenderManager::noTask() {
    taskQueueMutex.lock();
    bool empty = tasks.empty();
    taskQueueMutex.unlock();
    return empty;
}

void RenderManager::render() {
    current_utc_time(&start);
    
    rendering = true;
    
    printf("%d\n", tasks.size());
    while (!tasks.empty()) {
        tasks.pop();
    }
    
    refreshColorBuffer();
    
    completedTracerCount = 0;
    
    /* initialize render nodes for the primary rays from the camera */
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Ray* cameraRay = camera->getCameraRay(i, j);
            RenderNode* node = new RenderNode(cameraRay, i, j, 0, Vec3(1.f));
            addTask(node);
        }
    }
    
    /* initialize all the tracers and threads */
    tracers = new RayTracer*[numOfThreads];
    renderingThreads = new QThread*[numOfThreads];
    
    /* schedule task for all the threads */
    for (int i = 0; i < numOfThreads; i++) {
        tracers[i] = new RayTracer(this, i);
        renderingThreads[i] = new QThread;
        tracers[i]->moveToThread(renderingThreads[i]);
        
        connect(renderingThreads[i], SIGNAL(started()), tracers[i], SLOT(run()));
        connect(tracers[i], SIGNAL(rayTraced(int, int, Vec3)), this, SLOT(tracerRayCompleted(int, int, Vec3)));
        connect(tracers[i], SIGNAL(completed()), this, SLOT(tracerCompleted()));
        
        renderingThreads[i]->start();
    }
}

void RenderManager::tracerRayCompleted(int x, int y, Vec3 c) {
    QColor origColor = backBuffer->pixel(x, y);

    backBuffer->setPixel(x, y, qRgb(c.x * 255 + origColor.red(),
        c.y * 255 + origColor.green(), c.z * 255 + origColor.blue()));
}

void RenderManager::tracerCompleted() {
    if (++completedTracerCount == numOfThreads) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                backBuffer->setPixel(j, i, qRgb(colorBuffer[j][i].x * 255, colorBuffer[j][i].y * 255, colorBuffer[j][i].z * 255));
            }
        }
        
        QImage* tmp = backBuffer;
        backBuffer = frontBuffer;
        frontBuffer = tmp;
        rendering = false;
        emit updateScreen();
        current_utc_time(&end);
        printf("s:  %lu\n", end.tv_sec - start.tv_sec);
        printf("ns: %lu\n", end.tv_sec - start.tv_nsec);
        // cout << "time elapsed: " << float(clock() - startTime) / CLOCKS_PER_SEC << endl;
    }
}

void RenderManager::refreshColorBuffer() {
    if (colorBuffer) {
        for (int i = 0; i < height; i++) {
            delete [] colorBuffer[i];
        }
        delete [] colorBuffer;
    }
    
    colorBuffer = new Vec3*[height];
    for (int i = 0; i < height; i++) {
        colorBuffer[i] = new Vec3[width];
        for (int j = 0; j < width; j++) {
            colorBuffer[i][j] = Vec3(0.f);
        }
    }
}

void RenderManager::current_utc_time(struct timespec *ts) {
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
}