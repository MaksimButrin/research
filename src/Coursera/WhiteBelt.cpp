#include "WhiteBelt.h"
#include <QDebug>
#include <list>



/* weak 4 lesson 3*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>

const QString SEPARATOR{ "===============================================" };
const QString SEPARATOR_MINI{ "===================" };


using namespace std;


void myMessageOutput(QtMsgType type, const char *msg)
{
	switch (type) {
	case QtInfoMsg:
		fprintf(stdin, "%s", msg);
		break;
	case QtDebugMsg:
		fprintf(stderr, "Debug: %s\n", msg);
		break;
	case QtWarningMsg:
		fprintf(stderr, "Warning: %s\n", msg);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "Critical: %s\n", msg);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s\n", msg);
		abort();
	}
}



WhiteBelt::WhiteBelt()
{
}


WhiteBelt::~WhiteBelt()
{
}

void WhiteBelt::runWhiteBelt()
{
	//Predicates().run();
	MftiLessons().run();
}







weak4Lesson01::weak4Lesson01()
{
}



weak4Lesson01::~weak4Lesson01()
{
}

void weak4Lesson01::run()
{

	/* именно использование explicit не дает возможности неявно приеобразовать целые числа в объекты типа Day, Month, Year  */
	/* таким образом нижеследующий код не будет работать, и плюс необходимо явно указать к какому типу предобразовываем путем вызова конструктора */
	//Date data02 = { {28}, {2}, {1982} };
	//printDate(data02);
	/* вызов так */
	Date data01 = { Day{28}, Month{2}, Year{1982} };
	printDate(data01);
	/* либо так */
	Date data02 = { Day(28), Month(2), Year(2015) };
	printDate(data02);

	/* итоги: с помощью механизма контруктора и использования explicit мы создаем более прозрачный способ создания */


}



inline void weak4Lesson01::printDate(const Date & date) const
{
	qDebug().noquote() << QString("%1.%2.%3").arg(date.day).arg(date.month).arg(date.year);
}



double weak4Lesson02::computeImageWeight(const Params & params, const Image & image)
{
	Function func = makeWeightFunction(params, image);

	return func.apply(image.quality);
}

double weak4Lesson02::computeQualityByWeight(const Params & params, const Image & image, double weight)
{
	Function func = makeWeightFunction(params, image);
	func.invert();
	return func.apply(weight);
}

void weak4Lesson02::run()
{
	Image image = { 10, 2, 6 };
	Params params = { 4,2,6 };

	// 10 - 2 * 4 - 2 + 6 * 6 = 36
	qDebug().noquote() << computeImageWeight(params, image);

	// 20 - 2 * 4 - 2 + 6 * 6 = 46
	qDebug().noquote() << computeQualityByWeight(params, image, 46);
}

FunctionPart::FunctionPart(char nOperation, double nValue) :
	_operation{ nOperation },
	_value{ nValue }
{
}

void weak4Lesson03::printTheFileHello(const QString & fileFath) const
{
	ifstream input(fileFath.toStdString());
	string line;
	if (input.is_open())
	{
		qDebug().noquote() << QString("Opening file %1").arg(fileFath);
		while (getline(input, line))
		{
			qDebug().noquote() << QString::fromStdString(line);
		}
	}
	else
	{
		qDebug().noquote() << "File not exist";
	}
}




void weak4Lesson03::printTheFileDate(const QString & fileFath) const
{

	{

		ifstream input(fileFath.toStdString());

		if (input.is_open())
		{
			qDebug().noquote() << QString("Opening file %1").arg(fileFath);
			string year;
			string month;
			string day;

			getline(input, year, '-');
			getline(input, month, '-');
			getline(input, day, '-');
			qDebug().noquote() << QString::fromStdString(year)
				<< QString::fromStdString(month)
				<< QString::fromStdString(day);
		}
		else
		{
			qDebug().noquote() << "File not exist";
		}
	}

	{

		ifstream input(fileFath.toStdString());

		if (input)
		{
			qDebug().noquote() << QString("Opening file %1").arg(fileFath);
			int year;
			int month;
			int day;

			input >> year;
			input.ignore(1); // игнорировать 1 символ
			input >> month;
			input.ignore(1); // игнорировать 1 символ
			input >> day;
			qDebug().noquote() << QString::number(year)
				<< QString::number(month) // если не ипользовать number, будет выведен символ с данным кодом
				<< QString::number(day);

			qDebug().noquote() << QString(year)
				<< QString(month) // если не ипользовать number, будет выведен символ с данным кодом
				<< QString(day);
		}
		else
		{
			qDebug().noquote() << "File not exist";
		}
	}

}

void customHandler(QtMsgType type, const char* msg) {
	fprintf(stderr, msg);
	fflush(stderr);
}


void weak4Lesson03::run()
{
	printTheFileDate(QString("D:\\00 Work\\Book\\!C++ Books\\Teaching\\TeachingSolution\\src\\Coursera\\anyTrash\\weak4Lesson03-date.txt"));
	printTheFileHello(QString("D:\\00 Work\\Book\\!C++ Books\\Teaching\\TeachingSolution\\src\\Coursera\\anyTrash\\weak4Lesson03-hello.txt"));

}

void weak4Lesson04::printInFile(const QString & fileFath) const
{
	QVector<QString> names{ "a","b","c" };
	QVector<double> values{ 5, 0.01, 0.00005 };
	QDebug deb = qDebug();

	for (const auto & n : names)
	{
		deb << n;
	}

	qDebug().noquote() << "\n";

	for (const auto & v : values)
	{
		qDebug().noquote().nospace() << QString::number(v).toStdString().c_str();
	}


}

void weak4Lesson04::run()
{
	printInFile();

}



void Ravesli85::run()
{


}

QList<QString> Predicates::listInit() const
{
	QList<QString> dateAndTimeList;

	dateAndTimeList << QString("2021-11-26 19:07:23.957");
	dateAndTimeList << QString("2021-11-26 19:07:23.957");
	dateAndTimeList << QString("2021-11-26 19:07:23.957");
	dateAndTimeList << QString("2021-11-26 19:07:23.956");
	dateAndTimeList << QString("2021-11-26 19:07:23.956");
	dateAndTimeList << QString("2021-11-26 18:54:54.904");
	dateAndTimeList << QString("2021-11-26 18:54:54.903");
	dateAndTimeList << QString("2021-11-26 18:54:53.904");
	dateAndTimeList << QString("2021-11-26 18:54:53.904");
	dateAndTimeList << QString("2021-11-26 18:54:44.179");
	dateAndTimeList << QString("2021-11-26 18:54:44.179");
	dateAndTimeList << QString("2021-11-26 18:54:18.237");
	dateAndTimeList << QString("2021-11-26 18:54:18.237");
	dateAndTimeList << QString("2021-11-26 18:50:32.993");
	dateAndTimeList << QString("2021-11-26 18:50:32.993");
	dateAndTimeList << QString("2021-11-26 18:50:32.993");
	dateAndTimeList << QString("2021-11-26 18:50:32.993");
	dateAndTimeList << QString("2021-11-26 18:50:32.992");
	dateAndTimeList << QString("2021-11-26 18:34:20.486");
	dateAndTimeList << QString("2021-11-26 18:34:20.486");
	dateAndTimeList << QString("2021-11-26 18:34:20.485");
	dateAndTimeList << QString("2021-11-26 18:34:20.485");
	dateAndTimeList << QString("2021-11-26 18:34:20.484");
	dateAndTimeList << QString("2021-11-26 18:32:30.023");
	dateAndTimeList << QString("2021-11-26 18:32:15.363");
	dateAndTimeList << QString("2021-11-26 18:32:12.009");
	dateAndTimeList << QString("2021-11-26 18:32:12.009");
	dateAndTimeList << QString("2021-11-26 18:32:10.188");
	dateAndTimeList << QString("2021-11-26 18:31:27.514");
	dateAndTimeList << QString("2021-11-26 18:31:27.513");

	//dateAndTimeList << QString("2021-11-28 13:18:24.478");
	//dateAndTimeList << QString("2021-11-28 13:18:24.479");
	//dateAndTimeList << QString("2021-11-28 13:22:22.095");
	//dateAndTimeList << QString("2021-11-28 13:22:22.095");
	//dateAndTimeList << QString("2021-11-28 13:22:22.095");
	//dateAndTimeList << QString("2021-11-28 13:22:22.095");
	//dateAndTimeList << QString("2021-11-28 13:22:22.951");
	//dateAndTimeList << QString("2021-11-28 13:23:16.115");
	//dateAndTimeList << QString("2021-11-28 13:23:16.115");
	//dateAndTimeList << QString("2021-11-28 13:23:16.115");
	//dateAndTimeList << QString("2021-11-28 13:23:16.115");
	//dateAndTimeList << QString("2021-11-28 13:23:16.116");
	//dateAndTimeList << QString("2021-11-28 13:24:46.083");
	//dateAndTimeList << QString("2021-11-28 13:24:46.084");
	//dateAndTimeList << QString("2021-11-28 13:24:46.084");
	//dateAndTimeList << QString("2021-11-28 13:24:46.084");
	//dateAndTimeList << QString("2021-11-28 13:24:46.084");
	//dateAndTimeList << QString("2021-11-28 13:25:40.749");
	//dateAndTimeList << QString("2021-11-28 13:25:40.762");
	//dateAndTimeList << QString("2021-11-28 13:26:01.241");
	//dateAndTimeList << QString("2021-11-28 13:26:01.242");
	//dateAndTimeList << QString("2021-11-28 13:26:01.262");
	//dateAndTimeList << QString("2021-11-28 13:27:37.744");
	//dateAndTimeList << QString("2021-11-28 13:27:37.745");
	//dateAndTimeList << QString("2021-11-28 13:27:37.774");
	//dateAndTimeList << QString("2021-11-28 13:29:15.285");
	//dateAndTimeList << QString("2021-11-28 13:29:15.285");
	//dateAndTimeList << QString("2021-11-28 13:29:15.349");
	//dateAndTimeList << QString("2021-11-28 13:31:56.755");
	//dateAndTimeList << QString("2021-11-28 13:31:56.758");
	//dateAndTimeList << QString("2021-11-28 13:31:56.078");
	//dateAndTimeList << QString("2021-11-28 13:34:49.259");
	//dateAndTimeList << QString("2021-11-28 13:34:49.026");
	//dateAndTimeList << QString("2021-11-28 13:34:49.282");
	//dateAndTimeList << QString("2021-11-28 13:35:45.254");
	//dateAndTimeList << QString("2021-11-28 13:35:45.257");
	//dateAndTimeList << QString("2021-11-28 13:35:45.276");
	//dateAndTimeList << QString("2021-11-28 13:38:57.038");
	//dateAndTimeList << QString("2021-11-28 13:38:57.038");
	//dateAndTimeList << QString("2021-11-28 13:38:57.038");
	//dateAndTimeList << QString("2021-11-28 13:38:57.039");
	//dateAndTimeList << QString("2021-11-28 13:38:57.039");
	//dateAndTimeList << QString("2021-11-28 13:39:16.025");
	//dateAndTimeList << QString("2021-11-28 13:39:16.026");
	//dateAndTimeList << QString("2021-11-28 13:39:52.787");
	//dateAndTimeList << QString("2021-11-28 13:39:52.789");
	//dateAndTimeList << QString("2021-11-28 13:39:52.853");
	//dateAndTimeList << QString("2021-11-28 13:41:57.678");
	//dateAndTimeList << QString("2021-11-28 13:41:57.678");
	//dateAndTimeList << QString("2021-11-28 13:43:28.196");
	//dateAndTimeList << QString("2021-11-28 13:43:28.196");
	//dateAndTimeList << QString("2021-11-28 13:43:28.196");
	//dateAndTimeList << QString("2021-11-28 13:43:28.197");
	//dateAndTimeList << QString("2021-11-28 13:43:28.197");
	//dateAndTimeList << QString("2021-11-28 13:43:28.197");
	//dateAndTimeList << QString("2021-11-28 13:43:28.198");
	//dateAndTimeList << QString("2021-11-28 13:49:03.746");
	//dateAndTimeList << QString("2021-11-28 13:49:03.763");
	//dateAndTimeList << QString("2021-11-28 13:50:12.742");
	//dateAndTimeList << QString("2021-11-28 13:50:12.744");
	//dateAndTimeList << QString("2021-11-28 13:50:12.814");
	//dateAndTimeList << QString("2021-11-28 13:50:52.552");
	//dateAndTimeList << QString("2021-11-28 13:50:52.553");
	//dateAndTimeList << QString("2021-11-28 13:51:12.074");
	//dateAndTimeList << QString("2021-11-28 13:51:12.074");
	//dateAndTimeList << QString("2021-11-28 13:51:12.754");
	//dateAndTimeList << QString("2021-11-28 13:52:06.736");
	//dateAndTimeList << QString("2021-11-28 13:52:06.736");
	//dateAndTimeList << QString("2021-11-28 13:52:06.753");
	//dateAndTimeList << QString("2021-11-28 13:53:16.744");
	//dateAndTimeList << QString("2021-11-28 13:53:16.745");
	//dateAndTimeList << QString("2021-11-28 13:53:16.766");
	//dateAndTimeList << QString("2021-11-28 13:53:41.242");
	//dateAndTimeList << QString("2021-11-28 13:53:41.025");
	//dateAndTimeList << QString("2021-11-28 13:53:41.271");
	//dateAndTimeList << QString("2021-11-28 13:55:07.752");
	//dateAndTimeList << QString("2021-11-28 13:55:07.753");
	//dateAndTimeList << QString("2021-11-28 13:55:07.787");
	//dateAndTimeList << QString("2021-11-28 13:56:13.739");
	//dateAndTimeList << QString("2021-11-28 13:56:13.741");
	//dateAndTimeList << QString("2021-11-28 13:56:13.076");
	//dateAndTimeList << QString("2021-11-28 13:56:23.243");
	//dateAndTimeList << QString("2021-11-28 13:56:23.243");
	//dateAndTimeList << QString("2021-11-28 13:56:23.261");
	//dateAndTimeList << QString("2021-11-28 13:58:16.077");
	//dateAndTimeList << QString("2021-11-28 13:58:16.077");
	//dateAndTimeList << QString("2021-11-28 13:58:16.077");
	//dateAndTimeList << QString("2021-11-28 13:58:16.078");
	//dateAndTimeList << QString("2021-11-28 13:58:16.078");

	return dateAndTimeList;
}

void Predicates::run()
{
	diffDateTime();
}


void Predicates::lowerBond() const
{
	QList<DateToString> list;
	QString TIMESTAMP_FORMAT{ "yyyy-MM-dd hh:mm:ss.zzz" };

	QList<QString> dateAndTimeList{ listInit() };
	QDateTime compareWith1{ QDateTime().fromString(QString("2021-11-26 18:54:54.903"), TIMESTAMP_FORMAT) };
	//QDateTime compareWith2{ QDateTime().fromString(QString("2021-11-26 18:50:32.994"), TIMESTAMP_FORMAT) };
	//QDateTime compareWith3{ QDateTime().fromString(QString("2021-11-26 18:50:32.995"), TIMESTAMP_FORMAT) };


	//DateToString compareDateToString1{ compareWith1 , "" };
	//DateToString compareDateToString2{ compareWith2 , "" };
	//DateToString compareDateToString3{ compareWith3 , "" };

	//qDebug().noquote() << compareDateToString1._dt.toString(TIMESTAMP_FORMAT) << QString("is less %1").arg((compareDateToString1 < compareDateToString2) ? "YEN" : "NO") << compareDateToString2._dt.toString(TIMESTAMP_FORMAT);
	//qDebug().noquote() << compareDateToString2._dt.toString(TIMESTAMP_FORMAT) << QString("is less %1").arg((compareDateToString2 < compareDateToString3) ? "YEN" : "NO") << compareDateToString3._dt.toString(TIMESTAMP_FORMAT);
	//qDebug().noquote() << compareDateToString3._dt.toString(TIMESTAMP_FORMAT) << QString("is less %1").arg((compareDateToString3 < compareDateToString1) ? "YEN" : "NO") << compareDateToString1._dt.toString(TIMESTAMP_FORMAT);
	
	int i{ 0 };
	for (const auto dateAndTime : dateAndTimeList)
	{
		list << DateToString({ QDateTime().fromString(dateAndTime, TIMESTAMP_FORMAT), QString("%2: %1").arg(dateAndTime).arg(i) });
		i++;
	}

	//auto l = [compareWith](const QDateTime & dateTime)
	//{
	//	return (compareWith <= dateTime);
	//};

	//auto lb = std::lower_bound(list.constBegin(), list.constEnd(), l);
	
	DateToString dts{ compareWith1 , "" };
	
	//auto lll = list[68];
	auto lll = dts;

	auto lb = qLowerBound(list.constBegin(), list.constEnd(), lll);
	int d = std::distance(list.constBegin(), lb);

	qDebug().noquote() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	qDebug().noquote() << "lower_bound result" << d;
	qDebug().noquote() << "list[" << d << "]" << list[d]._dtString;
	qDebug().noquote() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";

	auto newList = list.mid(0, d);

	//auto lbItem = lb;

	for (const auto item : newList)
	{
		qDebug().noquote() << item._dt.toString(TIMESTAMP_FORMAT) << item._dtString;
	}
	
	//qDebug().noquote() << lb;


	QList<int> list02;
	list02 << 3 << 3 << 6 << 6 << 6 << 8 << 10 << 15;

	QList<int>::iterator it03 = lower_bound(list02.begin(), list02.end(), 9);
	auto di = std::distance(list02.begin(), it03);
	
	auto ddd = di;

	// list: [ 3, 3, 5, 6, 6, 6, 8 ]


	

}

void Predicates::diffDateTime() const
{
	QString TIMESTAMP_FORMAT{ "yyyy-MM-dd hh:mm:ss.zzz" };

	auto dtStartS = QString("2021-11-26 23:59:00.000");
	auto dtEndS =	QString("2021-11-27 00:01:00.000");


	auto dtStart =	QDateTime().fromString(dtStartS, TIMESTAMP_FORMAT);
	auto dtEnd =	QDateTime().fromString(dtEndS, TIMESTAMP_FORMAT);

	auto requestPeriodDepth = dtStart.secsTo(dtEnd);

	int secondsInMinute = 60;
	int secondsInDay = 24 * 60 * secondsInMinute;

	QTime time = QTime(0, 0).addSecs((requestPeriodDepth % secondsInDay) + secondsInMinute);

	//int days = dtStart.daysTo(dtEnd);
	int days = requestPeriodDepth / secondsInDay;
	auto hours = time.hour();

	QString requestPeriodDepthStr = days > 0 ? QString("%1d").arg(days) : "";
	requestPeriodDepthStr.append(QString("%1h").arg(hours));

	QString archiveFileName = QString("%1-%2-%3")
		.arg(dtStartS)
		.arg(requestPeriodDepthStr)
		.arg("Server");

	//qDebug().noquote() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	//int a = 7;
	//int b = 4;
	//int f = a / b;
	//auto af = a / b;
	//qDebug().noquote() << "f = a / b = " << f;
	//qDebug().noquote() << "af = a / b = " << af;

	qDebug().noquote() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	qDebug().noquote() << "Days = " << days;
	qDebug().noquote() << "Hours = " << hours;
	qDebug().noquote() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	qDebug().noquote() << archiveFileName;
	qDebug().noquote() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
}


//
bool operator<(const Predicates::DateToString & lhs, const Predicates::DateToString & rhs)
{
	return lhs._dt > rhs._dt;
}
//
//bool operator>(const Predicates::DateToString & lhs, const Predicates::DateToString & rhs)
//{
//	return lhs._dt > rhs._dt;
//}
//
//bool operator==(const Predicates::DateToString & lhs, const Predicates::DateToString & rhs)
//{
//	return lhs._dt == rhs._dt;
//}
//
//bool operator>=(const Predicates::DateToString & lhs, const Predicates::DateToString & rhs)
//{
//	return lhs._dt >= rhs._dt;
//}
//bool operator<=(const Predicates::DateToString & lhs, const Predicates::DateToString & rhs)
//{
//	return lhs._dt <= rhs._dt;
//}
//
//
//bool operator < (const Predicates::DateToString &lhs, const QDateTime &rhs)
//{
//	return lhs._dt < rhs;
//}


void MftiLessons::run()
{
	//lesson01();
	//lesson03();
	//typeConversion();
	constructors();
}



void MftiLessons::staticTest()
{
	static int x = 0;
	x++;

	qDebug().noquote() << QString("static int x = %1").arg(x);
}

void MftiLessons::lesson01()
{
	qDebug().noquote() << SEPARATOR_MINI << "POINTERS" << SEPARATOR_MINI;

	/* выделено в динамической памяти 4 байта со значением 10, и будет возвращен указатель на него */
	int * g = new int(10);

	qDebug().noquote() << QString("pointer address = %1").arg((unsigned)&g);
	qDebug().noquote() << QString("pointer value = %1").arg(*g);

	*g = 5;

	qDebug().noquote() << QString("pointer value = %1").arg(*g);

	/* освобождение памяти выделенной под g */
	delete g;
	/* ... не обнуляет указатель, его нужно = nullptr */
	*g++;
	qDebug().noquote() << QString("pointer value = %1").arg(*g);

	/*  */
	int n = 5;
	/* указатель на массив */
	int * arr = new int[n];
	/* удаление указателя на массив */
	delete[] arr;

	return;
	
	qDebug().noquote() << SEPARATOR_MINI << "REFERENCES" << SEPARATOR_MINI;

	int xxx{5};
	int &yyy = xxx; // yyy - ссылка на xxx
	int &zzz = xxx; // zzz - ссылка на xxx
	

	qDebug().noquote() << QString("xxx = %1").arg(xxx);
	qDebug().noquote() << QString("yyy = %1").arg(yyy);
	qDebug().noquote() << QString("zzz = %1").arg(zzz);
	qDebug().noquote() << QString("zzz++");
	/* при измненении значения ссылки ссылающейся на какой то объект меняется значение не только ссылки*/
	/* но и самоого объекта а также всех ссылок на этот объект ссылающиеся */
	zzz++;
	qDebug().noquote() << QString("xxx = %1").arg(xxx);
	qDebug().noquote() << QString("yyy = %1").arg(yyy);
	qDebug().noquote() << QString("zzz = %1").arg(zzz);

	return;



	qDebug().noquote() << SEPARATOR_MINI << "STATIC TEST" << SEPARATOR_MINI;

	for (int i = 0; i < 10; i++)
	{
		staticTest();
	}
	//int arrA[10];
	//int arrB[10];
	//arrB = arrA; // тут будет ошибка компиляции, нельзя массиву присвоить массив

	std::list<int> la;
	std::list<int> lb;
	la = lb;

	qDebug().noquote() << SEPARATOR;
	
	int xa{ 0 };
	int xb{ 0 };

	auto za = xa++;
	auto zb = ++xb;
	
	qDebug().noquote() << QString("xa = %1").arg(xa);
	qDebug().noquote() << QString("za = %1").arg(za);
	qDebug().noquote() << QString("xb = %1").arg(xb);
	qDebug().noquote() << QString("zb = %1").arg(zb);

	//za = 0;
	//zb = 0;
	za = xa++;
	zb = ++xb;
	qDebug().noquote() << QString("xa = %1").arg(xa);
	qDebug().noquote() << QString("za = %1").arg(za);
	qDebug().noquote() << QString("xb = %1").arg(xb);
	qDebug().noquote() << QString("zb = %1").arg(zb);

	qDebug().noquote() << SEPARATOR;

	int a{5};
	int b{ 0 };

	qDebug().noquote() << QString("a = %1").arg(a);

	b = ++(a = 12);

	qDebug().noquote() << QString("a = %1").arg(a);
	qDebug().noquote() << QString("b = %1").arg(b);

	
}



void MftiLessons::lesson03()
{
	/* ===== КОНСТАНТНЫЕ УКАЗАТЕЛИ ========*/
	
	const int CONST_INT = 5;
	int NON_CONST_INT = 15;

	/* указатель на константный int */
	/* указатель который сам может меняться, но разыменовав его вы получите константный int */
	/* а это значит что результат такого разыменования нельзя подвергать не константным операциям */
	const int * constIntP = new int();
	
	/* константный указатель*/
	/* разыменовав его, можно применять не константные методы, но нельзя менять указатель */
	int * const constP = new int();

	/* константный указатель на константный int */
	/* тогда нельзя менять ни сам указатель ни разыменованное (что под ним лежит) значение */
	const int * const constIntConstP = new int();

	int * p = new int();
	
	constIntP = &CONST_INT;
	constIntP = &NON_CONST_INT; /* константному можно присвоить не константный */

	//*constP = 5; /* результат разыменования нельзя подвергать не константным операциям */
	*p = 5;

	p = &NON_CONST_INT;
	//p = &CONST_INT; /* не константному нелья присвоить константный */
	
	/* ===== ССЫЛКИ и КОНСТАНТНЫЕ ССЫЛКИ ========*/
	/* про константный в ссылках  */
	/* ТОЛЬКО ССЫЛКА НА КОНСТАНТУ(константная ссылка - названо исторически) имеет осмысленное применение */
	/* КОНСТАНТНАЯ ССЫЛКА имеет не то значение что КОНСТАНТНЫЙ УКАЗАТЕЛЬ */
	/* КОНСТАНТНАЯ ССЫЛКА это ссылка которая ссылается на то что нельзя менять, потому что ссылку в принципе нельзя сдвинуть, в отличие от указателя */
	//int & const x = 1; /* безсмыслено и будет ошибка компиляции */

	/* ПРО ССЫЛКИ */
	/* если функция возвращается ссылку */
	int z{ 15 };

	qDebug().noquote() << QString("_gInt = %1").arg(_gInt);
	qDebug().noquote() << QString("z = %1").arg(z);


	/* присвоение сработает только как присвоить только тому что под ссылкой */
	gIntRef() = z;

	qDebug().noquote() << QString("_gInt = %1").arg(_gInt);
	qDebug().noquote() << QString("z = %1").arg(z);
	
	/* изменение связанной переменной не приводит к изменению переменной передаваемой как ссылка */
	gIntRef() = 25; /* ни это  */
	z = 26; /* ни это  */

	qDebug().noquote() << QString("_gInt = %1").arg(_gInt);
	qDebug().noquote() << QString("z = %1").arg(z);

	qDebug().noquote() << SEPARATOR;

	/* нельзя использовать константный параметр функции если аргумент ссылка*/
	//auto fff = reffTest01(5);
	/* но можно если аргумент константная ссылка */
	auto fff = reffTest02(5);
}



int MftiLessons::reffTest01(int & x)
{
	int y = x + 15;
	return y;
}

int MftiLessons::reffTest02(const int & x)
{
	int y = x + 15;
	return y;
}


int & MftiLessons::gIntRef()
{
	return _gInt;
}



void MftiLessons::typeConversion()
{
	/* static_cast<type>(exprsession) */
	/* для преобразования своих типов необходимо определить оператор создания своего типа из какого-то фундаментального типа*/
	/* и наоборот преобразование вашего типа к какому-то фундаментальному */
	/* явная просьба преобразовать по разрешенным правилам  */
	/* static потому что на этапе компиляции будет известно что cast будет успешен или нет */
	/* static_cast на основе exprsession создает объект типа type */

	/* reinterpret_cast<type>(exprsession) - не создает новый объект */
	/* крайне НЕ рекомендуется его использовать */
	/* четкое соблюдение константности, нельяза кастовать не константу к константе и наоборот */
	/* берет байты в памяти и начинает считать их другим типом фактическе не преобразовывания мантису, экпаненту */
	/* бывает к указателю reinterpret_cast<type*>(exprsession) - не явный reinterpret_cast, 
	в том случае если нужно сказать что теперь это указатель на другой тии, с самим указателем ничего в этом случае не происходит
	, при это при разменовании мы получаем новый тип. необходимо при работе с сырыми указателями */
	/* бывает к ссылке reinterpret_cast<type&>(exprsession)*/
	/* type y = reinterpret_cast<type&>(x) - теперь х называется как y и он нового типа */

	/* const_cast<type>(exprsession) - начни считать тип константным, или перестань считать тип константным */
	/* крайне НЕ рекомендуется его использовать */
	/* преобразование из НЕконстантного типа в константный является легковесной операция */
	/* преобразование из константного типа в НЕконстантный является невяно запрещено */
	int x{ 1 };
	const int & y = x;
	int & z = const_cast<int &>(y); /* нельзя! UNDEFINED BEHAVIOUR */
	/* потому что комипятор всегда оптизирует константы  */
	/* 
	при const int x = 5, компилятор может вместо х подставлять 5, 
	поэтому использование const_cast с целью преобразования константной ссылку в неконстантную 
	и последующее присваивание приведен ровным счетом к нечему т.к. кмоппилятор уже подставил везде значение 5
	пример когда нужно
	void f(const & int y) а нужно взять значение int g; то тогда это примени, но в обратную сторону невозможно 
	*/
}

void MftiLessons::constructors()
{
	qDebug().noquote() << SEPARATOR_MINI << "CONSTRUCTORS START" << SEPARATOR_MINI;

	{
		/* здесь будет ошибка 'is inaccessible' если конструктор MftiLessonsConstructors будет не в public */
		MftiLessonsConstructors ctr1;
		/* если не определить конструктор копирования
		то _str будет удален дважды при выходе из зоны видимости, т.к. при копировании была создана копия указателя 
		*/
		/* тут КОНСТРУКТОР КОПИРОВАНИЯ */
		MftiLessonsConstructors ctr2 = ctr1/* вызов конструктора */;
		
		/* это НЕ конструктор копировария, это операция присваивания */
		MftiLessonsConstructors ctr3;
		MftiLessonsConstructors ctr4;
		ctr3 = ctr4;
		/* нужно использовать копирующее присваивание */
		/* оператор присваивания это обычный метод, у оператора присвания возвращаемое значение - ссылка на тип */

	}

	qDebug().noquote() << SEPARATOR_MINI << "CONSTRUCTORS END" << SEPARATOR_MINI;
}

