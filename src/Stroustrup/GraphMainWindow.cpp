#include "GraphMainWindow.h"
#include <qpainter.h>
#include <QPolygon>
#include <QGraphicsWidget>
#include <QtCharts/QChartView>
#include <QTextItem>
#include <qdebug.h>

QT_CHARTS_USE_NAMESPACE

GraphMainWindow::GraphMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	_ui.setupUi(this);

	temporary();

}


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

GraphMainWindow::~GraphMainWindow()
{
}

void GraphMainWindow::drawPolygon()
{
	QPainter painter(this);

	static const int points[] = { 300, 200, 350, 100, 400, 200 };

	QPolygon poly;
	poly.setPoints(3, points);

	QPen linePen(Qt::gray);
	linePen.setWidth(5);

	painter.setPen(linePen);
	painter.drawPolygon(poly);

	QRect rec(QPoint(10, 10), QSize(400, 250));

	QPen recPen(Qt::red);
	QBrush recBrush(Qt::blue, Qt::DiagCrossPattern);
	recPen.setWidth(2);
	painter.setPen(recPen);
	//painter.setBrush(recBrush);
	painter.fillRect(rec, recBrush);
	painter.drawRect(rec);
	painter.drawEllipse(rec);

	//QPoint p1{ 150, 150 };
	//QPoint p2{ 400, 400 };
	QPair<QPoint, QPoint> p{ QPoint(150,150), QPoint(400,400) };

	MLine mL(&painter, p);

}



void GraphMainWindow::drawShape()
{
	QPainter painter{ this }; //this = QPaintDevice *device

}


void GraphMainWindow::drawAxis()
{

	//QChartView *chartView = new QChartView(chart);
	//chartView->setRenderHint(QPainter::Antialiasing);
	//QLineSeries *series = new QLineSeries;
	//// ...
	//chartView->chart()->addSeries(series);
	//
	//QValueAxis *axisX = new QValueAxis;
	//axisX->setRange(10, 20.5);
	//axisX->setTickCount(10);
	//axisX->setLabelFormat("%.2f");
	//chartView->chart()->setAxisX(axisX, series);


}

void GraphMainWindow::temporary()
{
}



void GraphMainWindow::paintEvent(QPaintEvent *)
{
	QPainter divecePainter{this};
	
	MCircle c1{ QPoint{150, 120}, 60 };
	c1.setLineColor(Qt::GlobalColor::red);
	c1.setLineStyle(MLineStyle(5));
	c1.draw(&divecePainter);

	MCircle c2{ QPoint{350, 120}, 300 };
	c2.setLineStyle(MLineStyle(5));
	c2.draw(&divecePainter);

//	MFunction f1{ slope, R_MIN, R_MAX, ORIG, N_POINTS, X_SCALE, Y_SCALE};
}

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

	if(_points.size() == 0 )
		return false;

	if (lineColor() != Qt::GlobalColor::transparent)
	{
		//int points[] = { p.first.x(), p.first.y(), p.second.x(), p.second.y() };
		
		QPolygon poly;

		for (int i = 0; i < _points.size(); i++)
		{
			poly.setPoint(i, _points[i]);
		}

		painterDevice->setPen(getLinePen());
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


MCircle::MCircle(QPoint p, int radius)
	: _radius(radius)
{
	add(QPoint{p.x()-_radius, p.y()-_radius});;
}


bool MCircle::drawLines(QPainter * painterDevice) const
{
	if (!painterDevice)
		return false;

	if (lineColor() != Qt::GlobalColor::transparent)
	{
		
		//на самом деле это будет елипс
		QRect elipse(topLeft(), size()); 

		painterDevice->setPen(getLinePen());
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
