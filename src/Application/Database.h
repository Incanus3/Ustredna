#ifndef DATABASE_H
#define DATABASE_H

#include "CategoryTree.h"
#include "PhoneLink.h"

typedef Category<PhoneLink> PhoneCategory;

class PhoneDatabase : public CategoryTree<PhoneLink>
{
	void loadDatabase(QString path)
			throw(InvalidFile);

	static const QString separator;

		public:
	PhoneDatabase(QString path, QString name = "Nemocnice") throw(InvalidFile);

	QList<PhoneLink>& phoneList() const;

	QList<PhoneLink>& findDataFiles(QString namePart);
	QList<PhoneLink>& findDataFiles(QString namePart,
									PhoneCategory& startCategory);

	void insertDataFile(PhoneLink& data, QString path = "/",
						bool createThePath = false)
			throw(ObjectNotFound, InvalidArgument);

	void removeDataFile(PhoneLink& data);

	void toHTML(PhoneCategory& cat, QTextStream& htmlStream, short int depth = 0);
	void toHTML(QTextStream& htmlStream);
	void printToHTML(QString path);

	QList<PhoneLink> _phoneList;
};

#endif // DATABASE_H
