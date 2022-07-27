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
void virtFunc04(); /* перекрытие */

class X
{
protected:
	int i;
public:
	void seti(int c) { i = c; }
	virtual void print() { cout << endl << "class X : " << i; }
};

class Y : public X // наследование
{
public:
	void print() { cout << endl << "class Y : " << i; } // переопределение базовой функции
};

/* ravesli.com - Урок №165 */
/* Виртуальные деструкторы и Виртуальное присваивание */
/* !!! При работе с наследованием ваши деструкторы всегда должны быть виртуальными */
/* иначе быдет вызываться только деструктор Parent */
class Parent01
{
public:
	// не виртуальный деструктор
	// Child01::_mArray не будет удален при удалении parent, т.к. не будет вызыван деструктор Child
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
	
	// не виртуальный деструктор :
	~Child01() 
	{
		qDebug().noquote() << "Calling NOT virtual ~Child01()";
		delete[] _mArray;
	}

private:
	int * _mArray;
};

/* Правильное наследование */
class Parent02
{
public:
	// виртуальный деструктор, теперь при удалении Parent будет вызван также деструктор Child 
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

	// виртуальный деструктор :
	virtual ~Child02()
	{
		qDebug().noquote() << "Calling Virtual ~Child02()";
		delete[] _mArray;
	}

private:
	int * _mArray;
};

/* Игнорирование виртуальных функций (игнорирование вызова переопределений) */

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

/* Страуструп 14.3.3 - Перекрытие, здесь же и про доступ от родителя к наследникам */
//void printCall(const QString & msg);
// ??? почему-то нельзя писать и реализацию ф-ии в h-нике (пишет что дублирование)
// inline foo() {}; в этом случае помогает
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
	//не виртуальная
	void g() const
	{
		printCall("not virtual B04::g()");
	}
};

struct D04: B04 /* public в данном случае не нужен т.к. см. в заметках телеге и в MShape */
{
	/* перекрывает B04::f() */
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
	/* перекрывает B04::f() */
	void f() const override
	{
		printCall("override C04::f()");
		g(); /* только тут можно обратится к B04::g()*/
	}
};


class E04 : private B04
{
public:
	/* !!! friend не следует использовать в наследовании, и friend ещё не наследуется */
	friend void virtFunc04(); /* теперь можно обращаться к B04::g() в ф-ии virtFunc04 */
	/* перекрывает B04::f() */
	void f() const override
	{
		printCall("override E04::f()");
	}
};

struct DD04 : D04
{
	/* не 'void f() const'(нет const) и поэтому НЕ перекрывает D04::f() */
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
	/* для того чтобы использовать версию и мамы, используя сына, 
	нужно привнести в область видимости версию мамы с использованием using*/
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
// Класс D04 - разновидность класса В04, поэтому функция call04()
// может получать объект класса D04. Класс DD04 - разновидность
// класса D04, а класс D04 - разновидность класса В04,
// !!! поэтому функция call04(использует родителя) может получать объект класса DD04 (наследника)
inline void call04(const B04 b)
{
	b.f();
	b.g();
}

}//namespace inh
