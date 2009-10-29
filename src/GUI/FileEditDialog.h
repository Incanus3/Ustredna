#ifndef FILEEDITDIALOG_H
#define FILEEDITDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "PhoneLink.h"

class FileEditDialog : public QDialog
{
	Q_OBJECT

public:
	FileEditDialog(PhoneLink& phoneLink);

private slots:
	void okClicked();
	void cancelClicked();

private:
	void initializeWidgets();
	void initializeLayouts();
	void initializeConnections();

	static const short int numberEditWidth;
	static const short int textEditMinWidth;

	QLineEdit* departmentEdit;
	QLineEdit* nameEdit;
	QLineEdit* phone1Edit;
	QLineEdit* phone2Edit;
	QLineEdit* cell1Edit;
	QLineEdit* cell2Edit;

	QPushButton* okButton;
	QPushButton* cancelButton;

	PhoneLink* editedLink;
};

#endif // FILEEDITDIALOG_H
