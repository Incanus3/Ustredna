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

const QString PhoneDatabase::separator = ";";

QList<PhoneLink>& PhoneDatabase::phoneList() const
{
	QList<PhoneLink>* phoneListCopy = new QList<PhoneLink>(_phoneList);
	return *phoneListCopy;
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
		splitLine = QString(line).remove('"').split(separator);
		if(splitLine.size() < 7)
			throw(InvalidFile(QString("Invalid line %1: %2 in file %3")
							  .arg(lineNumber).arg(line).arg(path)));
                PhoneLink* newLink = new PhoneLink(splitLine[1],
                                                   splitLine[2],
                                                   splitLine[3].toUShort(),
                                                   splitLine[4].toUShort(),
                                                   splitLine[5].toUShort(),
                                                   splitLine[6].toUShort());
		insertDataFile(*newLink, splitLine[0], true);
	}
}

void PhoneDatabase::saveFile(QTextStream& stream, QString path, PhoneLink& file)
{
	QString quotes = "\"";
	stream << quotes << path << quotes << separator
			<< quotes << file.department << quotes << separator
			<< quotes << file.name << quotes << separator
			<< file.phone1 << separator
			<< file.phone2 << separator
			<< file.cell1 << separator
			<< file.cell2 << endl;
}

void PhoneDatabase::saveCategory(QTextStream& stream, QString path,
								 PhoneCategory& category)
{
	for(int i = 0; i < category.subCategories().count(); i++)
		saveCategory(stream, path + category.name() + "/",
					 category.subCategories()[i]);

	for(int i = 0; i < category.dataFiles().count(); i++)
		saveFile(stream, path + category.name() + "/",
				 category.dataFiles()[i]);
}

void PhoneDatabase::saveDatabase(QString path)
{
	QFile dataFile(path);
	if(!dataFile.open(QFile::WriteOnly | QFile::Text))
		throw InvalidFile(QString("Can't open file %1").arg(path));

	QTextStream dataStream(&dataFile);
	saveCategory(dataStream, "", *root());
	dataStream.flush();
	dataFile.close();
}

QList<PhoneLink>& PhoneDatabase::findDataFiles(const PhoneLink& file,
											   const PhoneCategory& startCategory)
{
	QList<PhoneLink>* list = new QList<PhoneLink>;
	QList<Category<PhoneLink> >& subCats = startCategory.subCategories();
	QList<PhoneLink>& dtFiles = startCategory.dataFiles();

	for(int i = 0; i < subCats.count(); i++)
		list->append(findDataFiles(file, subCats[i]));

	for(int i = 0; i < dtFiles.count(); i++)
		if(dtFiles[i].name.contains(file.name, Qt::CaseInsensitive) &&
		   dtFiles[i].department.contains(file.department, Qt::CaseInsensitive))
			list->append(dtFiles[i]);

	return *list;
}

QList<PhoneLink>& PhoneDatabase::findDataFiles(const PhoneLink& file)
{
	return findDataFiles(file, *root());
}

void PhoneDatabase::insertDataFile(PhoneLink& data, QString path,
								   bool createThePath)
throw(ObjectNotFound, InvalidArgument)
{
	CategoryTree<PhoneLink>::insertDataFile(data, path, createThePath);
	_phoneList.removeAll(data);
	_phoneList.append(data);
}

void PhoneDatabase::removeDataFile(PhoneLink& data)
{
	CategoryTree<PhoneLink>::removeDataFile(data);
	_phoneList.removeAll(data);
}

void PhoneDatabase::replaceDataFile(PhoneLink &oldFile, PhoneLink newFile)
{
	int oldFilePosition = _phoneList.indexOf(oldFile);
	if(oldFilePosition != -1)
	{
		_phoneList.removeAll(oldFile);
		_phoneList.insert(oldFilePosition, newFile);
		_root->replaceDataFileRecursively(oldFile, newFile);
	}
}

void PhoneDatabase::toHTML(PhoneCategory& cat, QTextStream& htmlStream,
						   short int depth)
{
	if(depth)
		htmlStream << QString("<h%1>%2</h%1>\n").arg(depth + 1).arg(cat.name());
	QList<PhoneLink>& dataFiles = cat.dataFiles();
	if(dataFiles.size())
	{
		htmlStream << "<table border=\"1\">\n";
		PhoneLink::headToHTML(htmlStream);
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
