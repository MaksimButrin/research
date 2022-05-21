#pragma once
#include <QMainWindow>

#include "ui_GraphMainWindow.h"

#include <QPoint>
#include <QVector>
#include <QPen>
#include <math.h>



typedef double Fct(double);

double one();
double slope(double x);
double square(double x);
double slopeCos(double x);


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

private:
	Ui::MainWindow _ui;

protected:
	/* перерисовка окна: ,  */
	/* - виджет был скрыт->открыт */
	/* - вызваны методы repaint() или update()*/
	void paintEvent(QPaintEvent *);

};

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
class MShape
{
public:

	bool draw(QPainter * painterDevice);						// вывод цветных линий
	virtual void move(int dx, int dy);	// перемещение фигуры

	void setLineColor(const QColor & color);
	//void setLineWidth(const int wd);
	QColor lineColor() const;

	void setLineStyle(MLineStyle ls);
	MLineStyle lineStyle() const;

	QPen linePen() const { return _lPen; };
	QVector<QPoint> points() const { return _points; };

	void setFillColor(const QColor & color);
	QColor fillColor() const;

	QPoint point(int numPoint) const;	// Доступ только на чтение
	int numberOfPoints() const;			// ...

	MShape(const MShape&) = delete;				// предотвращение копирования. Т.е. класс Shape объявляет копирующий конструктор 
	MShape & operator=(const MShape&) = delete;	// и копирующее присваивание удаленными
	virtual ~MShape() {}

protected: // разжовано не листе 550
	MShape(QList<QPoint> lst);		// добавление точек

	MShape() {}
	/* использование virtual foo() = 0, говорит о том что foo Обязаны быть перекрытой в производном классе. В этом случае foo является "чистой" */
	virtual bool drawLines(QPainter * painterDevice) const = 0; // вывод линий

	void add(QPoint p);				// добавление 'p' к точкам
	bool setPoint(int numPoint, QPoint p); // _points[numPoint] = p;

private:

	QColor defaultFillColor() { return Qt::GlobalColor::transparent; };
	QColor defaultLineColor() { return Qt::GlobalColor::green; };

	QVector<QPoint> _points;

	QColor _lColor{ defaultLineColor() }; // Цвет линий и символов (значение по умолчанию)
	QColor _fColor{ defaultFillColor() }; // цвет заполнения

	MLineStyle _lStyle;

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
	using MShape::MShape; /* using - псевдоним. механизм времени выполнения (раздел А. 16)  */
	void add(QPoint p) { MShape::add(p); }
};



/* 13.7 */
struct MClosedPolyline : MOpenPolyline // закрытая последовательность линий
{
	/* Использует конструктор MOpenPolyline: */
	using MOpenPolyline::MOpenPolyline;
	virtual bool drawLines(QPainter * painterDevice) const;
};



/* 13.8 - !!!! Не реализовывалось, нет примера */
/* Замкнутая последовательность непересекающихся отрезков */
struct MPolygon : MClosedPolyline
{
	/* конструторы MClosedPolyline */
	using MClosedPolyline::MClosedPolyline;

	void add(const QPoint &p);
	/* почему-то написано что мы унаследовали определение drawLines */
	//bool drawLines(QPainter * painterDevice) const;
};

/* 13.9 ЗАКОНЧИЛ ТУТ */
struct MRectangle : MShape
{
};


struct MCircle : MShape
{
	// struct - по умолчанию все члены Открыты. Структуры необходимо использовать в тех случаях, когда сокрытие данных неуместно. Именно поэтому если был бы класс то по конструктор был бы в private, и прога бы не компилировалась без явного укащания "public"
	// class - по умолчанию все члены Закрыты

	MCircle(QPoint p, int radius);
	~MCircle() {}

	bool drawLines(QPainter * painterDevice) const;

	QPoint center() const;
	QPoint topLeft() const { return QPoint{ center().x() - radius(),center().y() - radius() }; };

	QSize size() const { return QSize{ diametr(), diametr() }; };
	void setRadius(int radius);
	int radius() const { return _radius; }
	int diametr() const { return radius() * 2; }

private:
	int _radius{ 20 };
};



struct MFunction : MShape
{
	/* параметры не сохраняются */
	MFunction(Fct f, double r1, double r2, QPoint orig, int count = 100, double xScale = 25, double yScale = 25);
};