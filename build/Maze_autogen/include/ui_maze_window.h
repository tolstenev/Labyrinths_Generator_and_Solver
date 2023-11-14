/********************************************************************************
** Form generated from reading UI file 'maze_window.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZE_WINDOW_H
#define UI_MAZE_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MazeWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MazeWindow)
    {
        if (MazeWindow->objectName().isEmpty())
            MazeWindow->setObjectName(QString::fromUtf8("MazeWindow"));
        MazeWindow->resize(800, 575);
        centralwidget = new QWidget(MazeWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(290, 10, 501, 501));
        MazeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MazeWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MazeWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MazeWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MazeWindow->setStatusBar(statusbar);

        retranslateUi(MazeWindow);

        QMetaObject::connectSlotsByName(MazeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MazeWindow)
    {
        MazeWindow->setWindowTitle(QCoreApplication::translate("MazeWindow", "MazeWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MazeWindow: public Ui_MazeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZE_WINDOW_H
