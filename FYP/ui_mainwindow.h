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
    QPushButton *pushButton;
    QCheckBox *HBVcheckBox;
    QCheckBox *AAcheckBox;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->setWindowModality(Qt::NonModal);
        MainWindowClass->resize(973, 639);
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
        pixmapLabel->setGeometry(QRect(0, 0, 500, 500));
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 973, 21));
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
        pushButton = new QPushButton(dockWidgetContents);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 310, 61, 23));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        HBVcheckBox = new QCheckBox(dockWidgetContents);
        HBVcheckBox->setObjectName(QString::fromUtf8("HBVcheckBox"));
        HBVcheckBox->setGeometry(QRect(20, 80, 51, 21));
        HBVcheckBox->setChecked(true);
        AAcheckBox = new QCheckBox(dockWidgetContents);
        AAcheckBox->setObjectName(QString::fromUtf8("AAcheckBox"));
        AAcheckBox->setGeometry(QRect(20, 100, 51, 21));
        AAcheckBox->setChecked(true);
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
        pushButton->setText(QApplication::translate("MainWindowClass", "Render", 0, QApplication::UnicodeUTF8));
        pushButton->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        HBVcheckBox->setText(QApplication::translate("MainWindowClass", "HBV", 0, QApplication::UnicodeUTF8));
        AAcheckBox->setText(QApplication::translate("MainWindowClass", "AA", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
