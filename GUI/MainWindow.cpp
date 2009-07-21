#include "MainWindow.h"

MainWindow::MainWindow()
{
	mainWidget = new MainWidget();

	setCentralWidget(mainWidget);
}
