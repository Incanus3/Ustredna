#include "PhoneLink.h"

PhoneLink::PhoneLink(QString department, QString name,
						unsigned short phone1,
						unsigned short cell1,
						unsigned short phone2 = 0,
						unsigned short cell2 = 0)
	{
		this->department = department;
		this->name = name;
		this->phone1 = phone1;
		this->phone2 = phone2;
		this->cell1 = cell1;
		this->cell2 = cell2;
	}

void PhoneLink::print(QTextStream& stream, unsigned short tabs)
{
    for(int i = 0; i < tabs; i++)
        stream << "\t";
    stream << department << " | " << name << " | " << phone1 << " | "
            << cell1 << endl;
}
