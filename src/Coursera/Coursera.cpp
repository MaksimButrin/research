#include <Coursera.h>

#include <QDebug>
#include <QString>

using namespace std;

void init()
{
	yellowWeek01Leson02().temporary();
	

}


yellowWeek01Leson01::yellowWeek01Leson01()
{
}

yellowWeek01Leson01::~yellowWeek01Leson01()
{
	qDebug() << "\n";
}

void yellowWeek01Leson01::temporary()
{
	qDebug() << __FUNCTION__;

	vector<int> t = { 8,7,3 };
	int sum{ 0 };
	for (int x : t)
	{
		sum += x;
	}

	auto avg = sum / t.size();
	auto x = t.size();

	qDebug() << "avg = sum / t.size()" << avg;
	qDebug() << "sizeof(int16_t)" << sizeof(int16_t); // 2
	qDebug() << "sizeof(size_t)" << sizeof(size_t); // 8
	qDebug() << "sizeof(t)" << sizeof(t); // 32
	qDebug() << "sizeof(int)" << sizeof(int); // 4
	qDebug() << "sizeof(vector<int>)" << sizeof(vector<int>); // 32
	qDebug() << "sizeof(vector<uint>)" << sizeof(vector<uint>); //32
	qDebug() << "sizeof(vector<int16_t>)" << sizeof(vector<int16_t>);
	qDebug() << "limits for <int>" << QString("min %1, max %2").arg(QString::number(numeric_limits<int>::min())).arg(QString::number(numeric_limits<int>::max()));
	qDebug() << "limits for <size_t>" << QString("min %1, max %2").arg(QString::number(numeric_limits<size_t>::min())).arg(QString::number(numeric_limits<size_t>::max()));
	
	qDebug() << "limits of <long long int> is" << QString("min %1, max %2").arg(QString::number(numeric_limits<long long int>::min())).arg(QString::number(numeric_limits<long long int>::max()));
	qDebug() << "limits of <long int> is" << QString("min %1, max %2").arg(QString::number(numeric_limits<long int>::min())).arg(QString::number(numeric_limits<long int>::max()));
}

yellowWeek01Leson02::yellowWeek01Leson02()
{
}

yellowWeek01Leson02::~yellowWeek01Leson02()
{
}

void yellowWeek01Leson02::temporary()
{
	qDebug() << __FUNCTION__;





}

void yellowWeek01Leson02::printAvg()
{
	vector<int> t = { -8,-7,3 };
	int sum{ 0 };
	for (int x : t)
	{
		sum += x;
	}

	auto avg = sum / t.size();
	
	qDebug() << "avg = sum / t.size()" << avg;
}
