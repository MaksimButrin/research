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

	void drawPolygon();
	void drawShape();
	void drawAxis();
	void temporary();

private:
	Ui::MainWindow _ui;

protected:
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

	QPen getLinePen() const { return _lPen; };

	void setFillColor(const QColor & color);
	QColor fillColor() const;

	QPoint point(int numPoint) const;	// Доступ только на чтение
	int numberOfPoints() const;			// ...

	MShape(const MShape&) = delete;				// предотвращение копирования. Т.е. класс Shape объявляет копирующий конструктор 
	MShape & operator=(const MShape&) = delete;	// и копирующее присваивание удаленными
	virtual ~MShape() {}

protected: // разжовано не листе 550

	MShape() {}
	MShape(QList<QPoint> lst);		// добавление точек
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



struct MFunction: MShape
{
	/* параметры не сохраняются */
	MFunction(Fct f, double r1, double r2, QPoint orig, int count = 100, double xScale = 25, double yScale = 25);
};