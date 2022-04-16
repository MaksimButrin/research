#include <iostream>
#include <QString>
#include <QPair>
#include <QList>
#include <QSharedPointer>
#include <QStack>
#include <QQueue>

void init();

class timopheyOOPLecture03Ex01
{
public:
	timopheyOOPLecture03Ex01();
	~timopheyOOPLecture03Ex01();

	void count2(int n = 0);
	void temporary();

private:

};


class timopheyOOPLecture04Ex01
{
public:
	timopheyOOPLecture04Ex01();
	~timopheyOOPLecture04Ex01();

	struct student
	{
		int8_t age{ 0 };
		int16_t group{ 0 };
		QString name{ "noname" };
	};

	void studentPrint(const student & s);
	void studentPrint(const student * s);
	void arrayPrint01(double arr[][4]); //must necessarily specify the number of columns
	void arrayPrint02(double **arr, const int h = 0, const int w = 0); // print double array

	void trash01(); /* new delete pointers */
	void trash02(); /* using of constant links and pointers */
	void trash03();
	void trash04(); /* static/automatic arrays */
	void trash05(); /* dinamic arrays */
	void trash06(); /* true dinamic arrays */
	void temporary();
	double foo01(const double &x);

private:

};

/* алгоритмы и структуры данных */
/* лекция 2 */
class ADSLecture02Ex01
{
public:
	ADSLecture02Ex01() {};
	~ADSLecture02Ex01() {};

	/* битовые операции */
	void bitOperations();
	void run();
	QString byteToString(int x, bool nubbles = true);
	void binPrintInt(int x, bool nubbles = true);
	/* Простые числа: Решето Эратосфена*/
	QList<int> simpleNumbersSeparator();
	/* Простые множители: Решето Эратосфена*/
	void simpleFactors(int & number);
	void sf();
private:
};

/* алгоритмы и структуры данных */
/* лекция 5 */
class ADSLecture05Ex01
{
public:
	ADSLecture05Ex01() {};
	~ADSLecture05Ex01() {};

	void run();

	/* инвертирование массива */
	void arrayReverse();

	/* расширение массива */
	void arrayAppend();

	/* стэк: append и pop */
	void stack();

	/* скобки. Прорешать */
	void stackBraces();
	/* Сортировка вставками. Прорешать */
	void insertSorting();

	/* простая сортировка и введение в сортировку */
	void arraySorting();

	/* пузырьковая сортировка */
	void bubbleSorting();
};

/* алгоритмы и структуры данных */
/* лекция 6-7 */
class ADSLecture06Ex01
{
public:
	ADSLecture06Ex01() {};
	~ADSLecture06Ex01() {};

	void run();

	/* указатели на указатели */
	void pointerOnPointer(); /* нигде не вызывается */

	/* звено */
	struct NodeT
	{
		int data; /* данные (конфета)*/
		NodeT * next; /* адрес на эти данные (записка, где искать конфету */
	};

	void goThrough(NodeT * pBegin);


	/* генерация связного списка */
	/* связный список - огранизация данных таким образом  */
	void generateNodes();
	/* выделение памяти */
	void generateNodesUnlim();

	/* двумерные массивы */
	void arrays2d();
	/* 2d массивы и передача их для печати */
	/* ВАЖНО: если не указать ширину массива то будет выдано сообщение
	для мультиразмерных массивов необходимо укахать границы для измерений за исключением первого
	(multidimensional array must have bounds for all dimensions exept the 1st
	например так:
	const MAX_SIZE{10};
	void array2dPrint(int arrayOrigin[][MAX_SIZE], const int arraySize, const int columns);
	НО! получаем ограние на максимальную ширину
	выход - передавать указатель на начало массива
	*/
	void array2dPrint(int *p, const int arraySize, const int columns);
	void arrays2dAndPrint();

	/* динамические двумерные массивы */
	void dinamicArrays2d();
};


/* алгоритмы и структуры данных */
/* лекция 8 - Поиск в массиве */
/* лекция 9 - ... */

class ADSLecture07Ex01
{
public:
	ADSLecture07Ex01() {};
	~ADSLecture07Ex01() {};

	void run();

	void search();

	/* самый простой это линейный поиск, перебираем от начала до конца. асимптотика O(N)*/
	/* оптимален для поиска в несортированных массивах, если нужно просто найти элемент не делая поиск куда вставлять */
	int linearSearch(int A[], int arraySize, int x);

	/* бинарынй поиск. . асимптотика O(2 log n) - количество срабатываний будет равно - log по основанию 2 от N
	в общем случае это наилучшая скорость поиска, но существует структура данных которая работает быстрее (??? позже)
	*/
	/* на каждом шаге множество объектов делится на две части и в
	работе остаётся та часть множества, где находится искомый объект */
	/* поиск левой границы - для вставки перед  */
	int leftBound(int A[], int arraySize, int x);
	int binarySearch(int A[], int arraySize, int x);
	/* сортировка подсчетом */
	void countSortStart();
	void randomArray(int A[], int arraySize, int m);
	void printArray(int A[], int arraySize);
	void countSort(int A[], int arraySize);
};

/* алгоритмы и структуры данных */
/* лекция 10 - Рекурсия */

class ADSLecture09Ex01
{
public:
	ADSLecture09Ex01() {};
	~ADSLecture09Ex01() {};

	void run();
	/* факториал числа */
	void getFactorial();
	uint64_t factorial(uint16_t n); /* не вызывать саму себя */

	/* тест таймеров (не в рамках лекции) */
	void timersTest();
	/* тест работы с указателями */
	struct Ts
	{
		bool switcher{ true };
		QPair<int, int> pair01{ 1,2 };
	};

	Ts _testStruct;
	void testPointers();

	/* наибольший общий делитель. Алгоритм евклида */
	void getGcd();
	int gcd(int a, int b);
	/* Ханойские башни */
	void callHanoi();
	void hanoi(int cl, int cr, int cnt); /* перекладывание со столбца 'cl' на 'cr' пирамиды высостой 'cnt' */
};

/* вопрос на собесе */
class Test
{
public:
	Test() {};
	~Test() {};

	void run();
private:

};
