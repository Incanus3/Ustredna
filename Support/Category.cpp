#include "Category.h"

template<class T>
void Category<T>::print(QTextStream& stream, unsigned short tabs)
{
    for(int i = 0; i < tabs; i++)
        stream << "\t";
    stream << name << endl;
    QListIterator<Category> iter(_subCategories);
    while(iter.hasNext())
        iter.next().print(stream, tabs + 1);
}
