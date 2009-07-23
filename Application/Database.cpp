#include "Database.h"
#include "Cout.h" // DEBUG

PhoneDatabase::PhoneDatabase(QString path)
{
	tree = loadDatabase(path);
}

CategoryTree<PhoneLink>* PhoneDatabase::loadDatabase(QString path)
{
	cout << "PhoneDatabase::loadDatabase() was called" << endl <<
			QString("and %1 was selected").arg(path) << endl; // DEBUG
}
