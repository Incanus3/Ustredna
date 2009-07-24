#include "PhoneLink.h"

PhoneLink::PhoneLink(
//		QString department,
		QString name,
					 unsigned short phone1,
					 unsigned short cell1,
					 unsigned short phone2,
					 unsigned short cell2)
{
//	this->department = department;
	this->name = name;
	this->phone1 = phone1;
	this->phone2 = phone2;
	this->cell1 = cell1;
	this->cell2 = cell2;
}

bool PhoneLink::operator== (PhoneLink link) const
{
	return this->name == link.name;
}

void PhoneLink::print(QTextStream& stream) const
{
	QString separator = " | ";
	stream << QString("%1%2%3%2%4").arg(name).arg(separator)
			.arg(phone1).arg(cell1) << endl;
}

PhoneLink::operator QString() const
{
	return name;
}
