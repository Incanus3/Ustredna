#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QList>
#include <QStringList>
//#include "Cout.h"
#include "Exceptions.h"

template<class T>
		class Category
{
		public:
	//! konstruktor třídy
	Category(QString name) : _name(name) {}

	//! změní jméno třídy
	void rename(QString name) throw(InvalidArgument);

	//! vrací kopii seznamu podkategorií
	QList<Category<T> >& subCategories() const;
	//! vrací kopii seznamu datových souborů
	QList<T>& dataFiles() const;

	//! přidá novou podkategorii subCat
	void addSubCategory(Category<T>& subCat, bool alreadyThereError = true)
			throw(InvalidArgument);
	//! vytvoří novou podkategorii se jménem name
	void addSubCategory(QString name, bool alreadyThereError = true)
			throw(InvalidArgument);
	//! odstraní podkategorii
	void removeSubCategory(Category<T>& subCat);

	//! přidá datový soubor
	void addDataFile(T data, bool alreadythereError = true);
	//! odstraní datový soubor
	void removeDataFile(T data);
	//! odstraní datový soubor i ze všech podkategorií
	void removeDataFileRecursively(T data);
	void replaceDataFile(T oldData, T newData);
	void replaceDataFileRecursively(T oldData, T newData);

	//! vyhledá v seznamu podkategorií kategorii cat (pomocí operátoru porovnání)
	//! a vrátí ji
	Category<T>& getSubCategory(Category<T>& cat) throw(ObjectNotFound);
	//! vyhledá v seznamu podkategorií kategorii s názvem name a vrátí ji
	Category<T>& getSubCategory(QString name) throw(ObjectNotFound);
	//! vyhledá v seznamu datových souborů soubor file (pomocí operátoru porovnání)
	//! a vrátí jej
	T& getDataFile(T file) throw(ObjectNotFound);

	//! rekurzivně vyhledá všechny datové soubory ==eqivalentní s data v seznamu
	//! souborů i v podkategoriích a vrátí je v QListu
	QList<T>& findDataFiles(T& data);

	//! operátor porovnání, kategorie jsou ==eqivalentní, pokud se rovná name
	bool operator== (Category cat) const;

	//! vrací jméno kategorie
	QString name() const;

	//! operátor implicitního přetypování na QString (vrací jméno kategorie)
	operator QString() const;

//	void print(QTextStream& stream = cout, unsigned short tabs = 0) const;

			protected:
	//! jméno kategorie
	QString _name;
	//! seznam podkategorií
	QList<Category> _subCategories;
	//! seznam datových souborů
	QList<T> _dataFiles;
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
		inline QList<Category<T> >& Category<T>::subCategories() const
{
	QList<Category<T> >* subCatsCopy = new QList<Category<T> >(_subCategories);
	
	return *subCatsCopy;
}

template<class T>
		inline QList<T>& Category<T>::dataFiles() const
{
	QList<T>* dtFilesCopy = new QList<T>(_dataFiles);

	return *dtFilesCopy;
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
		inline void Category<T>::addDataFile(T data, bool alreadythereError)
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
		inline void Category<T>::removeDataFile(T data)
{
	_dataFiles.removeAll(data);
}

template<class T>
		void Category<T>::removeDataFileRecursively(T data)
{
	removeDataFile(data);
//	foreach(Category<T>& subCat, _subCategories)
//		subCat.removeDataFileRecursively(data);
	QMutableListIterator<Category<T> > subCat(_subCategories);
	while (subCat.hasNext())
		subCat.next().removeDataFileRecursively(data);
}

template<class T>
		void Category<T>::replaceDataFile(T oldData, T newData)
{
	int oldFilePosition = _dataFiles.indexOf(oldData);
	if(oldFilePosition != -1)
	{
		_dataFiles.removeAll(oldData);
		_dataFiles.insert(oldFilePosition, newData);
	}
}

template<class T>
		void Category<T>::replaceDataFileRecursively(T oldData, T newData)
{
	replaceDataFile(oldData, newData);

	for(int i = 0; i < _subCategories.count(); i++)
		_subCategories[i].replaceDataFileRecursively(oldData, newData);
}

template<class T>
		inline Category<T>& Category<T>::getSubCategory(Category& cat)
		throw(ObjectNotFound)
{
	int index = _subCategories.indexOf(cat);
	if(index == -1)
		throw ObjectNotFound(QString("Category %1 not found").arg(cat));
	return _subCategories[index];
}

template<class T>
		inline Category<T>& Category<T>::getSubCategory(QString name)
		throw(ObjectNotFound)
{
	return getSubCategory(*(new Category(name)));
}

template<class T>
		inline T& Category<T>::getDataFile(T file) throw(ObjectNotFound)
{
	int index = _dataFiles.indexOf(file);
	if(index == -1)
		throw ObjectNotFound(QString("Object %1 not found").arg(file));
	return _dataFiles[index];
}

template<class T>
		QList<T>& Category<T>::findDataFiles(T& data)
{
	QList<T>* list = new QList<T>;
	for(int i = 0; i < _subCategories.count(); i++)
		list->append(_subCategories[i].findDataFiles(data));
	int index = _dataFiles.indexOf(data);
	if(index != -1)
		list->append(_dataFiles[index]);

	return *list;
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

//template<class T>
//		void Category<T>::print(QTextStream& stream, unsigned short tabs) const
//{
//	for(int i = 0; i < tabs; i++)
//		stream << "\t";
//	stream << _name << endl;
//	QListIterator<Category> subCatsIter(_subCategories);
//	while(subCatsIter.hasNext())
//		subCatsIter.next().print(stream, tabs + 1);
//	if(!_subCategories.empty() && !_dataFiles.empty())
//	{
//		for(int i = 0; i < tabs + 1; i++)
//			stream << "\t";
//		stream << "--------" << endl;
//	}
//	QListIterator<T> dataFilesIter(_dataFiles);
//	while(dataFilesIter.hasNext())
//	{
//		for(int i = 0; i < tabs + 1; i++)
//			stream << "\t";
//		dataFilesIter.next().print(stream);
//		stream << endl;
//	}
//}

#endif // CATEGORY_H
