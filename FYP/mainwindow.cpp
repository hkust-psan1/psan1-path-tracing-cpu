#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QSize size = ui.pixmapLabel->size();
	tracer = new RayTracer(size.width() - 2, size.height() - 2);
	tracer->setMainWindow(this);
	
    connect(this, SIGNAL(pressed()), this, SLOT(render()));
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
		PointLight* l1 = new PointLight(Vec3(4, 1, 6), Vec3(1, 1, 1));
		PointLight* l2 = new PointLight(Vec3(0, 10, 0), Vec3(1, 1, 1));
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
	if (!tracer->sceneLoaded()) {
		load_scene();
	}
	
	rendererThread = new QThread;
	
	tracer->moveToThread(rendererThread);
	connect(rendererThread, SIGNAL(started()), tracer, SLOT(render()));
	connect(tracer, SIGNAL(rowCompleted()), this, SLOT(updateScreen()));
	connect(rendererThread, SIGNAL(finished()), this, SLOT(threadTerminated()));
	
	rendererThread->start();
}

void MainWindow::threadTerminated() {
    std::cout << "thread terminated" << std::endl;
}

void MainWindow::updateScreen() {
	pixmap = QPixmap::fromImage(tracer->image);
	ui.pixmapLabel->setPixmap(pixmap);
}

/*
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        Camera* cam = tracer->getCamera();
        cam->setEyePos(cam->getEyePos() + Vec3(0.03, 0, 0));
        rendererThread->terminate();
        std::cout << rendererThread->isRunning() << std::endl;
        
        // emit pressed();
    }
}
*/ 
