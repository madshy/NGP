#include <QtWidgets/QApplication>

#include "../include/LoginUI.h"
#include "../include/RegisterUI.h"

#include <qlistwidget.h>
//test
#include <qtextedit.h>
#include <qtextdocument.h>
#include <qtextcursor.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//LoginUI loginUI;
	//loginUI.show();

	//RegisterUI *regUI = new RegisterUI;
	//regUI->show();

	QTextEdit *textEdit = new QTextEdit;
	QTextDocument *doc = new QTextDocument("image");
	//doc->addResource(QTextDocument::ResourceType::ImageResource, QUrl(":/images/bg.png"), QVariant("image"));

	QTextCursor *cursor = new QTextCursor(doc);
	cursor->insertImage(QImage(":/images/bg.png"), QString("isdfsdfsd"));

	textEdit->setDocument(doc);
	//textEdit->show();
	return a.exec();
}
