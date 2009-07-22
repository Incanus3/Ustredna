#include "MainWidget.h"
#include <QtGui/QBoxLayout>

const short int MainWidget::listsNumber = 5;

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	lists = new QListWidget[listsNumber];
	QHBoxLayout* listsLayout = new QHBoxLayout;
	for(int i = 0; i < listsNumber; i++)
	{
		lists[i].setMinimumWidth(160);
		lists[i].setMinimumHeight(400);
		listsLayout->addWidget(&lists[i]);
	}

	departmentLabel = new QLabel(tr("Oddělení:"));
	nameLabel = new QLabel(tr("Jméno:"));
	phonesLabel = new QLabel(tr("Linka:"));
	cellsLabel = new QLabel(tr("Ručka:"));

	departmentEdit = new QLineEdit;
	nameEdit = new QLineEdit;
	phone1Edit = new QLineEdit;
	phone2Edit = new QLineEdit;
	cell1Edit = new QLineEdit;
	cell2Edit = new QLineEdit;

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
