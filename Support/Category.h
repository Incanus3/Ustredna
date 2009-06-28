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

    QString name() const
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

    bool operator== (Category& cat) const
	{
		return _name == cat.name();
	}

    void print(QTextStream& stream = cout, unsigned short tabs = 0) const;
};

template<class T>
void Category<T>::print(QTextStream& stream, unsigned short tabs) const
{
    for(int i = 0; i < tabs; i++)
        stream << "\t";
    stream << _name << endl;
    QListIterator<Category> subCatsIter(_subCategories);
    while(subCatsIter.hasNext())
        subCatsIter.next().print(stream, tabs + 1);
    QListIterator<T> dataFilesIter(_dataFiles);
    while(dataFilesIter.hasNext())
    {
        for(int i = 0; i < tabs + 1; i++)
            stream << "\t";
        stream << dataFilesIter.next() << endl;
    }
}

#endif // CATEGORY_H

