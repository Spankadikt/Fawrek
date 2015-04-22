#include "fawrekeditorwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	FawrekEditorWindow window;
	window.show();
	return app.exec();
}
