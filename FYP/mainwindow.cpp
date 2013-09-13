#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QSize size = ui.pixmapLabel->size();
	tracer = new RayTracer(size.width() - 2, size.height() - 2);
	tracer->setMainWindow(this);
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
		DirectionalLight* l1 = new DirectionalLight(Vec3(88, 99, 100), Vec3(1.0, 1.0, 1.0));
		DirectionalLight* l2 = new DirectionalLight(Vec3(-66, -77, -100), Vec3(1.0, 1.0, 1.0));
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
	
	QThread* rendererThread = new QThread;
	
	tracer->moveToThread(rendererThread);
	connect(rendererThread, SIGNAL(started()), tracer, SLOT(render()));
	connect(tracer, SIGNAL(rowCompleted()), this, SLOT(updateScreen()));
	
	rendererThread->start();
}

void MainWindow::updateScreen() {
	pixmap = QPixmap::fromImage(tracer->image);
	ui.pixmapLabel->setPixmap(pixmap);
}
