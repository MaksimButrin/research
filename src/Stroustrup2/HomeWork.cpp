#include "HomeWork.h"


namespace hw
{
void run()
{
	ch14Task01();
}



void ch14Task01()
{
	qDebug().noquote() << SEPARATOR_MINI << "1" << SEPARATOR_MINI;
	/*  Создайте объект B1 и вызовите каждую из функций */
	B1 b1;
	b1.vf();
	b1.f();

	qDebug().noquote() << SEPARATOR_MINI << "2" << SEPARATOR_MINI;

	/* Создайте объект класса D1 и вызовите из него функции vf() и f() */
	D1 d1;
	d1.vf();
	d1.f();

	qDebug().noquote() << SEPARATOR_MINI << "3" << SEPARATOR_MINI;

	/* Определите ссылку на объект класса 81 (т.е . B1&) и инициализируйте
	ее только что созданным объектом класса Dl . Вызовите функции vf()
	и f() с помощью этой ссылки */
	B1 & lb1 = d1;

	lb1.vf();
	lb1.f();

	// Calling: D1::vf()
	// Calling: B1::f()

	qDebug().noquote() << SEPARATOR_MINI << "4" << SEPARATOR_MINI;

	D11 d11;
	d11.vf();
	d11.f();

	qDebug().noquote() << SEPARATOR_MINI;

	B1 & lb11 = d11;

	lb11.vf();
	lb11.f();
	/* Почему ? = lb1 */
	// Calling: D11::vf()
	// Calling: B1::f()

	qDebug().noquote() << SEPARATOR_MINI << "6" << SEPARATOR_MINI;
	D2 d2;
	d2.vf();
	d2.f();
	d2.pvf();

	qDebug().noquote() << SEPARATOR_MINI << "7" << SEPARATOR_MINI;
	D21 d21;
	D22 d22;
	callB2(d21);
	callB2(d22);

}




}//namespace hw