#include <QtGui/QApplication>
#include <QTextStream>
#include "mainwindow.h"
#include "CategoryTree.h"
#include "PhoneLink.h"

using namespace std;

int main(int argc, char *argv[])
{
	QTextStream cout(stdout);
	CategoryTree<PhoneLink> tree("abcd");
	PhoneLink pl("gynekologie", "boudova", 123, 456);
	PhoneLink pl2 = pl;
	pl2.name = "nekdo jinej";

	try {
		Category<PhoneLink> one("one"), two("two"), three("three");
		tree._root->addSubCategory(one);
		tree._root->addSubCategory(two);
		tree._root->subCategories()[0].addSubCategory(three);
		tree._root->findSubCategory("one").addDataFile(pl);
		tree._root->findSubCategory("one").addDataFile(pl2);
		tree._root->findSubCategory("one").addSubCategory(three);
		cout << tree._root->findSubCategory("one")
				.findDataFile(*(new PhoneLink("gynekologie")));

		tree.print();
		tree.insertCategory("abc", "/a/b/c/");
		tree.print();
	} catch (ObjectNotFound& expt) {
		cout << expt.what() << endl;
	}

	QApplication a(argc, argv);
	MainWindow w;
	//    w.show();
	//    return a.exec();
	return 0;
}
