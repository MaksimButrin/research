#include <iostream>
#include <QString>
#include <QVector>
#include "Consts.h"

using namespace std;
using namespace cst;

/* 9.4.1 Структура и функции */
class Chapter9dot04
{
public:
	Chapter9dot04() {};
	~Chapter9dot04() {};
	
	/* 9.4.2. */
	/* простая структура Date */
	/* гарантирующая инициализацию с помощью конструктора */
	/* и обеспечивающая удобство создания */
	struct MDateStruct
	{
		/* год, месяц, день */
		int _y, _m, _d;  // открыты и это неправильно
		MDateStruct(int y, int m, int d) {}; /* проверяем корректность даты и выполняем инициализацию */
		
		// увеличивает объект dd на n Дней
		void addDay(MDateStruct & dd, int n) {};
	};

	/* вспомогательные ф-ии: плохой вариант, лучше встроеные ф-ии */
	//void initDay(MDate & dd, int y, int m, int d)
	//{
	//	// Проверяет, является ли(y, m, d) правильной датой,
	//	// и, если является, то инициализирует объект dd
	//};

	// простой тип Date(управляемый доступ)
	class MDateClass
	{
		/* год, месяц, день */
		int _y, _m, _d; // скрыты, т.к. необходмо изменить дату без проверок
	
	public:
		/* проверяем корректность даты и выполняем инициализацию */
		MDateClass(int y, int m, int d) {}; 
		// увеличивает объект dd на n Дней
		void addDay(MDateStruct & dd, int n) {};
		// управляемый доступ к членам класса
		int year() { return _y; }
		int month() { return _m; }
		int day() { return _d; }
	};

	void init()
	{
		// ок: старый краткий стиль
		MDateStruct _last2(2007, 12, 24);
		++_last2._d; /* меняем без проверки - это плохо */
	}

private:
	/* использование конструктора для инициализации: */
	// ошибка компиляции: объект не инициализирован
	//MDate _myBirthday; 
	// ошибка времени выполнения (зеркально не правильный порядок аргументов)
	MDateStruct _today{24,12,2007};
	// ок: краткий стиль
	MDateStruct _last1{ 2007,12, 24 };
	// ок: старый краткий стиль (почему-то не работает в private/public), а только в методе (см. выше init)
	// MDate _last3(2007,12, 24);	
	// ок: немного более многословно
	MDateStruct _next = { 2008,11, 23 };
	// Ok (современный стиль списка инициализации)
	int _xs { 7 } ;
	// ок: многословный стиль (явное создание объекта MDate, и инициализация им _christmas с помощью синтаксиса инициализации '=')
	MDateStruct _christmas = MDateStruct { 2008,12, 24 };
};

/* 9.4.4 */
class MDate
{
public:
	/* проверка и инициализация даты */
	MDate(int yy, int mm, int dd);
	// увеличение Date на n Дней
	void addDay(int n);
	// Определения коротких и простых функций можно размещать
	// в объявлении класса
	/*
	Особенность: не размещайте тела функций-членов в
	объявлении класса, если вам не нужна повышенная эффективность
	программы за счет использования небольших встраиваемых
	функций
	*/
	int year() { return _y; }
	int month() { return _m; }
	int day() { return _d; }

private:
	/* год, месяц, день */
	int _y, _m, _d;

};


/* 9.4.5 Ссылка на текущий объект */
void UsingMDateFoo1(MDate d1, MDate d2);

class MYear
{
	/*
	Использование модификатора static по отношению к члену класса гарантирует, что в программе
	сушествует только одна копия его значения, а не по одной копии на каждый
	объект данного класса.
	*/
	static const int MIN{ 1800 };
	static const int MAX{ 2200 };

public:
	/* при вызове с ошибочными параметрами будет сформирована (throw) Ошибка времени выполнения */
	class  Invalid {}; 
	/* если не указать = MIN, то будет ошибка отсутствия конструктора по умолчанию */
	MYear(int y = MIN); 
	~MYear() {};
	int year() { return _y; };

private:
	int _y{ MIN };
};

enum class MMonth 
{
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class MDate2
{
public:
	MDate2();
	MDate2(MYear yy, MMonth mm, int dd) {};

	const MDate2 & defaultDate();

	MYear year() const { return _y; }
	MMonth month() const { return _m; }
	int day() const { return _d; }
private:
	MYear _y;
	MMonth _m;
	int _d{1};
};

