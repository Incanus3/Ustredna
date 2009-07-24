#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "Exceptions.h"
#include "Database.h"
#include "Cout.h" // DEBUG

PhoneDatabase::PhoneDatabase(QString path, QString name)
		throw(InvalidFile)
{
	tree = loadDatabase(path, name);
}

CategoryTree<PhoneLink>* PhoneDatabase::loadDatabase(QString path, QString name)
		throw(InvalidFile)
{
	QFile dataFile(path);
	if(!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
		throw InvalidFile(QString("Can't open file %1").arg(path));

	QTextStream dataStream(&dataFile);
	QString line;
	QStringList splitLine;
	CategoryTree<PhoneLink>* tree = new CategoryTree<PhoneLink>(name);

	while(!dataStream.atEnd())
	{
		line = dataStream.readLine().remove('"');
		splitLine = line.split(",");
		tree->insertDataFile(*(new PhoneLink(splitLine[1],
											 splitLine[2].toUShort(),
											 splitLine[3].toUShort(),
											 splitLine[4].toUShort(),
											 splitLine[5].toUShort())),
							 splitLine[0], true);
	}

	tree->print(); // DEBUG

	return tree;
}
