#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "QGraphicsScene.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
		
private slots:
	void load_scene();
	void about(); 

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
