/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionLoad_Scene;
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuStart;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QCheckBox *checkBox;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->setWindowModality(Qt::NonModal);
        MainWindowClass->resize(973, 543);
        actionLoad_Scene = new QAction(MainWindowClass);
        actionLoad_Scene->setObjectName(QStringLiteral("actionLoad_Scene"));
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(20, 20, 501, 431));
        graphicsView->setMinimumSize(QSize(471, 411));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 973, 21));
        menuStart = new QMenu(menuBar);
        menuStart->setObjectName(QStringLiteral("menuStart"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        dockWidget = new QDockWidget(MainWindowClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        checkBox = new QCheckBox(dockWidgetContents);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 10, 70, 17));
        dockWidget->setWidget(dockWidgetContents);
        MainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuStart->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuStart->addAction(actionLoad_Scene);
        menuStart->addSeparator();
        menuStart->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindowClass);
        QObject::connect(actionAbout, SIGNAL(triggered()), MainWindowClass, SLOT(about()));
        QObject::connect(actionLoad_Scene, SIGNAL(triggered()), MainWindowClass, SLOT(load_scene()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindowClass, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Ray Tracing", 0));
        actionLoad_Scene->setText(QApplication::translate("MainWindowClass", "Load Scene", 0));
        actionLoad_Scene->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+L", 0));
        actionAbout->setText(QApplication::translate("MainWindowClass", "About", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+W", 0));
        menuStart->setTitle(QApplication::translate("MainWindowClass", "Start", 0));
        menuHelp->setTitle(QApplication::translate("MainWindowClass", "About", 0));
        checkBox->setText(QApplication::translate("MainWindowClass", "HBV", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
