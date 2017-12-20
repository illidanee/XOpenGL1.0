/********************************************************************************
** Form generated from reading UI file 'OpenGLES20QT.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLES20QT_H
#define UI_OPENGLES20QT_H

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

class Ui_OpenGLES20QTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenGLES20QTClass)
    {
        if (OpenGLES20QTClass->objectName().isEmpty())
            OpenGLES20QTClass->setObjectName(QStringLiteral("OpenGLES20QTClass"));
        OpenGLES20QTClass->resize(600, 400);
        menuBar = new QMenuBar(OpenGLES20QTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        OpenGLES20QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenGLES20QTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OpenGLES20QTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(OpenGLES20QTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OpenGLES20QTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OpenGLES20QTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OpenGLES20QTClass->setStatusBar(statusBar);

        retranslateUi(OpenGLES20QTClass);

        QMetaObject::connectSlotsByName(OpenGLES20QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenGLES20QTClass)
    {
        OpenGLES20QTClass->setWindowTitle(QApplication::translate("OpenGLES20QTClass", "OpenGLES20QT", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OpenGLES20QTClass: public Ui_OpenGLES20QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLES20QT_H
