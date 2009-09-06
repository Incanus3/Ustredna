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
	openAction->setIcon(QIcon(":/images/fileopen.svg"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Otevřít existující soubor se seznamem"));
	QObject::connect(openAction, SIGNAL(triggered()),
					 mainWidget, SLOT(openDatabase()));

	findAction = new QAction(tr("&Vyhledat položku..."), this);
	findAction->setIcon(QIcon(":/images/search.svg"));
	findAction->setShortcut(QKeySequence::Find);
	findAction->setStatusTip(tr("Vyhledat položku v otevřeném seznamu"));
	QObject::connect(findAction, SIGNAL(triggered()),
					 mainWidget, SLOT(findFile()));

	exportAction = new QAction(tr("&Exportovat seznam..."), this);
	exportAction->setIcon(QIcon(":/images/export.svg"));
	exportAction->setShortcut(QKeySequence("Ctrl+E"));
	exportAction->setStatusTip(tr("Exportovat seznam do HTML"));
	QObject::connect(exportAction, SIGNAL(triggered()),
					 mainWidget, SLOT(exportDatabase()));

	settingsAction = new QAction(tr("&Nastavení..."), this);
	settingsAction->setIcon(QIcon(":/images/settings.svg"));
	settingsAction->setStatusTip(tr("Upravit nastavení programu"));
	QObject::connect(settingsAction, SIGNAL(triggered()),
					 mainWidget, SLOT(editSettings()));

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
	fileMenu->addAction(exportAction);
	editMenu = menuBar()->addMenu(tr("&Upravit"));
	editMenu->addAction(findAction);
	editMenu->addAction(settingsAction);
	helpMenu = menuBar()->addMenu(tr("&Nápověda"));
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
	mainToolBar = addToolBar(tr("&Soubor"));
	mainToolBar->addAction(openAction);
	mainToolBar->addAction(findAction);
	mainToolBar->addAction(exportAction);
	mainToolBar->addAction(settingsAction);
}
