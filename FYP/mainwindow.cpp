#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QSize size = ui.graphicsView->size();
	tracer = RayTracer(size.width() - 2, size.height() - 2);
}

MainWindow::~MainWindow()
{

}

void MainWindow::load_scene()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load Scene",  QDir::currentPath(), "Blender File(*.obj);;All files(*.*)");
	if (!filename.isNull()) 
	{
		tracer.setScene(&Parser::parseObjFile(filename.toStdString().c_str()));
	}
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About"), tr("HKUST 2014 FYP"));
}

void MainWindow::render()
{
	if (!tracer.sceneLoaded())
	{
		load_scene();
	}
	tracer.render();
	QPixmap pixmap = QPixmap::fromImage(tracer.image);
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(pixmap);
	ui.graphicsView->setScene(scene);
}