#include <QtGui/QApplication>
#include <QTextCodec>
#include "MainWindow.h"
#include "CategoryTree.h"
#include "PhoneLink.h"
#include "Cout.h"

using namespace std;

void pokusy();

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	QApplication a(argc, argv);
	MainWindow* w = new MainWindow;
	w->show();
	return a.exec();
}
