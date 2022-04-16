#include <TimopheyH.h>

#include <QDebug>
#include <array>
//#include <math.h> //old style include from C
#include <cmath> //current style include from C
#include <chrono>
#include <thread>
#include <ctime>    
#include <QDateTime>

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
	//graphs::GraphProcess().run();
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
	/* реверс массива */
	qDebug().noquote() << SEPARATOR_MINI << "REVERSE ARRAY" << SEPARATOR_MINI;

	const int arraySize{ 5 };
	int arrayOrigin[arraySize]{ 1,2,3,4,5 };
	/*
	Внимание! если вместо i < (arraySize / 2) написать i < arraySize
	то получим двойную перестановку после arraySize / 2, на выходе тот же массив
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
	/* расширение массива */
	qDebug().noquote() << SEPARATOR_MINI << "APPEND ARRAY" << SEPARATOR_MINI;

	const int arraySize{ MAX_ARRAY_SIZE };
	int arrayOrigin[arraySize];

	int x;

	qDebug().noquote() << "Enter new value, input zero for stop";
	cin >> x;

	/* текущий размер */
	int top{ 0 };

	while (x != 0)
	{
		/* вместо  */
		//arrayOrigin[top] = x;
		//++top;
		//можно написать
		arrayOrigin[top++] = x; /* обращаюсь к старому значению top */
		cin >> x;
	}

	qDebug().noquote() << "Result array:";

	for (int i = 0; i < top; ++i)
	{
		qDebug().noquote() << QString("%1").arg(QString::number(arrayOrigin[i]));
	}

	qDebug().noquote() << SEPARATOR;

	int var{ 1 };
	/* по поводу ++VAR и VAR++ */
	/* никогда не делать так: */
	var = var++; /* в данном случае ++ имеет lvalue и присвоится предыдущее значение*/
	/* если спросят, что будет если */
	var = var++ + ++var;
	/* тут три модификации одного и того-же участка памяти в рамках одной ТОЧКИ СЛЕДОВАНИЯ - не предсказуемое поведение,
	то есть может компилятор может выдать даже UNDEFINED BEFAVIOUR */
	/* ТОЧКА СЛЕДОВАНИЯ
	в программировании любая точка программы, в которой гарантируется, что все побочные эффекты предыдущих вычислений уже проявились, а побочные эффекты последующих ещё отсутствуют
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

	/* текущий размер */
	int top{ 0 };

	while (x != 0)
	{
		arrayOrigin[top++] = x; /* обращаюсь к старому значению top */
		cin >> x;
	}

	qDebug().noquote() << "Result array:";

	auto topA = top;
	auto topA0 = topA;
	/* topA1(lvalue) - старое значение; topA0(rvalue) - новое значение */
	auto topA1 = topA0--;

	auto topB = top;
	auto topB0 = topB;
	/* topB1(lvalue) - новое значение; topB0(rvalue) - новое значение */
	auto topB1 = --topB0;

	/* распечатать в обратном порядке  */
	while (top > 0)
	{
		/* --top потому что берем самое последнее и уменьшаем на 1 */
		auto value = arrayOrigin[--top];
		qDebug().noquote() << QString("%1").arg(QString::number(value));
	}

	/* распечатать в обратном порядке не получится т.к. top = 0 */
	/* стэк поинтер понизился значит что там выше - наплевать  */
	while (top > 0)
	{
		cout << arrayOrigin[--top] << "\t";
	}

	arrayOrigin;
	auto stop{ true };
}



void ADSLecture05Ex01::stackBraces()
{
	/* СКОБКИ. ПРОРЕШАТЬ.  */
}

void ADSLecture05Ex01::insertSorting()
{
	/* Сортировка вставками. Прорешать */
}

void ADSLecture05Ex01::arraySorting()
{
	qDebug().noquote() << SEPARATOR_MINI << "FOOL SORT" << SEPARATOR_MINI;

	const int arraySize{ 10000 };

	int arrayOrigin[arraySize]/*{ 5,3,2,1,4 }*/;

	for (int i = 0; i < arraySize; i++)
	{
		/* наихудший случай для сортировки, маскимальное количество возвратов в начало */
		arrayOrigin[i] = arraySize - i;
	}

	bool sorted{ true };

	int i{ 0 };
	/* выводить результат сортировки */
	auto print{ false };

	/* засекли время начала работы алгоритма */
	auto startTime = high_resolution_clock::now();

	/*
	недостаточно одного прохода, потому что в конце может быть значение,
	которое должно быть в начале а мы туда не вернемся, поэтому как только встречаем первый
	слуйчай не сортировки начинаем сначала, именно поэтому while лучше чем for для такой задачи
	*/
	/* в данном случае это fool sort - дурацкая сортировка, простая сортировка */
	/* сложность O(f) такого алгоритма O(n2) значение f называют асимтотикой  */
	/* существует более долгие алгоритмы, например сортировка обезьяны(бого сорт),
	у него асимптотика n! (факториальная асимптотика) */

	while (i < arraySize - 1)
	{
		auto a = arrayOrigin[i];
		auto b = arrayOrigin[++i];
		/* если не отсортировано то ++i будет отменено */
		if (a > b)
		{
			sorted = false;

			/* шифруется 'a' переменной 'b', а т.к. операция симетрична то можно считать что 'b' зашифровано 'a' */
			a = a ^ b;
			/* в 'b' присваиваем зашифрованный 'a' и расшифровываем 'b' значит получаем старое значение 'a' */
			b = a ^ b;
			/* расшировываем первое значение шифра 'a' c помощью 'b'(старое а) */
			a = a ^ b;

			arrayOrigin[i - 1] = a;
			arrayOrigin[i] = b;
			/* начинаем сначала чтобы не пропустить ранее не сортрированные элементы */
			/* например 321: шаг 1 -> 231 ... -> 213 */

			i = 0;
		}
	}

	/* засекли время конца работы алгоритма */
	auto endTime = high_resolution_clock::now();
	/* получили разницу */
	auto duration = duration_cast<microseconds>(endTime - startTime);
	auto mcs = duration.count();
	auto ms = duration.count() / 1000;
	mcs = mcs - ms * 1000;

	/* для сортировки 10000 получили 315 s 628 ms 423 mcs */
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
		/* наихудший случай для сортировки, маскимальное количество возвратов в начало */
		arrayOrigin[i] = arraySize - i;
	}

	bool sorted{ false };

	/* выводить результат сортировки */
	auto print{ false };

	/* засекли время начала работы алгоритма */
	auto startTime = high_resolution_clock::now();

	/* засекли время конца работы алгоритма */
	auto endTime = high_resolution_clock::now();

	/* пузрьковая сортировка */
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


	/* получили разницу */
	auto duration = duration_cast<microseconds>(endTime - startTime);
	auto mcs = duration.count();
	auto ms = duration.count() / 1000;
	mcs = mcs - ms * 1000;

	/* для сортировки 10000 получили 0 s 0 ms 6 mcs */
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
	int x = 5; /* имя переменной, когда к ней обращаемся, в каком то смысле это ее разыменованный адрес */
	/* создаем ячейку памяти типа 'int *' */
	/* ложим туда адрес 'x' */
	int *px = &x;
	/* &px - адрес ячейки замяти 'px' */
	int **ppx = &px;
	/* &ppx - адрес ячейки замяти 'ppx' */
	int ***pppx = &ppx; /* можно продолжать бесконечно */
	/* как можно достуПится к числу '5'?: */
	/* как можно достуПится к числу '5'?: */
	/* 1. По имени переменной (имя переменной это всегда ее константный адрес) */
	std::cout << x;
	/* 2. берется значение ячейки px, и разыменовывается ее значение (адрес) который в ней лежит,
	то есть обращаемся по адресу лежащему в ячейке px, таким образом доступаемся до той же самой 5ке */
	auto case2 = *px;
	std::cout << *px;
	/* 3.,4. аналогичный случаи с **ppx и с ***pppx */
	/* одна звездочка сняла одну звездочку с типа вторая вторую и так далее */
	auto case3 = **ppx; /* */
	std::cout << **ppx;
	auto case4 = ***pppx; /* */
	std::cout << ***pppx;
	/* !!! если написать ещё одну * передед ***pppx, то будет ошибка потому что тип int (5), int жто просто число и это не адресный тип */
	//auto case5 = ****pppx; /* Добавили ещё одну * - ошибка компиляции */

}

void ADSLecture06Ex01::goThrough(NodeT * pBegin)
{
	while (pBegin != nullptr)
	{
		/* по адресу pBegin взять значение элемента структуры */;
		qDebug().noquote() << (*pBegin).data; /* равносильно  pBegin->data */
		/* *pBegin.data не работает */
		//qDebug().noquote() << *pBegin.data;
		//pBegin /* адрес на звено */
		/* чтобы идти дальше нам нужно адресу присвоить адрес на следующее звено */
		pBegin = (*pBegin).next;
	}
}

void ADSLecture06Ex01::generateNodes()
{
	const int nodesSize{ 5 };
	NodeT nodes[nodesSize];

	/* формируем цепочку */
	for (int i = 0; i < nodesSize; i++)
	{
		nodes[i].data = i + 1;

		if (i != nodesSize - 1)
		{
			nodes[i].next = nodes/* адрес первого элемента */ + i + 1;
		}
		else
		{
			nodes[i].next = nullptr; /* говорим что это последний элемент */
		}
	}

	/* указатель на начло */
	NodeT *pBegin = nodes; /* адрес начала */
	/* чтобы не потерять, копируем указатель на начало */

	/* ф-ия перебора */
	goThrough(pBegin);
}


void ADSLecture06Ex01::generateNodesUnlim()
{
	/* выделение памяти */
	/* для чего нужны связные списки? на них можно: */
	/* - организовать стэк  */
	/* - организовать очередь */
	/* - организовать дэк - двойную очередь в которой можно добавлять и в начало и в конец */
	/* - но самое главное - вставка в середину очень эффективны */
	/* выделение памяти для первого элемента */
	NodeT *pBegin = new NodeT;
	/* выделить звено и прицепить его в конец */
	/* для этого создаем указатель и копируем туда стартовый указатель */
	NodeT *p = pBegin;

	const int nodesSize{ 5 };

	for (int i = 0; i < nodesSize; i++)
	{
		/* в начале в p.data ложим данные*/
		p->data = i + 1;
		/*, а в p.next ложим адрес выделенного */
		p->next = new NodeT;
		p = p->next;
	}
	/* у последнего звена ставим nullptr */
	p->next = nullptr;
	p->data = 777; /* иначе там будет мусор */

	/* ф-ия перебора */
	goThrough(pBegin);
}



void ADSLecture06Ex01::arrays2d()
{
	/* двумерыне массивы */
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
		/* исследование памяти, как устроен массив внутри. см. итог */
		/* получить адрес начала массива */
		int *p = reinterpret_cast<int *>(arrayOrigin);

		QStringList out;
		QStringList out2;
		for (int i = 0; i < arraySize*columns; i++)
		{

			out << QString::number(*(p + i)); /* *(p+i) равносильно p[i], а p+i адрес/указатель */

			 /* значение адреса */
			auto itemAddress = (quintptr)(p + i);
			/* значение адреса в строковом формате */
			auto itemAddressStr = QString("0x%1").arg(itemAddress, QT_POINTER_SIZE * 2, 16, QChar('0'));
			out2 << itemAddressStr;

			/*
			!!! можно вывести ещё вот так:
			auto x = p + i;
			std::cout << x << " ";
			*/
		}

		qDebug().noquote() << QString("%1").arg(out.join(" "));
		qDebug().noquote() << QString("%1").arg(out2.join(" "));

		/* ИТОГ: массив лежит последовательно, то есть: a[0][0], a[0][1], a[0][2], a[0][3], a[1][0], ..., a[2][3] */
		/*
		для одномерных массивов:
		при известном i в массиве a[i] найти ячейку памяти
		a[i] = (p + i);
		для двумерных массивов:
		при известном i,j в массиве a[i][j] найти ячейку памяти
		a[i][j] = *(p + i*<ширина массива> + j)  = p[i*<ширина массива> + j]
		при этом  i*<ширина массива> + j это смещение от начала массива в количестве ячеек, чтобы в байтах нужно *sizeof
		и адрес ячейки p + i*<ширина массива> + j
		!!! ВАЖНО: компилятор не сможет определять адреса ячеек для получения данных [i][j] элемента без знания ширины массива


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
			/* или */
			out2 << QString::number(p[i*columns + j]); /* равносильно a[i][j] */

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
	/* 2d массивы и передача их для печати */
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
	/* !!! ДЛЯ ЧЕГО ВСЕ ЭТО?: */
	/* для понимания как устроен двумерный динамический массив */
	const int arraySize{ 3 };
	/* ширина НЕ константа */
	int columns{ 4 };
	/* указатель на указатель на массив А, */
	int **A = new int*[arraySize];
	/* тогда А это ячейка которая хранит в себе хранит адрес, ссылающийся на ячейку типа int*(тип - указатель),
	изначально в ней хранится мусор, пусть **A это будет массив указателей, т.е.  */
	A = new int*[arraySize];

	/*!!! в первой генерации не было. см ниже что было */
	/* вторая генерация - сразу выделяем память */
	A[0] = new int[arraySize*columns];

	/* первая генерация */
	//for (size_t i = 0; i < arraySize; i++)
	/* вторая генерация */
	for (size_t i = 1; i < arraySize; i++)
	{
		/* первая генерация */
		{
			/* то есть в ячейках массивов мы храним одномерные массивы */
			//A[i] = new int[columns]; /* выделили память под ячейку в виде массива */
		}
		/* вторая генерация */
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

	/* НО. Такой подход требует очистки выделенной памяти  */
	/* первая генерация */
	//{
	//	for (int i = 0; i < arraySize; i++)
	//	{
	//		delete[] A[i];
	//	}
	//	delete[] A;
	//}

	/* вторая генерация не требует цикла освобождения памяти */
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

	/* засекли время начала работы алгоритма */
	auto startTime = high_resolution_clock::now();

	/* линейный поиск */
	for (int i = 0; i < arraySize; i++)
	{
		if (A[i] == x)
		{
			result = i;
			break;
		}
	}

	/* засекли время конца работы алгоритма */
	auto endTime = high_resolution_clock::now();
	/* получили разницу */
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
	int left{ -1 }; /* A[left] < x - инвариант цикла поиска (договоренность) */
	int right{ arraySize }; /* A[right] >= x */

	/* засекли время начала работы алгоритма */
	auto startTime = high_resolution_clock::now();

	/* бинарный поиск */
	while (right - left > 1)
	{
		int middle = (left + right) / 2;
		/* левый должен быть меньше чем искомый */
		if (A[middle] < x)
		{
			left = middle;
		}
		else
		{
			right = middle;
		}
	}



	/* засекли время конца работы алгоритма */
	auto endTime = high_resolution_clock::now();
	/* получили разницу */
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
	/* нужно выснять диапазон сортируемых числе, изначаль они от 0 до  arraySize*/
	int F[10] = { 0 }; /* в данном случае {0} - инициализация 0ми, если {1} только первый будет = 1 */
	for (int i = 0; i < arraySize; i++)
	{
		F[A[i]]++; /* собираем частоты */
	}
	int i = 0;
	/* чтобы знать куда частоты выдавать */
	for (int x = 0; x < 10; x++) /* перебор всевозможных значений ключа, их может быть М штук */
	{
		/* и для каждого ключей  */
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
	// *pair++; НЕДОПУСТИМО

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
