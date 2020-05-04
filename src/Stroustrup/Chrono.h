#pragma once

#include <iostream>
#include <QVector>
#include <QString>

using namespace std;


namespace nsChrono
{

enum class Month
{
	jan = 1, feb, mar, apr,
	may, jun, jul, aug,
	sep, oct, nov, dec
};

enum class Day
{
	monday = 1, tuesday, wednesday,
	thursday, friday, saturday, sunday
};

class Date
{
public:

	// для генерации исключения
	class Invalid {};
	Date();
	// проверка корректности и инициализация
	Date(int y, Month m, int d);
	/* копирование по молчанию нас устраивает, а если нет, то : */
	// Date(const Date &dt) {}

	~Date();

	// немодифицирующие операции
	int getDay() const;
	Month getMonth() const;
	int getYear() const;
	QString toString() const;

	// модифицирующие операции
	void addDay(int d = 1);
	void addMonth(int m = 1);
	void addYear(int y = 1);

private:

	int _year{ 2001 };
	Month _month{ Month::jan };
	int _day{ 01 };

};

const Date& defaultDate();

bool isDate(int y, Month m, int d);
bool leapYear(int y);
int dayInMonth(Month month, int year = 0);

bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

Month operator++(Month &m);

ostream& operator<<(ostream& out, const Date& d);
//istream& operator>>(istream& in, const Date& d);

void runChrono();


class NamePairs
{
public:
	NamePairs() {}
	~NamePairs() {}

	struct human
	{
		QString name{ "no name" };
		double age{ 0.0 };
	};

	human getHumanByName(const QString & name);
	void print();
	void print(const human & h);

	void pushBackHuman(const human & h);

	void sortHumansByNames();
	void sortHumansByAge();

private:
	QVector<human> _humans;
};

bool operator<(const NamePairs::human & lhs, const NamePairs::human & rhs);

struct Х
{
	void f(int x)
	{
		struct Y
		{
			int f()
			{
				return 1;
			}

			int m;
		};

		int m;
		m = x;

		Y m2;
		return f(m2.f());
	}

	int m;
	void g(int m)
	{
		if (m)
		{
			f(m + 2);
		}
		else
		{
			g(m + 2);
		}
	}

	Х() { }
	void m3() {}

};

}
