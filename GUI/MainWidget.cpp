#include <QtGui/QBoxLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QDir>
#include "MainWidget.h"
#include "Cout.h"

const short int MainWidget::listMinimumWidth = 160;
const short int MainWidget::listMinimumHeight = 400;
const short int MainWidget::listsNumber = 5;
const short int MainWidget::textEditMinWidth = 180;
const short int MainWidget::numberEditWidth = 40;

void MainWidget::initializeWidgets()
{
	lists = new QListWidget[listsNumber];
	for(int i = 0; i < listsNumber; i++)
	{
		lists[i].setMinimumWidth(listMinimumWidth);
		lists[i].setMinimumHeight(listMinimumHeight);
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

	const short int textEditsCount = 2;
	QLineEdit** textEdits = new QLineEdit*[textEditsCount];
	textEdits[0] = departmentEdit;
	textEdits[1] = nameEdit;

	const short int numberEditsCount = 4;
	QLineEdit** numberEdits = new QLineEdit*[numberEditsCount];
	numberEdits[0] = phone1Edit;
	numberEdits[1] = phone2Edit;
	numberEdits[2] = cell1Edit;
	numberEdits[3] = cell2Edit;

	for(int i = 0; i < textEditsCount; i++)
	{
		textEdits[i]->setMinimumWidth(textEditMinWidth);
		textEdits[i]->setReadOnly(true);
	}

	for(int i = 0; i < numberEditsCount; i++)
	{
		numberEdits[i]->setMinimumWidth(numberEditWidth);
		numberEdits[i]->setMaximumWidth(numberEditWidth);
		numberEdits[i]->setReadOnly(true);
	}
}

void MainWidget::initializeLayouts()
{
	QHBoxLayout* listsLayout = new QHBoxLayout;
	for(int i = 0; i < listsNumber; i++)
		listsLayout->addWidget(&lists[i]);

	QHBoxLayout* dataLayout = new QHBoxLayout;
	dataLayout->addWidget(departmentLabel);
	dataLayout->addWidget(departmentEdit);
	dataLayout->addStretch();

	dataLayout->addWidget(nameLabel);
	dataLayout->addWidget(nameEdit);
	dataLayout->addStretch();

	dataLayout->addWidget(phonesLabel);
	dataLayout->addWidget(phone1Edit);
	dataLayout->addWidget(phone2Edit);
	dataLayout->addStretch();

	dataLayout->addWidget(cellsLabel);
	dataLayout->addWidget(cell1Edit);
	dataLayout->addWidget(cell2Edit);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(listsLayout);
	mainLayout->addLayout(dataLayout);
	setLayout(mainLayout);
}

void MainWidget::initializeConnections()
{
	for(int i = 0; i < listsNumber; i++)
		QObject::connect(&lists[i], SIGNAL(itemSelectionChanged()),
						 this, SLOT(selectionChanged()));
}

void MainWidget::fillLists() // DEBUG
{
	for(int i = 0; i < listsNumber; i++)
		for(int j = 1; j <= i + 1; j++)
			lists[i].addItem(QString(tr("farebná televízia %1")).arg(j));

	departmentEdit->setText(tr("Centrální operační sály"));
	nameEdit->setText(tr("Ševicová, Marta"));
	phone1Edit->setText("123");
	phone2Edit->setText("456");
	cell1Edit->setText("789");
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	initializeWidgets();
	initializeLayouts();
	initializeConnections();
	fillLists(); // DEBUG
}

void MainWidget::selectionChanged()
{
	QMessageBox msgBox;
	msgBox.setText("Selection has changed");
	msgBox.exec();
}

void MainWidget::openDatabase()
{
	QString path =
			QFileDialog::
			getOpenFileName(this,
							tr("Otevřít soubor se seznamem"),
							".",
							tr("Phone Database Files (*.phd)"));

	database = new PhoneDatabase(path);
}
