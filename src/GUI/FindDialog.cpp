#include "FindDialog.h"
#include <QtGui/QBoxLayout>

FindDialog::FindDialog(PhoneDatabase* db, QWidget* parent) : QDialog(parent)
{
	setWindowTitle(tr("Vyhledat"));

	findEdit = new QLineEdit;
	findButton = new QPushButton(tr("&Hledat"));
	findButton->setDefault(true);
	nameRadio = new QRadioButton(tr("podle jména"));
	nameRadio->setChecked(true);
	departmentRadio = new QRadioButton(tr("podle postu"));
	foundList = new QTableWidget;
	foundList->setMinimumWidth(750);
	foundList->setColumnCount(4);

	QStringList headers;
	headers << tr("Post")
			<< tr("Jméno")
			<< tr("Linka")
			<< tr("Ručka");

	foundList->setHorizontalHeaderLabels(headers);

	QHBoxLayout* upperLayout = new QHBoxLayout;
	upperLayout->addWidget(findEdit);
	upperLayout->addWidget(findButton);

	QHBoxLayout* middleLayout = new QHBoxLayout;
	middleLayout->addWidget(nameRadio);
	middleLayout->addStretch();
	middleLayout->addWidget(departmentRadio);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(upperLayout);
	mainLayout->addLayout(middleLayout);
	mainLayout->addWidget(foundList);

	setLayout(mainLayout);

	database = db;

	QObject::connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
}

void FindDialog::findClicked()
{
	foundList->clearContents();
	QList<PhoneLink>& found = *(new QList<PhoneLink>());

	if(nameRadio->isChecked())
	{
		 found = database->findDataFiles(PhoneLink("", findEdit->text()));
	}
	else
	{
		found = database->findDataFiles(findEdit->text());
	}

	foundList->setRowCount(found.count());
	for(int i = 0; i < found.count(); i++)
	{
		foundList->setItem(i, 0, new QTableWidgetItem(found[i].department));
		foundList->setItem(i, 1, new QTableWidgetItem(found[i].name));
		foundList->setItem(i, 2, new QTableWidgetItem(QString("%1").arg(found[i].phone1)));
		foundList->setItem(i, 3, new QTableWidgetItem(QString("%1").arg(found[i].cell1)));
	}
	foundList->resizeColumnsToContents();
}
