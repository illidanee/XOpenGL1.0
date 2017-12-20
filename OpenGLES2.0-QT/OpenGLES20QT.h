#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLES20QT.h"

#include <QTimer>
#include "XGLESContent.h"

class OpenGLES20QT : public QMainWindow
{
	Q_OBJECT

public:
	OpenGLES20QT(QWidget *parent = Q_NULLPTR);
	~OpenGLES20QT();

private:
	Ui::OpenGLES20QTClass ui;

private:
	Smile::XGLESContent _GLESContent;

private:
	QTimer _timer;
private slots:
	void Render();
};
