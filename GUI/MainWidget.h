#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class MainWidget : public QWidget
{
	Q_OBJECT

		public:
	MainWidget(QWidget* parent = 0);

		private:
	static const short int listMinimumWidth;
	static const short int listMinimumHeight;
	static const short int listsNumber;
	static const short int numberEditWidth;
	static const short int textEditMinWidth;

	void initializeWidgets();
	void initializeLayouts();
	void fillLists();

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

};

#endif // MAINWIDGET_H
