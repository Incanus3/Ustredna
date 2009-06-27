#include <QtGui/QApplication>
#include <QTextStream>
#include "mainwindow.h"
#include "CategoryTree.h"

int main(int argc, char *argv[])
{
    QTextStream cout(stdout);
    CategoryTree<int> tree("abcd");

    tree._root->addSubCategory(*(new Category<int>("one")));
    tree._root->addSubCategory(*(new Category<int>("two")));
    tree._root->_subCategories[0].addSubCategory(*(new Category<int>("three")));
    tree.print();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
