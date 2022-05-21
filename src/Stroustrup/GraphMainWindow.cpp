#include "GraphMainWindow.h"
#include <qpainter.h>
#include <QPolygon>
#include <QGraphicsWidget>
#include <QtCharts/QChartView>
#include <QTextItem>
#include <qdebug.h>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCore/QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtCharts/QValueAxis>
#include <QSplineSeries>

QT_CHARTS_USE_NAMESPACE

/* размер экрана */
constexpr int X_MAX = 600;
constexpr int Y_MAX = 400;
/* центр окна */
constexpr int X_ORIG = X_MAX / 2;
constexpr int Y_ORIG = Y_MAX / 2;
constexpr QPoint ORIG{ X_ORIG , Y_ORIG };
/* диапазон -10 11 */
constexpr int R_MIN = -10;
constexpr int R_MAX = 11;
/* количество точек в диапазоне */
constexpr int N_POINTS = 400;
/* масштабные множители */
constexpr int X_SCALE = 30;
constexpr int Y_SCALE = 30;

GraphMainWindow::GraphMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	_ui.setupUi(this);


	//drawAxis();
	//drawPolygon();
	//temporary();
}

GraphMainWindow::~GraphMainWindow()
{
}

void GraphMainWindow::drawUsingQtLib()
{
	/* 12.7.5 Многоугольники  */

	QPainter painter(this);

	bool show[4]{ false, false, false, false };

	/* отрисовка треугольника */
	if (show[0])
	{
		const int points[] = { 300, 200, 350, 100, 400, 200 };

		QPolygon poly;
		poly.setPoints(3, points);

		QPen linePen(Qt::gray);
		linePen.setWidth(5);

		painter.setPen(linePen);
		painter.drawPolygon(poly);
	}

	/* 12.7.6 Прямоугольник */
	/* 12.7.7 Заполнение */

	if (show[1] || show[2])
	{
		QRect rec(QPoint(10, 10), QSize(400, 250));

		QPen recPen(Qt::red);
		QBrush recBrush(Qt::blue, Qt::DiagCrossPattern);
		recPen.setWidth(2);
		painter.setPen(recPen);
		//painter.setBrush(recBrush);
		painter.fillRect(rec, recBrush);

		/* отрисовка прямоугольника */
		if (show[1])
			painter.drawRect(rec);

		/* отрисовка окружности */
		if (show[2])
			painter.drawEllipse(rec);
	}

	/* 12.7.8 Текст - не прорабатывался(прочитан), т.к. нет смысла */
	/* 12.7.9 Изображения - не прорабатывался(прочитан), т.к. нет смысла */

	/* отрисовка }{3 */
	if (show[3])
	{

		//QPoint p1{ 150, 150 };
		//QPoint p2{ 400, 400 };
		QPair<QPoint, QPoint> p{ QPoint(150,150), QPoint(400,400) };

		MLine mL(&painter, p);
	}

}



void GraphMainWindow::drawShapeChildren(int children2Show)
{
	QPainter painter{ this };

	const int showSize{ 4 };
	bool show[showSize]{ true, false, false, false };

	if (children2Show > -1 && children2Show < showSize)
		for (int i = 0; i < children2Show; i++)
			show[i] = children2Show == i;

	if (show[0])
	{
		QPair<QPoint, QPoint> p{ QPoint(150,150), QPoint(400,400) };
		MLine(&painter, p);
	}

	if (show[1])
	{
		QList<QPoint> lst;
		//MOpenPolyline ssss(lst); /* ОШИБКИ КОМПИЛЯЦИИ */
	}
}



void GraphMainWindow::drawShape()
{
	QPainter painter{ this }; //this = QPaintDevice *device

}


void GraphMainWindow::drawAxis()
{
	/* 12.7.3 */
	/* не соответствует примеру из книги */
	QChart *chart = new QChart();
	chart->legend()->hide();
	chart->setTitle("Multiaxis chart example");

	QValueAxis *axisX = new QValueAxis;
	axisX->setTickCount(10);
	chart->addAxis(axisX, Qt::AlignBottom);

	QSplineSeries *series = new QSplineSeries;
	*series << QPointF(1, 5) << QPointF(3.5, 18) << QPointF(4.8, 7.5) << QPointF(10, 2.5);
	chart->addSeries(series);

	QValueAxis *axisY = new QValueAxis;
	axisY->setLinePenColor(series->pen().color());

	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisX);
	series->attachAxis(axisY);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	this->setCentralWidget(chartView);
}

void GraphMainWindow::init()
{

}



void GraphMainWindow::paintEvent(QPaintEvent *)
{
	QPainter divecePainter{ this };


	if (false)
	{

		MCircle c1{ QPoint{150, 120}, 60 };
		c1.setLineColor(Qt::GlobalColor::red);
		c1.setLineStyle(MLineStyle(5));
		c1.draw(&divecePainter);

		MCircle c2{ QPoint{350, 120}, 300 };
		c2.setLineStyle(MLineStyle(5));
		c2.draw(&divecePainter);
	}

	QPair<QPoint, QPoint> p{ QPoint(150,150), QPoint(400,400) };
	
	QList<QPoint> mopList{ QPoint(150,150), QPoint(400,400) };
	/* ХЕРНЯ... не получается использовать конструктор */
	//MShape::MShape op(mopList);
	//drawUsingQtLib();
	//drawShapeChildren(0);
	//drawShapeChildren(1);

	//	MFunction f1{ slope, R_MIN, R_MAX, ORIG, N_POINTS, X_SCALE, Y_SCALE};
}

/* ==================================================================================  */
MLine::MLine()
{
}

MLine::MLine(QPainter *painter, const QPair<QPoint, QPoint> & p)
{
	const int points[] = { p.first.x(), p.first.y(), p.second.x(), p.second.y() };

	QPolygon poly;

	poly.setPoints(2, points);

	QPen linePen(Qt::green);
	linePen.setWidth(5);

	painter->setPen(linePen);
	painter->drawPolygon(poly);
}

MLine::MLine(QPainter *painter, const int * points)
{
	QPolygon poly;
	poly.setPoints(2, points);

	QPen linePen(Qt::green);
	linePen.setWidth(5);

	painter->setPen(linePen);
	painter->drawPolygon(poly);
}

/* ==================================================================================  */

bool MShape::draw(QPainter * painterDevice)
{


	if (!painterDevice)
		return false;

	//QPolygon poly;
	//
	//for (int i = 0; i < numberOfPoints(); i++)
	//{
	//	poly.setPoint(i, _points[i]);
	//}

	_lPen.setColor(lineColor());			// цвет линии
	_lPen.setWidth(lineStyle().width());	// толщина линии
	_lPen.setStyle(lineStyle().style());	// стиль линии

	auto result{ drawLines(painterDevice) };

	// Восстанавливаем значения по умолчанию ? нах ?
	_lPen.setColor(defaultLineColor());		// цвет линии
	_lPen.setWidth(MLineStyle().width());	// толщина линии
	_lPen.setStyle(MLineStyle().style());	// стиль линии


	return result;
}



void MShape::move(int dx, int dy)
{
	for (auto & item : _points)
	{
		item.setX(item.x() + dx);
		item.setY(item.y() + dy);
	}
}



void MShape::setLineColor(const QColor & color)
{
	_lColor = color;
}


QColor MShape::lineColor() const
{
	return _lColor;
}



void MShape::setLineStyle(MLineStyle ls)
{
	_lStyle = ls;
}



MLineStyle MShape::lineStyle() const
{
	return _lStyle;
}



void MShape::setFillColor(const QColor & color)
{
	_fColor = color;
}



QColor MShape::fillColor() const
{
	return _fColor;
}



QPoint MShape::point(int numPoint) const
{
	return (_points.size() > numPoint) ? _points[numPoint] : QPoint();
}



int MShape::numberOfPoints() const
{
	return _points.size();
}



MShape::MShape(QList<QPoint> lst)
{
	for (auto & item : lst)
	{
		add(item);
	}
}



bool MShape::drawLines(QPainter * painterDevice) const
{
	if (!painterDevice)
		return false;

	if (points().size() == 0)
		return false;

	if (lineColor() != Qt::GlobalColor::transparent)
	{
		//int points[] = { p.first.x(), p.first.y(), p.second.x(), p.second.y() };

		QPolygon poly;

		for (int i = 0; i < points().size(); i++)
		{
			poly.setPoint(i, points()[i]);
		}

		painterDevice->setPen(linePen());
		painterDevice->drawPolygon(poly);
	}


	return true;
}



void MShape::add(QPoint p)
{
	_points.push_back(p);
}



bool MShape::setPoint(int numPoint, QPoint p)
{
	if (_points.size() > numPoint)
	{
		_points[numPoint] = p;

		return true;
	}

	return false;
}

/* ============================================  */

MCircle::MCircle(QPoint p, int radius)
	: _radius(radius)
{
	add(QPoint{ p.x() - _radius, p.y() - _radius });;
}


bool MCircle::drawLines(QPainter * painterDevice) const
{
	if (!painterDevice)
		return false;

	if (lineColor() != Qt::GlobalColor::transparent)
	{

		//на самом деле это будет елипс
		QRect elipse(topLeft(), size());

		painterDevice->setPen(linePen());
		painterDevice->drawEllipse(elipse);
	}



	return true;
}


QPoint MCircle::center() const
{
	return QPoint({ point(0).x() + _radius, point(0).y() + _radius });
}


void MCircle::setRadius(int radius)
{
	setPoint(0, QPoint{ center().x() - radius, center().y() - radius });
	_radius = radius;
}

/* ============================================  */
MFunction::MFunction(Fct f, double r1, double r2, QPoint orig, int count, double xScale, double yScale)
{
	if ((r2 - r1) <= 0)
	{
		qDebug().noquote() << "Bad graphing range";
		return;
	}

	if (count <= 0)
	{
		qDebug().noquote() << "Non-positive graphing count";
		return;
	}

	double dist = (r2 - r1) / count;
	double r = r1;
	for (int i = 0; i < count; ++i)
	{
		add(QPoint{ orig.x() + int(r*xScale),  orig.y() - int(f(r) * yScale) });
		r += dist;
	}

}

double one()
{
	return 1.0;
}

double slope(double x)
{
	return x / 2.0;
}

double square(double x)
{
	return x * x;
}

double slopeCos(double x)
{
	return cos(x) + slope(x);
}


// ============================================================================ 

bool MClosedPolyline::drawLines(QPainter * painterDevice) const
{
	/* !!! НЕ проверлось на корректность выполнения  */
	if (!painterDevice)
		return false;

	if (points().size() == 0)
		return false;

	/* вывод открытой последовательности */
	MOpenPolyline::drawLines(painterDevice);
	/* вывод замыкающей линии */
	if (lineColor() != Qt::GlobalColor::transparent)
	{
		QPolygon poly;

		if (points().size() >= 2)
		{
			poly.setPoint(0, points()[points().size() - 1]);
			poly.setPoint(1, points()[0]);
		}

		painterDevice->setPen(linePen());
		painterDevice->drawPolygon(poly);
	}


	return true;
}


void MPolygon::add(const QPoint & p)
{
	/* НУЖНО...  */
	/* реализовать проверку того, что новая линия не пересекает существующие */
	//intersect(); /* проверка на пересение линий, вызывать нужно N^2 раз - неэффективно */
	MClosedPolyline::add(p);
}
