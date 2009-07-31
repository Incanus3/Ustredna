#include "FindDialog.h"
#include <QtGui/QBoxLayout>

FindDialog::FindDialog(QWidget* parent) : QDialog(parent)
{
	setWindowTitle(tr("Vyhledat"));

	findEdit = new QLineEdit;
	findButton = new QPushButton(tr("&Hledat"));
	nameRadio = new QRadioButton(tr("podle jména"));
	nameRadio->setChecked(true);
	departmentRadio = new QRadioButton(tr("podle postu"));
	foundList = new QListWidget;
	foundList->setMinimumWidth(200);

	QHBoxLayout* upperLayout = new QHBoxLayout;
	upperLayout->addWidget(findEdit);
	upperLayout->addWidget(findButton);

	QHBoxLayout* middleLayout = new QHBoxLayout;
	middleLayout->addWidget(nameRadio);
	middleLayout->addWidget(departmentRadio);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(upperLayout);
	mainLayout->addLayout(middleLayout);
	mainLayout->addWidget(foundList);

	setLayout(mainLayout);
}

void FindDialog::findClicked()
{

}
