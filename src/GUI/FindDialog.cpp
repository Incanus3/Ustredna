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
	foundList = new QListWidget;
	foundList->setMinimumWidth(400);

	QHBoxLayout* upperLayout = new QHBoxLayout;
	upperLayout->addWidget(findEdit);
	upperLayout->addWidget(findButton);

	QHBoxLayout* middleLayout = new QHBoxLayout;
	middleLayout->addWidget(nameRadio);
	middleLayout->addStretch();
	middleLayout->addWidget(departmentRadio);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(upperLayout);
	//mainLayout->addLayout(middleLayout);
	mainLayout->addWidget(foundList);

	setLayout(mainLayout);

	database = db;

	QObject::connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
}

void FindDialog::findClicked()
{
	foundList->clear();

	if(nameRadio->isChecked())
	{
		QList<PhoneLink>& found = database->findDataFiles(findEdit->text());

		for(int i = 0; i < found.count(); i++)
			foundList->addItem(QString("%1     \t%2 | %3").arg(found[i].name)
							   .arg(found[i].phone1).arg(found[i].cell1));
	}
}
