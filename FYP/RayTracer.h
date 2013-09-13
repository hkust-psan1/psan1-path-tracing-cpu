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
#include "subdivision_renderer.h"

class MainWindow;

class RayTracer : public QObject {
    Q_OBJECT
public:
    RayTracer(QObject* parent = 0) : QObject(parent) { };
	RayTracer(int width, int height);
	~RayTracer();

    // Vec3 trace(double x, double y );
	Vec3 traceRay(const Ray& ray, int depth = 0);
	inline void setScene(Scene* scene) { this->scene = scene; };
	inline bool sceneLoaded() { return scene != NULL; };

	inline void addLight(Light* l) { lights.push_back(l); };
	
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
	
	QImage image;
	
public slots:
	void render();
	
signals:
    void rowCompleted();

private:
	static const int maxDepth = 2;
	int width;
	int height;

	Camera* camera;
	Scene* scene;
	std::vector<Light*> lights;
	MainWindow* window;
	
    bool** pixelRendered;
};

#endif // __RAYTRACER_H__
