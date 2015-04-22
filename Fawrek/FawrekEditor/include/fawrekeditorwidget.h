#ifndef FAWREKEDITORWIDGET_H
#define FAWREKEDITORWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include "ui_fawrekeditorwidget.h"

class FawrekEditorWidget : public QGLWidget
{
	Q_OBJECT

public:
	FawrekEditorWidget(QWidget *parent = 0);
	FawrekEditorWidget(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
	~FawrekEditorWidget();

    virtual void initializeGL() = 0;
    virtual void resizeGL(int width, int height) = 0;
    virtual void paintGL() = 0;
    virtual void keyPressEvent( QKeyEvent *keyEvent );
	void toggleFullWindow();

public slots:
    virtual void timeOutSlot();

private:
	Ui::FawrekEditorClass ui;
    QTimer *t_Timer;
	bool b_Fullscreen;

};

#endif // FAWREKEDITORWIDGET_H
