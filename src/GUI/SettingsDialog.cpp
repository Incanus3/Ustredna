#include <QtGui/QBoxLayout>
#include <QtGui/QFileDialog>
#include <QFile>
#include <QTextStream>
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QString path, QWidget* parent) : QDialog(parent)
{
	defaultDataPathLabel = new QLabel(tr("Implicitní cesta k souboru se seznamem:"));
	defaultDataPathEdit = new QLineEdit;
	defaultDataPathEdit->setText(path);
	openButton = new QPushButton(QIcon(":/images/fileopen_small.png"),"");
	openButton->setMaximumHeight(28); // hnusne, treba najdu lepsi reseni
	applyButton = new QPushButton(tr("&Použít"));
	okButton = new QPushButton(tr("OK"));
	okButton->setDefault(true);
	cancelButton = new QPushButton(tr("Strono"));
	cancelButton->setShortcut(QKeySequence("Esc"));

	createLayouts();
	initializeConnections();
}

void SettingsDialog::createLayouts()
{
	QHBoxLayout* midLayout = new QHBoxLayout;
	midLayout->addWidget(defaultDataPathEdit);
	midLayout->addWidget(openButton);

	QHBoxLayout* bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(applyButton);
	bottomLayout->addWidget(okButton);
	bottomLayout->addWidget(cancelButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(defaultDataPathLabel);
	mainLayout->addLayout(midLayout);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
}

void SettingsDialog::initializeConnections()
{
	QObject::connect(openButton, SIGNAL(clicked()),
					 this, SLOT(openFile()));

	QObject::connect(applyButton, SIGNAL(clicked()),
					 this, SLOT(saveSettings()));
	QObject::connect(okButton, SIGNAL(clicked()),
					 applyButton, SIGNAL(clicked()));
	QObject::connect(okButton, SIGNAL(clicked()),
					 cancelButton, SIGNAL(clicked()));
	QObject::connect(cancelButton, SIGNAL(clicked()),
					 this, SLOT(close()));
}

void SettingsDialog::openFile()
{
	defaultDataPathEdit->
			setText(QFileDialog::
					getOpenFileName(this,
							tr("Otevřít souQString pathbor se seznamem"), ".",
							tr("Phone Database Files (*.phd)")));
}

void SettingsDialog::saveSettings()
{
	if(QFile::exists(defaultDataPathEdit->text()))
	{
		QFile configFile(".config");
		configFile.remove();
		configFile.open(QIODevice::WriteOnly | QIODevice::Text);

		QTextStream configStream(&configFile);
		configStream << defaultDataPathEdit->text();

		configFile.close();
	}
}
