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

    void print(QTextStream& stream = cout, unsigned short tabs = 0);
};

#endif // CATEGORYTREE_H
