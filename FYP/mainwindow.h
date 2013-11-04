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
#include <QKeyEvent>
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "QGraphicsScene.h"
#include "rendering_thread_manager.h"

class ObjKVPair;
class ObjFileNode;
class Parser;

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
	void threadTerminated();
	
signals:
    void pressed();
	
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
	Ui::MainWindowClass ui;
	QPixmap pixmap;
	
	RenderManager* renderManager;
    QThread* rendererThread;
    
    bool imageRendered;
    bool frameReady;
    
    int lastX, lastY;
    QPoint* lastPos;
    
    Parser* parser;
};

#endif // MAINWINDOW_H
