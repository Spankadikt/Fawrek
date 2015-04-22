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
    }
}

void FawrekEditorWidget::timeOutSlot()
{
}
