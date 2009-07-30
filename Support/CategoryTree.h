#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "Category.h"

template<class T>
		class CategoryTree
{
	Category<T>* _root;

	Category<T>& findDirectory(QString path)
			throw(ObjectNotFound);
	T& findDataFile(QString path, T dataFile)
			throw(ObjectNotFound);

	Category<T>& createPath(QString path);

		public:
	CategoryTree(QString rootCategoryName = "");

	Category<T>* root() const;

	void insertCategory(Category<T>& cat, QString path = "/",
						bool createThePath = false)
			throw(ObjectNotFound);
	void insertCategory(QString name, QString path = "/",
						bool createThePath = false)
			throw(ObjectNotFound);

	void insertDataFile(T& data, QString path = "/",
						bool createThePath = false)
			throw(ObjectNotFound, InvalidArgument);

//	void print(QTextStream& stream = cout,
//			   unsigned short tabs = 0) const;

	void clear();
};

template<class T>
		inline CategoryTree<T>::CategoryTree(QString rootCategoryName)
{
	_root = new Category<T>(rootCategoryName);
}

template<class T>
		inline Category<T>* CategoryTree<T>::root() const
{
	Category<T>* rootCopy = new Category<T>(*_root);
	return rootCopy;
}

template<class T>
		Category<T>& CategoryTree<T>::findDirectory(QString path)
		throw(ObjectNotFound)
{
	Category<T>* current = _root;
	QStringList splitPath = path.split("/", QString::SkipEmptyParts);
	for(int i = 0; i < splitPath.size(); i++)
	{
		try {
			current = &current->findSubCategory(splitPath[i]);
		} catch(ObjectNotFound& expt) {
			throw ObjectNotFound(QString("invalid path:\n")
								 + expt.what());
		}
	}
	return *current;
}

template<class T>
		T& CategoryTree<T>::findDataFile(QString path, T dataFile)
		throw(ObjectNotFound)
{
	Category<T>* directory = findDirectory(path);
	return directory->findDataFile(dataFile);
}

template<class T>
		Category<T>& CategoryTree<T>::createPath(QString path)
{
	Category<T>* current = _root;
	QStringList splitPath = path.split("/", QString::SkipEmptyParts);
	for(int i = 0; i < splitPath.size(); i++)
	{
		current->addSubCategory(splitPath[i], false);
		current = &current->findSubCategory(splitPath[i]);
	}
	return *current;
}

template<class T>
		void CategoryTree<T>::insertCategory(Category<T>& cat, QString path,
											 bool createThePath)
		throw(ObjectNotFound)
{
	Category<T>& category = createThePath ? createPath(path) : findDirectory(path);
	category.addSubCategory(cat);
}

template<class T>
		inline void CategoryTree<T>::insertCategory(QString name, QString path,
													bool createThePath)
		throw(ObjectNotFound)
{
	insertCategory(*(new Category<T>(name)), path, createThePath);
}

template<class T>
		void CategoryTree<T>::insertDataFile(T& data, QString path,
											 bool createThePath)
		throw(ObjectNotFound, InvalidArgument)
{
	Category<T>& category = createThePath ? createPath(path) : findDirectory(path);
	category.addDataFile(data);
}

//template<class T>
//		inline void CategoryTree<T>::print(QTextStream& stream,
//										   unsigned short tabs) const
//{
//	_root->print(stream, tabs);
//}

template<class T>
		void CategoryTree<T>::clear()
{
	QString rootName = _root->name();
	delete _root;
	_root = new Category<T>(rootName);
}

#endif // CATEGORYTREE_H
