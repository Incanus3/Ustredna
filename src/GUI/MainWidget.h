#ifndef MAINWIDGET_H
#define MAINWIDGET_H

//#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QAction>
#include "Database.h"
#include "FindDialog.h"
#include "Exceptions.h"

class MainWidget : public QWidget
{
	Q_OBJECT

		public:
	MainWidget(QWidget* parent = 0);

		public slots:
	void openDatabase();
	void findFile();
	void editSettings();
	void exportDatabase();
	void viewPhoneList();

		private slots:
	void selectionChanged();

		private:
	static const short int listMinimumWidth;
	static const short int listMinimumHeight;
	static const short int listsNumber;
	static const short int numberEditWidth;
	static const short int textEditMinWidth;
	QString databasePath;

	void initializeWidgets();
	void initializeLayouts();
	void initializeConnections();

	void removeConnections();

	void loadConfig() throw (InvalidFile);

	void populateList(unsigned short int listNumber,
					  Category<PhoneLink> category);
	void showFile(PhoneLink file);

	QListWidget* lists;

	QLabel* departmentLabel;
	QLabel* nameLabel;
	QLabel* phonesLabel;
	QLabel* cellsLabel;

	QLineEdit* departmentEdit;
	QLineEdit* nameEdit;
	QLineEdit* phone1Edit;
	QLineEdit* phone2Edit;
	QLineEdit* cell1Edit;
	QLineEdit* cell2Edit;

	PhoneDatabase* database;

	int* lastSelection;

};

#endif // MAINWIDGET_H
