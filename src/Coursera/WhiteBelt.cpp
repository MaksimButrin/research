#include "WhiteBelt.h"
#include <QDebug>
#include <QString.h>


/* weak 4 lesson 3*/
#include <iostream>
#include <fstream>
#include <string>
#include <QtGlobal>
#include <stdio.h>
#include <stdlib.h>

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
	weak4Lesson04().run();
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
	QVector<QString> names{"a","b","c"};
	QVector<double> values{ 5, 0.01, 0.00005 };
	QDebug deb  = qDebug();

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
