#ifndef PHONELINK_H
#define PHONELINK_H

#include <QString>
#include <QTextStream>
//#include "Cout.h"

//! Struktura uchovávající telefonní informace o daném oddělení (postu)
struct PhoneLink
{
	//! název oddělení (postu)
	QString department;

	//! jméno osoby
	QString name;

	//! telefonní linky
	unsigned short phone1, phone2, cell1, cell2;

	//! konstruktor struktury
        PhoneLink(//! název oddělení
                QString department,
                //! jméno
                QString name = "",
                unsigned short phone1 = 0,
                unsigned short phone2 = 0,
                unsigned short cell1 = 0,
                unsigned short cell2 = 0);

	//! operátor implicitního přetypování na QString
    operator QString() const;

//	void print(QTextStream& stream = cout) const;

	//! operátor porovnání
	bool operator== (PhoneLink link) const;

	//! funkce pro výstup do HTML
	void toHTML(QTextStream& htmlStream);

	//! statická funkce pro vytištění hlavičky do html
	static void headToHTML(QTextStream& htmlStream);
};

#endif // PHONELINK_H
