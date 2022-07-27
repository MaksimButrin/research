#pragma once
/*
директива #include выполняется компилятором до любой иной
обработки файлов, выполняющая ее часть компилятора называется препроцессором
(preprocessing) (раздел А.17) .
*/
#include <QMainWindow>

#include "ui_GraphMainWindow.h"

#include <QPoint>
#include <QVector>
#include <QPen>
#include <math.h>
#include <qdebug.h>
#include <QLabel>


typedef double Fct(double);

double one(double);
double slope(double x);
double square(double x);
double slopeCos(double x);
int fac(int n);
double term(double x, int n);
double expe(double x, int n);


class GraphMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	GraphMainWindow(QWidget *parent = Q_NULLPTR);
	~GraphMainWindow();

	void init();

	void drawUsingQtLib();
	void drawShapeChildren(int children2Show = -1);
	void drawShape();
	void drawAxis();
	/* пример удаления копирующего конструктора и копирующего присваивания */
	void copyConstructorRemove(/*MOpenPolyline & op, const MCircle & ci*/);

private:
	Ui::MainWindow _ui;

protected:
	/* перерисовка окна: ,  */
	/* - виджет был скрыт->открыт */
	/* - вызваны методы repaint() или update()*/
	void paintEvent(QPaintEvent *);

};

void printError(const QString & err);

class MLine
{
public:
	MLine();
	MLine(QPainter *painter, const QPair<QPoint, QPoint> & p);
	MLine(QPainter *painter, const int * points);
	~MLine() {};

private:

};


/* ==================================================================================  */
struct MLineStyle
{
	Qt::PenStyle style() const { return _style; }
	int width() const { return _width; }

	MLineStyle() {}
	MLineStyle(Qt::PenStyle st) : _style{ st }, _width{ 0 } {}
	MLineStyle(Qt::PenStyle st, int wd) : _style{ st }, _width{ wd } {}
	MLineStyle(int wd) : _width{ wd } {}

private:

	Qt::PenStyle _style{ Qt::SolidLine };
	int _width{ 1 };
};

/* ==================================================================================  */
/* абстрактный класс Shape 14.2.1 */
/* 14.2.2 *//* 14.2.3 *//*14.2.4 */
/* 14.3.1 *//* 14.3.2 *//* 14.3.3 - Перекрытие (в Inheritance) */
/* 4.3.4 - Доступ (в Inheritance) *//* 14.3.5 - Чисто виртуальные ф-ии (интерефейсы, абстрактные классы) */

class MShape
{
public:
	// про виртуальные таблицы: скрытый указатель на главный родительский класс с вирутальными ф-ями (взято из ravesli.com)
	QFunctionPointer *__vptr; // адрес - unable to read memory
	// вывод цветных линий
	bool draw(QPainter * painterDevice); 
	// перемещение фигуры
	virtual void move(int dx, int dy);
	// == setColor (в книге это название)
	void setLineColor(const QColor & color);
	// == color (в книге это название)
	QColor lineColor() const;

	void setLineStyle(MLineStyle ls);
	MLineStyle lineStyle() const;

	QPen linePen() const { return _lPen; };
	QVector<QPoint> points() const { return _points; };

	void setFillColor(const QColor & color);
	QColor fillColor() const;

	QPoint point(int numPoint) const;	// Доступ только на чтение
	int numberOfPoints() const;			// ...

	// предотвращение копирования. Т.е. класс Shape объявляет копирующий конструктор и ...
	// !!! смотри примеры в copyConstructorRemove
	// конструктор копирования
	MShape(const MShape&) = delete;
	// ... копирующее присваивание удаленными
	MShape & operator=(const MShape&) = delete;	

	virtual ~MShape() {} // реализация вызова деструктора производного класса при вызове деструктора базового класса

/* protected - можно использовать непосредственно только в классах, производных
от класса MShape (используя запись : MShape)
!!! Цель модификатора protected : - гарантировать,
что мы не сможем создать объекты класса Shape непосредственно, 
потому что при этом мы обращаемся к конструктору не из наследника или друга, а из внешнего класса/функции
*/
protected: // разжовано не листе 550 (14.2.2)
	MShape(QList<QPoint> lst);		// добавление точек
	/* конструктор по умолчанию */
	MShape() {}
	// вывод линий
	/* использование virtual foo() = 0, говорит о том что foo Обязаны быть перекрытой в производном классе. В этом случае foo является "чистой"(чистая виртуальная функция). Почему =0 хотя в первом варианте без? */
	virtual bool drawLines(QPainter * painterDevice) const = 0; /* но! опеределить её всё же можно */
	/* 'защищенные' потому что только в конструкторе производного класса определено(класс 'знает') кол-во точек */
	/*
	мы сделали функцию add ( ) защищенной с помощью модификатора protected (т.е. сделали ее доступной только 
	для производных классов), чтобы гарантировать, что производные классы смогут управлять добавлением точек
	*/
	void add(QPoint p);				// добавление 'p' к точкам
	/*
	В общем случае только производный класс может "знать", что означают
	точки и можно ли их изменять, не нарушая инвариант. ее добавили в protected просто для того, чтобы обеспечить
	выполнение правил чтения и записи каждого атрибута класса Shape
	*/
	bool setPoint(int numPoint, QPoint p); // _points[numPoint] = p;

private:

	QColor defaultFillColor() { return Qt::GlobalColor::transparent; };
	QColor defaultLineColor() { return Qt::GlobalColor::green; };

	QVector<QPoint> _points;

	QColor _lColor{ defaultLineColor() }; // Цвет линий и символов (значение по умолчанию)
	QColor _fColor{ defaultFillColor() }; // цвет заполнения

	MLineStyle _lStyle{0}; // ширина равна 0

	QPen _lPen;
};

/* ==================================================================================  */
/* 13.6 */
// OpenPolyline определяет фигура, состоящую из ряда отрезков линий, 
// соединенных между собой и заданных последовательностью точек
struct MOpenPolyline : MShape // открытая последовательность линий
{
	/* Использует конструктор Shape: */
	/* MShape::MShape - Класс OpenPolyline может использоватль конструкторы */
	/* определенные в классе Shape. Класс Shape имеет конструтор по умолчанию(9.7.3) */
	/* и конструктор со списком инициализации (18.2.) */
	/* Вот так можно использовать вызов конструктора базового класса (Борис помог) */
	MOpenPolyline(QList<QPoint> list):MShape(list) {}
	/* это не компилировалось, при вызове конструктора с параметрами !!! */
	//using MShape::MShape; /* using - псевдоним. механизм времени выполнения (раздел А. 16)  */
	void add(QPoint p) { MShape::add(p); }
	bool drawLines(QPainter * painterDevice) const { return MShape::drawLines(painterDevice); }
};


/* ==================================================================================  */
/* 13.7 */
struct MClosedPolyline : MOpenPolyline // закрытая последовательность линий
{
	/* Использует конструктор MOpenPolyline: */
	using MOpenPolyline::MOpenPolyline;
	//Рисует линии, соединяющие пары точек
	virtual bool drawLines(QPainter * painterDevice) const;
};


/* ==================================================================================  */
/* 13.8 - !!!! Не реализовывалось, нет примера */
/* Замкнутая последовательность непересекающихся отрезков */
struct MPolygon : MClosedPolyline
{
	/* конструторы MClosedPolyline */
	using MClosedPolyline::MClosedPolyline;
	/* Проверка того , что новая линия не пересекает существующие (код не показан)*/
	void add(const QPoint &p); // MShape::add
	/* почему-то написано что мы унаследовали определение drawLines */
	//bool drawLines(QPainter * painterDevice) const;
};

/* ==================================================================================  */
/* 13.9 Прямоугольник */
struct MRectangle : MShape
{
	MRectangle(QPoint xy, int width, int height);
	MRectangle(QPoint x, QPoint y);
	//Рисует линии, соединяющие пары точек
	void drawLines() const;

	int height() const { return _h; }
	int width() const { return _h; }

private: 
	int _h{0}; // высота
	int _w{0}; // ширина
};

/* ==================================================================================  */
/* 13.10 Управление неименованными объектами - ПРОЧИТАНО */
/* пример палитры цветов */
/* ==================================================================================  */
/* 13.11 Класс Text - ПРОЧИТАНО */
/* ==================================================================================  */
/* 13.12 */
struct MCircle : MShape
/* равносильно что написать (см. 14.3.2): class MOpenPolyline : public MShape */
/* public в данном случае это объявление открытых членов класса. */
/* Если не указать public то класс Shape является закрытым базовым классом для класса Circle, */ 
/* что делает открытые функции-члены Shape недоступными для класса Circle */
{
	// struct - по умолчанию все члены Открыты. Структуры необходимо использовать в тех случаях, когда сокрытие данных неуместно. Именно поэтому если был бы класс то по конструктор был бы в private, и прога бы не компилировалась без явного указания "public"
	// class - по умолчанию все члены Закрыты

	MCircle(QPoint p, int radius);
	~MCircle() {}

	//"перекрытие" ф-ии MShape::drawLines(), подробнее про это в 14.3.3
	bool drawLines(QPainter * painterDevice) const override;

	QPoint center() const;
	QPoint topLeft() const { return QPoint{ center().x() - radius(),center().y() - radius() }; };

	QSize size() const { return QSize{ diametr(), diametr() }; };
	void setRadius(int radius);
	int radius() const { return _radius; }
	int diametr() const { return radius() * 2; }

private:
	int _radius{ 20 };
};

/* ==================================================================================  */
/* 13.12 Класс Ellipse - ПРОЧИТАНО. Главу 13 закончил тут */
/* ==================================================================================  */
/* xx.xx */


/* 13.3 Связанные друг с другом линии */
struct MLines : MShape
{
	/* пустой набор линий */
	MLines() {}
	/* Инициализация списком точек */
	MLines(const QList<QPair<QPoint, QPoint>> & lst);
	bool drawLines(QPainter * painterDevice) const override;
	/* Добавление линии заданной двумя точками */
	void add(const QPair<QPoint, QPoint> & lineByPoints);
};



/* 15.1 */
struct MFunction : MShape
{
	/* параметры не сохраняются */
	MFunction(Fct f, double r1, double r2, QPoint orig, int count = 100, double xScale = 25, double yScale = 25);

protected:
		bool drawLines(QPainter * painterDevice) const { return MShape::drawLines(painterDevice); }
};

// вместо класса Text (13.11)
struct MLabel
{
	QPoint _xy{ 0,0 };
	QString _labelText;
	MLabel() {};
	MLabel(const QPoint xy, const QString label) : _xy{ xy }, _labelText{ label } {};
};

// 17.5.2. Деструкторы и динамическая память
MShape * getMFunctionPtr(QPainter * painterDevice);

/* 15.4 Оси координат */
/* 15.5 Апроксимация - ошибка компиляции */
/* 15.6 ГРафическое представление - не прорабатывалось из-за спотыкания в 15.5 */
/* 16 - не прорабатывалось т.к. виджеты, окна (GUI) */
struct MAxis:MShape
{
	enum Orientation{ x, y, z};
	MAxis(Orientation d, QPoint xy, int length, int numberOfNotches, QString & label = QString());

	bool drawLines(QPainter * painterDevice) const override;
	void move(int xx, int xy) override;
	void setLineColor(const QColor & color);

	MLines _noches;


	MLabel _label;
};


