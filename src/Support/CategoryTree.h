#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "Category.h"
#include <QTextStream>
#include <QVector>

template<class T>
	class CategoryTree
{
		protected:
    Category<T>* _root;

    Category<T>& createPath(QString path);

		public:
    CategoryTree(QString rootCategoryName = "");

    Category<T>* root() const;

    Category<T>& getDirectory(QString path)
	    throw(ObjectNotFound);
    Category<T>& getDirectory(QVector<unsigned short int> path)
	    throw(ObjectNotFound);

    T& getDataFile(QString path, T dataFile)
	    throw(ObjectNotFound);

    void insertCategory(Category<T>& cat, QString path = "/",
			bool createThePath = false)
    throw(ObjectNotFound);
    void insertCategory(QString name, QString path = "/",
			bool createThePath = false)
    throw(ObjectNotFound);

    void insertDataFile(T& data, QString path = "/",
			bool createThePath = false)
    throw(ObjectNotFound, InvalidArgument);
    void insertDataFile(T& data, QVector<unsigned short int> path)
	    throw(ObjectNotFound);

    void removeDataFile(T& data);

    QList<T>& findDataFile(T& data)
	    throw(ObjectNotFound);

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
	Category<T>& CategoryTree<T>::getDirectory(QString path)
	throw(ObjectNotFound)
{
    Category<T>* current = _root;
    QStringList splitPath = path.split("/", QString::SkipEmptyParts);
    for(int i = 0; i < splitPath.size(); i++)
    {
	try {
	    current = &current->getSubCategory(splitPath[i]);
	} catch(ObjectNotFound& expt) {
	    throw ObjectNotFound(QString("invalid path:\n")
				 + expt.what());
	}
    }
    return *current;
}

template<class T>
	Category<T>& CategoryTree<T>::getDirectory(QVector<unsigned short int> path)
	throw(ObjectNotFound)
{
    Category<T>* current = _root;
    for(int i = 0; i < path.size(); i++)
    {
	current = &current->getSubCategory(path[i]);
    }
    return *current;
}

template<class T>
	T& CategoryTree<T>::getDataFile(QString path, T dataFile)
	throw(ObjectNotFound)
{
    Category<T>* directory = getDirectory(path);
    return directory->getDataFile(dataFile);
}

template<class T>
	Category<T>& CategoryTree<T>::createPath(QString path)
{
    Category<T>* current = _root;
    QStringList splitPath = path.split("/", QString::SkipEmptyParts);
    for(int i = 0; i < splitPath.size(); i++)
    {
	current->addSubCategory(splitPath[i], false);
	current = &current->getSubCategory(splitPath[i]);
    }
    return *current;
}

template<class T>
	void CategoryTree<T>::insertCategory(Category<T>& cat, QString path,
					     bool createThePath)
	throw(ObjectNotFound)
{
    Category<T>& category = createThePath ? createPath(path) : getDirectory(path);
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
    Category<T>& category = createThePath ? createPath(path) : getDirectory(path);
    category.addDataFile(data, false);
}

template<class T>
	void CategoryTree<T>::insertDataFile(T& data,
					     QVector<unsigned short int> path)
	throw(ObjectNotFound)
{
    Category<T>& category = getDirectory(path);
    category.addDataFile(data);
}

template<class T>
	void CategoryTree<T>::removeDataFile(T& data)
{
    _root->removeDataFileRecursively(data);
}

template<class T>
	QList<T>& CategoryTree<T>::findDataFile(T& data) throw(ObjectNotFound)
{
    return _root->findDataFile(data);
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
