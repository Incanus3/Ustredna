#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "MainWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

		public:
	MainWindow(QWidget* parent = 0);

		private:
	MainWidget* mainWidget;
};

#endif // MAINWINDOW_H
