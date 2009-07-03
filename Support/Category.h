#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QList>
#include "Cout.h"

template<class T>
class Category
{
	QString _name;
    QList<Category> _subCategories;
    QList<T> _dataFiles;
	
		public:
	Category(QString name) : _name(name) {}

	void rename(QString name);

	QList<Category> subCategories() const;
	QList<T> dataFiles() const;

	void addSubCategory(Category<T>& subCat);
	void removeSubCategory(Category<T>& subCat);

	void addDataFile(T& data);
	void removeDataFile(T& data);

	Category& findSubCategory(Category& cat);
	Category& findSubCategory(QString name);
	T& findDataFile(T& file);

	bool operator== (Category cat) const;

	QString name() const;
    void print(QTextStream& stream = cout, unsigned short tabs = 0) const;
};

template<class T>
inline QString Category<T>::name() const
{
	return _name;
}

template<class T>
inline void Category<T>::rename(QString name)
{
	_name = name;
}

template<class T>
inline QList<Category<T> > Category<T>::subCategories() const
{
	return _subCategories;
}

template<class T>
inline QList<T> Category<T>::dataFiles() const
{
	return _dataFiles;
}

template<class T>
inline void Category<T>::addSubCategory(Category<T>& subCat)
{
	_subCategories += subCat;
}

template<class T>
inline void Category<T>::removeSubCategory(Category<T>& subCat)
{
	_subCategories.removeAll(subCat);
}

template<class T>
inline void Category<T>::addDataFile(T& data)
{
	_dataFiles += data;
}

template<class T>
inline void Category<T>::removeDataFile(T& data)
{
	_dataFiles.removeAll(data);
}

template<class T>
inline Category<T>& Category<T>::findSubCategory(Category& cat)
{
	return _subCategories[_subCategories.indexOf(cat)];
}

template<class T>
inline Category<T>& Category<T>::findSubCategory(QString name)
{
	return findSubCategory(*(new Category(name)));
}

template<class T>
inline T& Category<T>::findDataFile(T& file)
{
	return _dataFiles[_dataFiles.indexOf(file)];
}

template<class T>
inline bool Category<T>::operator== (Category cat) const
{
	return _name == cat.name();
}

template<class T>
void Category<T>::print(QTextStream& stream, unsigned short tabs) const
{
    for(int i = 0; i < tabs; i++)
        stream << "\t";
    stream << _name << endl;
    QListIterator<Category> subCatsIter(_subCategories);
    while(subCatsIter.hasNext())
        subCatsIter.next().print(stream, tabs + 1);
	if(!_subCategories.empty() && !_dataFiles.empty())
	{
		for(int i = 0; i < tabs + 1; i++)
			stream << "\t";
		stream << "--------" << endl;
	}
    QListIterator<T> dataFilesIter(_dataFiles);
    while(dataFilesIter.hasNext())
    {
        for(int i = 0; i < tabs + 1; i++)
            stream << "\t";
        stream << dataFilesIter.next() << endl;
    }
}

#endif // CATEGORY_H
