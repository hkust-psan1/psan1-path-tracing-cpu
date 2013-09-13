#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __APPLE__
	#include <QMainWindow>
    #include <QLabel>
#else
	#include <QtWidgets/QMainWindow>
    #include <QtWidgets/QLabel>
#endif

#include <QMessageBox>
#include <QThread>
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "QGraphicsScene.h"
#include "parser.h"
#include "RayTracer.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
		
private slots:
	void load_scene();
	void about(); 
	void render();

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	
public slots:
	void updateScreen();

private:
	Ui::MainWindowClass ui;
	QPixmap pixmap;
	
	RayTracer* tracer;
};

#endif // MAINWINDOW_H
