#ifndef PHONELINK_H
#define PHONELINK_H

#include <QString>
#include "Cout.h"

struct PhoneLink
{
	QString department;
	QString name;
	unsigned short phone1, phone2, cell1, cell2;

	PhoneLink(QString department, QString name,
				unsigned short phone1,
				unsigned short cell1,
				unsigned short phone2,
				unsigned short cell2);

    void print(QTextStream& stream = cout, unsigned short tabs = 0);

    bool operator== (PhoneLink& link)
    {
        return this->department == link.department;
    }
};

#endif // PHONELINK_H
