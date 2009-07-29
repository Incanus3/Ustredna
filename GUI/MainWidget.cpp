#include <QtGui/QBoxLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QList>
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
		database = new PhoneDatabase("seznam.phd");
		populateList(0, *database->root());
	} catch(InvalidFile) {}

}

void MainWidget::populateList(unsigned short int listNumber,
							  Category<PhoneLink> category)
{
	cout << endl << "zacatek populateList()" << endl;
	cout << "listNumber: " << listNumber << endl;
	cout << "category.name(): " << category.name() << endl;

	QList<Category<PhoneLink> > categories = category.subCategories();
	for(int i = 0; i < categories.size(); i++)
		lists[listNumber].addItem(categories[i].name());

	QList<PhoneLink> files = category.dataFiles();
	for(int i = 0; i < files.size(); i++)
		lists[listNumber].addItem(files[i].name);
}

void MainWidget::showFile(PhoneLink file)
{
	nameEdit->setText(file.name);
	phone1Edit->setText(QString("%1").arg(file.phone1));
	phone2Edit->setText(QString("%1").arg(file.phone2));
	cell1Edit->setText(QString("%1").arg(file.cell1));
	cell2Edit->setText(QString("%1").arg(file.cell2));
}

void MainWidget::selectionChanged()
{
	if(!database)
		return;

	removeConnections();

	// zjistim, ve kterem listu se zmenil vyber
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

	// index nove vybraneho radku
	int changedRow = lists[changedListNumber].currentRow();

	// aktualizuji posledni ulozeny vyber
	lastSelection[changedListNumber] = changedRow;

	// vymazu vsechny listy vpravo od prave zmeneneho
	for(int i = changedListNumber + 1; i < listsNumber; i++)
	{
		lastSelection[i] = -1;
		lists[i].clear();
	}

	// najdu kategorii, ktera je v prave zmenenem listu zobrazena

	Category<PhoneLink>* current = database->root();

	for(int i = 0; i < changedListNumber; i++)
		current = &current->subCategories()[lists[i].currentRow()];

	// extrahuju jeji podkategorie a datove polozky
	QList<Category<PhoneLink> > categories = current->subCategories();
	QList<PhoneLink> files = current->dataFiles();

	// pokud byla vybrana podkategorie
	if(changedRow < categories.count())
		// zobrazim jeji obsah v dalsim listu
		populateList(changedListNumber + 1,
					 current->subCategories()[changedRow]);
	else
		// jinak zobrazim vybranou datovou polozku
		showFile(files[changedRow - categories.size()]);
	initializeConnections();
}

void MainWidget::openDatabase()
{
	QString path =
			QFileDialog::
			getOpenFileName(this,
							tr("Otevřít soubor se seznamem"), ".",
							tr("Phone Database Files (*.phd)"));

	cout << path << endl;

	database = new PhoneDatabase(path);

	for(int i = 0; i < listsNumber; i++)
		lists[i].clear();

	populateList(0, *database->root());
}
