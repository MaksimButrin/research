#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <QVector>
#include <QString.h>
#include <QDatetime.h>
#include <qlist.h>


using namespace std;


class WhiteBelt
{
public:
	WhiteBelt();
	~WhiteBelt();

	void runWhiteBelt();
};


/* ���� �85. ������������ ��������� ������ */
class Ravesli85
{
public:
	Ravesli85() {};
	~Ravesli85() {};

	void run();
};

/* ������ */
class weak4Lesson03
{
public:
	weak4Lesson03() {};
	~weak4Lesson03() {};

	void printTheFileHello(const QString & fileFath) const;
	void printTheFileDate(const QString & fileFath) const;
	void run();
};


/* ������ */
class weak4Lesson04
{
public:
	weak4Lesson04() {};
	~weak4Lesson04() {};

	void printInFile(const QString & fileFath = "") const;
	void run();
};


class Predicates
{
public:
	Predicates() {};
	~Predicates() {};

	struct DateToString
	{
		QDateTime _dt;
		QString _dtString;
	};

	QList<QString> listInit() const;

	void run();
	void lowerBond() const;
	void diffDateTime() const;
};

/* ������������ ����������� */
class MftiLessonsConstructors
{
public: /* */

	MftiLessonsConstructors()
	{
		//char chArr[20] = "char array";
		_str = new char[20];
	};

	/* ����������� ����������� */
	/* ����� ��������� ������������� ����� ���� � private ��� ��������, ���� �������� = delete */
	MftiLessonsConstructors(const MftiLessonsConstructors & c) // = delete - ��������� �������, � ������ ������ �����������, ������� � �++ 11
	{
		_str = new char[20];
	}

	/*
	= delete - ������ ������������� �������� � ����� �������
	
	*/

	/* !!! ���� �������� ���, �� ��������� ����������� ����������� ������� 
	�� ��� � ��������, �.�. ���������� ����������� ������� */
	//MftiLessonsConstructors(MftiLessonsConstructors c) {};

	/* ��� ���� ����� �� �� ����� ������������ */
	MftiLessonsConstructors(MftiLessonsConstructors & c)
	{
		_str = new char[20];
	}

	~MftiLessonsConstructors() 
	{
		delete[] _str;
	};

	bool isConstMethod() const 
	{
		_n++; /* ����� ������ �.�. ������� ��� mutable - "���� �����" */
		int f; /* ����� ������ �.�. ��������� ���������� ������ */
		f++;
		//_m++; /* ������ ������ � ����������� ������ */
		return true; 
	};
	bool isConstMethod() { return false; };

private:
	char * _str = nullptr;
	mutable int _n;
	int _m;

};

/* ������� �� ����� */
//MftiLessonsConstructors & operator = (const MftiLessonsConstructors &lhs)
//{
//	return *this;
//}

class MftiLessons
{
public: /* ����������� ������� */
	MftiLessons() = default;
	MftiLessons(int & x, int y):
		_initListX(x) // ������ ������������� � ������������
		, _initListY(y)
	{
		/* �����: 
		����� ������������� ��� ���������, � ���� ���������������� ��� ������ ���� 
		�� ��������� �������� �� ��������� � ����� ���������� �����������, �.�. ������ �������� ������������
		��� ���������� ����� �������� ��������������� ������������ ������ �������������
		*/
		/* ��� ��� (x = _initListX) �� ��������� ������ ��� ������ ������ ���� ����������������� ��� ����� � ���� ������������ */
		/* �� ������������� � ������ ������ �� �� ��������� ���� �� ������������ ������ ������������� */
		//x = _initListX;
	};


	~MftiLessons() {};

	struct DateToString
	{
		QDateTime _dt;
		QString _dtString;
	};

	void run();
	void staticTest();
	void lesson01();
	void lesson03();
	int reffTest01(int & x);
	int reffTest02(const int & x);

	int & gIntRef();
	// 
	void typeConversion();

	void constructors();

	int _gInt{ 0 };
	int & _initListX;
	int _initListY;
};

bool operator < (const Predicates::DateToString &lhs, const Predicates::DateToString &rhs);
//bool operator > (const Predicates::DateToString &lhs, const Predicates::DateToString &rhs);
//bool operator == (const Predicates::DateToString &lhs, const Predicates::DateToString &rhs);
//bool operator >= (const Predicates::DateToString &lhs, const Predicates::DateToString &rhs);
//bool operator <= (const Predicates::DateToString &lhs, const Predicates::DateToString &rhs);

bool operator < (const Predicates::DateToString &lhs, const QDateTime &rhs);


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
	double _value{ 0.0 };
};



class Function
{
public:
	void addPArt(char operation, double value)
	{
		_parts.push_back({ operation, value });
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
		/* ����������� ������� */
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
	int value{ 0 };
	/* Explicit �������� ������, �.�. ������������ ����� � ��������� �������� ��� ������ ������.
	�.�. �������������� ����� ����� � ������ ���� Day
	*/
	explicit Day(int nValue)
	{
		value = nValue;
	}
};

struct Month
{
	int value{ 0 };
	explicit Month(int nValue)
	{
		value = nValue;
	}
};

struct Year
{
	int value{ 0 };
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


