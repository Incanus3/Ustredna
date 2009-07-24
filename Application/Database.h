#ifndef DATABASE_H
#define DATABASE_H

#include "CategoryTree.h"
#include "PhoneLink.h"

class PhoneDatabase
{
	CategoryTree<PhoneLink>* tree;

	CategoryTree<PhoneLink>* loadDatabase(QString path, QString name)
			throw(InvalidFile);

		public:
	PhoneDatabase(QString path, QString name = "Nemocnice") throw(InvalidFile);
};

#endif // DATABASE_H
