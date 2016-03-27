#include <QtWidgets/QApplication>
#include <qfile.h>
#include <qstring.h>

#include "../include/LoginUI.h"

#include <qwidget.h>
#include <qlineedit.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//LoginUI loginUI;
	QWidget loginUI;
	QLineEdit line(&loginUI);

	QFile file(":/styles/style.css");
	file.open(QFile::ReadOnly);
	QString styleSheet = QObject::tr(file.readAll());
	loginUI.setStyleSheet(styleSheet);

	loginUI.show();

	return a.exec();
}
