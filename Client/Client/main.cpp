#include <QtWidgets/QApplication>
#include <qdockwidget.h>

#include "tests/test_CloseAndMinButton.h"
#include <qwidget.h>
#include <qlabel.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//Widget w;
	//w.setStyleSheet("QPushButton{background-image : url(':/images/ccc.jpg')}");
	//w.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//QDockWidget *dockWidget = new QDockWidget("Dock", &w, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	//dockWidget->setFloating(false);
	//w.addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
	//w.show();

	TestCloseAndMinButton test;
	test.show();

	return a.exec();
}
