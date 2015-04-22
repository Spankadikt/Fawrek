#include "fawrekeditorwidget.h"

FawrekEditorWidget::FawrekEditorWidget(QWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
}

FawrekEditorWidget::FawrekEditorWidget(int framesPerSecond, QWidget *parent, char *name)
	: QGLWidget(parent)
{
	setWindowTitle(QString::fromUtf8(name));
	if(framesPerSecond == 0)
		t_Timer = NULL;
	else
	{
		int seconde = 1000; // 1 seconde = 1000 ms
		int timerInterval = seconde / framesPerSecond;
		t_Timer = new QTimer(this);
		connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
		t_Timer->start( timerInterval );
	}
	b_Fullscreen = false;
}


FawrekEditorWidget::~FawrekEditorWidget()
{

}

void FawrekEditorWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
		case Qt::Key_F1:
            toggleFullWindow();
            break;
    }
}

void FawrekEditorWidget::timeOutSlot()
{
	updateGL();
}

void FawrekEditorWidget::toggleFullWindow()
{
    if(b_Fullscreen)
    {
        showNormal();
        b_Fullscreen = false;
    }
    else
    {
        showFullScreen();
        b_Fullscreen = true;
    }
}
