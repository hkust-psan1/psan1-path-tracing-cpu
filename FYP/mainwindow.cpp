#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::load_scene()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load Scene",  QDir::currentPath(), "Blender File(*.obj);;All files(*.*)");
	if (!filename.isNull()) 
	{
	   QMessageBox::information(this, "Document", "Has document", QMessageBox::Ok | QMessageBox::Cancel);
	}
}

void MainWindow::about()
{
	QGraphicsScene* scene = new QGraphicsScene();
	scene->addLine(15, 18, 90, 80);
	ui.graphicsView->setScene(scene);
	QMessageBox::about(this, tr("About"), tr("HKUST 2014 FYP"));
}