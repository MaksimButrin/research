#include <Coursera.h>

#include <QDebug>
#include <QString>
#include <string>
#include <QPair>
#include <tuple>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

void init()
{
	YellowWeek01Leson05().temporary();

}


YellowWeek01Leson01::YellowWeek01Leson01()
{
}

YellowWeek01Leson01::~YellowWeek01Leson01()
{
	qDebug() << "\n";
}

void YellowWeek01Leson01::temporary()
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
	qDebug() << "sizeof(double)" << sizeof(double); // 8
	qDebug() << "sizeof(float)" << sizeof(float); // 8
	qDebug() << "sizeof(vector<int>)" << sizeof(vector<int>); // 32
	qDebug() << "sizeof(vector<uint>)" << sizeof(vector<uint>); //32
	qDebug() << "sizeof(vector<int16_t>)" << sizeof(vector<int16_t>);
	qDebug() << "limits for <int>" << QString("min %1, max %2").arg(QString::number(numeric_limits<int>::min())).arg(QString::number(numeric_limits<int>::max()));
	qDebug() << "limits for <size_t>" << QString("min %1, max %2").arg(QString::number(numeric_limits<size_t>::min())).arg(QString::number(numeric_limits<size_t>::max()));

	qDebug() << "limits of <long long int> is" << QString("min %1, max %2").arg(QString::number(numeric_limits<long long int>::min())).arg(QString::number(numeric_limits<long long int>::max()));
	qDebug() << "limits of <long int> is" << QString("min %1, max %2").arg(QString::number(numeric_limits<long int>::min())).arg(QString::number(numeric_limits<long int>::max()));
	qDebug() << "limits of <double> is" << QString("min %1, max %2").arg(QString::number(numeric_limits<double>::min())).arg(QString::number(numeric_limits<double>::max()));
	qDebug() << "limits of <float> is" << QString("min %1, max %2").arg(QString::number(numeric_limits<float>::min())).arg(QString::number(numeric_limits<float>::max()));
}

YellowWeek01Leson02::YellowWeek01Leson02()
{
}

YellowWeek01Leson02::~YellowWeek01Leson02()
{
}

void YellowWeek01Leson02::temporary()
{
	vector<int> v{ 1, 4, 6, 2, 5 };

	size_t n = 1;
	size_t m = 2;

	for (size_t i = n; i + m < v.size(); ++i)
	{
		qDebug().noquote() << v[i];
	}
	qDebug().noquote() << " === ";

	for (size_t k = v.size(); k > 0; --k)
	{
		auto i{ k - 1 };
		qDebug().noquote() << v[i];
	}

	qDebug().noquote() << " === ";


	for (size_t k = v.size(); k > n + m; --k)
	{
		auto i{ k - m - 1 };
		qDebug().noquote() << v[i];
	}

	qDebug().noquote() << " === ";
}

void YellowWeek01Leson02::trash01()
{
	vector<int> v{ 1, 4, 6 };
	/*
	если использовать
	i < v.size() - 1 вместо i + 1 < v.size()
	то при пустом векторе получим exeption
	*/
	for (size_t i = 0; i + 1 < v.size(); ++i)
	{
		qDebug().noquote() << v[i];
	}
}

void YellowWeek01Leson02::printAvg()
{
	vector<int> t = { -8,-7,3 };
	int sum{ 0 };

	// range based for
	for (int x : t)
	{
		sum += x;
	}

	auto avg = sum / static_cast<int>(t.size());

	qDebug() << "avg = sum / t.size() is equals " << avg;
}

YellowWeek01Leson03::YellowWeek01Leson03()
{
	qDebug() << "\n";
}

YellowWeek01Leson03::~YellowWeek01Leson03()
{
	qDebug() << "\n";
}

void YellowWeek01Leson03::temporary()
{
	trash03();
}

void YellowWeek01Leson03::trash01()
{
	/* сравнение дат */
	auto res = (Date{ 2015,6,3 } < Date{ 2015, 6, 5 }) ? "left date is less" : "left date not less";
	qDebug().noquote() << res;
}

void YellowWeek01Leson03::trash02()
{
	/*
	кортежи
	некоторое подобие структур,
	большой недостаток - обращение к элементу структуры только по индексу
	*/
	/* в QT нет кортежей */
	//tuple tpl00(7, "c++", true); /* вариант C++17 */
	tuple<int, string, bool> tpl01(7, "c++", true); /* 1ый вариант обявления */
	auto tpl02 = make_tuple(7, "c++", true); /* 2ый вариант обявления */
	qDebug().noquote() << QString("second element in tuple tpl01 is '%1'").arg(get<1>(tpl02));
}

void YellowWeek01Leson03::trash03()
{
	/* пары и перебор по словарю*/
	auto pair01 = make_pair(7, "c++");
	qDebug().noquote() << QString("1st element in pair '%1' is '%2', 2nd is '%3'").arg("pair01").arg(pair01.first).arg(pair01.second);

	QPair<int, QString> qPair01{ 88, "QT C++" };
	qDebug().noquote() << QString("1st element in pair '%1' is '%2', 2nd is '%3'").arg("qPair01").arg(qPair01.first).arg(qPair01.second);

	map<int, string> digits{ {1, "one"}, {2, "two"} };
	for (const auto & item : digits)
	{
		/* oheret' !*/
		QString exampleConvert01{ item.second.c_str() };
		QString exampleConvert02 = QString::fromStdString(item.second);
		qDebug().noquote() << QString("item.first is '%1', item.second is '%2'").arg(item.first).arg(item.second.c_str());
	}
	/* по факту в map каждый элемент предтсавляет собой pair: */
	for (const pair<int, string>&item : digits)
	{
		/* oheret' !*/
		QString exampleConvert01{ item.second.c_str() }; // Возвращает указатель на массив символов с завершающим нулем, который содержит данные, идентичные тем, что хранятся в строке
		QString exampleConvert02 = QString::fromStdString(item.second); // более предпочтительно, т.к c_str неведомая хрень
		qDebug().noquote() << QString("item.first is '%1', item.second is '%2'").arg(item.first).arg(item.second.c_str());
	}

}

bool operator<(const YellowWeek01Leson03::Date & lhs, const YellowWeek01Leson03::Date & rhs)
{
	/* слишком много памяти будет потрачено, оптимальнее использовать кортежи (tuple)*/
	/*
	return (vector<int>{lhs.dtYear, lhs.dtMonth, lhs.dtDay}) < (vector<int>{rhs.dtYear, rhs.dtMonth, rhs.dtDay});
	*/

	/* используем кортежи, кортеж не следует использовать как замену структуре */
	auto lhs_key = tie(lhs.dtYear, lhs.dtMonth, lhs.dtDay);
	auto rhs_key = tie(rhs.dtYear, rhs.dtMonth, rhs.dtDay);
	return lhs_key < rhs_key;

	/*
	if (lhs.dtYear != rhs.dtYear)
	{
		return lhs.dtYear < rhs.dtYear;
	}

	if (lhs.dtMonth != rhs.dtMonth)
	{
		return lhs.dtMonth < rhs.dtMonth;
	}

	return lhs.dtDay < rhs.dtDay;
	*/




	/*
	if (lhs.dtYear < rhs.dtYear)
	{
		if (lhs.dtMonth < rhs.dtMonth)
		{
			return lhs.dtDay < rhs.dtDay;
		}
	}

	return false;*/
}

bool operator==(const YellowWeek01Leson04::Region & lhs, const YellowWeek01Leson04::Region & rhs)
{
	auto result{ false };

	auto lhsKey = tie(lhs.stdName, lhs.parentStdName, lhs.population, lhs.names);
	auto rhsKey = tie(rhs.stdName, rhs.parentStdName, rhs.population, rhs.names);

	return lhsKey == rhsKey;

	/*
		все что нужно сделано выше, нету смысла в нижнем коде
		не было уверенности что сравнение кортежей будет работать с MAP
	*/
	if (lhsKey == rhsKey)
	{
		result = true;
		for (auto &lhsItem : lhs.names)
		{
			auto lhsItemKey = tie(lhsItem.first, lhsItem.second);

			auto rhsItemSecond = rhs.names.at(lhsItem.first);
			auto rhsItemKey = tie(lhsItem.first, rhsItemSecond);
			if (rhsItemKey != lhsItemKey)
				result = false;
		}
	}

	return result;
}


YellowWeek01Leson04::YellowWeek01Leson04()
{
	qDebug() << "\n";
}

YellowWeek01Leson04::~YellowWeek01Leson04()
{
	qDebug() << "\n";
}

int YellowWeek01Leson04::findMaxRepetitionCount(const vector<Region>& regions)
{
	auto currenMaximum{ 0 };

	for (size_t curentItem = 0; curentItem < regions.size(); ++curentItem)
	{
		auto result{ 1 };

		for (size_t item = 0; item < regions.size(); ++item)
		{
			if (curentItem != item)
				result += regions.at(curentItem) == regions.at(item);
		}

		currenMaximum = max(currenMaximum, result);

	}

	return currenMaximum;
}

void YellowWeek01Leson04::temporary()
{
	auto count{ 0 };
	QString message{ "result of '%1' equals '%2' " };

	count = findMaxRepetitionCount(getListRegions(1));
	qDebug().noquote() << message.arg("getListRegions(1)").arg(count);

	count = findMaxRepetitionCount(getListRegions(2));
	qDebug().noquote() << message.arg("getListRegions(2)").arg(count);
}



void YellowWeek01Leson04::trash01()
{
	Cities cities;
	bool success;
	string message;
	tie(success, message) = cities.findCountry("Volgograd");

	qDebug().noquote() << QString("success '%1', message '%2'").arg(success).arg(QString::fromStdString(message));
	/*
	в C++ 17 появилось т.к. structured bindings, в этом случае не нужно обявлять заранее переменные и код сводится к вот такому варианту
	По сути, этот метод нам вернет кортеж, мы его сразу распакуем в эту пару переменных
	*/
	//auto [success, message] = cities.findCountry("Volgograd");
}


vector<YellowWeek01Leson04::Region> YellowWeek01Leson04::getListRegions(int example)
{
	vector<YellowWeek01Leson04::Region> regions{};

	switch (example)
	{
	case 1:
		regions =
		{
		{
			"Moscow",
			"Russia",
			{{Lang::FR, "Moscou"}, {Lang::DE, "Moskau"}, {Lang::IT, "Mosca"}},
			89
		},
		{
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		},
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		},
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		},
		{
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		},
		};

		break;

	case 2:
		regions =
		{
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		},
		{
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		},
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			89
		},
		{
			"Moscow",
			"Toulouse",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		},
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			31
		},
		};

		break;

	default:
		break;
	}



	return regions;
}

/* ==================== week 01 exercise 05 ======================= */

Cities::Cities()
{
}

Cities::~Cities()
{
}

tuple<bool, string> Cities::findCountry(const string & city) const
{
	/*
	поскольку метод константный то при обращении к map посредством [], будет добавлен элемент что недопустимо и компилятор выдаст ошибку компиляции
	поэтому, в таких случаях обращаемя посредством метода at()
	*/
	if (_cityToCountry.count(city) == 1)
	{
		return make_tuple(true, _cityToCountry.at(city));
	}
	else if (_ambiguousCities.count(city) == 1)
	{
		return make_tuple(false, "Ambiguous");
	}

	return make_tuple(false, "Not Exist");
}

void YellowWeek01Leson05::temporary()
{
	vector<vector<int>> vInt{ {1, 2}, {3}, {9,8,86} };
	vector<double> vDbl{1.5, 2.4, 3.3};
	//qDebug().noquote() << vInt; // переопределение для qDebug не удалось (qDebug может сам делать вывод). Почему ?
	cout << vInt << endl;
	cout << vDbl << endl;

	map<int, double> mp{ {1,2.5},{6,7.7} };
	cout << mp << endl;
}

void YellowWeek01Leson05::trash01()
{
	auto pair01 = make_pair(2.5, 3);
	QString message{ "first is '%1', second is '%2' " };
	auto resPair01 = tmpSqr(pair01);
	qDebug().noquote() << message.arg(resPair01.first).arg(resPair01.second);

}

void YellowWeek01Leson05::trash02()
{
}

void YellowWeek01Leson05::trash03()
{
}

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& anyVector)
{
	//Так как операторы вывода в поток возвращают ссылку на поток, в который они выводят, 
	//то можно сразу написать return 
	return out << '[' << join(anyVector, ',') << ']';

	/* код ниже без join */
	for (const auto &item : anyVector)
	{
		out << item << " ";
	}

	return out;
}

template<typename key, typename value>
ostream& operator<<(ostream& out, const map<key, value>& anyMap)
{
	return out << '{' << join(anyMap, ',') << '}';
	
	/* код ниже без join */
	for (const auto &item : anyMap)
	{
		out << join(anyMap, ',') << ' ';
	}

	return out;
}

template<typename collection>
string join(const collection & c, const char d)
{
	stringstream ss;
	auto first{ true };
	for (const auto & item : c)
	{
		if (!first)
		{
			ss << d;
		}
		first = false;
		ss << item;
	}
	return ss.str();
}


template<typename fst, typename scnd>
inline pair<fst, scnd> operator*(const pair<fst, scnd>& p1, const pair<fst, scnd>& p2)
{
	fst f = p1.first * p2.first;
	scnd s = p1.second * p2.second;
	return make_pair(f, s);
}

template<typename fst, typename scnd>
ostream& operator<<(ostream& out, const pair<fst, scnd> & p)
{
	out << '(' << p.first << ", " << p.second << ')';
	return out;
}