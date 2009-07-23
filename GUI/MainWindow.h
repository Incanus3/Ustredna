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

	QMenu* fileMenu;

	QToolBar* fileToolBar;
};

#endif // MAINWINDOW_H
