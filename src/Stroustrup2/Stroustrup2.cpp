#include <Stroustrup2.h>
#include <QDebug>
#include <QSharedPointer>

void UsingMDateFoo1(MDate d1, MDate d2)
{
	/* ??? к чему бы это?: */
/* Откуда функции Date : : month ( ) известно, что при первом вызове следует
вернуть значение переменной dl._m, а при втором - d2._m? */
/*	Функции - члены класса, такие как MDate::month(), получают неявный аргумент,
	позволяющий идентифицировать объект, для которого они вызываются.
	Таким образом, при первом вызове переменная _m правильно ссылается
	на dl._m, а при втором - на d2._m. Другие варианты использования
	неявного аргумента описаны в разделе 17.10 */
	std::cout << d1.month() << " " << d2.month() << "\n";
}


/* 9.4.4 ==================================================================== */
MDate::MDate(int yy, int mm, int dd) // конструктор
: _y(yy), _m(mm), _d(dd) // список инициализации членов
// !!! нужно бы уточнить в какой момент времени это выполняется (у Хирьянов было)
{
}

/*
Определение функции-члена в классе приводит к следующим последствиям.
 - Функция становится встраиваемой (inline), т.е . компилятор будет
пытаться вместо вызова функции генерировать ее код
...
*/
void MDate::addDay(int n)
{
}

MYear::MYear(int y): _y(y)
{
	if (y < MIN || y > MAX)
	{
		/*
		В языке C++ оператор throw используется для сигнализирования о возникновении исключения или ошибки (аналогия тому, когда свистит арбитр). Сигнализирование о том, что произошло исключение, называется генерацией исключения (или «выбрасыванием исключения»
		*/
		//throw Invalid{};
	}
}

MDate2::MDate2()
	: _y{ defaultDate().year() },
	_m{ defaultDate().month() },
	_d{ defaultDate().day() }
{
}

const MDate2 & MDate2::defaultDate()
{
	/*
	Ключевое слово static здесь использовано для того, чтобы переменная dd
	создавалась только один раз, а не каждый раз при очередном вызове функции
	defaultDate() . Инициализация этой переменной происходит при
	первом вызове функции defaultDate()
	*/

	static MDate2 dd{ 2001, MMonth::jan, 1 };
	return dd;
}
