#include <QtGui/QBoxLayout>
#include <QtGui/QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QtGui/QMessageBox>
#include <QList>
#include <QStringList>
#include "MainWidget.h"
#include "SettingsDialog.h"
#include "PhoneListWindow.h"
//#include "Cout.h"

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

	departmentLabel = new QLabel(tr("Post:"));
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
	dataLayout->addSpacing(10);

	dataLayout->addWidget(nameLabel);
	dataLayout->addWidget(nameEdit);
	dataLayout->addSpacing(10);

	dataLayout->addWidget(phonesLabel);
	dataLayout->addWidget(phone1Edit);
	dataLayout->addWidget(phone2Edit);
	dataLayout->addSpacing(10);

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

void MainWidget::resetLists()
{
	removeConnections();

	for(int i = 0; i < listsNumber; i++)
		lists[i].clear();

	initializeConnections();
	selectionChanged();
}

void MainWidget::clearTextBoxes()
{
	departmentEdit->clear();
	nameEdit->clear();
	phone1Edit->clear();
	phone2Edit->clear();
	cell1Edit->clear();
	cell2Edit->clear();
}

void MainWidget::loadConfig() throw(InvalidFile)
{
	QFile configFile(".config");
	if(!configFile.exists())
		throw InvalidFile("Can't open configuration file");
	configFile.open(QIODevice::ReadOnly | QIODevice::Text);

	QTextStream configStream(&configFile);
	databasePath = configStream.readLine();

	configFile.close();
}

void MainWidget::removeConnections()
{
	for(int i = 0; i < listsNumber; i++)
		QObject::disconnect(&lists[i], SIGNAL(itemSelectionChanged()),
						 this, SLOT(selectionChanged()));
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	lastSelection = new int[listsNumber];
	lastSelection[0] = 0;
	for(int i = 1; i < listsNumber; i++)
		lastSelection[i] = -1;

	initializeWidgets();
	initializeLayouts();
	initializeConnections();

	try {
		loadConfig();
	} catch(InvalidFile) { databasePath = "seznam.phd"; }

	try {
		database = new PhoneDatabase(databasePath);
		populateList(0, *database->root());
	} catch(InvalidFile) { database = NULL; }
}


void MainWidget::populateList(unsigned short int listNumber,
							  Category<PhoneLink> category)
{
	QList<Category<PhoneLink> > categories = category.subCategories();
	QList<PhoneLink> files = category.dataFiles();
	if(categories.count() == 0 && files.count() == 1)
	{
		showFile(files[0]);
//		return;
	}

	short int counter = 1;

	for(int i = 0; i < categories.size(); i++)
		lists[listNumber].addItem(QString("%1: %2").arg(counter++)
								  .arg(categories[i].name()));
	for(int i = 0; i < files.size(); i++)
		lists[listNumber].addItem(QString(tr("%1: %2")).arg(counter++)
								  .arg(files[i].department));
}

void MainWidget::showFile(PhoneLink file)
{
	departmentEdit->setText(file.department);
	nameEdit->setText(file.name);
	phone1Edit->setText(QString("%1").arg(file.phone1));
	phone2Edit->setText(QString("%1").arg(file.phone2));
	cell1Edit->setText(QString("%1").arg(file.cell1));
	cell2Edit->setText(QString("%1").arg(file.cell2));
}

unsigned short MainWidget::getChangedListNumber()
{
	unsigned short changedListNumber;
	for(changedListNumber = 0; changedListNumber < listsNumber;
		changedListNumber++)
	{
		if(lists[changedListNumber].currentRow() == -1 ||
		   lastSelection[changedListNumber] !=
		   lists[changedListNumber].currentRow())
			break;
	}

	if(lists[changedListNumber].currentRow() == -1)
		changedListNumber--;

	return changedListNumber;
}

void MainWidget::selectionChanged()
{
	if(!database)
		return;

	// zajistim, aby volani metody clean na listy v tele teto metody
	// nevolalo opet tuto obsluhu
	removeConnections();

	// zjistim, ve kterem listu se zmenil vyber
	unsigned short changedListNumber = getChangedListNumber();

	// ulozim si indexy vybranych radku a pritom listy vymazu
	int selection[listsNumber];
	for(int i = 0; i < listsNumber; i++)
	{
		selection[i] = lists[i].currentRow();
		lists[i].clear();
	}

	{
		// prochazim listy zleva
		// pritom prochazim hierarchii linek
		Category<PhoneLink>& current = *database->root();
		populateList(0, current);
		lists[0].setCurrentRow(selection[0]);
		int i = 0;
		while(selection[i] != -1 && i != changedListNumber + 1)
		{
			lists[i].setCurrentRow(selection[i]);
			// pokud jsem vybral kategorii
			if(selection[i] < current.subCategories().count())
			{
				// vlezu do podkatetegorie
				current = current.subCategories()[selection[i]];
				// zobrazim ji v listu o 1 vedle
				populateList(i + 1, current);
				// a pokracuju o list doprava
				i++;
			}
			// pokud jsem vybral linku
			else
			{
				// zobrazim ji
				showFile(current.dataFiles()[selection[i]
											 - current.subCategories().count()]);
				// a prochazeni ukoncim
				break;
			}
		}
	}

	// aktualizuju lastSelection
	for(int i = 0; i < listsNumber; i++)
		lastSelection[i] = selection[i];

	initializeConnections();
}

void MainWidget::openDatabase()
{
	removeConnections();

	QString path =
			QFileDialog::
			getOpenFileName(this,
							tr("Otevřít soubor se seznamem"), ".",
							tr("Phone Database Files (*.phd)"));

	if(path == "")
		return;

	PhoneDatabase* dbPtr = database;

	try{
		database = new PhoneDatabase(path);
	} catch(InvalidFile) {
		database = dbPtr;
		return;
	}

	databasePath = path;

	if(dbPtr)
		delete dbPtr;

	resetLists();
	clearTextBoxes();

	// resetLists() po vycisteni listu vola selectionChanged(), ta vyplni
	// prvni list a zavola initializeConnections(), neni tedy treba volat
	//initializeConnections();
}

void MainWidget::saveDatabase()
{
	database->saveDatabase(databasePath);
}

void MainWidget::saveDatabaseAs()
{
	QString path =
			QFileDialog::
			getOpenFileName(this,
							tr("Uložit soubor se seznamem"), ".",
							tr("Phone Database Files (*.phd)"));

	database->saveDatabase(path);
}

void MainWidget::findFile()
{
	if(database)
	{
		FindDialog findDialog(database);

		findDialog.exec();
	}
	else
		QMessageBox::warning(this, "Nekritická chyba",
							 "Nebyla načtena databáze, \n"
							 "není tedy v čem vyhledávat");
}

void MainWidget::editSettings()
{
	SettingsDialog settingsDialog(databasePath);

	settingsDialog.exec();
}

void MainWidget::exportDatabase()
{
	if(database)
	{
		QString path =
			QFileDialog::
			getSaveFileName(this,
							tr("Exportovat seznam do HTML"), ".",
							tr("HTML soubor (*.html)"));

		database->printToHTML(path);
	}
}

void MainWidget::viewPhoneList()
{
	if(database)
	{
		PhoneListWindow* phoneListWindow = new PhoneListWindow(database);
		phoneListWindow->setWindowModality(Qt::ApplicationModal);
		phoneListWindow->show();
		resetLists();
	}
	else
		QMessageBox::warning(this, "Nekritická chyba",
							 "Nebyla načtena databáze,\n"
							 "nemohu tedy zobrazit seznam linek");
}
