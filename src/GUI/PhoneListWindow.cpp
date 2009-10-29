#include <QtGui/QHBoxLayout>
#include "PhoneListWindow.h"
#include "FileEditDialog.h"

void PhoneListWindow::addFile()
{
	// zobraz prazdny dialog pro editaci linky
	// dialog linku vrati, uloz ji do db
	fillTable();
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

void PhoneListWindow::createActions()
{
	addAction = new QAction(QIcon(":/images/filenew.svg"),
							tr("Přidat položku"), this);
	QObject::connect(addAction, SIGNAL(triggered()), this, SLOT(addFile()));

	editAction = new QAction(QIcon(":/images/fileedit.svg"),
							 tr("Editovat položku"), this);
	QObject::connect(editAction, SIGNAL(triggered()), this, SLOT(editFile()));

	delAction = new QAction(QIcon(":/images/filedel.svg"),
							tr("Odstranit položku"), this);
	QObject::connect(delAction, SIGNAL(triggered()), this, SLOT(deleteFile()));
}

void PhoneListWindow::createMenus()
{
	listMenu = menuBar()->addMenu(tr("&Seznam"));
	listMenu->addAction(addAction);
	listMenu->addAction(editAction);
	listMenu->addAction(delAction);
}

void PhoneListWindow::createToolBars()
{
	listToolbar = addToolBar(tr("&Seznam"));
	listToolbar->addAction(addAction);
	listToolbar->addAction(editAction);
	listToolbar->addAction(delAction);
}

PhoneListWindow::PhoneListWindow(PhoneDatabase* database, QWidget* parent) :
		QMainWindow(parent), db(database)
{
	setWindowTitle(tr("Seznam linek"));

	phoneTable = new QTableWidget(this);
	phoneTable->setColumnCount(6);
	phoneTable->setMinimumHeight(500);
	// zaruci needitovatelnost bunek
	phoneTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	fillTable();

	QStringList headers;
	headers.append(QString(tr("Oddělení")));
	headers.append(QString(tr("Jméno")));
	headers.append(QString(tr("Linka1")));
	headers.append(QString(tr("Linka2")));
	headers.append(QString(tr("Ručka1")));
	headers.append(QString(tr("Ručka2")));
	phoneTable->setHorizontalHeaderLabels(headers);

	setCentralWidget(phoneTable);

#ifdef ADMIN
	createActions();
	createMenus();
	createToolBars();
#endif // ADMIN
}

void PhoneListWindow::fillTable()
{
	phoneTable->clear();
	phoneTable->setRowCount(0);

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
