#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "Category.h"

template<class T>
		class CategoryTree
{
	Category<T>* _root;

	Category<T>* findDirectory(QString path) const
			throw(ObjectNotFound);

		public:
	CategoryTree(QString rootCategoryName);

	Category<T> root() const;

	void insertCategory(Category<T>& cat, QString path = "/")
			throw(ObjectNotFound);
	void insertCategory(QString name, QString path = "/")
			throw(ObjectNotFound);

	void insertDataFile(T& data, QString path = "/")
			throw(ObjectNotFound, InvalidArgument);

	void print(QTextStream& stream = cout,
			   unsigned short tabs = 0) const;
};

template<class T>
		inline CategoryTree<T>::CategoryTree(QString rootCategoryName)
{
	_root = new Category<T>(rootCategoryName);
}

template<class T>
		inline Category<T> CategoryTree<T>::root() const
{
	return *_root;
}

template<class T>
Category<T>* CategoryTree<T>::findDirectory(QString path) const
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
	return current;
}

template<class T>
		void CategoryTree<T>::insertCategory(Category<T>& cat, QString path)
		throw(ObjectNotFound)
{
	Category<T>* category = findDirectory(path);
	category->addSubCategory(cat);
}

template<class T>
		inline void CategoryTree<T>::insertCategory(QString name, QString path)
		throw(ObjectNotFound)
{
	Category<T> cat(name);
	insertCategory(cat, path);
}

template<class T>
		void CategoryTree<T>::insertDataFile(T& data, QString path)
		throw(ObjectNotFound, InvalidArgument)
{
	Category<T>* category = findDirectory(path);
	category->addDataFile(data);
}

template<class T>
		inline void CategoryTree<T>::print(QTextStream& stream,
										   unsigned short tabs) const
{
	_root->print(stream, tabs);
}

#endif // CATEGORYTREE_H
