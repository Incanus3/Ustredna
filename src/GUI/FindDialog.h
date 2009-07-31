#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QListWidget>

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
	QListWidget* foundList;
};

#endif // FINDDIALOG_H
