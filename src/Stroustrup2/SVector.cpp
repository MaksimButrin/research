#include <SVector.h>
#include <QSharedPointer>

// vector
namespace sv
{

void run()
{
	//WorkWithSvector().run();
	//WorkWithAnother().run();
	testX();
	//testPalindrome();
}

/* записки про указатели */
void infoPointers()
{
	/* стр ...650... */
	/* оператор new делает доступной динамическую память (которую ещё называют КУЧЕй) */
	/* а память выделяемая для использования при вызове ф-ии для хранения ее аргументов и лок. пер. - СТЭКОМ */
	/* в данном случае инструкция просит систему поддержки выполнения программ резместить четыре числа типа double */
	/* в ДИНАМИЧЕСКОЙ памяти (куче) и вернуть указатель на первое из них */
	double *p = new double[4]; /* размещаем 4ре числа в куче (динамической памяти) */
	/* количество элментов может в данном случае задаваться переменной */
	int n{ 5 };
	double *pd = new double[n];
	/* разрешение присваивания друг другу указателей разных типов привело бы */
	/* к TYPE ERROR - ошибкам типов */

	/* ИНИЦИАЛИЗАЦИЯ */
	/* обявлять указатели без инициализации ОПАСНО */
	/* если указано кол-во инициализированных элементов */
	int *p1 = new int[4]{ 0,1,2 };
	/* как здесь, то размер массива указывать не обязательно */
	/* НО в моем компиляторе - ОШИБКА */
	// int *p2 = new int[] { 0, 1, 2, 4 };

	/* двойное удаление */
	int * р2{ 0 };
	// Отлично : никаких действий не нужно
	delete р2;
	// То же самое - по-прежнему ника ких действий
	delete р2;


	SVector *sv = new SVector(6);

	//QSharedPointer<SVector> shp1 = QSharedPointer<SVector>::create(5);
	//QSharedPointer<SVector> shp2 = QSharedPointer<SVector>(new SVector(5));
	//QSharedPointer<SVector> shp3(new SVector(5));

	//QVector<int> v;
	//auto c = v.capacity(); //оставшееся место
}

/* 17. Векторы и динамическое выделение памяти */
/* 17.2. Основы */
SVector::SVector(int s)  // через : это список инициализации членов класса
	/* инициализация члена _sz */
	: _sz(s),
	/* инициализация члена _elem, выделение памяти */
	_elem{ new double[s] }
{
	qDebug().noquote() << QString("'SVector', size %1: called Costructor").arg(_sz);

	/* инициализация элементов */
	for (int i = 0; i < s; i++)
	{
		_elem[i] = 0;
	}

}

SVector::SVector(std::initializer_list<double> lst)
	: _sz{ (int)lst.size() },
	// неинициализированная память
	_elem{ new double[(int)lst.size()] }
{
	// initializer_list НЕ поддерживает оператор индексации([])
	//инициализация с помощью std::copy();(раздел Б.5.2)
	std::copy(lst.begin(), lst.end(), _elem);
}



SVector::SVector(const SVector & arg)
// размещает элементы, инициализирует их копированием
	: _sz{ arg._sz }, _elem{ new double[arg._sz] }
{
	std::copy(arg._elem, arg._elem + _sz, _elem);
}

// делаем данный вектор копией source
SVector & SVector::operator=(const SVector & source)
{
	// версия из 18.3.2 копирующее присваивание
	if (false)
	{
		double * p = new double[source._sz]; // выделение памяти, на случай самоприсваивания (v=v)
		std::copy(source._elem, source._elem + source._sz, p); // копирование элементов из источника
		delete[] _elem; // освобождение памяти из целевого объекта класса
		_elem = p; // переназначение указателя на новые элементы
		_sz = source._sz;
	}
	// версия из 19.2.5. Присваивание
	{
		// Самоприсваивание , ничего делать не надо
		if (this == &source)
		{
			return *this;
		}

		// Памяти достаточно, новая память не нужна
		if (source._sz <= _space)
		{
			for (int i = 0; i < source._sz; ++i)
			{
				_elem[i] = source._elem[i]; // Копируем элементы
			}
			_sz = source._sz;
			return *this;
		}

		double * p = new double[source._sz]; //Выделяем новую память
		for (int i = 0; i < source._sz; ++i)
		{
			p[i] = source._elem[i]; // Копируем элементы
		}
		delete[] _elem; // Освобождаем старую память
		_space = _sz = source._sz; // Устанавливаем новый размер
		_elem = p; //Устанавливаем указатель на новые элементы
	}

	return *this; //возврат ссылки на себя
}

SVector::SVector(SVector && a)
// копируем elem и size из 'a'
	: _sz{ a._sz }, _elem{ a._elem }
{
	// делаем исходный вектор пустым
	a._sz = 0;
	a._elem = nullptr;
}

// Перемещаем source в текущий вектор
SVector & SVector::operator=(SVector && source)
{
	delete[] _elem; // освобождение старой памяти
	_elem = source._elem; // Копирование elem и ...
	_sz = source._sz; // и sz из исходного вектора ...
	// делаем исходный вектор пустым
	source._sz = 0;
	source._elem = nullptr;

	return *this; // возврат ссылки на себя
}

SVector::~SVector()
{
	qDebug().noquote() << QString("'SVector', size %1: called Destructor").arg(_sz);

	/* освобождение памяти выделенной с помощью оператора new для массива объектов */
	delete[] _elem;
	/* delete без [] - освобождает память выделенную с помощью оператора new для отдельного объекта */
	double * p = new double(8.8);
	delete p;
}



double SVector::get(int n) const
{
	return _elem[n];
}



void SVector::set(int n, double v)
{
	_elem[n] = v;
}

bool SVector::reserve(int newAlloc)
{
	// размер никогда не уменьшается
	if (newAlloc <= _space)
	{
		return false;
	}
	// выделение новой памяти
	double * p = new double[newAlloc];
	for (int i = 0; i < _sz; ++i)
	{
		// копируем старые элементы
		// новые эелменты не инициализируем, это задача других методов
		p[i] = _elem[i];
	}

	// освобождение старой памяти
	delete _elem;

	_elem = p;
	_space = newAlloc;

	return true;
}



void SVector::resize(int newSize)
// Создаем вектор, содержащий newSize элементов
// Инициализируем каждый элемент зна чением по умолчанию 0.0
{
	if (!reserve(newSize))
		return;

	for (int i = _sz; i < newSize; ++i)
	{
		// новые эелменты инициализируем значением '0'
		_elem[i] = 0;
	}
}



void SVector::pushBack(double d)
// Увеличивает ра змер вектора на единицу;
// инициализирует новый элемент зна чением d
{
	if (_space == 0)
	{
		// выделяем память для 8 эелментов (почему именно 8?)
		reserve(8);
	}
	else if (_sz == _space)
	{
		// выделяем дополнительную память
		reserve(2 * _space);
		// если у нас нет свободной памяти, то мы удваиваем размер
		// выделенной памяти.На практике эта стратегия оказывается очень
		// удачной, поэтому она используется в большинстве реализаций масса
		// vector из стандартной библиотеки
	}
	// добавляем 'd' в конец вектора 
	_elem[_sz] = d;
	//увеличивем количество элементов
	++_sz;
}



void SVector::print() const
{
	for (int i = 0; i < size(); ++i)
	{
		qDebug().noquote() << QString("v[%1] == %2").arg(i).arg(get(i));
	}
}


SVector * svPtr(int s)
{
	printName("svPtr");

	/* вектор в динамической памяти */
	SVector * p = new SVector(s);
	/* ... используем *p */
	return p;
}

/* вывести размеры типов */
void printSizes()
{
	qDebug().noquote() << SEPARATOR;
	char ch;
	int i;
	int * pi;

	qDebug().noquote() << QString("size of 'char': ") << sizeof(ch);
	qDebug().noquote() << QString("size of 'i': ") << sizeof(i);
	qDebug().noquote() << QString("size of 'pi': ") << sizeof(pi);
}


// 18.4.2 Отладка конструкторов и деструкторов
// !!! смысл, того что ниже, не понятен
X glob(2); // глобальная переменная
X copy(X a) { return a; } // копирующий конструктор
X copy2(X a) { X aa = a;  return aa; }  // копирующий конструктор
X & refTo(X& a) { return a; } // копирующее присваивание
X * make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

void testX()
{
	printName("X loc{ 4 };");
	X loc{ 4 }; // локальная переменная
	printName("X loc2{ loc };");
	X loc2{ loc }; // копирующий конструктор
	printName("loc = X{ 5 };");
	loc = X{ 5 }; // копирующее присваивание
	printName("loc2 = copy(loc);");
	loc2 = copy(loc); // передача по значению и возврат
	printName("loc2 = copy2(loc);");
	loc2 = copy2(loc);
	printName("X loc3{ 6 };");
	X loc3{ 6 };
	printName("X &r = refTo(loc);");
	X &r = refTo(loc); // передача по ссылке и возврат
	printName("delete make(7);");
	delete make(7);
	printName("delete make(8);");
	delete make(8);
	printName("QVector<X> v(4);");
	QVector<X> v(4); //значения по умолчанию
	printName("XX loc4;");
	XX loc4;
	printName("X*p = new X{ 9 };");
	X*p = new X{ 9 }; // X В динамической памяти
	printName("delete p;");
	delete p;
	printName("X*pp = new X[5];");
	X*pp = new X[5]; // массив X В динамической памяти
	printName("delete pp; !!! NOT call - ERROR");
	//delete pp;
	printName("THE END");
}



void testPalindrome()
{
	constexpr int max = 128;
	for (char s[max]; readWord(std::cin, s, max); )
	{
		QString str;
		str.append(s);
		str.append(" is");
		str.append(!isPalindrome(s, std::strlen(s)) ? " not" : "");
		str.append(" palindrome");
		qDebug().noquote() << str;
	}
};











/* =============================================================  */
WorkWithSvector::WorkWithSvector()
{
	qDebug().noquote() << QString("'WorkWithSvector': called costructor");
}


WorkWithSvector::~WorkWithSvector()
{
	qDebug().noquote() << QString("'WorkWithSvector': called destructor");

}


void WorkWithSvector::run()
{
	/* 17.5 деструторы */
	//f3(5);
	/* 17.6 доступ к элементам */
	//f4(5);
	/* 17.7 Указатели на объекты класса */
	//ff();
	// 18.2 Использование конструктора со списком инициализации
	// usingInitializerList();
	// 18.3 копирование векторов
	// copyСonstructor();
	// 18.3.3. копирующее присванивание 
	//copyAssignment();
	simpleAccess();
}

void WorkWithSvector::f3(int n)
{
	printName("f3");
	/* выделяем память для n чисел типа double */
	double*p = new double[n];
	/* определяем вектор (выделяем память для n других double) */
	auto stopDebug01{ true };
	SVector v(n);
	auto stopDebug02{ true };

	/* используем 'v' и 'p' */
	/* .... */

	/* освобождаем паять, занятую массивом чисел типа double */
	delete[] p;

} // SVector автоматически освободит память, занятую объектом 'v'.



void WorkWithSvector::f4(int n)
{
	printName("f4");

	SVector v(5);
	for (int i = 0; i < v.size(); ++i)
	{
		v.set(i, 1.1*i);
		qDebug().noquote() << QString("v[%1] == %2").arg(i).arg(v.get(i));
	}
}

void WorkWithSvector::ff()
{
	//printName("ff");

	SVector * q = svPtr(4);
	/* ... используем *q */
	delete q;
}

void WorkWithSvector::voidAsterisk(void * pv)
{
	/* указателю типа void* можно присвоить указатель на любой объект */
	/* ОК: int * превращается в void* */
	void * pv1 = new int;
	/* ОК: double * превращается в void* */
	void * pv2 = new double[10];
	/* Поскольку компилятор ничего не знает о том, на что ссылается указатель
	типа void* , мы должны сообщить ему об этом */
	void *pv3 = pv; // правильно (тип void * для этого и предназначен
	//double * pd = pv; // ОШИБКА: невозможно привести тип void* к double*
	//*pv = 7; // ОШИБКА: невозможно разыменовать void * (тип объекта, на который указывает pv, неизвестен)
	//pv[2] = 9; // ОШИБКА: void* нельзя индексировать
	int *pi = static_cast<int*>(pv); // ОК: явное преобразование
}

void WorkWithSvector::ptrAndLink()
{
	// =============== УКАЗАТЕЛИ ===========
	int x{ 10 };
	/* для получения указателя нужен оператор '&' */
	int * p = &x;
	// для присвоения значения переменной 'х' через указатель 'p' используется '*' (оператор разыменования)
	*p = 7;
	// считыавем значение 'х' c помощью указателя 'p'
	int x2 = *p;
	// получаем указaтель на другую переменную типа int
	int *p2 = &x2;
	//указатели 'p2' и 'p' указывают на переменную 'х'
	p2 = p;
	// указтель 'p' указывает на другой объект
	p = &x2;

	// ================ ССЫЛКИ ==================
	int y{ 10 };
	// символ '&' означает тип, а не инициализатор (??? то есть '&' для получения адреса, это инициализатор)
	int &r = y;
	// присвоение значения переменной 'y' c помощью ссылки 'r' (оператор * не нужен :))
	r = 7;
	// считываем переменную 'y' c помощью ссылки 'r' (оператор * не нужен)
	int y2 = r;
	// ссылка на другую переменную типа int
	int &r2 = y2;
	// значение переменной 'y' присваивается переменной 'y2'
	r2 = r;
	// ОШИБКА: нельзя изменить значение ссыли (нельзя присовить int* ссылке int&)
	//r = &y2;
}

void WorkWithSvector::usingInitializerList()
{
	printName("usingInitializerList");
	SVector v1 = { 2.5, 5.0, 12.8 };
	// Обратите внимание. что мы использовали круглые скобки для количества
	// элементов, а фигурные - для списков элементов
	// Если у компилятора есть выбор, то значение в фигурных скобках{ } он трактует как значение элемента
	// и передает его конструктору как элемент initializer_list.
	SVector v2{ 3.3 }; //ФИГУРНЫЕ скобки: ОДИН ЭЛЕМЕНТ со значением 3.3
	SVector v3(3); //КРУГЛЫЕ скобки: Три элемента со значениями ПО УМОЛЧАНИЮ 0.0

	printName("v1");
	v1.print();

	printName("v2");
	v2.print();

	printName("v3");
	v3.print();
}



void WorkWithSvector::copyСonstructor()
{
	/*18.3 Копирование */
	// определяем вектор из трех элементов
	SVector v(3);
	//устанавливаем v[2] равным 2.2
	v.set(2, 2.2);
	// что здесь происходит, если ничего не менять ?
	// при выходе из ф-ии будут дважды удалены _elem, т.к. 
	// при копировании было выполнено копирование указателей а не выделение памяти и занесение данных
	// нужен конструктор копирования
	SVector v2 = v;

	// проверка после добавления конструтора копирования
	SVector v3(3);
	v3.set(2, 2.2);
	SVector v4 = v3;
	// другой вариант вызова конструктора копирования
	// SVector v4 {v3};
	v3.set(1, 99);
	v4.set(0, 88);
	// печать результатов
	printName("18.1");
	printName("v3");
	v3.print();
	printName("v4");
	v4.print();

}

void WorkWithSvector::copyAssignment()
{
	/*18.3.2 копирующее присванивание */
	// определяем вектор из трех элементов
	SVector v1(3);
	v1.set(2, 2.2);
	SVector v2(2);
	v2 = v1;
	// печать результатов
	printName("18.2");
	printName("v1");
	v1.print();
	printName("v2");
	v2.print();

}

void WorkWithSvector::movingAssignment()
{
}

SVector WorkWithSvector::fill(std::istream & is)
{
	SVector res(0); // на текущий момент безсмысленно т.к. нет ф-ий расширения размера вектора

	for (double x; is >> x; )
	{
		res.pushBack(x); // на момент 18.3.4. безсмысленно т.к. нет ф-ий добавления
	}
	// Для реализации возврата неявно используется перемещающий конструктор.
	// Компилятору известно, что возвращаемая локальная переменная
	// (res) выходит из области видимости, так что ее можно перемещать, а не
	// копировать.
	return res;
}

void WorkWithSvector::explicitConstructors()
{
	// // класс vector, имеет конструктор, принимающий аргумент типа int, откуда следует, что
	// // он определяет преобразование типа int в класс vector, то есть возможно следующее:
	// SVector v = 10; // Создаем вектор из 10 double. 
	// v = 20; // Присваиваем вектору v новый вектор из 20 double Бред?  Да
	// auto f = [](const SVector & sv) {};
	// f(10); // Бред - вызываем ф-ию f с новым вектором из 10 double
	// // то есть поведение которое явно не очевидно, для исключения таких ситуаций нужно
	// // пометить конструктор ключевым словом explicit
}

void WorkWithSvector::simpleAccess()
{
	printName("simpleAccess");

	SVector v1(10);
	for (int i = 0; i < v1.size(); ++i)
	{
		v1[i] = i;
	}

	v1.print();

	const SVector v2(10);
	// если не предусмотреть const версию оператора индексирования
	// то то что ниже работать не будет
	double d = v2[1]; //это не работало бы

	//SVector v3();
}



void WorkWithAnother::run()
{
	//doubleLinkedList0();
	//doubleLinkedList1();
	doubleLinkedList2();
}



MList::MList()
{
}

MList::~MList()
{
}

// вставка перед элементом
MLink0 * MList::insert(MLink0 * p, MLink0 * n)
{
	if (!n)
		return p;
	if (!p)
		return n;

	// 'p' следует после 'n'
	n->_succ = p;
	// 'n' следует после предшественника 'p'
	if (p->_prev)
		p->_prev->_succ = n;
	// предшественник 'p' становится предшественником 'n'
	n->_prev = p->_prev;
	// 'n' становится предшественником 'p'
	p->_prev = n;
	return n;
}

// вставка после элемента
MLink0 * MList::add(MLink0 * p, MLink0 * n)
{
	if (!n)
		return p;
	if (!p)
		return n;

	// 'p' следует перед 'n'
	n->_prev = p;
	// 'n' следует перед последующим 'p'
	if (p->_succ)
		p->_succ->_prev = n;
	// последующим 'n' становится последующий 'p'
	n->_succ = p->_succ;
	//последующий p становится n
	p->_succ = n;

	return n;
}

// удаление элемента
MLink0 * MList::erase(MLink0 * p)
{
	if (!p)
		return nullptr;
	// смена у последующего значения предыдущего на предыдущий у 'p'
	if (p->_succ)
		p->_succ->_prev = p->_prev;
	// смена у предыдущего значения последующего на последующий у 'p'
	if (p->_prev)
		p->_prev->_succ = p->_succ;

	// возврат последующего т.к. теперь он на месте 'p'
	return p->_succ;
}

// поиск узла с заданным значением
MLink0 * MList::find(MLink0 * p, const QString & s)
{
	while (p)
	{
		if (p->_value == s)
			return p;
		p = p->_succ;
	}
	return nullptr;
}

// переход к n-му последующему узлу
MLink0 * MList::advance(MLink0 * p, int n)
{
	if (!p)
		return nullptr;

	if (n > 0)
	{
		// n-- используется текущее значение, а потом декремент
		while (n--)
		{
			p->_succ == nullptr ? nullptr : p->_succ;
		}
	}
	else if (n < 0)
	{
		while (n++)
		{
			p->_prev == nullptr ? nullptr : p->_prev;
		}
	}

	return p;
}

void MList::print(MLink0 * p)
{
	printName("List of gods");
	while (p)
	{
		QString v{ p->_value };
		if (p->_succ)
			v += QString(",");

		p = p->_succ;

		qDebug().noquote() << v;
	}
}

void MList::print(MLink1 * p)
{
	printName("List of gods");
	while (p)
	{
		QString v{ p->_value };
		if (p->next())
			v += QString(",");

		p = p->next();

		qDebug().noquote() << v;
	}
}


void WorkWithAnother::doubleLinkedList0()
{
	/* создаем список богов:
	сначала - Тор , за ним следует Один , являющийся
	предшественником Тора, а завершает список Фрея - предшественница
	Одина
	*/
	/* не оптимальное решение */
	MLink0 * norseGods0 = new MLink0("Thor", 0/* нет предыдущего */, 0 /* нет последующего */);
	norseGods0 = new MLink0{ "Odin",0, norseGods0 }; /* создали узел. ??? Не понятно почему почему последующий */
	norseGods0->_succ->_prev = norseGods0; /* у последующего предыдущий это только что созданный */
	norseGods0 = new MLink0{ "Freia",0, norseGods0 };
	norseGods0->_succ->_prev = norseGods0;

	// вставка 'n' перед 'p'; возврат 'n'
	auto insert = [](MLink0 *p, MLink0 * n)
	{
		if (!n)
			return p;
		if (!p)
			return n;

		// 'p' следует после 'n'
		n->_succ = p;
		// 'n' следует полсе предшественника 'p'
		p->_prev->_succ = n;
		// предшественник 'p' становится предшественником 'n'
		n->_prev = p->_prev;
		// 'n' становится предшественником 'p'
		p->_prev = n;
		return n;
	};

	/* использование встаки */
	MLink0 * norseGods1 = new MLink0("Thor");
	norseGods1 = insert(norseGods1, new MLink0("Odin"));
	norseGods1 = insert(norseGods1, new MLink0("Freia"));

}

void WorkWithAnother::doubleLinkedList1()
{
	MLink0 * norseGods = new MLink0{ "Thor" };
	auto norseGods1st = norseGods;
	norseGods = MList().add(norseGods, new MLink0("Odin"));
	norseGods = MList().add(norseGods, new MLink0("Zeus"));
	norseGods = MList().add(norseGods, new MLink0("Freia"));

	MLink0 * greekGods = new MLink0{ "Hera" };
	auto greekGods1st = greekGods;
	greekGods = MList().add(greekGods, new MLink0("Athena"));
	greekGods = MList().add(greekGods, new MLink0("Mars"));
	greekGods = MList().add(greekGods, new MLink0("Poseidon"));

	MList().print(norseGods1st);
	MList().print(greekGods1st);

	{
		auto p = MList().find(greekGods1st, "Mars");
		if (p)
			p->_value = "Areas";

		MList().print(greekGods1st);
	}

	{
		auto p = MList().find(norseGods1st, "Zeus");
		if (p)
		{
			MList().erase(p);
			MList().add(greekGods, p);
		}

		MList().print(norseGods1st);
		MList().print(greekGods1st);
	}


}

void WorkWithAnother::doubleLinkedList2()
{
	MLink1 * norseGods = new MLink1{ "Thor" };
	auto norseGods1st = norseGods;

	norseGods->add(new MLink1("Odin"));
	norseGods->add(new MLink1("Zeus"));
	norseGods->add(new MLink1("Freia"));

	MLink1 * greekGods = new MLink1{ "Hera" };
	auto greekGods1st = greekGods;

	greekGods->add(new MLink1("Athena"));
	greekGods->add(new MLink1("Mars"));
	greekGods->add(new MLink1("Poseidon"));


	MList().print(norseGods1st);
	MList().print(greekGods1st);

	{
		auto p = greekGods1st->find("Mars");
		if (p)
			p->_value = "Areas";

		MList().print(greekGods1st);
	}

	{
		auto p = norseGods1st->find("Zeus");
		if (p)
		{
			p->erase();
			greekGods1st->add(p);
		}

		MList().print(norseGods1st);
		MList().print(greekGods1st);
	}
}

MLink1 * MLink1::insert(MLink1 * n)
{
	if (!n)
		return this;
	if (!this)
		return n;

	// this следует после 'n'
	n->_succ = this;
	// 'n' следует после предшественника this
	if (this->_prev)
		this->_prev->_succ = n;
	// предшественник this становится предшественником 'n'
	n->_prev = this->_prev;
	// 'n' становится предшественником this
	this->_prev = n;

	return n;
}

MLink1 * MLink1::add(MLink1 * n)
{
	if (!n)
		return this;
	if (!this)
		return n;

	n->_prev = this;

	if (this->_succ)
		this->_succ->_prev = n;

	n->_succ = this->_succ;
	this->_succ = n;

	return n;
}

MLink1 * MLink1::erase()
{
	if (!this)
		return nullptr;
	// смена у последующего значения предыдущего на предыдущий у 'p'
	if (this->_succ)
		this->_succ->_prev = this->_prev;
	// смена у предыдущего значения последующего на последующий у 'p'
	if (this->_prev)
		this->_prev->_succ = this->_succ;

	// возврат последующего т.к. теперь он на месте 'p'
	return this->_succ;
}

MLink1 * MLink1::find(const QString & s)
{
	auto p = this;
	while (p)
	{
		if (p->_value == s)
			return p;
		p = p->_succ;
	}
	return nullptr;
}

MLink1 * MLink1::advance(int n)
{
	auto p = this;

	if (!p)
		return nullptr;

	if (n > 0)
	{
		// n-- используется текущее значение, а потом декремент
		while (n--)
		{
			p->_succ == nullptr ? nullptr : p->_succ;
		}
	}
	else if (n < 0)
	{
		while (n++)
		{
			p->_prev == nullptr ? nullptr : p->_prev;
		}
	}

	return p;
}

}
