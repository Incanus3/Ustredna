#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QListWidget>
#include <QtGui/QRadioButton>

class FindDialog : public QDialog
{
	Q_OBJECT

		public:
	FindDialog(QWidget* parent = 0);

		private slots:
	void findClicked();

		private:
	QLineEdit* findEdit;
	QPushButton* findButton;
	QRadioButton* nameRadio;
	QRadioButton* departmentRadio;
	QListWidget* foundList;
};

#endif // FINDDIALOG_H
