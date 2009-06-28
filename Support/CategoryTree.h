#ifndef CATEGORYTREE_H
#define CATEGORYTREE_H

#include "Category.h"

template<class T>
class CategoryTree
{
        public: // DEBUG
    Category<T>* _root;

        public:
    CategoryTree(QString rootCategoryName)
    {
        _root = new Category<T>(rootCategoryName);
    }

    void print(QTextStream& stream = cout, unsigned short tabs = 0) const;
};

template<class T>
void CategoryTree<T>::print(QTextStream& stream,
                            unsigned short tabs) const
{
    _root->print(stream, tabs);
}

#endif // CATEGORYTREE_H
