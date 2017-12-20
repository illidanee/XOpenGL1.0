/********************************************************************************
** Form generated from reading UI file 'OpenGLQT.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLQT_H
#define UI_OPENGLQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLQTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenGLQTClass)
    {
        if (OpenGLQTClass->objectName().isEmpty())
            OpenGLQTClass->setObjectName(QStringLiteral("OpenGLQTClass"));
        OpenGLQTClass->resize(600, 400);
        menuBar = new QMenuBar(OpenGLQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        OpenGLQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenGLQTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OpenGLQTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OpenGLQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OpenGLQTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OpenGLQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OpenGLQTClass->setStatusBar(statusBar);

        retranslateUi(OpenGLQTClass);

        QMetaObject::connectSlotsByName(OpenGLQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenGLQTClass)
    {
        OpenGLQTClass->setWindowTitle(QApplication::translate("OpenGLQTClass", "OpenGLQT", 0));
    } // retranslateUi

};

namespace Ui {
    class OpenGLQTClass: public Ui_OpenGLQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLQT_H
