#include <iostream>
#include <QString>
#include <QVector>

using namespace std;

void run();

/* записки про указатели */
void infoPointers();

/* 17. Векторы и динамическое выделение памяти */
/* 17.2. Основы */
class SVector
{
public:
	/* конструктор: размещает в памяти s чисел */
	/* типа double, направляет на них указатель */
	/* elem и сохраняет s в члене _sz */
	SVector(int s);

	/* 17.5 деструторы */
	~SVector();

	int size() const { return _sz; };
	void printSizes();
private:
	/* размер */
	int _sz{ 0 };
	/* указатель на первый элемент (типа double) */
	double * _elem;


};



class WorkWithSvector
{
public:
	WorkWithSvector();
	~WorkWithSvector();

	void run();
	/* 17.5 деструторы */
	void f3(int n);

private:

};


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



//class TestLink
//{
//public:
//	TestLink();
//	~TestLink();
//	void setLinkVal(int & x);
//	void printXx();
//private:
//	int _xx{ -1 };
//	/* так нельзя - нужна инициализация. почему? */
//	//int & _xxLink;
//	int _xxLink;
//};