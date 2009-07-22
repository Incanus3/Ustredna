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
	static const short int listsNumber;

	void initializeWidgets();
	void initializeLayouts();

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
