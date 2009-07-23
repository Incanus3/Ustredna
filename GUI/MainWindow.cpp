#include "MainWindow.h"

MainWindow::MainWindow()
{
	mainWidget = new MainWidget();

	setCentralWidget(mainWidget);
	createActions();
	createMenus();
	createToolBars();
}

void MainWindow::createActions()
{
	openAction = new QAction(tr("&Otevřít seznam..."), this);
	openAction->setIcon(QIcon(":/images/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Otevřít existující soubor se seznamem"));
	QObject::connect(openAction, SIGNAL(triggered()),
					 mainWidget, SLOT(openDatabase()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&Soubor"));
	fileMenu->addAction(openAction);
}

void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("&Soubor"));
	fileToolBar->addAction(openAction);
}
