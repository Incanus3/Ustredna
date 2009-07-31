#include "FindDialog.h"
#include <QtGui/QBoxLayout>

FindDialog::FindDialog(QWidget* parent) : QDialog(parent)
{
	findEdit = new QLineEdit;
	findButton = new QPushButton(tr("&Hledat"));
	foundList = new QListWidget;
	foundList->setMinimumWidth(200);

	QHBoxLayout* upperLayout = new QHBoxLayout;
	upperLayout->addWidget(findEdit);
	upperLayout->addWidget(findButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(upperLayout);
	mainLayout->addWidget(foundList);

	setLayout(mainLayout);
}

void FindDialog::findClicked()
{

}
