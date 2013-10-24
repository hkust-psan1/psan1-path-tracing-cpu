#include "rendering_thread_manager.h"

RenderManager::RenderManager(int w, int h, int n)
: width(w), height(h), maxDepth(10), threshold(Vec3(0.01)), numOfThreads(n) {
    camera = new Camera(Vec3(15, 10, 20), Vec3(0, 0, 0), Vec3(0, 1, 0));
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
    tasks.push(n);
    taskQueueMutex.unlock();
}

RenderNode* RenderManager::getTask() {
    taskQueueMutex.lock();
    RenderNode* task;
    if (tasks.size() > 0) {
         task = tasks.front();
        tasks.pop();
    } else {
        task = NULL;
    }
    taskQueueMutex.unlock();
    return task;
}

bool RenderManager::noTask() {
    taskQueueMutex.lock();
    bool empty = tasks.empty();
    taskQueueMutex.unlock();
    return empty;
}

void RenderManager::setPixelData(int x, int y, const Vec3& color) {
    PixelData& data = colorBuffer[x][y];
    if (data.rendered) {
        data.color += color;
    } else {
        data.color = color;
        data.rendered = true;
    }
    data.color.clamp();
    
    if (numOfRenderedNodes++ % 50000 == 0) {
        draw();
    }
}

void RenderManager::stopRendering() {
    rendering = false;
    for (int i = 0; i < numOfThreads; i++) {
        renderingThreads[i]->terminate();
    }
}

void RenderManager::clearTasks() {
    taskQueueMutex.lock();
    while (tasks.size() > 0) {
        tasks.pop();
    }
    taskQueueMutex.unlock();
}

void RenderManager::render() {
    //current_utc_time(&start);
    
    rendering = true;
    numOfRenderedNodes = 0;
    completedTracerCount = 0;
    
    while (!tasks.empty()) {
        tasks.pop();
    }
    
    refreshColorBuffer();
    
    /* initialize render nodes for the primary rays from the camera */
    /*
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Ray* cameraRay = camera->getCameraRay(i, j);
            RenderNode* node = new RenderNode(cameraRay, i, j, 0, Vec3(1.f));
            addTask(node);
        }
    }
    */
    
    int centerX = width / 2;
    int centerY = height / 2;
    int distance = 0;
    
    while (true) {
        bool nodeAdded = false;
        
        for (int i = centerX - distance; i <= centerX + distance; i++) {
            for (int j = centerY - distance; j <= centerY + distance; j++) {
                if (i == centerX - distance || i == centerX + distance
                    || j == centerY - distance || j == centerY + distance) {
                    if (i >= 0 && i < width && j >= 0 && j < height) {
                        Ray* cameraRay = camera->getCameraRay(i, j);
                        RenderNode* node = new RenderNode(cameraRay, i, j, 0, Vec3(1.f));
                        addTask(node);
                        nodeAdded = true;
                    }
                }
            }
        }
        
        if (!nodeAdded) {
            break;
        }
        
        distance++;
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
        // rendering = false;
        draw();
    }
        
    // current_utc_time(&end);
    /*
     printf("s:  %lu\n", end.tv_sec - start.tv_sec);
     printf("ns: %lu\n", end.tv_sec - start.tv_nsec);
     */
    // cout << "time elapsed: " << float(clock() - startTime) / CLOCKS_PER_SEC << endl;
}

void RenderManager::draw() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            backBuffer->setPixel(j, i, qRgb(colorBuffer[j][i].color.x * 255,
                colorBuffer[j][i].color.y * 255, colorBuffer[j][i].color.z * 255));
        }
    }
    
    QImage* tmp = backBuffer;
    backBuffer = frontBuffer;
    frontBuffer = tmp;
    
    emit updateScreen();
}

void RenderManager::refreshColorBuffer() {
    if (colorBuffer == NULL) {
        colorBuffer = new PixelData*[height];
        for (int i = 0; i < height; i++) {
            colorBuffer[i] = new PixelData[width];
            for (int j = 0; j < width; j++) {
                colorBuffer[i][j] = PixelData(Vec3(0.f));
            }
        }
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // colorBuffer[i][j].color(Vec3(0.f));
            colorBuffer[i][j].rendered = false;
        }
    }
}

void RenderManager::current_utc_time(struct timespec *ts) {
    /*clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;*/
}