#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "Category.h"

template<class T>
class CategoryTree
{
        public: // DEBUG
    Category<T>* _root;

        public:
	CategoryTree(QString rootCategoryName);

	void insertCategory(Category<T>& cat, QString path = "")
		throw(ObjectNotFound);
	void insertCategory(QString name, QString path = "")
		throw(ObjectNotFound);

	void print(QTextStream& stream = cout, unsigned short tabs = 0) const;
};

template<class T>
inline CategoryTree<T>::CategoryTree(QString rootCategoryName)
{
	_root = new Category<T>(rootCategoryName);
}

template<class T>
void CategoryTree<T>::insertCategory(Category<T>& cat, QString path)
	throw(ObjectNotFound)
{
	Category<T>* current = _root;
	QStringList splitPath = path.split("/", QString::SkipEmptyParts);
	for(int i = 0; i < splitPath.size(); i++)
	{
		try {
			current = &current->findSubCategory(splitPath[i]);
		} catch(ObjectNotFound& expt) {
			throw new ObjectNotFound(QString("invalid path:\n")
									 + expt.what());
		}
	}
	current->addSubCategory(cat);
}

template<class T>
inline void CategoryTree<T>::insertCategory(QString name, QString path)
	throw(ObjectNotFound)
{
	Category<T> cat(name);
	insertCategory(cat, path);
}

template<class T>
inline void CategoryTree<T>::print(QTextStream& stream,
                            unsigned short tabs) const
{
    _root->print(stream, tabs);
}

#endif // CATEGORYTREE_H
