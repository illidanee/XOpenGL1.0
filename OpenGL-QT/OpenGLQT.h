#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLQT.h"

#include <QTimer>

#include "XGLContent.h"

class OpenGLQT : public QMainWindow
{
	Q_OBJECT

public:
	OpenGLQT(QWidget *parent = Q_NULLPTR);
	~OpenGLQT();

private:
	Ui::OpenGLQTClass ui;

private:
	QTimer _Timer;
private slots:
	void Render();

private:
	Smile::XGLContent _GLContent;
};
