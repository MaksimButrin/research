#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <QVector>

using namespace std;


class WhiteBelt
{
public:
	WhiteBelt();
	~WhiteBelt();

	void runWhiteBelt();
};


/* потоки */
class weak4Lesson03
{
public:
	weak4Lesson03() {};
	~weak4Lesson03() {};

	void printTheFileHello(const QString & fileFath) const;
	void printTheFileDate(const QString & fileFath) const;
	void run();
};



/* потоки */
class weak4Lesson04
{
public:
	weak4Lesson04() {};
	~weak4Lesson04() {};

	void printInFile(const QString & fileFath = "") const;
	void run();
};

class FunctionPart
{
public:
	FunctionPart() {};

	FunctionPart(char nOperation, double nValue);
	~FunctionPart() {};

	double apply(double sourceValue) const
	{
		return _operation == '+' ? sourceValue + _value : sourceValue - _value;
	}

	void invert()
	{
		_operation = _operation == '+' ? '-' : '+';
	}


private:
	char _operation = '+';
	double _value{0.0};
};



class Function
{
public:
	void addPArt(char operation, double value) 
	{
		_parts.push_back({operation, value});
	}
	double apply(double value) const
	{
		for (const FunctionPart & part : _parts)
		{
			value = part.apply(value);
		}
		return value;
	}
	void invert()
	{
		for (FunctionPart & part : _parts)
		{
			part.invert();
		}
		/* перевернуть порядок */
		reverse(_parts.begin(), _parts.end());
	}

private:
	QVector<FunctionPart> _parts;
};


class weak4Lesson02
{
public:
	weak4Lesson02() {};
	~weak4Lesson02() {};

	struct Image
	{
		double quality;
		double freshness;
		double raiting;
	};

	struct Params
	{
		double a;
		double b;
		double c;
	};

	Function makeWeightFunction(const Params & params, const Image & image)
	{
		Function function;
		function.addPArt('-', image.freshness * params.a + params.b);
		function.addPArt('+', image.raiting * params.c);
		return function;

	}

	double computeImageWeight(const Params & params, const Image & image);
	double computeQualityByWeight(const Params & params, const Image & image, double weight);


	void run();
private:

};






struct Day
{
	int value{0};
	/* Explicit означает «явный», т.е. конструкторы явный и запрещает вызывать без нашего ведома. 
	т.е. преобраовывать целое число в объект типа Day
	*/
	explicit Day(int nValue)
	{
		value = nValue;
	}
};

struct Month
{
	int value{0};
	explicit Month(int nValue)
	{
		value = nValue;
	}
};

struct Year
{
	int value{0};
	explicit Year(int nValue)
	{
		value = nValue;
	}
};

struct Date
{
	int day{ 1 };
	int month{ 1 };
	int year{ 2020 };

	Date(Day nDay, Month nMonth, Year nYear)
	{
		day = nDay.value;
		month = nMonth.value;
		year = nYear.value;
	}
};


class weak4Lesson01
{
public:
	weak4Lesson01();
	~weak4Lesson01();

	void run();

	void printDate(const Date & date) const;


private:

};


