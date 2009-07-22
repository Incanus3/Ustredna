#include <QtGui/QApplication>
#include <QTextCodec>
#include "MainWindow.h"
#include "CategoryTree.h"
#include "PhoneLink.h"
#include "Cout.h"

using namespace std;

void pokusy();

int main(int argc, char *argv[])
{
	pokusy();

	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

void pokusy()
{
	CategoryTree<PhoneLink> tree("abcd");
	PhoneLink pl("gynekologie", "boudova", 123, 456);
	PhoneLink pl2 = pl;
	pl2.name = "nekdo jinej";

	Category<PhoneLink> one("one"), two("two"), three("three");
	tree.insertCategory(one);
	tree.insertCategory(two);
	tree.insertCategory(three, "/one/");
	tree.insertDataFile(pl, "/one/");

	try {
		tree.insertDataFile(pl2, "/one/");
	} catch(QException& expt) {
		cout << expt.what() << endl;
	}

	cout << tree.root().findSubCategory("one")
			.findDataFile(*(new PhoneLink("gynekologie"))) << endl;

	tree.print();
	cout << "volam tree.insertCategory(\"abc\", \"/one/three/\")" << endl;
	try {
		tree.insertCategory("abc", "/one/three/");
	} catch (ObjectNotFound& expt) {
		cout << endl << expt.what() << endl;
	}
	tree.print();
}
