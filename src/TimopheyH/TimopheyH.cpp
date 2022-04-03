#include <TimopheyH.h>

#include <QDebug>
#include <array>
//#include <math.h> //old style include from C
#include <cmath> //current style include from C
#include <chrono>
#include <thread>
#include <ctime>    
#include <QDateTime>
#include <QFile>
#include <QDir>

const QString SEPARATOR{ "===============================================" };
const QString SEPARATOR_MINI{ "===================" };
const QString ANDS{ "\t\t\t&&&& &&&& &&&& &&&&" };
const QString ORS{ "\t\t\t|||| |||| |||| ||||" };
const QString XORS{ "\t\t\t^^^^ ^^^^ ^^^^ ^^^^" };
const QString EQUALS{ "\t\t\t==== ==== ==== ====" };

using namespace std;
using namespace std::chrono;

void init()
{
	//timopheyOOPLecture04Ex01().temporary();

	//timopheyOOPLecture04Ex01().trash01();
	//timopheyOOPLecture04Ex01().trash02();
	//ADSLecture02Ex01().simpleNumbersSeparator();
	//ADSLecture02Ex01().run();
	//ADSLecture05Ex01().arrayReverse();
	//ADSLecture05Ex01().run();
	//ADSLecture06Ex01().run();
	//ADSLecture07Ex01().run();
	//ADSLecture09Ex01().run();
	graphs::GraphProcess().run();
	//graphs::Test().run();

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
		/* ��������� ��������� ����� �������� � ��������� */
		/* ��������� �������� */
		xXorKey = xXorKey ^ key;
		qDebug().noquote() << EQUALS;
		binPrintInt(xXorKey);
		qDebug().noquote() << XORS;
		/* ����� ������������ ��� ������ �������� ���� ���������� */
		QString message;
		int a{ 5 };
		int b{ 10 };
		message.append(QString("old a=%1; ").arg(a));
		message.append(QString("old b=%1;\n").arg(b));
		/* ����� ���� ��������  */
		/* a = a+b; ����� ���� ������������*/
		/* b = a-b; */
		/* a = a-b; */

		/* �������� ������ ���� a != b */
		if (a != b)
		{
			/* ���� */
			a = a ^ b; /* ��������� 'a' ���������� 'b', � �.�. �������� ���������� �� ����� ������� ��� 'b' ����������� 'a' */
			/*  */
			b = a ^ b; /* � 'b' ����������� ������������� 'a' � �������������� 'b' ������ �������� ������ �������� 'a' */
			a = a ^ b; /* ������������� ������ �������� ����� 'a' c ������� 'b'(������ �) */
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

/* ������� �����: ������ ����������*/
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
		numbers.append(QPair<int, bool>{i, status::simple});
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

		if (pow(simpleNumber, 2) >= numbersSize)
		{
			break;
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



void ADSLecture05Ex01::run()
{
	bubbleSorting();
}

void ADSLecture05Ex01::arrayReverse()
{
	/* ������ ������� */
	qDebug().noquote() << SEPARATOR_MINI << "REVERSE ARRAY" << SEPARATOR_MINI;

	const int arraySize{ 5 };
	int arrayOrigin[arraySize]{ 1,2,3,4,5 };
	/*
	��������! ���� ������ i < (arraySize / 2) �������� i < arraySize
	�� ������� ������� ������������ ����� arraySize / 2, �� ������ ��� �� ������
	*/
	for (int i = 0; i < (arraySize / 2); ++i)
	{
		auto tmp{ arrayOrigin[i] };
		arrayOrigin[i] = arrayOrigin[arraySize - 1 - i];
		arrayOrigin[arraySize - 1 - i] = tmp;
	}

	for (auto el : arrayOrigin)
	{
		qDebug().noquote() << QString("%1").arg(el);
	}

	qDebug().noquote() << SEPARATOR;

}



const int MAX_ARRAY_SIZE{ 100 };

void ADSLecture05Ex01::arrayAppend()
{
	/* ���������� ������� */
	qDebug().noquote() << SEPARATOR_MINI << "APPEND ARRAY" << SEPARATOR_MINI;

	const int arraySize{ MAX_ARRAY_SIZE };
	int arrayOrigin[arraySize];

	int x;

	qDebug().noquote() << "Enter new value, input zero for stop";
	cin >> x;

	/* ������� ������ */
	int top{ 0 };

	while (x != 0)
	{
		/* ������  */
		//arrayOrigin[top] = x;
		//++top;
		//����� ��������
		arrayOrigin[top++] = x; /* ��������� � ������� �������� top */
		cin >> x;
	}

	qDebug().noquote() << "Result array:";

	for (int i = 0; i < top; ++i)
	{
		qDebug().noquote() << QString("%1").arg(QString::number(arrayOrigin[i]));
	}

	qDebug().noquote() << SEPARATOR;

	int var{ 1 };
	/* �� ������ ++VAR � VAR++ */
	/* ������� �� ������ ���: */
	var = var++; /* � ������ ������ ++ ����� lvalue � ���������� ���������� ��������*/
	/* ���� �������, ��� ����� ���� */
	var = var++ + ++var;
	/* ��� ��� ����������� ������ � ����-�� ������� ������ � ������ ����� ����� ���������� - �� ������������� ���������,
	�� ���� ����� ���������� ����� ������ ���� UNDEFINED BEFAVIOUR */
	/* ����� ����������
	� ���������������� ����� ����� ���������, � ������� �������������, ��� ��� �������� ������� ���������� ���������� ��� ����������, � �������� ������� ����������� ��� �����������
	*/


}

void ADSLecture05Ex01::stack()
{
	qDebug().noquote() << SEPARATOR_MINI << "STACK: append and pop" << SEPARATOR_MINI;

	const int arraySize{ MAX_ARRAY_SIZE };
	int arrayOrigin[arraySize];

	int x;

	qDebug().noquote() << "Enter new value, input zero for stop";
	cin >> x;

	/* ������� ������ */
	int top{ 0 };

	while (x != 0)
	{
		arrayOrigin[top++] = x; /* ��������� � ������� �������� top */
		cin >> x;
	}

	qDebug().noquote() << "Result array:";

	auto topA = top;
	auto topA0 = topA;
	/* topA1(lvalue) - ������ ��������; topA0(rvalue) - ����� �������� */
	auto topA1 = topA0--;

	auto topB = top;
	auto topB0 = topB;
	/* topB1(lvalue) - ����� ��������; topB0(rvalue) - ����� �������� */
	auto topB1 = --topB0;

	/* ����������� � �������� �������  */
	while (top > 0)
	{
		/* --top ������ ��� ����� ����� ��������� � ��������� �� 1 */
		auto value = arrayOrigin[--top];
		qDebug().noquote() << QString("%1").arg(QString::number(value));
	}

	/* ����������� � �������� ������� �� ��������� �.�. top = 0 */
	/* ���� ������� ��������� ������ ��� ��� ���� - ���������  */
	while (top > 0)
	{
		cout << arrayOrigin[--top] << "\t";
	}

	arrayOrigin;
	auto stop{ true };
}



void ADSLecture05Ex01::stackBraces()
{
	/* ������. ���������.  */
}

void ADSLecture05Ex01::insertSorting()
{
	/* ���������� ���������. ��������� */
}

void ADSLecture05Ex01::arraySorting()
{
	qDebug().noquote() << SEPARATOR_MINI << "FOOL SORT" << SEPARATOR_MINI;

	const int arraySize{ 10000 };

	int arrayOrigin[arraySize]/*{ 5,3,2,1,4 }*/;

	for (int i = 0; i < arraySize; i++)
	{
		/* ��������� ������ ��� ����������, ������������ ���������� ��������� � ������ */
		arrayOrigin[i] = arraySize - i;
	}

	bool sorted{ true };

	int i{ 0 };
	/* �������� ��������� ���������� */
	auto print{ false };

	/* ������� ����� ������ ������ ��������� */
	auto startTime = high_resolution_clock::now();

	/*
	������������ ������ �������, ������ ��� � ����� ����� ���� ��������,
	������� ������ ���� � ������ � �� ���� �� ��������, ������� ��� ������ ��������� ������
	������� �� ���������� �������� �������, ������ ������� while ����� ��� for ��� ����� ������
	*/
	/* � ������ ������ ��� fool sort - �������� ����������, ������� ���������� */
	/* ��������� O(f) ������ ��������� O(n2) �������� f �������� �����������  */
	/* ���������� ����� ������ ���������, �������� ���������� ��������(���� ����),
	� ���� ����������� n! (������������� �����������) */

	while (i < arraySize - 1)
	{
		auto a = arrayOrigin[i];
		auto b = arrayOrigin[++i];
		/* ���� �� ������������� �� ++i ����� �������� */
		if (a > b)
		{
			sorted = false;

			/* ��������� 'a' ���������� 'b', � �.�. �������� ���������� �� ����� ������� ��� 'b' ����������� 'a' */
			a = a ^ b;
			/* � 'b' ����������� ������������� 'a' � �������������� 'b' ������ �������� ������ �������� 'a' */
			b = a ^ b;
			/* ������������� ������ �������� ����� 'a' c ������� 'b'(������ �) */
			a = a ^ b;

			arrayOrigin[i - 1] = a;
			arrayOrigin[i] = b;
			/* �������� ������� ����� �� ���������� ����� �� �������������� �������� */
			/* �������� 321: ��� 1 -> 231 ... -> 213 */

			i = 0;
		}
	}

	/* ������� ����� ����� ������ ��������� */
	auto endTime = high_resolution_clock::now();
	/* �������� ������� */
	auto duration = duration_cast<microseconds>(endTime - startTime);
	auto mcs = duration.count();
	auto ms = duration.count() / 1000;
	mcs = mcs - ms * 1000;

	/* ��� ���������� 10000 �������� 315 s 628 ms 423 mcs */
	qDebug().noquote() << QString("Sort time is %1 ms %2 mcs").arg(ms).arg(mcs);

	if (print)
	{
		qDebug().noquote() << QString("Sorted is %1").arg(sorted ? "TRUE" : "FALSE");

		for (auto el : arrayOrigin)
		{
			qDebug().noquote() << QString("%1").arg(el);
		}
	}

	qDebug().noquote() << SEPARATOR;
}

void ADSLecture05Ex01::bubbleSorting()
{
	qDebug().noquote() << SEPARATOR_MINI << "BUBBLE SORT" << SEPARATOR_MINI;

	const int arraySize{ 10000 };

	int arrayOrigin[arraySize];

	for (int i = 0; i < arraySize; i++)
	{
		/* ��������� ������ ��� ����������, ������������ ���������� ��������� � ������ */
		arrayOrigin[i] = arraySize - i;
	}

	bool sorted{ false };

	/* �������� ��������� ���������� */
	auto print{ false };

	/* ������� ����� ������ ������ ��������� */
	auto startTime = high_resolution_clock::now();

	/* ������� ����� ����� ������ ��������� */
	auto endTime = high_resolution_clock::now();

	/* ���������� ���������� */
	while (!sorted)
	{
		int i{ 0 };
		sorted = true;

		while (i < arraySize - 1)
		{
			if (arrayOrigin[i] > arrayOrigin[i + 1])
			{
				auto tmp = arrayOrigin[i];
				arrayOrigin[i] = arrayOrigin[i + 1];
				arrayOrigin[i + 1] = tmp;

				sorted = false;
			}

			++i;
		}
	}


	/* �������� ������� */
	auto duration = duration_cast<microseconds>(endTime - startTime);
	auto mcs = duration.count();
	auto ms = duration.count() / 1000;
	mcs = mcs - ms * 1000;

	/* ��� ���������� 10000 �������� 0 s 0 ms 6 mcs */
	qDebug().noquote() << QString("Sort time is %1 ms %2 mcs").arg(ms).arg(mcs);

	//print = true;

	if (print)
	{
		qDebug().noquote() << QString("Sorted is %1").arg(sorted ? "TRUE" : "FALSE");

		for (auto el : arrayOrigin)
		{
			qDebug().noquote() << QString("%1").arg(el);
		}
	}

	qDebug().noquote() << SEPARATOR;

}

void ADSLecture06Ex01::run()
{
	dinamicArrays2d();
}



void ADSLecture06Ex01::pointerOnPointer()
{
	int x = 5; /* ��� ����������, ����� � ��� ����������, � ����� �� ������ ��� �� �������������� ����� */
	/* ������� ������ ������ ���� 'int *' */
	/* ����� ���� ����� 'x' */
	int *px = &x;
	/* &px - ����� ������ ������ 'px' */
	int **ppx = &px;
	/* &ppx - ����� ������ ������ 'ppx' */
	int ***pppx = &ppx; /* ����� ���������� ���������� */
	/* ��� ����� ���������� � ����� '5'?: */
	/* ��� ����� ���������� � ����� '5'?: */
	/* 1. �� ����� ���������� (��� ���������� ��� ������ �� ����������� �����) */
	std::cout << x;
	/* 2. ������� �������� ������ px, � ���������������� �� �������� (�����) ������� � ��� �����,
	�� ���� ���������� �� ������ �������� � ������ px, ����� ������� ����������� �� ��� �� ����� 5�� */
	auto case2 = *px;
	std::cout << *px;
	/* 3.,4. ����������� ������ � **ppx � � ***pppx */
	/* ���� ��������� ����� ���� ��������� � ���� ������ ������ � ��� ����� */
	auto case3 = **ppx; /* */
	std::cout << **ppx;
	auto case4 = ***pppx; /* */
	std::cout << ***pppx;
	/* !!! ���� �������� ��� ���� * ������� ***pppx, �� ����� ������ ������ ��� ��� int (5), int ��� ������ ����� � ��� �� �������� ��� */
	//auto case5 = ****pppx; /* �������� ��� ���� * - ������ ���������� */

}

void ADSLecture06Ex01::goThrough(NodeT * pBegin)
{
	while (pBegin != nullptr)
	{
		/* �� ������ pBegin ����� �������� �������� ��������� */;
		qDebug().noquote() << (*pBegin).data; /* �����������  pBegin->data */
		/* *pBegin.data �� �������� */
		//qDebug().noquote() << *pBegin.data;
		//pBegin /* ����� �� ����� */
		/* ����� ���� ������ ��� ����� ������ ��������� ����� �� ��������� ����� */
		pBegin = (*pBegin).next;
	}
}

void ADSLecture06Ex01::generateNodes()
{
	const int nodesSize{ 5 };
	NodeT nodes[nodesSize];

	/* ��������� ������� */
	for (int i = 0; i < nodesSize; i++)
	{
		nodes[i].data = i + 1;

		if (i != nodesSize - 1)
		{
			nodes[i].next = nodes/* ����� ������� �������� */ + i + 1;
		}
		else
		{
			nodes[i].next = nullptr; /* ������� ��� ��� ��������� ������� */
		}
	}

	/* ��������� �� ����� */
	NodeT *pBegin = nodes; /* ����� ������ */
	/* ����� �� ��������, �������� ��������� �� ������ */

	/* �-�� �������� */
	goThrough(pBegin);
}


void ADSLecture06Ex01::generateNodesUnlim()
{
	/* ��������� ������ */
	/* ��� ���� ����� ������� ������? �� ��� �����: */
	/* - ������������ ����  */
	/* - ������������ ������� */
	/* - ������������ ��� - ������� ������� � ������� ����� ��������� � � ������ � � ����� */
	/* - �� ����� ������� - ������� � �������� ����� ���������� */
	/* ��������� ������ ��� ������� �������� */
	NodeT *pBegin = new NodeT;
	/* �������� ����� � ��������� ��� � ����� */
	/* ��� ����� ������� ��������� � �������� ���� ��������� ��������� */
	NodeT *p = pBegin;

	const int nodesSize{ 5 };

	for (int i = 0; i < nodesSize; i++)
	{
		/* � ������ � p.data ����� ������*/
		p->data = i + 1;
		/*, � � p.next ����� ����� ����������� */
		p->next = new NodeT;
		p = p->next;
	}
	/* � ���������� ����� ������ nullptr */
	p->next = nullptr;
	p->data = 777; /* ����� ��� ����� ����� */

	/* �-�� �������� */
	goThrough(pBegin);
}



void ADSLecture06Ex01::arrays2d()
{
	/* ��������� ������� */
	const int arraySize{ 3 };
	const int columns{ 4 };

	int arrayOrigin[arraySize][columns];


	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			arrayOrigin[i][j] = i * columns + j;
		}
	}

	auto print{ true };
	if (print)
	{
		for (int i = 0; i < arraySize; i++)
		{
			QStringList out;
			for (int j = 0; j < columns; j++)
			{
				out << QString::number(arrayOrigin[i][j]);

			}

			qDebug().noquote() << QString("%1").arg(out.join("\t"));
		}

	}

	qDebug().noquote() << SEPARATOR;

	{
		/* ������������ ������, ��� ������� ������ ������. ��. ���� */
		/* �������� ����� ������ ������� */
		int *p = reinterpret_cast<int *>(arrayOrigin);

		QStringList out;
		QStringList out2;
		for (int i = 0; i < arraySize*columns; i++)
		{

			out << QString::number(*(p + i)); /* *(p+i) ����������� p[i], � p+i �����/��������� */

			 /* �������� ������ */
			auto itemAddress = (quintptr)(p + i);
			/* �������� ������ � ��������� ������� */
			auto itemAddressStr = QString("0x%1").arg(itemAddress, QT_POINTER_SIZE * 2, 16, QChar('0'));
			out2 << itemAddressStr;

			/*
			!!! ����� ������� ��� ��� ���:
			auto x = p + i;
			std::cout << x << " ";
			*/
		}

		qDebug().noquote() << QString("%1").arg(out.join(" "));
		qDebug().noquote() << QString("%1").arg(out2.join(" "));

		/* ����: ������ ����� ���������������, �� ����: a[0][0], a[0][1], a[0][2], a[0][3], a[1][0], ..., a[2][3] */
		/*
		��� ���������� ��������:
		��� ��������� i � ������� a[i] ����� ������ ������
		a[i] = (p + i);
		��� ��������� ��������:
		��� ��������� i,j � ������� a[i][j] ����� ������ ������
		a[i][j] = *(p + i*<������ �������> + j)  = p[i*<������ �������> + j]
		��� ����  i*<������ �������> + j ��� �������� �� ������ ������� � ���������� �����, ����� � ������ ����� *sizeof
		� ����� ������ p + i*<������ �������> + j
		!!! �����: ���������� �� ������ ���������� ������ ����� ��� ��������� ������ [i][j] �������� ��� ������ ������ �������


		*/

	}

	qDebug().noquote() << SEPARATOR;

}

void ADSLecture06Ex01::array2dPrint(int *p, const int arraySize, const int columns)
{
	for (int i = 0; i < arraySize; i++)
	{
		QStringList out1;
		QStringList out2;
		for (int j = 0; j < columns; j++)
		{
			out1 << QString::number(*(p + i * columns + j));
			/* ��� */
			out2 << QString::number(p[i*columns + j]); /* ����������� a[i][j] */

		}

		qDebug().noquote() << QString("1st version");
		qDebug().noquote() << QString("%1").arg(out1.join("\t"));
		qDebug().noquote() << QString("2nd version");
		qDebug().noquote() << QString("%1").arg(out2.join("\t"));
	}

	qDebug().noquote() << SEPARATOR;
}

void ADSLecture06Ex01::arrays2dAndPrint()
{
	/* 2d ������� � �������� �� ��� ������ */
	qDebug().noquote() << SEPARATOR_MINI << "ARRAYS 2D AND PRINT" << SEPARATOR_MINI;

	const int arraySize{ 3 };
	const int columns{ 4 };

	int arrayOrigin[arraySize][columns];


	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			arrayOrigin[i][j] = i * columns + j;
		}
	}

	int *p = reinterpret_cast<int *>(arrayOrigin);

	array2dPrint(p, arraySize, columns);

	qDebug().noquote() << SEPARATOR;
}



void ADSLecture06Ex01::dinamicArrays2d()
{
	/* !!! ��� ���� ��� ���?: */
	/* ��� ��������� ��� ������� ��������� ������������ ������ */
	const int arraySize{ 3 };
	/* ������ �� ��������� */
	int columns{ 4 };
	/* ��������� �� ��������� �� ������ �, */
	int **A = new int*[arraySize];
	/* ����� � ��� ������ ������� ������ � ���� ������ �����, ����������� �� ������ ���� int*(��� - ���������),
	���������� � ��� �������� �����, ����� **A ��� ����� ������ ����������, �.�.  */
	A = new int*[arraySize];

	/*!!! � ������ ��������� �� ����. �� ���� ��� ���� */
	/* ������ ��������� - ����� �������� ������ */
	A[0] = new int[arraySize*columns];

	/* ������ ��������� */
	//for (size_t i = 0; i < arraySize; i++)
	/* ������ ��������� */
	for (size_t i = 1; i < arraySize; i++)
	{
		/* ������ ��������� */
		{
			/* �� ���� � ������� �������� �� ������ ���������� ������� */
			//A[i] = new int[columns]; /* �������� ������ ��� ������ � ���� ������� */
		}
		/* ������ ��������� */
		{
			A[i] = A[0] + (columns * i);
		}
	}

	for (int i = 0; i < arraySize; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			A[i][j] = i * columns + j;
		}
	}


	for (int i = 0; i < arraySize; i++)
	{
		QStringList out;

		for (int j = 0; j < columns; j++)
		{

			out << QString::number(A[i][j]);
		}

		qDebug().noquote() << QString("%1").arg(out.join("\t"));
	}

	/* ��. ����� ������ ������� ������� ���������� ������  */
	/* ������ ��������� */
	//{
	//	for (int i = 0; i < arraySize; i++)
	//	{
	//		delete[] A[i];
	//	}
	//	delete[] A;
	//}

	/* ������ ��������� �� ������� ����� ������������ ������ */
	delete[] A[0];
	delete[] A;



}


void ADSLecture07Ex01::run()
{
	countSortStart();
}



void ADSLecture07Ex01::search()
{
	const int arraySize = 10;
	int A[arraySize] = { 1,3,3,7,7,7,7,9,10,10 };
	int x{ -1 };

	qDebug().noquote() << QString("The base array looks like this:");
	QStringList out;
	for (int i = 0; i < arraySize; i++)
	{
		out << QString("%1(%2) \t").arg(A[i]).arg(i);
	}
	qDebug().noquote() << QString("%1").arg(out.join("\t"));


	qDebug().noquote() << QString("Please enter the desired value:");
	cin >> x;

	//auto result = linearSearch(A, arraySize, x);
	auto result = leftBound(A, arraySize, x);

}



int ADSLecture07Ex01::linearSearch(int A[], int arraySize, int x)
{
	int result{ -1 };

	/* ������� ����� ������ ������ ��������� */
	auto startTime = high_resolution_clock::now();

	/* �������� ����� */
	for (int i = 0; i < arraySize; i++)
	{
		if (A[i] == x)
		{
			result = i;
			break;
		}
	}

	/* ������� ����� ����� ������ ��������� */
	auto endTime = high_resolution_clock::now();
	/* �������� ������� */
	auto duration = duration_cast<microseconds>(endTime - startTime);
	auto mcs = duration.count();
	auto ms = duration.count() / 1000;
	mcs = mcs - ms * 1000;

	qDebug().noquote() << QString("Linear search: time is %1 ms %2 mcs").arg(ms).arg(mcs);

	qDebug().noquote() << QString("Linear search: inxed of 'x' is %1").arg(result);

	return result;
}

int ADSLecture07Ex01::leftBound(int A[], int arraySize, int x)
{
	int left{ -1 }; /* A[left] < x - ��������� ����� ������ (��������������) */
	int right{ arraySize }; /* A[right] >= x */

	/* ������� ����� ������ ������ ��������� */
	auto startTime = high_resolution_clock::now();

	/* �������� ����� */
	while (right - left > 1)
	{
		int middle = (left + right) / 2;
		/* ����� ������ ���� ������ ��� ������� */
		if (A[middle] < x)
		{
			left = middle;
		}
		else
		{
			right = middle;
		}
	}



	/* ������� ����� ����� ������ ��������� */
	auto endTime = high_resolution_clock::now();
	/* �������� ������� */
	auto duration = duration_cast<microseconds>(endTime - startTime);
	auto mcs = duration.count();
	auto ms = duration.count() / 1000;
	mcs = mcs - ms * 1000;

	qDebug().noquote() << QString("Binary search: time is %1 ms %2 mcs").arg(ms).arg(mcs);

	qDebug().noquote() << QString("Binary search: left inxed of 'x' is %1").arg(left);

	return left;
}



int ADSLecture07Ex01::binarySearch(int A[], int arraySize, int x)
{
	int left = leftBound(A, arraySize, x);
	int potentialFstIndexOfXInA = left + 1;
	if ((potentialFstIndexOfXInA < arraySize) && A[potentialFstIndexOfXInA] == x)
	{
		return potentialFstIndexOfXInA;
	}
	else
	{
		return -1;
	}

	return 0;
}

void ADSLecture07Ex01::countSortStart()
{
	const int arraySize = 10;
	int A[arraySize];
	int m = 10;

	randomArray(A, arraySize, m);

	qDebug().noquote() << QString("The base array looks like this:");

	printArray(A, arraySize);

	countSort(A, arraySize);

	printArray(A, arraySize);
}



void ADSLecture07Ex01::randomArray(int A[], int arraySize, int m)
{
	for (int i = 0; i < arraySize; i++)
	{
		A[i] = rand() % m;
	}
}



void ADSLecture07Ex01::printArray(int A[], int arraySize)
{
	QStringList out;
	for (int i = 0; i < arraySize; i++)
	{
		out << QString("%1(%2) \t").arg(A[i]).arg(i);
	}
	qDebug().noquote() << QString("%1").arg(out.join("\t"));
}



void ADSLecture07Ex01::countSort(int A[], int arraySize)
{
	/* ����� ������� �������� ����������� �����, �������� ��� �� 0 ��  arraySize*/
	int F[10] = { 0 }; /* � ������ ������ {0} - ������������� 0��, ���� {1} ������ ������ ����� = 1 */
	for (int i = 0; i < arraySize; i++)
	{
		F[A[i]]++; /* �������� ������� */
	}
	int i = 0;
	/* ����� ����� ���� ������� �������� */
	for (int x = 0; x < 10; x++) /* ������� ������������ �������� �����, �� ����� ���� � ���� */
	{
		/* � ��� ������� ������  */
		for (size_t k = 0; k < F[x]; k++)
		{
			A[i] = x;
			i++;
		}
	}

}

void ADSLecture09Ex01::run()
{
	//testPointers();
	//return;
	//timersTest();
	//return;

	//getFactorial();
	//getGcd();
	callHanoi();
}


void ADSLecture09Ex01::getFactorial()
{
	uint16_t x;
	qDebug().noquote() << QString("Please input 'n' to calculate factorial:");
	std::cin >> x;
	qDebug().noquote() << QString("Factorial of '%1' = %2").arg(QString::number(x)).arg(QString::number(factorial(x)));
}

uint64_t ADSLecture09Ex01::factorial(uint16_t n)
{
	/* n! = n*(n-1)!
	<->
	f(n) = n*f(n-1)  */
	uint16_t result{ 0 };

	qDebug().noquote() << QString("Factorial n(%1) is called").arg(n);


	if (n == 0)
	{
		result = 1;
	}
	else
	{
		result = factorial(n - 1)*n;
	}

	qDebug().noquote() << QString("Factorial n(%1) is exitting").arg(n);
	return result;
}



void ADSLecture09Ex01::timersTest()
{


	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << QDateTime::currentDateTime().time().toString("mm.ss.zzz").toStdString() << std::flush;

	using namespace std::chrono_literals;
	std::cout << "Hello waiter\n" << std::flush;
	auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(2000ms);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = end - start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
}



void ADSLecture09Ex01::testPointers()
{
	qDebug().noquote() << QString("Value of pair { %1, %2 } ").arg(_testStruct.pair01.first).arg(_testStruct.pair01.second);

	int *pair;
	if (_testStruct.switcher)
	{
		pair = &_testStruct.pair01.second;
		qDebug().noquote() << QString("Selected 'second'");
	}
	else
	{
		pair = &_testStruct.pair01.first;
		qDebug().noquote() << QString("Selected 'first'");
	}

	++*pair;
	// *pair++; �����������

	qDebug().noquote() << QString("Value pair = %1").arg(*pair);

	qDebug().noquote() << QString("Value of pair { %1, %2 } ").arg(_testStruct.pair01.first).arg(_testStruct.pair01.second);
}





void ADSLecture09Ex01::getGcd()
{
	int a{ 14 };
	int b{ 8 };


	qDebug().noquote() << QString("Value gcd(%1,%2) = %3").arg(a).arg(b).arg(gcd(a, b));


}

int ADSLecture09Ex01::gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a%b);
}

void ADSLecture09Ex01::callHanoi()
{
	hanoi(1, 2, 3);
}

void ADSLecture09Ex01::hanoi(int cl, int cr, int cnt)
{
	qDebug().noquote() << QString("s: hanoi(%1,%2,%3)").arg(cl).arg(cr).arg(cnt);

	if (cnt == 1)
	{
		qDebug().noquote() << QString("1: Move disk %1 from pin %2 to pin %3").arg(1).arg(cl).arg(cr);
	}
	else
	{
		auto tmp = (1 + 2 + 3) - cl - cr; /* third pin (temporary) */
		qDebug().noquote() << QString("call #1");
		hanoi(cl, tmp, cnt - 1);
		qDebug().noquote() << QString("2: Move disk %1 from pin %2 to pin %3").arg(cnt).arg(cl).arg(cr);
		qDebug().noquote() << QString("call #2");
		hanoi(tmp, cr, cnt - 1);
	}
}



void Test::run()
{
	char x = -1;
	short y = -2;
	auto debug{ false };
	//int &r = 10;
}

namespace graphs
{

/* 4.1. ����������������� ����� */
/* �������� ����� � v ��������� ��� ���� */
Graph::Graph(int v) : _vertices(v), _edges(0)
{
	for (int i = 0; i < v; i++)
	{
		_adjacent.append(QList<int>());
	}
}

int Graph::vertices() const
{
	return _vertices;
}



int Graph::edges() const
{
	return _edges;
}

void Graph::setEdges(int cnt)
{
	_edges = cnt;
}



bool Graph::addEdge(QPair<int, int> edge, QString *error)
{
	auto v = edge.first;
	auto w = edge.second;

	if (v >= _adjacent.size() || w >= _adjacent.size())
	{
		if (error)
			*error = QString("Wrong vertices(%1,%2) for edge").arg(v).arg(w);
		return false;
	}
	/*
		������ ����� ������������ ������:
		���� ��� ��������� ������� 'v' � 'w', �� 'w' ������������ � ������ ������ 'v'
		� 'v' ������������ � ������ ������ 'w'
	*/
	_adjacent[v].prepend(w);
	//qDebug().noquote() << QString("_adjacent[%1].append(%2), new size %3").arg(v).arg(w).arg(_adjacent[v].size());
	_adjacent[w].prepend(v);
	//qDebug().noquote() << QString("_adjacent[%1].append(%2), new size %3").arg(w).arg(v).arg(_adjacent[w].size());

	_edges++;

	return true;
}



QList<int> Graph::adjacentOfVertex(int v, QString *error) const
{
	if (v >= _adjacent.size())
	{
		if (error)
			*error = QString("Wrong vertex(%1) to get adjacent").arg(v);

		return QList<int>();
	}


	return _adjacent[v];
}



QString Graph::toString()
{
	QStringList s{ QString("%1 vertices, %2 edges").arg(_vertices).arg(_edges) };
	for (int v = 0; v < _vertices; v++)
	{
		s << QString("%1:").arg(v);
		for (const auto & w : adjacentOfVertex(v))
		{
			s.last() = QString("%1%2 ").arg(s.last()).arg(w);
		}
	}
	return s.join("\n");
}



void GraphProcess::run()
{
	QString path{ "D:/00 Work/Book/!C++ Books/Teaching/TeachingSolution/tmp/tinyG.txt" };
	QString localError;
	if (!readGraph(path, &localError))
	{
		qDebug().noquote() << QString("Error: %1").arg(localError);
	}

	qDebug().noquote() << SEPARATOR_MINI << "Graph:" << SEPARATOR_MINI;

	auto graphToString = _graph->toString();

	qDebug().noquote() << graphToString;

	qDebug().noquote() << SEPARATOR_MINI << "Depth first search:" << SEPARATOR_MINI;

	//DepthFirstSearch(_graph, 0);
	_search = QSharedPointer<DepthFirstPaths>(new DepthFirstPaths(_graph, 0));

	qDebug().noquote() << SEPARATOR_MINI << "Paths in graph:" << SEPARATOR_MINI;

	printPaths(_search, _graph, 0);
}



int GraphProcess::degree(const Graph & graph, int v)
{
	int degree = graph.adjacentOfVertex(v).size();
	return degree;
}



int GraphProcess::maxDegree(const Graph & graph)
{
	int max{ 0 };
	for (int v = 0; v < graph.vertices(); v++)
	{
		max = degree(graph, v) > max ? degree(graph, v) : max;
	}

	return max;
}



int GraphProcess::avgDegree(const Graph & graph)
{
	/* ����: ��� ������ ����� ��� ������ ������� */
	return 2 * graph.edges() / graph.vertices();
}



int GraphProcess::numberOfSelfLoops(const Graph & graph)
{
	int loopsCount{ 0 };
	for (int v = 0; graph.vertices(); v++)
	{
		for (const auto & w : graph.adjacentOfVertex(v))
		{
			if (v == w)
				loopsCount++;
		}
	}

	/* ������ ����� ��������� ������ */
	return loopsCount / 2;
}



bool GraphProcess::readGraph(QString & pathToFile, QString * error)
{
	qDebug().noquote() << SEPARATOR_MINI << "Reading the graph file" << SEPARATOR_MINI;

	QFile file(pathToFile);
	if (!file.exists())
	{
		if (error)
			*error = QString("File does not exist: %1").arg(pathToFile);

		return false;
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		if (error)
			*error = QString("Something wrong with access to file: %1").arg(pathToFile);

		return false;
	}

	QTextStream in(&file);

	QString line = in.readLine();
	int ln{ 0 };
	bool ok;
	auto vertices = line.toInt(&ok);

	if (!ok)
	{
		if (error)
			*error = QString("Line %1: Wrong vertices count in the file").arg(ln);
		return false;
	}

	qDebug().noquote() << QString("Vertices count: %1").arg(vertices);

	/* �������� ���������� ����� */
	_graph = QSharedPointer<Graph>(new Graph(vertices));

	//
	line = in.readLine();
	auto edges = line.toInt(&ok);
	ln++;

	if (!ok)
	{
		if (error)
			*error = QString("Line %1: Wrong edges count in the file").arg(ln);
		return false;
	}

	qDebug().noquote() << QString("Edges count: %1").arg(edges);

	_graph->setEdges(edges);

	while (!in.atEnd())
	{
		QString line = in.readLine();
		ln++;
		QStringList vw = line.split(" ");
		bool result{ true };

		QPair<int, int> edge;
		if (vw.size() == 2)
		{
			edge.first = vw.first().toInt(&ok);
			result = result && ok;
			edge.second = vw.last().toInt(&ok);
			result = result && ok;

			if (result)
			{
				QString localError;
				if (_graph->addEdge(edge, &localError))
				{
					qDebug().noquote() << QString("Added edge: %1-%2").arg(edge.first).arg(edge.second);
				}
				else
				{
					if (error)
						*error = localError;

					return false;
				}
			}
		}

		if (!result)
		{
			if (error)
				*error = QString("Line %1: Wrong edge parameters(%2)").arg(ln).arg(line);
			return false;
		}

	}

	qDebug().noquote() << SEPARATOR;

	return true;
}



void GraphProcess::printPaths(const QSharedPointer<DepthFirstPaths> & search, const QSharedPointer<Graph> & graph, int sourceVertex)
{
	//auto search = Paths(graph, sourceVertex);

	for (int v = 0; v < graph->vertices(); v++)
	{
		QString result{ QString("Paths from %1 to %2: ") };
		result = result.arg(sourceVertex).arg(v);

		if (search->hasPathTo(v))
		{
			auto pt = search->pathTo(v);
			for (int i = 0; i < search->pathTo(v).size(); i++)
			{
				auto p = pt.pop();

				if (p == sourceVertex)
				{
					result += QString("%1").arg(p);
				}
				else
				{
					result += QString("-%1").arg(p);
				}
			}

			qDebug().noquote() << result;
		}
	}
}


SearchInGraph::SearchInGraph(const Graph & graph, int source)
{
}

bool SearchInGraph::marked(int v)
{
	return false;
}

int SearchInGraph::count()
{
	return 0;
}


/* =========================== */
/* ����� � ������� */
DepthFirstSearch::DepthFirstSearch(const QSharedPointer<Graph> & graph, int sourceVertex)
{
	init(graph, sourceVertex);
}


void DepthFirstSearch::init(const QSharedPointer<Graph> & graph, int sourceVertex)
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
	}

	dfs(graph, sourceVertex);
}

bool DepthFirstSearch::marked(int v)
{
	if (v >= _marked.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) get marked value").arg(v);
		return false;
	}

	return _marked[v];
}



int DepthFirstSearch::count() const
{
	return _count;
}



void DepthFirstSearch::dfs(const QSharedPointer<Graph> & graph, int vertex)
{
	if (vertex >= _marked.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) to mark of adjacent vertices").arg(vertex);
		return;
	}

	_marked[vertex] = true;
	_count++;

	qDebug().noquote() << QString("Info: Vertex(%1) marked").arg(vertex);

	for (const auto w : graph->adjacentOfVertex(vertex))
	{
		if (!marked(w))
		{
			edgeTo(w, vertex);
			dfs(graph, w);
		}
		else
		{
			qDebug().noquote() << QString("Info: Vertex(%1) already marked").arg(w);
		}
	}
}



void DepthFirstSearch::edgeTo(int w, int v)
{
}



/* ================================= */
/* ���������� ����� */
/* �������� 4.1. ����� � ������� ��� ���������� ����� */

DepthFirstPaths::DepthFirstPaths(const QSharedPointer<Graph> & graph, int sourceVertex) :
	_sourceVertex{ sourceVertex }
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_edgeTo.append(-1);
	}

	init(graph, sourceVertex);
}



bool DepthFirstPaths::hasPathTo(int v, QString * error)
{
	return marked(v);
}

void DepthFirstPaths::edgeTo(int w, int v)
{
	if (w >= _edgeTo.size())
	{
		qDebug().noquote() << QString("Error: Wrong vertex(%1) set _edgeTo[%1]").arg(w);
		return;
	}

	_edgeTo[w] = v;
}

QStack<int> DepthFirstPaths::pathTo(int v)
{
	QStack<int> path;
	if (!hasPathTo(v))
		return path;

	for (int x = v; x != _sourceVertex; x = _edgeTo[x])
	{
		path.push(x);
	}
	path.push(_sourceVertex);

	return path;
}




BreadFirstPath::BreadFirstPath(const QSharedPointer<Graph>& graph, int sourceVertex): _sourceVertex(sourceVertex)
{
	//const int _sourceVertex = sourceVertex;
	
	
	//const int _sourceVertex = 1;
}

void BreadFirstPath::init(const QSharedPointer<Graph>& graph, int sourceVertex)
{
	for (int i = 0; i < graph->vertices(); i++)
	{
		_marked.append(false);
	}
}

} //namespace graphs