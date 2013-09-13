/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionLoad_Scene;
    QAction *actionAbout;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *pixmapLabel;
    QMenuBar *menuBar;
    QMenu *menuStart;
    QMenu *menuHelp;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QCheckBox *checkBox;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->setWindowModality(Qt::NonModal);
        MainWindowClass->resize(973, 543);
        actionLoad_Scene = new QAction(MainWindowClass);
        actionLoad_Scene->setObjectName(QString::fromUtf8("actionLoad_Scene"));
        actionAbout = new QAction(MainWindowClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pixmapLabel = new QLabel(centralWidget);
        pixmapLabel->setObjectName(QString::fromUtf8("pixmapLabel"));
        pixmapLabel->setGeometry(QRect(100, 40, 500, 400));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 973, 22));
        menuStart = new QMenu(menuBar);
        menuStart->setObjectName(QString::fromUtf8("menuStart"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        dockWidget = new QDockWidget(MainWindowClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        checkBox = new QCheckBox(dockWidgetContents);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 40, 70, 17));
        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 270, 75, 23));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
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
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindowClass, SLOT(render()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Ray Tracing", 0, QApplication::UnicodeUTF8));
        actionLoad_Scene->setText(QApplication::translate("MainWindowClass", "Load Scene", 0, QApplication::UnicodeUTF8));
        actionLoad_Scene->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+L", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowClass", "About", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        pixmapLabel->setText(QString());
        menuStart->setTitle(QApplication::translate("MainWindowClass", "Start", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindowClass", "About", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindowClass", "HBV", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindowClass", "Render", 0, QApplication::UnicodeUTF8));
        pushButton->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+R", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
