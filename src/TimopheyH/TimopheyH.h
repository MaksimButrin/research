#include <iostream>
#include <QString>

void init();

class timopheyOOPLecture03Ex01
{
public:
	timopheyOOPLecture03Ex01();
	~timopheyOOPLecture03Ex01();

	void count2(int n = 0);
	void temporary();

private:

};


class timopheyOOPLecture04Ex01
{
public:
	timopheyOOPLecture04Ex01();
	~timopheyOOPLecture04Ex01();

	struct student
	{
		int8_t age{0};
		int16_t group{0};
		QString name{"noname"};
	};

	void studentPrint(const student & s);
	void studentPrint(const student * s);
	void arrayPrint01(double arr[][4]); //must necessarily specify the number of columns
	void arrayPrint02(double **arr, const int h = 0, const int w = 0); // print double array

	void trash01(); /* new delete pointers */
	void trash02(); /* using of constant links and pointers */
	void trash03(); 
	void trash04(); /* static/automatic arrays */
	void trash05(); /* dinamic arrays */
	void trash06(); /* true dinamic arrays */
	void temporary();
	double foo01(const double &x);

private:

};

/* ��������� � ��������� ������ */
/* ������ 2 */
class ADSLecture02Ex01
{
public:
	ADSLecture02Ex01() {};
	~ADSLecture02Ex01() {};
	
	/* ������� �������� */
	void bitOperations();
	void run();
	QString byteToString(int x, bool nubbles = true);
	void binPrintInt(int x, bool nubbles = true);
	/* ������� �����: ������ ����������*/
	QList<int> simpleNumbersSeparator();
	/* ������� ���������: ������ ����������*/
	void simpleFactors(int & number);
	void sf();
private:

};