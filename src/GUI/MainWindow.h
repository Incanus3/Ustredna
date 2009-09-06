#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include "MainWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

		public:
	MainWindow();

		private:
	void createActions();
	void createMenus();
	void createToolBars();

	MainWidget* mainWidget;

	QAction* openAction;
	QAction* findAction;
	QAction* settingsAction;
	QAction* aboutQtAction;
	QAction* exportAction;

	QMenu* fileMenu;
	QMenu* editMenu;
	QMenu* helpMenu;

	QToolBar* mainToolBar;
};

#endif // MAINWINDOW_H
