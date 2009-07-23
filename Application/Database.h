#ifndef DATABASE_H
#define DATABASE_H

#include "CategoryTree.h"
#include "PhoneLink.h"

class PhoneDatabase
{
	CategoryTree<PhoneLink>* tree;

	CategoryTree<PhoneLink>* loadDatabase(QString path);

		public:
	PhoneDatabase(QString path);
};

#endif // DATABASE_H
