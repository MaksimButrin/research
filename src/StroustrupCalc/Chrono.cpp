#include <tuple>
#include <QString>
#include "Chrono.h"
#include <QDebug>
#include <QtAlgorithms>




using namespace std;

namespace nsChrono
{


Date::Date()
	:_year{ defaultDate().getYear()}, 
	_month{ defaultDate().getMonth() },
	_day{ defaultDate().getDay() }
{

}


Date::Date(int y, Month m, int d)
	: _year(y), _month(m), _day(d)
{
	if (!isDate(y, m, d))
		throw Invalid{};
}


Date::~Date()
{
}


int Date::getDay() const
{
	return _day;
}


Month Date::getMonth() const
{
	return _month;
}


int Date::getYear() const
{
	return _year;
}

QString Date::toString() const
{
	return QString("%1/%2/%3").arg(getYear()).arg(int(getMonth())).arg(getDay());
}


void Date::addDay(int d)
{
	auto cntDayInMonth = dayInMonth(_month, _year);
	auto newDay = _day + d;

	if (newDay <= cntDayInMonth)
	{
		_day += d;
	}
	else
	{
		++_month;
		_day = (newDay % cntDayInMonth);
	}

}


void Date::addMonth(int m)
{
	auto newMonth = (int)_month + m;
	
	if (newMonth <= 12)
	{
		_month = Month(newMonth);
	}
	else
	{
		_month = Month(newMonth % 12);
		_year++;
	}

}


void Date::addYear(int y)
{
	if (getMonth() == Month::feb && 
		getDay() == 29 && 
		!leapYear(getYear() + y))
	{
		_month = Month::mar;
		_day = 1;
	}
	_year += y;
}


const Date & defaultDate()
{
	static Date dDate{ 2001, Month::jan, 1 };
	return dDate;
}


bool isDate(int y, Month m, int d)
{
	if (d < 1)
		return false;

	if (m < Month::jan || m > Month::dec)
		return false;

	return !(dayInMonth(m, y) < d);
}


bool leapYear(int y)
{
	return ((y - 1800) % 4) == 0;
}

int dayInMonth(Month month, int year)
{
	int cntDayInMonth{ 31 };
	
	switch (month)
	{
	case Month::feb:
		cntDayInMonth = (leapYear(year) && year > 0) ? 29 : 28;
		break;
	case Month::apr:
	case Month::jun:
	case Month::sep:
	case Month::nov:
		cntDayInMonth = 30;
		break;
	default:
		break;
	}

	return cntDayInMonth;
}


bool operator==(const Date & lhs, const Date & rhs)
{
	auto lhsKey = make_tuple(lhs.getDay(), lhs.getMonth(), lhs.getYear());
	auto rhsKey = make_tuple(rhs.getDay(), rhs.getMonth(), rhs.getYear());

	return lhsKey == rhsKey;
}


bool operator!=(const Date & lhs, const Date & rhs)
{
	auto lhsKey = make_tuple(lhs.getDay(), lhs.getMonth(), lhs.getYear());
	auto rhsKey = make_tuple(rhs.getDay(), rhs.getMonth(), rhs.getYear());

	return lhsKey != rhsKey;
}

Month operator++(Month & m)
{
	m = (m == Month::dec) ? Month::jan : Month((int)m + 1);
	return m;
}


ostream & operator<<(ostream & out, const Date & d)
{
	auto message = QString("( %1 , %2, %3 )\n").arg(d.getYear()).arg(int(d.getMonth())).arg(d.getDay());

	return out << message.toStdString();
}


istream & operator>>(istream & in, Date & d)
{
	int year, month, day;
	char ch1, ch2, ch3, ch4;
	in >> ch1 >> year >> ch2 >> month >> ch3 >> day >> ch4;

	if (!in)
		return in;

	if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
	{
		in.clear(ios_base::failbit);
		return in;
	}
	
	d = Date(year, Month(month), day);

	return in;
}


void runChrono()
{
	Date today;
	Date tomorrow;
	Date test(2005, Month::may, 05);
	
	test.addYear(14);

	auto td = today.getYear();
	auto tm = tomorrow.getYear();

	tomorrow.addDay(55);

	//auto b1 = isDate(2020, Month::feb, 30);
	//auto b2 = isDate(2019, Month::feb, 29);
	//auto b3 = isDate(2020, Month::feb, 28);

	//qDebug() << QString(leapYear(1796) ? "leap" : "no leap");
	//qDebug() << QString(leapYear(1804) ? "leap" : "no leap");
	//qDebug() << QString(leapYear(1805) ? "leap" : "no leap");

	cout << today;
	cout << tomorrow;
	cout << test;

	NamePairs np;
	np.pushBackHuman(NamePairs::human{ "ivan", 5.0 });
	np.pushBackHuman(NamePairs::human{ "aslan", 9.0 });
	np.pushBackHuman(NamePairs::human{ "misorslav", 11.0 });
	np.pushBackHuman(NamePairs::human{ "gosh", 9.1 });

	np.print();
	np.sortHumansByNames();
	np.print();
}



NamePairs::human NamePairs::getHumanByName(const QString & name)
{
	auto result = human();
	
	for (auto & item : _humans)
	{
		if (item.name == name)
			return item;
	}
	
	return result;
}


void NamePairs::print()
{
	for (auto & item : _humans)
	{
		print(item);
	}

}


void NamePairs::print(const human & h)
{
	qDebug().noquote() << QString("name '%1', \t age is %2").arg(h.name).arg(h.age);
}

void NamePairs::pushBackHuman(const human & h)
{
	_humans.push_back(h);
}


void NamePairs::sortHumansByNames()
{
	qSort(_humans);
}


void NamePairs::sortHumansByAge()
{
}


bool operator<(const NamePairs::human & lhs, const NamePairs::human & rhs)
{
	return lhs.name < rhs.name;
}

}

