#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QList>
#include "Cout.h"
#include "Exceptions.h"

template<class T>
		class Category
{
	QString _name;
	QList<Category> _subCategories;
	QList<T> _dataFiles;
	
		public:
	Category(QString name) : _name(name) {}

	void rename(QString name) throw(InvalidArgument);

	QList<Category> subCategories() const;
	QList<T> dataFiles() const;

	void addSubCategory(Category<T>& subCat, bool alreadyThereError = true)
			throw(InvalidArgument);
	void addSubCategory(QString name, bool alreadyThereError = true)
			throw(InvalidArgument);
	void removeSubCategory(Category<T>& subCat);

	void addDataFile(T& data, bool alreadythereError = true);
	void removeDataFile(T& data);

	Category& findSubCategory(Category& cat) throw(ObjectNotFound);
	Category& findSubCategory(QString name) throw(ObjectNotFound);
	T& findDataFile(T& file) throw(ObjectNotFound);

	bool operator== (Category cat) const;

	QString name() const;
	operator QString() const;
	void print(QTextStream& stream = cout, unsigned short tabs = 0) const;
};

// Type T must implement bool operator== and method void print(QTextStream&)

template<class T>
		inline QString Category<T>::name() const
{
	return _name;
}

template<class T>
		inline void Category<T>::rename(QString name)
		throw(InvalidArgument)
{
	if(name == "")
		throw InvalidArgument("Name of the category mustn't be emtpy string");
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
		void Category<T>::addSubCategory(Category<T>& subCat,
												bool alreadythereError)
		throw(InvalidArgument)
{
	if(_subCategories.contains(subCat))
	{
		if(alreadythereError)
			throw InvalidArgument(
					QString("Subcategory %1 is already a subcategory "
							"of category %2").arg(subCat).arg(*this));
		return;
	}
	_subCategories += subCat;
}

template<class T>
		inline void Category<T>::addSubCategory(QString name,
												bool alreadyThereError)
		throw(InvalidArgument)
{
	return addSubCategory(*(new Category<T>(name)), alreadyThereError);
}

template<class T>
		inline void Category<T>::removeSubCategory(Category<T>& subCat)
{
	_subCategories.removeAll(subCat);
}

template<class T>
		inline void Category<T>::addDataFile(T& data, bool alreadythereError)
{
	if(_dataFiles.contains(data))
	{
		if(alreadythereError)
			throw InvalidArgument(
					QString("Data file %1 is already in "
							"category %2").arg(data).arg(*this));
		return;
	}
	_dataFiles += data;
}

template<class T>
		inline void Category<T>::removeDataFile(T& data)
{
	_dataFiles.removeAll(data);
}

template<class T>
		inline Category<T>& Category<T>::findSubCategory(Category& cat)
		throw(ObjectNotFound)
{
	int index = _subCategories.indexOf(cat);
	if(index == -1)
		throw ObjectNotFound(QString("Category %1 not found").arg(cat));
	return _subCategories[index];
}

template<class T>
		inline Category<T>& Category<T>::findSubCategory(QString name)
		throw(ObjectNotFound)
{
	return findSubCategory(*(new Category(name)));
}

template<class T>
		inline T& Category<T>::findDataFile(T& file) throw(ObjectNotFound)
{
	int index = _dataFiles.indexOf(file);
	if(index == -1)
		throw ObjectNotFound(QString("Object %1 not found").arg(file));
	return _dataFiles[index];
}

template<class T>
		inline bool Category<T>::operator== (Category cat) const
{
	return _name == cat.name();
}

template<class T>
		inline Category<T>::operator QString() const
{
	return _name;
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
		dataFilesIter.next().print(stream);
		stream << endl;
	}
}

#endif // CATEGORY_H
