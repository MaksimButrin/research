//#pragma once

#include <iostream>
#include <QDebug>
#include <QString>
#include "Consts.h"

using namespace cst;


namespace hw
{

void run();
void ch14Task01();

inline void printCall(const QString & msg)
{
	qDebug().noquote() << QString("Calling: %1").arg(msg);
}
/*
Определите класс 81 с виртуальной функцией vf() и невиртуальной
функцией f() . Определите эти функции в классе 81 . Реализуйте
каждую функцию так, чтобы она выводила свое имя (например,
"B1::vf()") . Сделайте эти функции открытыми.
*/
class B1
{
public:
	B1() {};
	~B1() {};

	virtual void vf() { printCall("B1::vf()"); };
	/* Добавьте в класс B1 чисто виртуальную функцию pvf() и попытайтесь повторить */
	/* это приведет к ошибке компиляции, даже если будет реализации */
	//virtual void pvf() = 0 { printCall("B1::pvf()"); };
	void f() { printCall("B1::f()"); };
};

/* Определите класс D1 , производный от класса B1, и перекройте в нем функцию vf() */
class D1: public B1
{
public:
	D1() {};
	~D1() {};

	void vf() override { printCall("D1::vf()"); };
};

/*
Теперь определите функцию f() в классе D1(мой D11) и повторите пп. 1-3. Объясните
результаты.
*/
class D11 : public B1
{
public:
	D11() {};
	~D11() {};

	void vf() override { printCall("D11::vf()"); };
	void f() { printCall("D11::f()"); };

};


/*
Определите класс D2, производный от класса Dl , и перекройте в нем
функцию pvf() . Создайте объект класса D2 и вызовите из него функции
f() , vf() и pvf()
*/
class B11
{
public:
	B11() {};
	~B11() {};

	virtual void vf() { printCall("B11::vf()"); };
	virtual void pvf() = 0;
	void f() { printCall("B11::f()"); };
};

class D12 : public B11
{
public:
	D12() {};
	~D12() {};

	void vf() override { printCall("D12::vf()"); };
	virtual void pvf() = 0;
	void f() { printCall("D12::f()"); };

};

class D2 : public D12
{
public:
	D2() {};
	~D2() {};

	void pvf() override { printCall("D2::pvf()"); };

};

/*
Определите класс B2 с чисто виртуальной функцией pvf() . Определите
класс D21 с данным-членом типа string и функцией-членом, перекрывающей
функцию pvf() ; функция D21::pvf() должна выводить
значение упомянутого выше члена типа string. Определите класс D22,
аналогичный классу D21, за исключением того, что его член имеет тип
int. Определите функцию f() , получающую аргумент типа B2& и вызывающую
функцию pvf() для этого аргумента. Вызовите функцию
f() с аргументами D21 и D22.

*/
class B2
{
public:
	B2() {};
	~B2() {};

	virtual void pvf() = 0; /* чисто виртуальная ф-ия (pure virtual function) */
};

class D21 : public B2
{
public:
	D21() {};
	~D21() {};

	void pvf() override { printCall(QString("D21::pvf() - %1").arg(QString::fromStdString(_s))); };
	std::string _s{ "string" };
};

class D22 : public B2
{
public:
	D22() {};
	~D22() {};

	void pvf() override { printCall(QString("D22::pvf() - %1").arg(QString::number(_s))); };
	int _s{ 5 };
};

inline void callB2(B2 & b)
{
	b.pvf();
}


















}//namespace hw