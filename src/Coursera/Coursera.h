#include <iostream>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;


void init();

class YellowWeek01Leson01
{
public:
	YellowWeek01Leson01();
	~YellowWeek01Leson01();

	void temporary();

private:

};

class YellowWeek01Leson02
{
public:
	YellowWeek01Leson02();
	~YellowWeek01Leson02();

	void temporary();
	void trash01();
	void printAvg();

private:

};


class YellowWeek01Leson03
{
public:
	YellowWeek01Leson03();
	~YellowWeek01Leson03();

	struct Date
	{
		int dtYear;
		int dtMonth;
		int dtDay;
	};

	void temporary();
	void trash01();
	void trash02();
	void trash03();

private:
	
};



class Cities
{
public:
	Cities();
	~Cities();

	tuple<bool, string> findCountry(const string & city) const;


private:
	map<string, string> _cityToCountry;
	set<string> _ambiguousCities;

};



class YellowWeek01Leson04
{
public:
	YellowWeek01Leson04();
	~YellowWeek01Leson04();

	enum class Lang
	{
		DE, FR, IT
	};

	struct Region
	{
		string stdName;
		string parentStdName;
		map<Lang, string> names;
		int64_t population;
	};

	int findMaxRepetitionCount(const vector<Region>& regions);

	void temporary();
	void trash01();

private:

	vector<Region> getListRegions(int example = 0);

};


class YellowWeek01Leson05
{
public:
	YellowWeek01Leson05() {}
	~YellowWeek01Leson05() {}

	/* шаблоны функций, преимущество - экономия кода (нет необходимости в нескольких сигнатурах) при одинаковых операциях */
	template<typename T>
	/* 
		в данном случае тип Т должен поддерживать операцию умножения, 
		а поскольку в коде не предусмотрено умножение pair пришлось переопределить ч/з шаблон оператор умножения пар
	*/
	T tmpSqr(T x)
	{
		return x * x;
	}

	void temporary();
	void trash01();
	void trash02();
	void trash03();

private:

};


bool operator < (const YellowWeek01Leson03::Date &lhs, const YellowWeek01Leson03::Date &rhs);
bool operator == (const YellowWeek01Leson04::Region &lhs, const YellowWeek01Leson04::Region &rhs);

template<typename fst, typename scnd>
pair<fst, scnd> operator * (const pair<fst, scnd> & p1, const pair<fst, scnd> & p2);
/*
перегрузка операора вывода в поток '<<'
На вход он Возвращает ссылку на поток, оператор вывода. Принимает поток, в который мы будем выводить данные, и также сам вектор 
*/
template<typename T> 
ostream& operator<<(ostream& out, const vector<T>& anyVector); // изначально только вывод значений вектора целых чисел

template<typename fst, typename scnd>
ostream& operator<<(ostream& out, const pair<fst, scnd> & p);

template<typename key, typename value>
ostream& operator<<(ostream& out, const map<key, value>& anyMap);

// шаблонная функция для подставновки в поток разделителей. На входе коллекция из возможных типов и разделитель
template<typename collection>
string join(const collection& c, char d); 