#include "mainwindow.h"
#include "setting.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QSize size = ui.pixmapLabel->size();
	tracer = new RayTracer(size.width() - 2, size.height() - 2);
	tracer->setMainWindow(this);
    lastPos = NULL;
}

MainWindow::~MainWindow()
{

}

void MainWindow::load_scene()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load Scene",  QDir::currentPath(), "Wavefront Object File(*.obj);;All files(*.*)");
	if (!filename.isNull()) 
	{
		tracer->setScene(Parser::parseScene(filename.toStdString().c_str()));
		PointLight* l1 = new PointLight(Vec3(14, 9, 6), Vec3(1, 1, 1));
		PointLight* l2 = new PointLight(Vec3(15, 15, 15), Vec3(1, 1, 1));
		tracer->addLight(l1);
		tracer->addLight(l2);
	}
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About"), tr("HKUST 2014 FYP"));
}

void MainWindow::render()
{
	if (!tracer->sceneLoaded())
	{
		load_scene();
	}
	Setting::HBV = ui.HBVcheckBox->isChecked();

	rendererThread = new QThread;

	tracer->moveToThread(rendererThread);
	connect(rendererThread, SIGNAL(started()), tracer, SLOT(render()));
	connect(tracer, SIGNAL(rowCompleted()), this, SLOT(updateScreen()));
	// connect(rendererThread, SIGNAL(finished()), this, SLOT(threadTerminated()));
	
    frameReady = false;
    
	rendererThread->start();
}

void MainWindow::threadTerminated() {
    std::cout << "thread terminated" << std::endl;
    render();
}

void MainWindow::updateScreen() {
	pixmap = QPixmap::fromImage(*tracer->frontBuffer);
	ui.pixmapLabel->setPixmap(pixmap);
    
    frameReady = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (frameReady) {
        Camera* cam = tracer->getCamera();
        
        if (event->key() == Qt::Key_Left) {
            cam->setEyePos(cam->getEyePos() - Vec3(0.3, 0, 0));
            tracer->stopRendering();
            render();
        } else if (event->key() == Qt::Key_Right) {
            cam->setEyePos(cam->getEyePos() + Vec3(0.3, 0, 0));
            tracer->stopRendering();
            render();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {    
    if (lastPos == NULL) {
        lastPos = new QPoint(event->pos());
    }
    
    Camera* cam = tracer->getCamera();
        
    int xDiff = event->x() - lastPos->x();
    int yDiff = event->y() - lastPos->y();
    // std::cout << xDiff << '\t' << yDiff << std::endl;
    
    Vec3 eye = cam->getEyePos();
    Vec3 ctr = cam->getCenterPos();
    
    float newX = (eye.x - ctr.x) * cos(xDiff / 30.0) - (eye.z - ctr.z) * sin(xDiff / 30.0);
    float newY = (eye.z - ctr.z) * cos(xDiff / 30.0) + (eye.x - ctr.x) * sin(xDiff / 30.0);
    
    cam->setEyePos(Vec3(newX, cam->getEyePos().y, newY) + cam->getCenterPos());
    cam->update();
    
    std::cout << cam->getEyePos() << std::endl;
    std::cout << Vec3(newX, cam->getEyePos().y, newY) << std::endl;
    
    //cam->setEyePos(cam->getEyePos() - Vec3(0.1 * xDiff, 0.1 * yDiff, 0));
    tracer->stopRendering();
    render();

    lastPos = new QPoint(event->pos());
    lastX = event->x();
    lastY = event->y();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    Camera* cam = tracer->getCamera();
    Vec3 view = cam->getEyePos() - cam->getCenterPos();

    cam->setEyePos(cam->getCenterPos() + view * (1 - event->delta() * 0.001));
    
    tracer->stopRendering();
    render();
}
