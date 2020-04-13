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

	void trash01(); /* new delete pointers */
	void trash02(); /* using of constant links and pointers */
	void temporary();

private:

};