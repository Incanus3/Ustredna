#include "MainWidget.h"
#include <QtGui/QBoxLayout>
#include <QTextCodec>

const short int MainWidget::listsNumber = 5;

void MainWidget::initializeWidgets()
{
	lists = new QListWidget[listsNumber];
	for(int i = 0; i < listsNumber; i++)
	{
		lists[i].setMinimumWidth(160);
		lists[i].setMinimumHeight(400);
	}

	departmentLabel = new QLabel(tr("Oddělení:"));
	nameLabel = new QLabel(tr("Jméno:"));
	phonesLabel = new QLabel(tr("Linky:"));
	cellsLabel = new QLabel(tr("Ručky:"));

	departmentEdit = new QLineEdit;
	nameEdit = new QLineEdit;
	phone1Edit = new QLineEdit;
	phone2Edit = new QLineEdit;
	cell1Edit = new QLineEdit;
	cell2Edit = new QLineEdit;
}

void MainWidget::initializeLayouts()
{
	QHBoxLayout* listsLayout = new QHBoxLayout;
	for(int i = 0; i < listsNumber; i++)
		listsLayout->addWidget(&lists[i]);

	QHBoxLayout* dataLayout = new QHBoxLayout;
	dataLayout->addWidget(departmentLabel);
	dataLayout->addWidget(departmentEdit);
	dataLayout->addWidget(nameLabel);
	dataLayout->addWidget(nameEdit);
	dataLayout->addWidget(phonesLabel);
	dataLayout->addWidget(phone1Edit);
	dataLayout->addWidget(phone2Edit);
	dataLayout->addWidget(cellsLabel);
	dataLayout->addWidget(cell1Edit);
	dataLayout->addWidget(cell2Edit);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(listsLayout);
	mainLayout->addLayout(dataLayout);
	setLayout(mainLayout);
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	initializeWidgets();
	initializeLayouts();
}
