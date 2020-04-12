#include <Geekbrains.h>

#include <QDebug>
#include <QString>

#define HOMEWORK "Homework 02 task 01"

using namespace std;

void homework02Part01()
{
	qDebug() << __FUNCTION__;
	
	short varShort = 45000;
	unsigned char varUnsignedChar = 1400;
	
	QString message = "Value of %1 if equal %2";

	qDebug() << message.arg("varShort").arg(varShort);
	qDebug() << message.arg("varUnsigned").arg(varUnsignedChar);
	qDebug() << "\n";
}