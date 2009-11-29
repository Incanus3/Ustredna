#include <QtGui/QHBoxLayout>
#include <QInputDialog>
#include "PhoneListWindow.h"
#include "FileEditDialog.h"

void PhoneListWindow::addFile()
{
	// zobraz prazdny dialog pro editaci linky
	// dialog linku vrati, uloz ji do db
	fillTable();
}

void PhoneListWindow::editFile(int index)
{
        PhoneLink fileToEdit = db->phoneList()[index];
        FileEditDialog* editDialog = new FileEditDialog(fileToEdit);
        editDialog->exec();

        db->replaceDataFile(db->phoneList()[index], fileToEdit);

        fillTable();
}

void PhoneListWindow::editFile()
{
        editFile(phoneTable->currentRow());
}

void PhoneListWindow::addToTree(int index)
{
    bool ok;
    QString position = QInputDialog::getText(this, tr("Zařazení položky do stromu"),
                                        tr("Zadejte požadovanou pozici ve stromu"),
					QLineEdit::Normal, "1111", &ok);
    // vlozit prvek do stromu
    db->insertDataFile(db->phoneList()[index], toDigitArray(position));
}

void PhoneListWindow::addToTree()
{
    addToTree(phoneTable->currentRow());
}

void PhoneListWindow::deleteFile(int index)
{
	db->removeDataFile(db->phoneList()[index]);
	fillTable();
}

void PhoneListWindow::deleteFile()
{
	deleteFile(phoneTable->currentRow());
}

void PhoneListWindow::createActions()
{
    addAction = new QAction(QIcon(":/images/filenew.svg"),
                            tr("Přidat položku"), this);
    QObject::connect(addAction, SIGNAL(triggered()), this, SLOT(addFile()));

    editAction = new QAction(QIcon(":/images/fileedit.svg"),
                             tr("Editovat položku"), this);
    QObject::connect(editAction, SIGNAL(triggered()), this, SLOT(editFile()));

    addToTreeAction = new QAction(QIcon(":/images/addtotree.svg"),
                                  tr("Umístit do stromu..."), this);
    QObject::connect(addToTreeAction, SIGNAL(triggered()), this, SLOT(addToTree()));

    delAction = new QAction(QIcon(":/images/filedel.svg"),
                            tr("Odstranit položku"), this);
    QObject::connect(delAction, SIGNAL(triggered()), this, SLOT(deleteFile()));
}

void PhoneListWindow::createMenus()
{
	listMenu = menuBar()->addMenu(tr("&Seznam"));
	listMenu->addAction(addAction);
	listMenu->addAction(editAction);
        listMenu->addAction(addToTreeAction);
	listMenu->addAction(delAction);
}

void PhoneListWindow::createToolBars()
{
	listToolbar = addToolBar(tr("&Seznam"));
	listToolbar->addAction(addAction);
	listToolbar->addAction(editAction);
        listToolbar->addAction(addToTreeAction);
	listToolbar->addAction(delAction);
}

PhoneListWindow::PhoneListWindow(PhoneDatabase* database, QWidget* parent) :
		QMainWindow(parent), db(database)
{
	setWindowTitle(tr("Seznam linek"));

	phoneTable = new QTableWidget(this);
	phoneTable->setColumnCount(6);
	phoneTable->setMinimumHeight(500);

	QStringList headers;
	headers << tr("Post")
			<< tr("Jméno")
			<< tr("Linka1")
			<< tr("Linka2")
			<< tr("Ručka1")
			<< tr("Ručka2");

	phoneTable->setHorizontalHeaderLabels(headers);
	// zaruci needitovatelnost bunek
	phoneTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	fillTable();

	setCentralWidget(phoneTable);

#ifdef ADMIN
	createActions();
	createMenus();
	createToolBars();
#endif // ADMIN
}

void PhoneListWindow::clearTable()
{
	phoneTable->clearContents();
	phoneTable->setRowCount(0);
}

void PhoneListWindow::fillTable()
{
	clearTable();

	PhoneLink* currentLink;
	for (int i = 0; i < db->phoneList().size(); i++)
	{
		currentLink = &db->phoneList()[i];
		phoneTable->insertRow(i);
		phoneTable->setItem(i, 0, new QTableWidgetItem(currentLink->department));
		phoneTable->setItem(i, 1, new QTableWidgetItem(currentLink->name));
		phoneTable->setItem(i, 2, new QTableWidgetItem(
				QString("%1").arg(currentLink->phone1)));
		phoneTable->setItem(i, 3, new QTableWidgetItem(
				QString("%1").arg(currentLink->phone2)));
		phoneTable->setItem(i, 4, new QTableWidgetItem(
				QString("%1").arg(currentLink->cell1)));
		phoneTable->setItem(i, 5, new QTableWidgetItem(
				QString("%1").arg(currentLink->cell2)));
	}

	phoneTable->resizeColumnsToContents();
	for(int i = 2; i < 6; i++)
		phoneTable->setColumnWidth(i, 60);
	int width = 0;
	for (int i = 0; i < 6; i++)
	{
		width += phoneTable->columnWidth(i);
	}
	phoneTable->setMinimumWidth(width + 50);
}

// bere v QStringu ulozene cislo, vraci pole jeho cifer, SNIZENYCH O 1,
// ve vstupnim stringu se nesmi vyskytovat nenumerice znaky ani 0
QVector<unsigned short int> PhoneListWindow::toDigitArray(QString number)
	throw(InvalidArgument)
{
    QVector<unsigned short int>* vector = new QVector<unsigned short int>;
    for(unsigned short int i = 0, digit; i < number.length(); i++)
    {
	digit = number[i].digitValue();
	if(digit < 1) throw InvalidArgument(
		QString("%1 is not valid directory index").arg(digit));
	vector->append(digit - 1);
    }
    return *vector;
}
