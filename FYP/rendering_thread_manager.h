#ifndef FYP_rendering_thread_manager_h
#define FYP_rendering_thread_manager_h

#include <QThread>
#include <QObject>
#include <QMutex>
#include <queue>
#include "RayTracer.h"

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <mach/clock.h>
#include <mach/mach.h>

class MainWindow;

struct RenderNode {
    RenderNode(Ray* r, int x, int y, int d, Vec3 p) : ray(r), x(x), y(y), depth(d), p(p) {};
	Ray* ray;
	int x;
	int y;
	int depth;
	Vec3 p;
};

struct PixelData {
    PixelData(): color(Vec3(0.f)), rendered(false) {};
    PixelData(const Vec3& c): color(c), rendered(false) {};
    Vec3 color;
    bool rendered;
};

class RenderManager : public QObject {
    Q_OBJECT
public:
    RenderManager(QObject* parent = 0) : QObject(parent) { };
    RenderManager(int w, int h, int n = 4);
    ~RenderManager();
    
    RenderNode* getTask();
    void addTask(RenderNode* n);
    bool noTask();
    void clearTasks();
    void setPixelData(int x, int y, const Vec3& color);
    void stopRendering();
    
    inline bool isRendering() const { return rendering; };
    inline void setScene(Scene* s) { scene = s; };
	inline bool sceneLoaded() const { return scene != NULL; };
    inline void setMainWindow(MainWindow* w) { window = w; };
    inline Camera* getCamera() const { return camera; };
    inline Scene* getScene() const { return scene; };
    inline QImage* getFrontBuffer() const { return frontBuffer; };
    inline QImage* getBackBuffer() const { return backBuffer; };
    inline queue<RenderNode*>* getTasks() { return &tasks; };
    
    int width, height;
    int maxDepth;
    Vec3 threshold;
    PixelData** colorBuffer;
    QMutex taskQueueMutex;
    
    /* number of nodes already rendered, used to update screen gradually */
    int numOfRenderedNodes;
public slots:
    /* triggered by the mainwindow */
    void render();
    
    /* triggered when a tracer signals the completion of a ray */
    void tracerRayCompleted(int x, int y, Vec3 color);
    
    /* tracer has completed all jobs */
    void tracerCompleted();
signals:
    void updateScreen();
    
private:
    void draw();
    void refreshColorBuffer();
    
    QThread** renderingThreads;
    RayTracer** tracers;
    queue<RenderNode*> tasks;
    int numOfThreads;
    
    Camera* camera;
    Scene* scene;
    MainWindow* window;
    
    QImage* frontBuffer;
    QImage* backBuffer;

    bool rendering;
    
    int completedTracerCount;
    
    /* used for testing speed */
    // clock_t startTime;
    void current_utc_time(struct timespec *ts);
    struct timespec start, end;
};

#endif
