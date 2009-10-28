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

	saveAction = new QAction(QIcon(":/images/filesave.svg"),
							 tr("&Uložit seznam"), this);
	saveAction->setShortcut(QKeySequence::Save);
	QObject::connect(saveAction, SIGNAL(triggered()),
					 mainWidget, SLOT(saveDatabase()));

	saveAsAction = new QAction(QIcon(":/images/filesaveas.svg"),
							   tr("&Uložit seznam jako..."), this);
	saveAsAction->setShortcut(QKeySequence::SaveAs);
	QObject::connect(saveAsAction, SIGNAL(triggered()),
					 mainWidget, SLOT(saveDatabaseAs()));

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

	viewPhoneListAction = new QAction(tr("&Zobrazit seznam linek..."), this);
	viewPhoneListAction->setIcon(QIcon(":/images/spreadsheet.svg"));
	QObject::connect(viewPhoneListAction, SIGNAL(triggered()),
					 mainWidget, SLOT(viewPhoneList()));

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
#ifdef ADMIN
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
#endif // ADMIN
	fileMenu->addAction(exportAction);
	editMenu = menuBar()->addMenu(tr("&Upravit"));
	editMenu->addAction(findAction);
	editMenu->addAction(settingsAction);
	viewMenu = menuBar()->addMenu(tr("&Zobrazit"));
	viewMenu->addAction(viewPhoneListAction);
	helpMenu = menuBar()->addMenu(tr("&Nápověda"));
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
	mainToolBar = addToolBar(tr("&Soubor"));
	mainToolBar->addAction(openAction);
#ifdef ADMIN
	mainToolBar->addAction(saveAction);
	mainToolBar->addAction(saveAsAction);
#endif // ADMIN
	mainToolBar->addAction(findAction);
	mainToolBar->addAction(exportAction);
	mainToolBar->addAction(settingsAction);
}
