#ifndef DATABASE_H
#define DATABASE_H

#include "CategoryTree.h"
#include "PhoneLink.h"

#define ADMIN

typedef Category<PhoneLink> PhoneCategory;

class PhoneDatabase : public CategoryTree<PhoneLink>
{
	void loadDatabase(QString path)
			throw(InvalidFile);

	QList<PhoneLink> _phoneList;
	static const QString separator;

	void saveCategory(QTextStream& stream, QString path, PhoneCategory& category);
	void saveFile(QTextStream& stream, QString path, PhoneLink& file);

		public:
	PhoneDatabase(QString path, QString name = "") throw(InvalidFile);

	QList<PhoneLink>& phoneList() const;

	QList<PhoneLink>& findDataFiles(const PhoneLink& file,
									const PhoneCategory& startCategory);
	QList<PhoneLink>& findDataFiles(const PhoneLink& file);

	void insertDataFile(PhoneLink& data, QString path = "/",
						bool createThePath = false)
			throw(ObjectNotFound, InvalidArgument);

	void removeDataFile(PhoneLink& data);
	void replaceDataFile(PhoneLink& oldFile, PhoneLink newFile);

	void toHTML(PhoneCategory& cat, QTextStream& htmlStream, short int depth = 0);
	void toHTML(QTextStream& htmlStream);
	void printToHTML(QString path);
	
	void saveDatabase(QString path);
};

#endif // DATABASE_H
