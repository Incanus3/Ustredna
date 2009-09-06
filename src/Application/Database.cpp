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

void PhoneDatabase::toHTML(PhoneCategory& cat, QTextStream& htmlStream,
						   short int depth)
{
	if(depth)
		htmlStream << QString("<h%1>%2</h%1>\n").arg(depth).arg(cat.name());
	QList<PhoneLink>& dataFiles = cat.dataFiles();
	if(dataFiles.size())
	{
		htmlStream << "<table border=\"1\">\n";
		for(int i = 0; i < dataFiles.size(); i++)
			dataFiles[i].toHTML(htmlStream);
		htmlStream << "</table>\n";
	}

	QList<PhoneCategory>& subCats = cat.subCategories();
	for(int i = 0; i < subCats.size(); i++)
		toHTML(subCats[i], htmlStream, depth + 1);
}

void PhoneDatabase::printToHTML(QString path)
{
	QFile outFile(path);
	outFile.remove();
	outFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream outStream(&outFile);
	outStream.setCodec("UTF-8");

	outStream << QString("<html>\n<head>\n"
			"<meta http-equiv=\"Content-Language\" content=\"cs\">\n"
			"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n"
			"<title>Telefonní seznam Městské nemocnice v Litoměřicích</title>\n"
			"</head>\n"
			"<body>\n"
			"<h1>Telefonní seznam Městské nemocnice v Litoměřicích</h1>\n");

	toHTML(*root(), outStream);

	outStream << "</body>\n</html>";
}
