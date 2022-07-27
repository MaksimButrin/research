#pragma once

#include <iostream>
#include <QVector>
#include <QDebug>
#include "Consts.h"


using namespace std;
using namespace cst;

namespace sv
{


void run();

/* записки про указатели */
void infoPointers();

/* 17. Векторы и динамическое выделение памяти */
/* 17.2. Основы */
class SVector
{
public:
	/* конструктор по умолчанию */
	SVector::SVector() : _sz(0), _elem(nullptr), _space(0) {}
	/* конструктор: размещает в памяти s чисел */
	/* типа double, направляет на них указатель */
	/* elem и сохраняет s в члене _sz, см. использование в explicitConstructors() */
	explicit SVector(int s); // explicit допускает только обычную семантику конструирования	и не допускает неявные преобразования

	// 18.2 Инициализация
	// конструктор со списком инициализации
	// lst передается по значению - требование языка  (Б.6.4)
	SVector(std::initializer_list<double> lst);

	// 18.3.1 копирующие конструкторы
	SVector(const SVector & arg); // копирующий конструктор/конструктор копирования
	// 18.3.2 копирующее присваивание / 19.2.5. Присваивание
	SVector & operator=(const SVector & source);
	// 18.3.4 Перемещение
	// Перемещающий конструктор
	SVector(SVector && a);
	// Перемещающее присваивание
	SVector & operator=(SVector && source); // && - ссылка на rvalue
	//18.5 доступ к элементам вектора
	~SVector();
	// оператор индексирования (operator []()) 
	//double operator[](int n) { return _elem[n]; }; // возвращает ! только значение (не lvalue)
	// * operator[] возвращает указатель,
	// писать можно используя разыменование но *v[i] = x - не красиво
	//double * operator[](int n) { return &_elem[n]; };
	// возвращает ссылку для НЕ Константных векторов
	double & operator[](int n) { return _elem[n]; };  // вот теперь всё хорошо
	// 18.5.1. Константная перегрузка
	// копирует для константных векторов малого размера,
	// double operator[](int n) const { return _elem[n]; };
	// для больших размеров лучше использовать ссылку
	double & operator[](int n) const { return _elem[n]; };

	/* 17.5 деструкторы */

	int size() const { return _sz; };
	/* чтение */
	double get(int n) const;
	/* запись */
	void set(int n, double v);

	/* 19.2.2. Функции reserve и capacity */
	/* добавление памяти для новых элементов */
	bool reserve(int newAlloc);
	int capacity() const { return _space; };
	/* 19.2.3. Функция resize */
	void resize(int newSize);
	/* 19.2.4. Функция push_back */
	void pushBack(double d);
// вспомогательные
public:
	void print() const;

private:
	/* размер */
	int _sz{ 0 };
	/* кол-во элементов плюс "свободное место"/"слоты" для новых элементов (текущий выделенный размер) */
	int _space{ 0 };
	/* указатель на первый элемент (типа double) */
	double * _elem = nullptr;


};

/* 17.7 указатели на объекты класса */
SVector * svPtr(int s);


// 18.4.2 Отладка конструкторов и деструкторов
struct X //простой тестоый класс
{
	int _val;
	void out(const QString & s, int nv)
	{
		qDebug().noquote() << this << QString("->%1: %2 (%3)").arg(s).arg(_val).arg(nv);
	};

	// конструктор по умолчанию
	X() { out("X() ", 0); _val = 0; }
	X(int v) { _val = v; out("X(int) ", v); }
	// копирующий конструктор
	X(const X& x) { _val = x._val; out("X(X&) ", x._val); }
	// копирующее присваивание
	X& operator=(const X& a)
	{
		out("X::operator=() ", a._val);
		_val = a._val; return *this;
	}
	// деструктор
	~X() { out("~X() ", 0); }
};

void testX();

// ===========================================
// палиндром с ипользованием массивов
inline bool isPalindrome(const char s[], int n)
// s указывает на первый символ массива из n символов
{
	// индекс первой буквы
	int first{ 0 };
	// индекс последней буквы
	int last{ n-1 };
	// не достигли серидны
	while (first < last)
	{
		if (s[first] != s[last])
			return false;
		++first; // переход вперед
		--last; // переход назад
	}
	return true;
};

inline istream & readWord(istream & is, char * bufer, int max)
// считывает не более max-1 символов в массиве bufer
{
	// при выполнении следующего оператора >>
	// будет считано не более max-1 символов
	is.width(max);
	// читаем слово, завершающееся пробельным
	// символом, добавляем в конец нулевой указатель
	is >> bufer;

	return is;
};


void testPalindrome();

// ===========================================
class WorkWithSvector
{
public:
	WorkWithSvector();
	~WorkWithSvector();

	void run();

	/* 17.5 деструторы */
	void f3(int n);
	/* 17.6 доступ к элементам */
	void f4(int n);
	/* 17.7 Указатели на объекты класса */
	void ff();
	// 17.8 void* и операторы приведения типа
	void voidAsterisk(void * pv);
	//17.9. Указатели и ссылки ЗАКОНЧИЛ ТУТ
	void ptrAndLink();
	// 18.2 Использование конструктора со списком инициализации
	void usingInitializerList();
	// 18.3 копирование векторов
	// 18.3.1. конструктор копирования
	void copyСonstructor();
	// 18.3.2. копирующее присванивание 
	void copyAssignment();
	// 18.3.4. перемещающее присванивание 
	void movingAssignment();
	SVector fill(std::istream & is);
	// 18.4.1 Явные конструкторы
	void explicitConstructors();
	// 18.4.2 смотри в struct X
	// 18.5 доступ к элементам вектора
	void simpleAccess();
private:

};



// 17.9.2. Указатели, ссылки и наследование
// 17.9.3. Пример: списки

/* двусвязный узел в списке */
struct MLink0
{
	QString _value;
	MLink0 *_prev;
	MLink0 *_succ;
	MLink0(const QString & v, MLink0 * p = nullptr, MLink0 * s = nullptr)
		: _value(v), _prev(p), _succ(s) {}
};

/* двусвязный узел в списке */
/* 17.10 указатель this */
class MLink1
{
public:
	MLink1(const QString & v, MLink1 * p = nullptr, MLink1 * s = nullptr)
		: _value(v), _prev(p), _succ(s) {}

	MLink1 * insert(MLink1 * n);
	MLink1 * add(MLink1 * n);
	MLink1 * erase();
	MLink1 * find(const QString & s);
	// поиска в константном списке (см. раздел 18.5.1)
	const MLink0 * find(const QString & s) const { return nullptr; };
	MLink1 * advance(int n);

	MLink1* next() const { return _succ; };
	MLink1* previous() const { return _prev; };

	QString _value;
private:
	MLink1 *_prev;
	MLink1 *_succ;
};

// 17.9.4. Операции над списками
class MList
{
public:
	MList();
	~MList();
	
	//MList(MLink *p);
	
	// вставка перед элементом: вставка 'n' после 'p'; возрат 'n'
	MLink0 * insert(MLink0 *p, MLink0 * n);
	// вставка после элемента: вставка 'n' после 'p'; возрат 'n'
	MLink0 * add(MLink0 *p, MLink0 * n);
	// удаление элемента: удаление '*p' из списка; возврат приемника 'p'
	MLink0 * erase(MLink0 *p);
	// поиск узла с заданным значением: поиск 's' в списке; возврат nullptr, если не найден
	MLink0 * find(MLink0 *p, const QString & s);
	// переход к n-му последующему узлу: Переход на 'n' позиций в списке
	// Возвращает nullptr , если это невозможно
	// Положительное 'n' - движение вперед; отрицательное - назад
	MLink0 * advance(MLink0 *p, int n);
	// 
	void print(MLink0 * p);
	void print(MLink1 * p);
private:
	//MLink * _p;
};



struct WorkWithAnother
{
	void run();

	// 17.9.3. Пример: списки
	void doubleLinkedList0();
	// 17.9.5. Использование списков
	void doubleLinkedList1();	
	// 17.10. Указатель this
	void doubleLinkedList2();
};


// =================================================
/* вывести размеры типов */
void printSizes();

inline void printName(const QString & name)
{
	qDebug().noquote() << QString("%1 %2 %3").arg(SEPARATOR_MINI, name, SEPARATOR_MINI);
}

/* === Эксперименты над ссылками === */
/* впервые работы над ссылками в стр. 326 */
class TestLink2
{
public:
	TestLink2();
	~TestLink2();
	void run();
private:
	void init(QVector<QVector<int>> &v);
	void print(const QVector<QVector<int>> &v);
	void changeValueByUsingLink(QVector<QVector<int>> &v);
	void changeLineByUsingLink(QVector<QVector<int>> &v);
	/* вектор векторов double */
	QVector<QVector<int>> _v;
};
}
