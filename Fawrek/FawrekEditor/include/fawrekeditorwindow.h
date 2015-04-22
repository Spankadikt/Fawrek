#ifndef FAWREKEDITORWINDOW_H
#define FAWREKEDITORWINDOW_H

#include "fawrekeditorwidget.h"

class FawrekEditorWindow : public FawrekEditorWidget
{
    Q_OBJECT
public:
    FawrekEditorWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif // FAWREKEDITORWINDOW_H