#include <QFormLayout>
#include "FileEditDialog.h"

const short int FileEditDialog::textEditMinWidth = 240;
const short int FileEditDialog::numberEditWidth = 40;

FileEditDialog::FileEditDialog(PhoneLink& phoneLink)
{
	editedLink = &phoneLink;

	setWindowTitle(tr("Editace linky"));
	initializeWidgets();
	initializeLayouts();
	initializeConnections();
}

void FileEditDialog::initializeWidgets()
{
	departmentEdit = new QLineEdit;
	departmentEdit->setMinimumWidth(textEditMinWidth);
	nameEdit = new QLineEdit;
	nameEdit->setMinimumWidth(textEditMinWidth);

	phone1Edit = new QLineEdit;
	phone1Edit->setMinimumWidth(numberEditWidth);
	phone1Edit->setMaximumWidth(numberEditWidth);
	phone2Edit = new QLineEdit;
	phone2Edit->setMinimumWidth(numberEditWidth);
	phone2Edit->setMaximumWidth(numberEditWidth);

	cell1Edit = new QLineEdit;
	cell1Edit->setMinimumWidth(numberEditWidth);
	cell1Edit->setMaximumWidth(numberEditWidth);
	cell2Edit = new QLineEdit;
	cell2Edit->setMinimumWidth(numberEditWidth);
	cell2Edit->setMaximumWidth(numberEditWidth);

	departmentEdit->setText(editedLink->department);
	nameEdit->setText(editedLink->name);
	phone1Edit->setText(QString("%1").arg(editedLink->phone1));
	phone2Edit->setText(QString("%1").arg(editedLink->phone2));
	cell1Edit->setText(QString("%1").arg(editedLink->cell1));
	cell2Edit->setText(QString("%1").arg(editedLink->cell2));

	okButton = new QPushButton(tr("OK"));
	okButton->setDefault(true);
	cancelButton = new QPushButton(tr("Storno"));
}

void FileEditDialog::initializeLayouts()
{
	QHBoxLayout* phonesLayout = new QHBoxLayout;
	phonesLayout->addWidget(phone1Edit);
	phonesLayout->addWidget(phone2Edit);
	phonesLayout->addStretch();

	QHBoxLayout* cellsLayout = new QHBoxLayout;
	cellsLayout->addWidget(cell1Edit);
	cellsLayout->addWidget(cell2Edit);
	cellsLayout->addStretch();

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow(tr("Post:"), departmentEdit);
	formLayout->addRow(tr("Jméno:"), nameEdit);
	formLayout->addRow(tr("Linky:"), phonesLayout);
	formLayout->addRow(tr("Ručky:"), cellsLayout);

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(okButton);
	buttonsLayout->addWidget(cancelButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(formLayout);
	mainLayout->addLayout(buttonsLayout);

	setLayout(mainLayout);
}

void FileEditDialog::initializeConnections()
{
	QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
	QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
}

void FileEditDialog::okClicked()
{
	editedLink->department = departmentEdit->text();
	editedLink->name = nameEdit->text();
	editedLink->phone1 = phone1Edit->text().toInt();
	editedLink->phone2 = phone2Edit->text().toInt();
	editedLink->cell1 = cell1Edit->text().toInt();
	editedLink->cell1 = cell1Edit->text().toInt();
	accept();
}

void FileEditDialog::cancelClicked()
{
	reject();
}
