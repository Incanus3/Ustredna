#include "MainWindow.h"
#include <QtGui/QHBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	mainWidget = new MainWidget();

	setCentralWidget(mainWidget);
}
