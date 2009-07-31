#ifndef DATABASE_H
#define DATABASE_H

#include "CategoryTree.h"
#include "PhoneLink.h"

class PhoneDatabase : public CategoryTree<PhoneLink>
{
	void loadDatabase(QString path)
			throw(InvalidFile);

		public:
	PhoneDatabase(QString path, QString name = "Nemocnice") throw(InvalidFile);
};

#endif // DATABASE_H