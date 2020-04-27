#include <TimopheyH.h>

#include <QDebug>
#include <array>
//#include <math.h> //old style include from C
#include <cmath> //current style include from C


using namespace std;

void init()
{
	timopheyOOPLecture04Ex01().temporary();

	timopheyOOPLecture04Ex01().trash01();
	timopheyOOPLecture04Ex01().trash02();
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
	a[0] = new double [height * width];

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
