#include "MainWidget.h"

#include <QtGui/QHBoxLayout>

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	lists = new QListWidget[6];
	QHBoxLayout* mainLayout = new QHBoxLayout;
	for(int i = 0; i < 6; i++)
		mainLayout->addWidget(&lists[i]);
	setLayout(mainLayout);
}
