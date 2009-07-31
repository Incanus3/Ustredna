#include <QApplication>
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

	findAction = new QAction(tr("&Vyhledat položku..."), this);
	findAction->setIcon(QIcon(":/images/find.png"));
	findAction->setShortcut(QKeySequence::Find);
	findAction->setStatusTip(tr("Vyhledat položku v otevřeném seznamu"));
	QObject::connect(findAction, SIGNAL(triggered()),
					 mainWidget, SLOT(findFile()));

	aboutQtAction = new QAction(tr("O toolkitu &Qt"), this);
	aboutQtAction->setIcon(QIcon(":/images/qt.png"));
	aboutQtAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
	QObject::connect(aboutQtAction, SIGNAL(triggered()),
					 qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&Soubor"));
	fileMenu->addAction(openAction);
	editMenu = menuBar()->addMenu(tr("&Upravit"));
	editMenu->addAction(findAction);
	helpMenu = menuBar()->addMenu(tr("&Nápověda"));
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
	mainToolBar = addToolBar(tr("&Soubor"));
	mainToolBar->addAction(openAction);
	mainToolBar->addAction(findAction);
}
