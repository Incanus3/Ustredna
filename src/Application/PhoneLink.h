#ifndef PHONELINK_H
#define PHONELINK_H

#include <QString>
#include <QTextStream>
//#include "Cout.h"

struct PhoneLink
{
	QString department;
	QString name;
	unsigned short phone1, phone2, cell1, cell2;

	PhoneLink(
			QString department,
			QString name = "",
				unsigned short phone1 = 0,
				unsigned short cell1 = 0,
                unsigned short phone2 = 0,
                unsigned short cell2 = 0);

    operator QString() const;

//	void print(QTextStream& stream = cout) const;

	bool operator== (PhoneLink link) const;

	void toHTML(QTextStream& htmlStream);
	static void headToHTML(QTextStream& htmlStream);
};

#endif // PHONELINK_H
