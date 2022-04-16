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

/* ��������� � ��������� ������ */
/* ������ 2 */
class ADSLecture02Ex01
{
public:
	ADSLecture02Ex01() {};
	~ADSLecture02Ex01() {};

	/* ������� �������� */
	void bitOperations();
	void run();
	QString byteToString(int x, bool nubbles = true);
	void binPrintInt(int x, bool nubbles = true);
	/* ������� �����: ������ ����������*/
	QList<int> simpleNumbersSeparator();
	/* ������� ���������: ������ ����������*/
	void simpleFactors(int & number);
	void sf();
private:
};

/* ��������� � ��������� ������ */
/* ������ 5 */
class ADSLecture05Ex01
{
public:
	ADSLecture05Ex01() {};
	~ADSLecture05Ex01() {};

	void run();

	/* �������������� ������� */
	void arrayReverse();

	/* ���������� ������� */
	void arrayAppend();

	/* ����: append � pop */
	void stack();

	/* ������. ��������� */
	void stackBraces();
	/* ���������� ���������. ��������� */
	void insertSorting();

	/* ������� ���������� � �������� � ���������� */
	void arraySorting();

	/* ����������� ���������� */
	void bubbleSorting();
};

/* ��������� � ��������� ������ */
/* ������ 6-7 */
class ADSLecture06Ex01
{
public:
	ADSLecture06Ex01() {};
	~ADSLecture06Ex01() {};

	void run();

	/* ��������� �� ��������� */
	void pointerOnPointer(); /* ����� �� ���������� */

	/* ����� */
	struct NodeT
	{
		int data; /* ������ (�������)*/
		NodeT * next; /* ����� �� ��� ������ (�������, ��� ������ ������� */
	};

	void goThrough(NodeT * pBegin);


	/* ��������� �������� ������ */
	/* ������� ������ - ����������� ������ ����� �������  */
	void generateNodes();
	/* ��������� ������ */
	void generateNodesUnlim();

	/* ��������� ������� */
	void arrays2d();
	/* 2d ������� � �������� �� ��� ������ */
	/* �����: ���� �� ������� ������ ������� �� ����� ������ ���������
	��� ��������������� �������� ���������� ������� ������� ��� ��������� �� ����������� �������
	(multidimensional array must have bounds for all dimensions exept the 1st
	�������� ���:
	const MAX_SIZE{10};
	void array2dPrint(int arrayOrigin[][MAX_SIZE], const int arraySize, const int columns);
	��! �������� ������� �� ������������ ������
	����� - ���������� ��������� �� ������ �������
	*/
	void array2dPrint(int *p, const int arraySize, const int columns);
	void arrays2dAndPrint();

	/* ������������ ��������� ������� */
	void dinamicArrays2d();
};


/* ��������� � ��������� ������ */
/* ������ 8 - ����� � ������� */
/* ������ 9 - ... */

class ADSLecture07Ex01
{
public:
	ADSLecture07Ex01() {};
	~ADSLecture07Ex01() {};

	void run();

	void search();

	/* ����� ������� ��� �������� �����, ���������� �� ������ �� �����. ����������� O(N)*/
	/* ��������� ��� ������ � ��������������� ��������, ���� ����� ������ ����� ������� �� ����� ����� ���� ��������� */
	int linearSearch(int A[], int arraySize, int x);

	/* �������� �����. . ����������� O(2 log n) - ���������� ������������ ����� ����� - log �� ��������� 2 �� N
	� ����� ������ ��� ��������� �������� ������, �� ���������� ��������� ������ ������� �������� ������� (??? �����)
	*/
	/* �� ������ ���� ��������� �������� ������� �� ��� ����� � �
	������ ������� �� ����� ���������, ��� ��������� ������� ������ */
	/* ����� ����� ������� - ��� ������� �����  */
	int leftBound(int A[], int arraySize, int x);
	int binarySearch(int A[], int arraySize, int x);
	/* ���������� ��������� */
	void countSortStart();
	void randomArray(int A[], int arraySize, int m);
	void printArray(int A[], int arraySize);
	void countSort(int A[], int arraySize);
};

/* ��������� � ��������� ������ */
/* ������ 10 - �������� */

class ADSLecture09Ex01
{
public:
	ADSLecture09Ex01() {};
	~ADSLecture09Ex01() {};

	void run();
	/* ��������� ����� */
	void getFactorial();
	uint64_t factorial(uint16_t n); /* �� �������� ���� ���� */

	/* ���� �������� (�� � ������ ������) */
	void timersTest();
	/* ���� ������ � ����������� */
	struct Ts
	{
		bool switcher{ true };
		QPair<int, int> pair01{ 1,2 };
	};

	Ts _testStruct;
	void testPointers();

	/* ���������� ����� ��������. �������� ������� */
	void getGcd();
	int gcd(int a, int b);
	/* ��������� ����� */
	void callHanoi();
	void hanoi(int cl, int cr, int cnt); /* �������������� �� ������� 'cl' �� 'cr' �������� �������� 'cnt' */
};

/* ������ �� ������ */
class Test
{
public:
	Test() {};
	~Test() {};

	void run();
private:

};
