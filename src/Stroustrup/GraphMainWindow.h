#pragma once
/*
��������� #include ����������� ������������ �� ����� ����
��������� ������, ����������� �� ����� ����������� ���������� ��������������
(preprocessing) (������ �.17) .
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
	/* ������ �������� ����������� ������������ � ����������� ������������ */
	void copyConstructorRemove(/*MOpenPolyline & op, const MCircle & ci*/);

private:
	Ui::MainWindow _ui;

protected:
	/* ����������� ����: ,  */
	/* - ������ ��� �����->������ */
	/* - ������� ������ repaint() ��� update()*/
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
/* ����������� ����� Shape 14.2.1 */
/* 14.2.2 *//* 14.2.3 *//*14.2.4 */
/* 14.3.1 *//* 14.3.2 *//* 14.3.3 - ���������� (� Inheritance) */
/* 4.3.4 - ������ (� Inheritance) *//* 14.3.5 - ����� ����������� �-�� (�����������, ����������� ������) */

class MShape
{
public:
	// ��� ����������� �������: ������� ��������� �� ������� ������������ ����� � ������������ �-��� (����� �� ravesli.com)
	QFunctionPointer *__vptr; // ����� - unable to read memory
	// ����� ������� �����
	bool draw(QPainter * painterDevice); 
	// ����������� ������
	virtual void move(int dx, int dy);
	// == setColor (� ����� ��� ��������)
	void setLineColor(const QColor & color);
	// == color (� ����� ��� ��������)
	QColor lineColor() const;

	void setLineStyle(MLineStyle ls);
	MLineStyle lineStyle() const;

	QPen linePen() const { return _lPen; };
	QVector<QPoint> points() const { return _points; };

	void setFillColor(const QColor & color);
	QColor fillColor() const;

	QPoint point(int numPoint) const;	// ������ ������ �� ������
	int numberOfPoints() const;			// ...

	// �������������� �����������. �.�. ����� Shape ��������� ���������� ����������� � ...
	// !!! ������ ������� � copyConstructorRemove
	// ����������� �����������
	MShape(const MShape&) = delete;
	// ... ���������� ������������ ����������
	MShape & operator=(const MShape&) = delete;	

	virtual ~MShape() {} // ���������� ������ ����������� ������������ ������ ��� ������ ����������� �������� ������

/* protected - ����� ������������ ��������������� ������ � �������, �����������
�� ������ MShape (��������� ������ : MShape)
!!! ���� ������������ protected : - �������������,
��� �� �� ������ ������� ������� ������ Shape ���������������, 
������ ��� ��� ���� �� ���������� � ������������ �� �� ���������� ��� �����, � �� �������� ������/�������
*/
protected: // ��������� �� ����� 550 (14.2.2)
	MShape(QList<QPoint> lst);		// ���������� �����
	/* ����������� �� ��������� */
	MShape() {}
	// ����� �����
	/* ������������� virtual foo() = 0, ������� � ��� ��� foo ������� ���� ���������� � ����������� ������. � ���� ������ foo �������� "������"(������ ����������� �������). ������ =0 ���� � ������ �������� ���? */
	virtual bool drawLines(QPainter * painterDevice) const = 0; /* ��! ����������� � �� �� ����� */
	/* '����������' ������ ��� ������ � ������������ ������������ ������ ����������(����� '�����') ���-�� ����� */
	/*
	�� ������� ������� add ( ) ���������� � ������� ������������ protected (�.�. ������� �� ��������� ������ 
	��� ����������� �������), ����� �������������, ��� ����������� ������ ������ ��������� ����������� �����
	*/
	void add(QPoint p);				// ���������� 'p' � ������
	/*
	� ����� ������ ������ ����������� ����� ����� "�����", ��� ��������
	����� � ����� �� �� ��������, �� ������� ���������. �� �������� � protected ������ ��� ����, ����� ����������
	���������� ������ ������ � ������ ������� �������� ������ Shape
	*/
	bool setPoint(int numPoint, QPoint p); // _points[numPoint] = p;

private:

	QColor defaultFillColor() { return Qt::GlobalColor::transparent; };
	QColor defaultLineColor() { return Qt::GlobalColor::green; };

	QVector<QPoint> _points;

	QColor _lColor{ defaultLineColor() }; // ���� ����� � �������� (�������� �� ���������)
	QColor _fColor{ defaultFillColor() }; // ���� ����������

	MLineStyle _lStyle{0}; // ������ ����� 0

	QPen _lPen;
};

/* ==================================================================================  */
/* 13.6 */
// OpenPolyline ���������� ������, ��������� �� ���� �������� �����, 
// ����������� ����� ����� � �������� ������������������� �����
struct MOpenPolyline : MShape // �������� ������������������ �����
{
	/* ���������� ����������� Shape: */
	/* MShape::MShape - ����� OpenPolyline ����� ������������� ������������ */
	/* ������������ � ������ Shape. ����� Shape ����� ���������� �� ���������(9.7.3) */
	/* � ����������� �� ������� ������������� (18.2.) */
	/* ��� ��� ����� ������������ ����� ������������ �������� ������ (����� �����) */
	MOpenPolyline(QList<QPoint> list):MShape(list) {}
	/* ��� �� ���������������, ��� ������ ������������ � ����������� !!! */
	//using MShape::MShape; /* using - ���������. �������� ������� ���������� (������ �. 16)  */
	void add(QPoint p) { MShape::add(p); }
	bool drawLines(QPainter * painterDevice) const { return MShape::drawLines(painterDevice); }
};


/* ==================================================================================  */
/* 13.7 */
struct MClosedPolyline : MOpenPolyline // �������� ������������������ �����
{
	/* ���������� ����������� MOpenPolyline: */
	using MOpenPolyline::MOpenPolyline;
	//������ �����, ����������� ���� �����
	virtual bool drawLines(QPainter * painterDevice) const;
};


/* ==================================================================================  */
/* 13.8 - !!!! �� ���������������, ��� ������� */
/* ��������� ������������������ ���������������� �������� */
struct MPolygon : MClosedPolyline
{
	/* ����������� MClosedPolyline */
	using MClosedPolyline::MClosedPolyline;
	/* �������� ���� , ��� ����� ����� �� ���������� ������������ (��� �� �������)*/
	void add(const QPoint &p); // MShape::add
	/* ������-�� �������� ��� �� ������������ ����������� drawLines */
	//bool drawLines(QPainter * painterDevice) const;
};

/* ==================================================================================  */
/* 13.9 ������������� */
struct MRectangle : MShape
{
	MRectangle(QPoint xy, int width, int height);
	MRectangle(QPoint x, QPoint y);
	//������ �����, ����������� ���� �����
	void drawLines() const;

	int height() const { return _h; }
	int width() const { return _h; }

private: 
	int _h{0}; // ������
	int _w{0}; // ������
};

/* ==================================================================================  */
/* 13.10 ���������� �������������� ��������� - ��������� */
/* ������ ������� ������ */
/* ==================================================================================  */
/* 13.11 ����� Text - ��������� */
/* ==================================================================================  */
/* 13.12 */
struct MCircle : MShape
/* ����������� ��� �������� (��. 14.3.2): class MOpenPolyline : public MShape */
/* public � ������ ������ ��� ���������� �������� ������ ������. */
/* ���� �� ������� public �� ����� Shape �������� �������� ������� ������� ��� ������ Circle, */ 
/* ��� ������ �������� �������-����� Shape ������������ ��� ������ Circle */
{
	// struct - �� ��������� ��� ����� �������. ��������� ���������� ������������ � ��� �������, ����� �������� ������ ���������. ������ ������� ���� ��� �� ����� �� �� ����������� ��� �� � private, � ����� �� �� ��������������� ��� ������ �������� "public"
	// class - �� ��������� ��� ����� �������

	MCircle(QPoint p, int radius);
	~MCircle() {}

	//"����������" �-�� MShape::drawLines(), ��������� ��� ��� � 14.3.3
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
/* 13.12 ����� Ellipse - ���������. ����� 13 �������� ��� */
/* ==================================================================================  */
/* xx.xx */


/* 13.3 ��������� ���� � ������ ����� */
struct MLines : MShape
{
	/* ������ ����� ����� */
	MLines() {}
	/* ������������� ������� ����� */
	MLines(const QList<QPair<QPoint, QPoint>> & lst);
	bool drawLines(QPainter * painterDevice) const override;
	/* ���������� ����� �������� ����� ������� */
	void add(const QPair<QPoint, QPoint> & lineByPoints);
};



/* 15.1 */
struct MFunction : MShape
{
	/* ��������� �� ����������� */
	MFunction(Fct f, double r1, double r2, QPoint orig, int count = 100, double xScale = 25, double yScale = 25);

protected:
		bool drawLines(QPainter * painterDevice) const { return MShape::drawLines(painterDevice); }
};

// ������ ������ Text (13.11)
struct MLabel
{
	QPoint _xy{ 0,0 };
	QString _labelText;
	MLabel() {};
	MLabel(const QPoint xy, const QString label) : _xy{ xy }, _labelText{ label } {};
};

// 17.5.2. ����������� � ������������ ������
MShape * getMFunctionPtr(QPainter * painterDevice);

/* 15.4 ��� ��������� */
/* 15.5 ������������ - ������ ���������� */
/* 15.6 ����������� ������������� - �� ��������������� ��-�� ���������� � 15.5 */
/* 16 - �� ��������������� �.�. �������, ���� (GUI) */
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


