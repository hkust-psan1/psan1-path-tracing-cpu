#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

// The main ray tracer.

#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "qimage.h"
#include "parser.h"
#include "scene.h"
#include "light.h"
#include "qobject.h"
#include <queue>

class MainWindow;

struct node
{
	Ray* ray;
	int x;
	int y;
	int depth;
	Vec3 p;
};

class RayTracer : public QObject {
    Q_OBJECT
public:
    RayTracer(QObject* parent = 0) : QObject(parent) { };
	RayTracer(int width, int height);
	~RayTracer();

    // Vec3 trace(double x, double y );
	void traceRay(node n);
	Vec3 traceRay(int x, int y);
	inline void setScene(Scene* scene) { this->scene = scene; };
	inline bool sceneLoaded() { return scene != NULL; };
	
    inline Camera* getCamera() const { return camera; };
	
    void renderWithGridSize(int gridSize);

    /*
	inline void setMaxDepth(int m) { maxDepth = m; }
	void getBuffer( unsigned char *&buf, int &w, int &h );
	double aspectRatio();
	void traceSetup( int w, int h );
	void traceLines( int start = 0, int stop = 10000000 );
	void tracePixel( int i, int j );
	void antiAliasing(int part);
	*/

	// bool loadScene( char* fn );
	
    inline void setMainWindow(MainWindow* w) { window = w; };
	
	
    inline void stopRendering() { rendering = false; };

    QImage* frontBuffer;
    QImage* backBuffer;
	
public slots:
	void render();
    
signals:
    void rowCompleted();

private:
	static const int maxDepth = 10;
	static const Vec3 threshold;
	int width;
	int height;

	Camera* camera;
	Scene* scene;
	MainWindow* window;
	
    bool** pixelRendered;
	Vec3** colorBuffer;
	std::queue<node> queue;
    
    bool rendering;
};

#endif // __RAYTRACER_H__
