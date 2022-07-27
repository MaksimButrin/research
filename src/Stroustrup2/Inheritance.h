//#pragma once

#include <QString>
#include <QDebug>
#include <iostream>
#include "Consts.h"

using namespace std;
using namespace cst;

namespace inh
{
	
void run();
void virtFunc01();
void virtFunc02();
void virtFunc04(); /* ���������� */

class X
{
protected:
	int i;
public:
	void seti(int c) { i = c; }
	virtual void print() { cout << endl << "class X : " << i; }
};

class Y : public X // ������������
{
public:
	void print() { cout << endl << "class Y : " << i; } // ��������������� ������� �������
};

/* ravesli.com - ���� �165 */
/* ����������� ����������� � ����������� ������������ */
/* !!! ��� ������ � ������������� ���� ����������� ������ ������ ���� ������������ */
/* ����� ����� ���������� ������ ���������� Parent */
class Parent01
{
public:
	// �� ����������� ����������
	// Child01::_mArray �� ����� ������ ��� �������� parent, �.�. �� ����� ������� ���������� Child
	~Parent01() 
	{
		qDebug().noquote() << "Calling NOT virtual ~Parent01()";
	}

private:

};


class Child01: public Parent01
{
public:
	Child01(int length)
	{
		_mArray = new int[length];
	}
	
	// �� ����������� ���������� :
	~Child01() 
	{
		qDebug().noquote() << "Calling NOT virtual ~Child01()";
		delete[] _mArray;
	}

private:
	int * _mArray;
};

/* ���������� ������������ */
class Parent02
{
public:
	// ����������� ����������, ������ ��� �������� Parent ����� ������ ����� ���������� Child 
	virtual ~Parent02()
	{
		qDebug().noquote() << "Calling Virtual ~Parent02()";
	}
private:
	int _xx{0};
	int xx() { return _xx; };
};
class Child02 : public Parent02
{
public:
	Child02(int length)
	{
		_mArray = new int[length];
		
		//auto f = Parent02::xx();
	}

	// ����������� ���������� :
	virtual ~Child02()
	{
		qDebug().noquote() << "Calling Virtual ~Child02()";
		delete[] _mArray;
	}

private:
	int * _mArray;
};

/* ������������� ����������� ������� (������������� ������ ���������������) */

class Parent03
{
public:
	virtual const char * getName()
	{
		return "getName = Parent";
	}
};
class Child03: public Parent03
{
public:
	virtual const char * getName()
	{
		return "getName = Child";
	}
};

/* ���������� 14.3.3 - ����������, ����� �� � ��� ������ �� �������� � ����������� */
//void printCall(const QString & msg);
// ??? ������-�� ������ ������ � ���������� �-�� � h-���� (����� ��� ������������)
// inline foo() {}; � ���� ������ ��������
inline void printCall(const QString & msg)
{
	qDebug().noquote() << QString("Calling: %1").arg(msg);
}


inline void test()
{

}

struct B04
{
	virtual void f() const
	{
		printCall("virtual B04::f()");
	}
	//�� �����������
	void g() const
	{
		printCall("not virtual B04::g()");
	}
};

struct D04: B04 /* public � ������ ������ �� ����� �.�. ��. � �������� ������ � � MShape */
{
	/* ����������� B04::f() */
	void f() const override
	{
		printCall("override D04::f()"); 
	}
	void g() const
	{
		printCall("D04::g()");
	}
};

class C04 : private B04
{
public:
	/* ����������� B04::f() */
	void f() const override
	{
		printCall("override C04::f()");
		g(); /* ������ ��� ����� ��������� � B04::g()*/
	}
};


class E04 : private B04
{
public:
	/* !!! friend �� ������� ������������ � ������������, � friend ��� �� ����������� */
	friend void virtFunc04(); /* ������ ����� ���������� � B04::g() � �-�� virtFunc04 */
	/* ����������� B04::f() */
	void f() const override
	{
		printCall("override E04::f()");
	}
};

struct DD04 : D04
{
	/* �� 'void f() const'(��� const) � ������� �� ����������� D04::f() */
	void f() /*override*/
	{
		printCall("DD04::f()"); 
	}
	void g() const
	{
		printCall("DD04::g()");
	}
};

struct Mom04
{
	int a{ 0 };
	void f()
	{
		printCall("not virtual Mom04::f()");
	}

	void g(double)
	{
		printCall("not virtual Mom04::g(double)");
	}
};


struct Son04: Mom04
{
	int a{ 1 };
	void f()
	{
		printCall("not virtual Son04::f()");
	}
	/* ��� ���� ����� ������������ ������ � ����, ��������� ����, 
	����� ��������� � ������� ��������� ������ ���� � �������������� using*/
	using Mom04::g;
	void g(int)
	{
		printCall("not virtual Son04::g(int)");
	}

};


struct Son0401 : Mom04
{
private:
	int a{ 3 };
	void f()
	{
		printCall("not virtual Son0401::f()");
	}
};
// ����� D04 - ������������� ������ �04, ������� ������� call04()
// ����� �������� ������ ������ D04. ����� DD04 - �������������
// ������ D04, � ����� D04 - ������������� ������ �04,
// !!! ������� ������� call04(���������� ��������) ����� �������� ������ ������ DD04 (����������)
inline void call04(const B04 b)
{
	b.f();
	b.g();
}

}//namespace inh
