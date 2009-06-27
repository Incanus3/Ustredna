#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QList>
#include "Cout.h"

template<class T>
class Category
{
        public: // DEBUG
	QString _name;
    QList<Category> _subCategories;
    QList<T> _dataFiles;
	
		public:
	Category(QString name) : _name(name) {}

	QString name()
	{
		return _name;
	}

	void addSubCategory(Category<T>& subCat)
	{
		_subCategories += subCat;
	}

	void removeSubCategory(Category<T>& subCat)
	{
		_subCategories.removeAll(subCat);
	}

	void addDataFile(T& data)
	{
		_dataFiles += data;
	}

	void removeDataFile(T& data)
	{
		_dataFiles.removeAll(data);
	}

	bool operator== (Category& cat)
	{
		return _name == cat.name();
	}

    void print(QTextStream& stream = cout, unsigned short tabs = 0);
};

#endif // CATEGORY_H

