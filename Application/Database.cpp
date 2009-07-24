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
	int lineNumber = 0;

	while(!dataStream.atEnd())
	{
		lineNumber++;
		line = dataStream.readLine();
		splitLine = QString(line).remove('"').split(",");
		if(splitLine.size() != 6)
			throw(InvalidFile(QString("Invalid line %1: %2 in file %3")
							  .arg(lineNumber).arg(line).arg(path)));
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
