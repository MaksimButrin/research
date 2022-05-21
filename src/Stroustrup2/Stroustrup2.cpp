#include <Stroustrup2.h>
#include <QDebug>
#include <QSharedPointer>

const QString SEPARATOR{ "===============================================" };
const QString SEPARATOR_MINI{ "===================" };

void run()
{
	//SVector v(5);

	//char c = 97;
	//qDebug() << c;;
	//qDebug() << static_cast<int>(c);
	TestLink2 tl1();
	TestLink2 tl2;
	TestLink2 tl3{};

	tl3.run();
}

/* записки про указатели */
void infoPointers()
{
	/* стр ...650... */
	/* оператор new делает доступной динамическую память (которую ещё называют КУЧЕй) */
	/* а память выделяемая для использования при вызове ф-ии для хранения ее аргументов и лок. пер. - СТЭКОМ */
	/* в данном случае инструкция просит систему поддержки выполнения программ резместить четыре числа типа double */
	/* в ДИНАМИЧЕСКОЙ памяти (куче) и вернуть указательна первое из них */
	double *p = new double[4]; /* размещаем 4ре числа в куче (динамической памяти) */
	/* количество элментов может в данном случае задаваться переменной */
	int n{ 5 };
	double *pd = new double[n];
	/* разрешение присваивания друг другу указателей разных типов привело бы */
	/* к TYPE ERROR - ошибкам типов */

	/* ИНИЦИАЛИЗАЦИЯ */
	/* обявлять указатели без инициализации ОПАСНО */
	/* если указано кол-во инициализированных элементов */
	int *p1 = new int[4]{ 0,1,2 };
	/* как здесь, то размер массива указывать не обязательно */
	/* НО в моем компиляторе - ОШИБКА */
	// int *p2 = new int[] { 0, 1, 2, 4 };
	SVector *sv = new SVector(5);

	//QSharedPointer<SVector> shp1 = QSharedPointer<SVector>::create(5);
	//QSharedPointer<SVector> shp2 = QSharedPointer<SVector>(new SVector(5));
	//QSharedPointer<SVector> shp3(new SVector(5));

}

/* 17. Векторы и динамическое выделение памяти */
/* 17.2. Основы */
SVector::SVector(int s) :
	/* инициализация члена _sz */
	_sz(s),
	/* инициализация члена _elem */
	_elem{ new double[s] }
{
	/* инициализация элементов */
	for (int i = 0; i < s; i++)
	{
		_elem[i] = 0;
	}
	// printSizes();
}

SVector::~SVector()
{
	/* освобождение памяти выделенной с помощью оператора new для массива объектов */
	delete[] _elem;
	/* delete без [] - освобождает память выделенную с помощью оператора new для отдельного объекта */
	double * p = new double(8.8);
	delete p;
}

void SVector::printSizes()
{
	qDebug().noquote() << SEPARATOR;
	char ch;
	int i;
	int * pi;

	qDebug().noquote() << QString("size of 'char': ") << sizeof(ch);
	qDebug().noquote() << QString("size of 'i': ") << sizeof(i);
	qDebug().noquote() << QString("size of 'pi': ") << sizeof(pi);
}


WorkWithSvector::WorkWithSvector()
{



	run();
}


WorkWithSvector::~WorkWithSvector()
{
}

void WorkWithSvector::run()
{
	f3(5);
}


void WorkWithSvector::f3(int n)
{
	/* выделяем память для n чисел типа double */
	double*p = new double[n];
	/* определяем вектор (выделяем память для n других double) */
	SVector v(n);
	
	/* используем 'v' и 'p' */
	/* .... */

	/* освобождаем паять, занятую массивом чисел типа double */
	delete[] p;

} // SVector автоматически освободит память, занятую объектом 'v'.



TestLink2::TestLink2()
{
	
}

TestLink2::~TestLink2()
{
}

void TestLink2::run()
{
	init(_v);
	print(_v);

	changeValueByUsingLink(_v);
	qDebug().noquote() << SEPARATOR;
	print(_v);

	changeLineByUsingLink(_v);
	qDebug().noquote() << SEPARATOR;
	print(_v);
}

void TestLink2::init(QVector<QVector<int>> &v)
{
	int height{ 6 };
	int width{ 5 };

	for (int h = 0; h < height; h++)
	{
		QVector<int> wv;
		for (int w = 0; w < width; w++)
		{
			wv.append(h * 10 + w);
		}

		v.append(wv);
	}

}

void TestLink2::print(const QVector<QVector<int>>& v)
{
	for (int h = 0; h < v.size(); h++)
	{
		QStringList line;
		for (int w = 0; w < v[h].size(); w++)
		{
			line << QString("\t[%1][%2] = %3").arg(QString::number(h)).arg(QString::number(w)).arg(QString::number(v[h][w]));
		}
		qDebug().noquote() << line.join(";");
	}
}

void TestLink2::changeValueByUsingLink(QVector<QVector<int>> &v)
{
	int h{ 3 };
	int w{ 3 };
	/* ссылка на элемент v[h][w] */
	int & var = v[w][h]; //ключевое свойство ссылок - ссылка может служить "аббревиатурой" объекта.
	var = 99;

}

void TestLink2::changeLineByUsingLink(QVector<QVector<int>>& v)
{
	int h{ 4 };
	/* ссылка на элемент v[h][w] */
	auto & line = v[h];
	for (int w = 0; w < line.size(); w++)
	{
		line[w] = line[w] * 2;
	}
}

//TestLink::TestLink()
//{
//}
//
//TestLink::~TestLink()
//{
//}
//
//
//inline void TestLink::printXx()
//{
//}
//
//inline void TestLink::setLinkVal(int & x)
//{
//&_xxLink = x;
//}