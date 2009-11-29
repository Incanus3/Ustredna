#ifndef PHONELISTDIALOG_H
#define PHONELISTDIALOG_H

#include <QVector>
#include <QtGui/QMainWindow>
#include <QtGui/QTableWidget>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include "Exceptions.h"
#include "Database.h"

class PhoneListWindow : public QMainWindow
{
	Q_OBJECT

		public:
	PhoneListWindow(PhoneDatabase* database, QWidget* parent = 0);

		private slots:
	void fillTable();
	void addFile();
	void editFile(int index);
	void editFile();
        void addToTree(int index);
        void addToTree();
	void deleteFile(int index);
	void deleteFile();

		private:
	void createActions();
	void createMenus();
	void createToolBars();
	void clearTable();

	QVector<unsigned short int> toDigitArray(QString number)
		throw(InvalidArgument);

	QTableWidget* phoneTable;

	QMenu* listMenu;
	QToolBar* listToolbar;

	QAction* addAction;
	QAction* editAction;
        QAction* addToTreeAction;
	QAction* delAction;

	PhoneDatabase* db;
};


#endif // PHONELISTDIALOG_H
