#include "Inheritance.h"

#include <QSharedPointer>


namespace inh
{


void run()
{
	//virtFunc01();
	//virtFunc02();
	virtFunc04();
}



void virtFunc01()
{
	/*
		Виртуальная функция — это функция, которая определяется в базовом классе,
		а любой порожденный класс может ее переопределить.
		Виртуальная функция вызывается только через указатель или ссылку на базовый класс.
	*/

	X x;
	X *px = &x;  // Указатель на базовый класс
	Y y;
	x.seti(10);
	y.seti(15);

	px->print();  // класс X: 10
	px = &y;
	px->print();  // класс Y: 15
	cin.get();
}

void virtFunc02()
{
	{
		Child01 *child = new Child01(7);
		Parent01 * parent = child;
		delete parent;
	}
	
	qDebug().noquote() << SEPARATOR;

	{
		Child02 *child = new Child02(7);
		Parent02 * parent = child;
		delete parent;
	}

	qDebug().noquote() << SEPARATOR;

	{
		/*
			Здесь мы хотим, чтобы ссылка класса Parent на объект класса Child вызывала Parent::getName() вместо Child::getName(). Чтобы это сделать, нужно просто использовать оператор разрешения области видимости
		*/
		Child03 child;
		Parent03 & parent = child;
		// по умолчанию будет вызван Child::GetName()
		qDebug().noquote() << "parent.getName = " << parent.getName();
		// Вызов Parent::GetName() вместо переопределения Child::GetName()
		// !!! Используется редко
		qDebug().noquote() << "parent.Parent03::getName = " << parent.Parent03::getName();
	}

}

void virtFunc04()
{
	B04 b;
	D04 d;
	DD04 dd;

	qDebug().noquote() << SEPARATOR_MINI << "call04(b)" << SEPARATOR_MINI;
	call04(b);

	qDebug().noquote() << SEPARATOR_MINI << "call04(d)" << SEPARATOR_MINI;
	call04(d);
	
	qDebug().noquote() << SEPARATOR_MINI << "call04(dd)" << SEPARATOR_MINI;
	call04(dd);
	
	qDebug().noquote() << SEPARATOR;

	qDebug().noquote() << SEPARATOR_MINI << "b.f(); b.g();" << SEPARATOR_MINI;
	b.f();
	b.g();	
	
	qDebug().noquote() << SEPARATOR_MINI << "d.f(); d.g();" << SEPARATOR_MINI;
	d.f();
	d.g();

	qDebug().noquote() << SEPARATOR_MINI << "dd.f(); dd.g();" << SEPARATOR_MINI;
	dd.f();
	dd.g();

	/* private наледование (защита от внешнего доступа), т.е. вы объявляется наследуемую часть как private */
	C04 c;
	c.f(); /* обратится можно */
	//c.g(); /* нет доступа т.к. обратится можно только через тело наследника */

	E04 e;
	e.f(); /* обратится можно */
	e.g(); /* теперь обратится можно т.к. virtFunc04 является friend у E04 */

	qDebug().noquote() << SEPARATOR_MINI << "s.f(); s.Mom04::f();" << SEPARATOR_MINI;

	Son04 s;
	// будет вызвана версия сына
	s.f();
	// для явнового вызова версия мамы нужно писать с обращением к родителю
	s.Mom04::f(); /* !!! причём, автоподстановка не работает  */
	Son0401 s1;
	//s1.f(); 
	/* ошибка компиляции, потому что доступность проверяется после разрешения перегрузки и выбора версии и уж точно после выбора видимой переменной 
	кратко: f() не видна из данного места, проверка доступности проиходит после определения версии при наследовании
	
	версия Mom04::f() доступны но из Son0401 не видны, 
	а версия Son0401::f() видны из Son0401 но не доступны
	*/

	/* выбор происходит также до выполнения перегрузки, то есть при таком варианте */
	s.g(0.0); /* произойдет выбор Son04::g(int), если не использовать usin Mom04:g; 
			, потому произойдет привдеение типов, потому что версии g() в сыне затмевают версии мамы,
			и выбор кандидатов происходит до разрешения перегрузки 
			usin Mom04:g; - тут g именно метод, нельзя использовать член класса (компилятор выдаст ошибку компиляции), 
			и метод Mom04 должен быть не с такой же сигнатурой как в Son04 (компилятор об этом даже не кашлянёт, просто выберет версию Son) */




	/* ??? До конца не понятно !!! */

	// Calling: virtual B04::f()
	// Calling: not virtual B04::g()
	// =================== call04(d) ===================
	// Calling: override D04::f()
	// Calling: not virtual B04::g()
	// =================== call04(dd) ===================
	// Calling: override D04::f()
	// Calling: not virtual B04::g()
	// ===============================================
	// =================== b.f(); b.g(); ===================
	// Calling: virtual B04::f()
	// Calling: not virtual B04::g()
	// =================== d.f(); d.g(); ===================
	// Calling: override D04::f()
	// Calling: D04::g()
	// =================== dd.f(); dd.g(); ===================
	// Calling: DD04::f()
	// Calling: DD04::g()
}












}//namespace inh
