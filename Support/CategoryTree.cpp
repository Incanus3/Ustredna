#include "CategoryTree.h"

template<class T>
void CategoryTree<T>::print(QTextStream& stream,
							unsigned short tabs)
{
    _root->print(stream, tabs);
}
