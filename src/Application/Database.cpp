#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "Exceptions.h"
#include "Database.h"

PhoneDatabase::PhoneDatabase(QString path, QString name)
		throw(InvalidFile) : CategoryTree<PhoneLink>(name)
{
	loadDatabase(path);
}

void PhoneDatabase::loadDatabase(QString path)
		throw(InvalidFile)
{
	QFile dataFile(path);
	if(!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
		throw InvalidFile(QString("Can't open file %1").arg(path));

	QTextStream dataStream(&dataFile);
	QString line;
	QStringList splitLine;
	int lineNumber = 0;

	clear();

	while(!dataStream.atEnd())
	{
		lineNumber++;
		line = dataStream.readLine();
		splitLine = QString(line).remove('"').split(",");
		if(splitLine.size() != 6)
			throw(InvalidFile(QString("Invalid line %1: %2 in file %3")
							  .arg(lineNumber).arg(line).arg(path)));
		insertDataFile(*(new PhoneLink(splitLine[1],
									   splitLine[2].toUShort(),
									   splitLine[3].toUShort(),
									   splitLine[4].toUShort(),
									   splitLine[5].toUShort())),
					   splitLine[0], true);
	}
}

QList<PhoneLink>& PhoneDatabase::
		findDataFiles(QString namePart,
					  Category<PhoneLink>& startCategory)
{
	QList<PhoneLink>* list = new QList<PhoneLink>;
	QList<Category<PhoneLink> >& subCats = startCategory.subCategories();
	QList<PhoneLink>& dtFiles = startCategory.dataFiles();

	for(int i = 0; i < subCats.count(); i++)
		list->append(findDataFiles(namePart, subCats[i]));

	for(int i = 0; i < dtFiles.count(); i++)
		if(dtFiles[i].name.contains(namePart, Qt::CaseInsensitive))
			list->append(dtFiles[i]);

	return *list;
}

QList<PhoneLink>& PhoneDatabase::
		findDataFiles(QString namePart)
{
	return findDataFiles(namePart, *root());
}
