#include <TimopheyH.h>

#include <QDebug>
#include <array>
//#include <math.h> //old style include from C
#include <cmath> //current style include from C

const QString SEPARATOR{ "===============================================" };
const QString SEPARATOR_MINI{ "===================" };
const QString ANDS{ "\t\t\t&&&& &&&& &&&& &&&&" };
const QString ORS{ "\t\t\t|||| |||| |||| ||||" };
const QString XORS{ "\t\t\t^^^^ ^^^^ ^^^^ ^^^^" };
const QString EQUALS{ "\t\t\t==== ==== ==== ====" };

using namespace std;

void init()
{
	//timopheyOOPLecture04Ex01().temporary();

	//timopheyOOPLecture04Ex01().trash01();
	//timopheyOOPLecture04Ex01().trash02();
	//ADSLecture02Ex01().simpleNumbersSeparator();
	ADSLecture02Ex01().run();

}

/* ============== L-03 Ex-01 =================  */

timopheyOOPLecture03Ex01::timopheyOOPLecture03Ex01()
{
}

timopheyOOPLecture03Ex01::~timopheyOOPLecture03Ex01()
{
	qDebug() << "\n";
}

void timopheyOOPLecture03Ex01::count2(int n)
{
	qDebug() << __FUNCTION__;

	static int k3{ 0 };
	k3++;

	qDebug() << k3;
	if (n > 0)
		count2(n - 1);

	k3--;

}

void timopheyOOPLecture03Ex01::temporary()
{
	int x{ 0 };
	auto f = &x;

	*f = 5;

	qDebug() << x;

	int a[5];

	auto z = a;

}

/* ============== L-04 Ex-01 =================  */

timopheyOOPLecture04Ex01::timopheyOOPLecture04Ex01()
{

}


timopheyOOPLecture04Ex01::~timopheyOOPLecture04Ex01()
{
	qDebug() << "\n";
}


void timopheyOOPLecture04Ex01::studentPrint(const student & s)
{
	const QString studenInfo = "Student name %1, age %2, group %3";
	qDebug().noquote() << studenInfo.arg(s.name).arg(s.age).arg(s.group);
}


void timopheyOOPLecture04Ex01::studentPrint(const student * ptr = nullptr)
{
	if (ptr)
	{
		const QString studenInfo = "Student name %1, age %2, group %3";
		qDebug().noquote() << studenInfo.arg(ptr->name).arg(ptr->age).arg(ptr->group);
	}
}


void timopheyOOPLecture04Ex01::trash01()
{

	const QString message = "Value of %1 is equal %2";

	double a[100]{ 2,5,6,8,9,10 };
	auto x = a;
	double *p1 = a; // in fact this is the pointer to a[1]
	double *p2 = a + 5;

	auto checkNullPtr = [](double *ptr, const QString &ptrName)
	{
		if (ptr)
			qDebug() << QString("%1 not nullptr").arg(ptrName);
		else
			qDebug() << QString("%1 is nullptr").arg(ptrName);
	};

	double *p3 = new double(5.0);
	checkNullPtr(p3, "p3");

	delete p3; // deleting of one value
	checkNullPtr(p3, "p3");

	double *p4 = new double[50];
	checkNullPtr(p4, "p4");

	delete[] p4; // deleting of array
	checkNullPtr(p4, "p4");

	// == ??? Why ===
	// checkNullPtr is always not equals nullptr


	auto z1 = p1;
	auto z2 = 5.0;
	auto z3 = QString::number(z2, 'f', 3);

	qDebug() << message.arg("p1").arg(*p1);
	qDebug() << message.arg("p2").arg(*p2);
}


void timopheyOOPLecture04Ex01::trash02()
{
	const QString message = "Value of %1 is equal %2";
	const QString studenInfo = "Student name %1, age %2, group %3";

	student ivan{ 17,649,"Ivan" };
	student julia{ 16,645,"Julia" };

	student * pStudent = nullptr;
	pStudent = &ivan;

	/* with using of constant link (konstantnaya ssylka) */
	studentPrint(ivan);
	studentPrint(julia);
	studentPrint(*pStudent);
	qDebug() << "\n";

	/* with using of constant pointer (konstantnyy ukazatel') */
	studentPrint(&ivan);
	studentPrint(&julia);
	studentPrint(pStudent);
}


void timopheyOOPLecture04Ex01::trash03()
{
	student * pStudent = new student{ 15, 116,"Alibaba" };
	student * pStudentArray = new student[2]{ { 15, 116,"Alibaba 1" }, { 15, 116,"Alibaba 2" } };

	auto endPtr = sizeof(pStudentArray);

	/* ??? how simple determinate size of pStudentArray ??? */
	for (int i = 0; i < 2; i++, pStudentArray++)
	{
		studentPrint(pStudentArray);
	}
}

void timopheyOOPLecture04Ex01::trash04()
{
	/* static/automatic arrays */
	double a[3][4]{};
	auto b = a[3][4];
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 4; j++)
		{
			a[k][j] = 1 + k * 4 + j;
		}
	}
	/*
		!!! Attention
		a - this is pointer of first element
		a[k][j] = *(a + k*4 + j)
	*/
	arrayPrint01(a);
}


void timopheyOOPLecture04Ex01::trash05()
{
	/* dinamic arrays */
	const int height{ 3 };
	const int width{ 4 };
	// if using of width/height without const we are do not compile - int b[height][width];

	double **a{ nullptr };
	a = new double *[height];

	for (int k = 0; k < height; k++)
	{
		a[k] = new double[width];
	}

	for (int k = 0; k < height; k++)
	{
		for (int j = 0; j < width; j++)
		{
			a[k][j] = 1 + k * width + j;
		}
	}

	arrayPrint02(a, height, width);

	delete[] a[0];
	delete[] a;

	auto checkNullPtr = [](double **ptr, const QString &ptrName)
	{
		if (ptr)
			qDebug() << QString("%1 not nullptr").arg(ptrName);
		else
			qDebug() << QString("%1 is nullptr").arg(ptrName);
	};


	checkNullPtr(a, "array a");

}


void timopheyOOPLecture04Ex01::trash06()
{
	/* true dinamic arrays */
	const int height{ 3 };
	const int width{ 4 };

	double **a{ nullptr };
	a = new double *[height];
	a[0] = new double[height * width];

	for (int k = 0; k < height; k++)
	{
		a[k] = a[0] + (k * width);
	}

	/*
	in this case a[k][j]:
		a[k]... = *(a+k)
		a[k][j] = *(*(a+k)+j)
	*/

	for (int k = 0; k < height; k++)
	{
		for (int j = 0; j < width; j++)
		{
			a[k][j] = 1 + k * width + j;
		}
	}



	arrayPrint02(a, height, width);

	for (int k = 0; k < height; k++)
	{
		delete[] a[k];
	}
	delete[] a;

	auto checkNullPtr = [](double **ptr, const QString &ptrName)
	{
		if (ptr)
			qDebug() << QString("%1 not nullptr").arg(ptrName);
		else
			qDebug() << QString("%1 is nullptr").arg(ptrName);
	};


	checkNullPtr(a, "array a");
}


void timopheyOOPLecture04Ex01::arrayPrint01(double arr[][4])
{
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 4; j++)
		{
			qDebug().noquote() << arr[k][j] << "\t";
		}
		qDebug().noquote() << "\n";
	}
}

void timopheyOOPLecture04Ex01::arrayPrint02(double ** arr, const int h, const int w)
{
	for (int k = 0; k < h; k++)
	{
		for (int j = 0; j < w; j++)
		{
			qDebug().noquote() << arr[k][j] << "\t";
		}
		qDebug().noquote() << "\n";
	}
}


void timopheyOOPLecture04Ex01::temporary()
{
	double x = 0.33;

	qDebug().noquote() << QString("value is equal %1").arg(foo01(x));

	double s = 0.0;
	double factor;

	for (int n = 0, factor = 1; n < 10; n++)
	{
		s += pow(-1, 2) * pow(x, 2 * n + 1) / factor;
		factor *= 2 * n*(2 * n + 1);

	}
	qDebug().noquote() << QString("value is equal %1").arg(foo01(s));
}

double timopheyOOPLecture04Ex01::foo01(const double &x)
{
	return 2 * sin(x);
}



void ADSLecture02Ex01::bitOperations()
{

	qDebug().noquote() << SEPARATOR_MINI << "BIT OPERATIONS" << SEPARATOR_MINI;


	{
		int x{ 0b01010101 };
		int mask{ 0b11000011 };

		auto xAndMask = x & mask;

		binPrintInt(x);
		qDebug().noquote() << ANDS;
		binPrintInt(mask);
		qDebug().noquote() << EQUALS;
		binPrintInt(xAndMask);
	}

	qDebug().noquote() << SEPARATOR;

	{
		int x{ 0b01010101 };
		int mask{ 0b11000011 };

		auto xOrMask = x | mask;

		binPrintInt(x);
		qDebug().noquote() << ORS;
		binPrintInt(mask);
		qDebug().noquote() << EQUALS;
		binPrintInt(xOrMask);
	}

	qDebug().noquote() << SEPARATOR;

	{
		int x{ 0b01010101 };
		int key{ 0b11001011 };

		auto xXorKey = x ^ key;

		binPrintInt(x);
		qDebug().noquote() << XORS;
		binPrintInt(key);
		qDebug().noquote() << EQUALS;
		binPrintInt(xXorKey);
		qDebug().noquote() << XORS;
		/* повторное наложение ключа приводит к получению */
		/* исходного значения */
		xXorKey = xXorKey ^ key;
		qDebug().noquote() << EQUALS;
		binPrintInt(xXorKey);
		qDebug().noquote() << XORS;
		/* можно использовать для замены значений двух переменных */
		QString message;
		int a{ 5 };
		int b{ 10 };
		message.append(QString("old a=%1; ").arg(a));
		message.append(QString("old b=%1;\n").arg(b));
		/* обмен двух значений  */
		/* a = a+b; может быть переполнение*/
		/* b = a-b; */
		/* a = a-b; */

		/* работает только если a != b */
		if (a != b)
		{
			/* шифр */
			a = a ^ b; /* шифруется 'a' переменной 'b', а т.к. операция симетрична то можно считать что 'b' зашифровано 'a' */
			/*  */
			b = a ^ b; /* в 'b' присваиваем зашифрованный 'a' и расшифровываем 'b' значит получаем старое значение 'a' */
			a = a ^ b; /* расшировываем первое значение шифра 'a' c помощью 'b'(старое а) */
		}
		message.append(QString("new a=%1; ").arg(a));
		message.append(QString("new b=%1;\n").arg(b));
		qDebug().noquote() << message;
	}

	qDebug().noquote() << SEPARATOR;
}

void ADSLecture02Ex01::run()
{
	int numberForGetFactors{ 360 };
	simpleFactors(numberForGetFactors);

	//sf();
}



QString ADSLecture02Ex01::byteToString(int x, bool nubbles)
{
	QString result;

	int n;
	for (n = 0; n < 8; n++)
	{
		result.append(((x & 0x80) != 0) ? "1" : "0");

		if (nubbles && n == 3)
		{
			result.append(" ");
		}

		x = x << 1;
	}

	return result;
}

void ADSLecture02Ex01::binPrintInt(int x, bool nubbles)
{

	QString intToBynaryString;

	int hi, lo;
	hi = (x >> 8) & 0xff;
	lo = x & 0xff;

	intToBynaryString.append(byteToString(hi, nubbles));
	intToBynaryString.append(nubbles ? " " : "");
	intToBynaryString.append(byteToString(lo, nubbles));

	qDebug().noquote() << QString("Value %1 in binary: \t%2").arg(x).arg(intToBynaryString);
}

/* Простые числа: Решето Эратосфена*/
QList<int> ADSLecture02Ex01::simpleNumbersSeparator()
{
	qDebug().noquote() << SEPARATOR_MINI << "SIMPLE NUMBERS SEPARATOR" << SEPARATOR_MINI;
	QList<QPair<int, int>> numbers;
	int numbersSize{ 100 };

	QList<int> simpleNumbers;

	enum status
	{
		init = 0,
		simple = 1,
		removed = 2
	};

	int simpleNumber{ 2 };
	for (int i = 0; i < numbersSize + 1; ++i)
	{
		numbers.append(QPair<int, bool>{i, status::init});
	}

	bool allChecked{ false };
	for (auto simpleNumber = 2; simpleNumber < numbers.size(); ++simpleNumber)
	{
		if (numbers[simpleNumber].second != status::removed)
		{
			numbers[simpleNumber].second = status::simple;
			simpleNumbers.append(numbers[simpleNumber].second);

			for (int j = simpleNumber * simpleNumber; j < numbersSize + 1; j += simpleNumber)
			{
				numbers[j].second = status::removed;
			}
		}
	}

	QStringList statusStrings{ "Init", "Simple", "Removed" };
	QString msg{ "Value %1 is %2" };
	for (const auto & num : qAsConst(numbers))
	{
		qDebug().noquote() << msg.arg(num.first).arg(statusStrings[static_cast<int>(num.second)]);
	}

	qDebug().noquote() << SEPARATOR;

	return simpleNumbers;
}



void ADSLecture02Ex01::simpleFactors(int & number)
{
	int div{ 2 };
	const int numberOrigin{ number };

	struct Factor
	{
		int _div{ 0 };
		int _power{ 1 };
	};

	QList<Factor> factors{ Factor{ 1 } };

	Factor prevFactor;

	while (number > 1)
	{
		while (number % div == 0)
		{
			number = number / div;

			Factor factor{ div };

			if (!factors.isEmpty())
			{
				if (factors.last()._div == factor._div)
				{
					factors.last()._power += 1;
				}
				else
				{
					factors.append(factor);
				}
			}
			else
			{
				factors.append(factor);
			}
		}

		++div;
	}

	QStringList result;
	for (const auto & f : qAsConst(factors))
	{
		result.append((f._power > 1) ? QString("%1^%2").arg(f._div).arg(f._power) : QString("%1").arg(f._div));
	}

	qDebug().noquote() << QString("Factors of num %1:").arg(numberOrigin) << result.join("*");
}

void ADSLecture02Ex01::sf()
{
	int n, div = 2;
	cout << "N = ";
	cin >> n;
	cout << n << " = 1";
	while (n > 1)
	{
		while (n % div == 0)
		{
			cout << " * " << div;
			n = n / div;
		}
		div++;
	}
	cin.get(); cin.get();
}
