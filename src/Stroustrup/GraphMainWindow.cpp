#include "GraphMainWindow.h"
#include <qpainter.h>
#include <QPolygon>
#include <QGraphicsWidget>
#include <QtCharts/QChartView>
#include <QTextItem>

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



void GraphMainWindow::copyConstructorRemove(/*MOpenPolyline & op, const MCircle & ci*/)
{
	// Также если в сигнатуре используются класс с удаленными копирующимим конструкторами и копирующим присваиванием
	// то будет ошибки компиляции:
	// - syntax error: identifier 'MOpenPolyline'
	// - 'void GraphMainWindow::copyConstructorRemove(MOpenPolyline &,const MCircle &)': overloaded member function not found in 'GraphMainWindow'

	MCircle ci1(QPoint(), 5);
	MCircle ci2(QPoint(), 5);
	// Ошибка: копирующий конструктор удалён
	// Ошибки компилятора:
	// function "MCircle::MCircle(const MCircle &)" (declared implicitly) cannot be referenced -- it is a deleted function
	// 'MCircle::MCircle(const MCircle &)': attempting to reference a deleted function
	//MCircle ci3 = ci2; 


	// Ошибка: копирующий конструктор удалён
	// Ошибка компилятора - 'MCircle &MCircle::operator =(const MCircle &)': attempting to reference a deleted
	//QVector<MCircle> v;
	//v.push_back(ci1);

	/* ошибка: присваивание удалено */
	// Ошибки компилятора 
	//- function "MCircle::operator=(const MCircle &)" (declared implicitly) cannot be referenced -- it is a deleted function
	//- 'MCircle &MCircle::operator =(const MCircle &)': attempting to reference a deleted function

	//ci2 = ci1; 
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

	if (false)
	{
		/* почему список нельзя в конструктор ??? ошибка компиляции */
		QList<QPoint> list{ QPoint{ 100, 100 }, QPoint{ 150, 200 }, QPoint{ 250, 250 }, QPoint{ 300, 200 } };
		MOpenPolyline opl(list);
		opl.setLineColor(Qt::GlobalColor::red);
		opl.setLineStyle(MLineStyle(2));
		opl.draw(&divecePainter);
	}
	if (false)
	{
		QList<QPoint> list{ QPoint{100, 100}, QPoint{150, 200}, QPoint{250, 250}, QPoint{300, 200} };
		MClosedPolyline cpl(list);
		cpl.setLineColor(Qt::GlobalColor::red);
		cpl.setLineStyle(MLineStyle(2));
		cpl.draw(&divecePainter);
	}

	if (true)
	{
		//!!! обрати ВНИМАНИЕ, что используем указатель не наследника а именно указатель родителя (но можно и наследника)
		QList<MShape*> listBlue{ };
		// замена Shape* q = fct(); из примера на л.664
		listBlue.append(getMFunctionPtr(&divecePainter));
		listBlue.append(new MFunction{ slope, (double)R_MIN, (double)R_MAX, ORIG, N_POINTS, (double)X_SCALE, (double)Y_SCALE });
		listBlue.append(new MFunction{ square, (double)R_MIN, (double)R_MAX, ORIG, N_POINTS, (double)X_SCALE, (double)Y_SCALE });
		//MFunction f4{ slopeCos, (double)R_MIN, (double)R_MAX, ORIG, N_POINTS, (double)X_SCALE, (double)Y_SCALE };

		for (const auto f : listBlue)
		{
			f->setLineColor(Qt::GlobalColor::blue);
			f->setLineStyle(MLineStyle(2));
			f->draw(&divecePainter);
			// освобождение памяти, выделенной под указатели с использованием оператора new
			delete f;
		}
		

		MFunction f5{ [](double x) { return cos(x) + slope(x);  },
			(double)R_MIN, (double)R_MAX, ORIG, N_POINTS, (double)30, (double)30 };

		QList<MFunction*> listRed{ &f5 };
		for (const auto f : listRed)
		{
			f->setLineColor(Qt::GlobalColor::red);
			f->setLineStyle(MLineStyle(2));
			f->draw(&divecePainter);
		}
	}

	if (false)
	{
		MLines ls = QList<QPair<QPoint, QPoint>>{
			{ QPoint{100, 100}, QPoint{200,100} },
			{ QPoint{150, 50}, QPoint{150,150} }
		};

		ls.setLineColor(Qt::GlobalColor::red);
		ls.setLineStyle(MLineStyle(2));
		ls.draw(&divecePainter);

		divecePainter.setPen(Qt::GlobalColor::blue);
		divecePainter.drawText(QPoint(50, 50), QString("String ... "));
	}

	if (false)
	{
		int length{ 300 };
		QPoint xy{ 250, 300 };
		MAxis xAxis(MAxis::Orientation::x, QPoint{ xy.x() - length / 2, xy.y() }, length, 10, QString("x"));
		MAxis yAxis(MAxis::Orientation::y, QPoint{ xy.x(), xy.y() + length / 2 }, length, 10, QString("y"));
		QList<MAxis*> list{ &xAxis, &yAxis };
		for (const auto axis : list)
		{
			axis->setLineColor(Qt::GlobalColor::blue);
			axis->setLineStyle(MLineStyle(2));
			axis->draw(&divecePainter);

			// delete axis - здесь выдаёт ошибку доступа, потому что динамическая память не выделялась  
			// (объекты были созданы на стеке а не в куче)
		}
	}

	// не компилируется - не конфертируется lambda в Fct
	// хотя у страуса написано что должно
	if (false)
	{
		for (int n = 0; n < 50; ++n)
		{
			/* очередное приближение */
			auto fct = [n](double x) { return expe(x, n);  };
			//auto f = new MFunction { fct,
			//		(double)R_MIN, (double)R_MAX, ORIG, 200, (double)X_SCALE, (double)Y_SCALE };

			//f->setLineColor(Qt::GlobalColor::red);
			//f->setLineStyle(MLineStyle(2));
			//f->draw(&divecePainter);
		}
	}

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

	// Восстанавливаем значения по умолчанию: в библиотеке из примера (FLTK) не предусмотрен способ идентификации текущего стиля
	// как в Qt? - вопрос
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
	/* Проверено! Работает */

	if (!painterDevice)
		return false;

	if (points().size() == 0)
		return false;

	if (lineColor() != Qt::GlobalColor::transparent)
	{

		painterDevice->setPen(linePen());

		for (int i = 1; i < points().size(); i++)
		{
			painterDevice->drawLine(points()[i - 1], points()[i]);
		}


		/* Отрисовка полигона, нам не подходит, т.к. нужно рисовать именно линии */
		//QPolygon poly(points().size());

		//for (int i = 0; i < points().size(); i++)
		//{
		//	poly.setPoint(i, points()[i]);
		//}

		//painterDevice->drawPolygon(poly);
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
	// Строит график функции f(x) для х из диапазона[r1, r2),
	// используя count отрезков. Начало координат (0,0)
	// располагается в точке ху;
	// координаты х масштабируются множителем xscale;
	// координаты у масштабируются множителем yscale

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

/* горизонтальная линия */
double one(double x)
{
	return 1.0;
}

/* наклонная линия */
double slope(double x)
{
	return x / 2.0;
}
/* парабола симметричная относительно оси y */
double square(double x)
{
	return x * x;
}

double slopeCos(double x)
{
	return cos(x) + slope(x);
}

// factorial(n) ; п !
int fac(int n)
{
	int r = 1;
	while (n > 1)
	{
		r *= n;
		--n;
	};

	return r;
}

// n-й член ряда
double term(double x, int n)
{
	return pow(x, n) / fac(n);
}

//экспонента с точностью до n-членов:
// сумма n членов для значения x
double expe(double x, int n)
{
	double sum{ 0.0 };
	for (int i = 0; i < n; ++i)
	{
		sum += term(x, i);
	}
	return sum;
}


void printError(const QString & err)
{
	qDebug().noquote() << QString("Error: %1").arg(err);

	Q_ASSERT(!err.isEmpty());
}

// 17.5.2. Деструкторы и динамическая память
// замена MShape * fct() на листе 664
MShape * getMFunctionPtr(QPainter * painterDevice)
{
	// При выходе из функции getMFunctionPtr() объект label класса MLabel, существующий в ней, 
	// уничтожается вполне корректно, если он бы наследовался от МShape (про это смотри ниже).
	auto label = MLabel{ QPoint{200, 200},QString("Annemarine") };
	painterDevice->setPen(Qt::GlobalColor::green);
	painterDevice->drawText(label._xy, label._labelText);

	// данный указатель должен быть удалён извне (об этом ниже)
	MShape * p = new MFunction{ one, (double)R_MIN, (double)R_MAX, ORIG, N_POINTS, (double)X_SCALE, (double)Y_SCALE };
	
	/*
	Инструкция delete q вызывает деструктор ~Shape() класса Shape. Однако деструктор ~Shape() является виртуальным, 
	поэтому с помощью механизма вызова виртуальной функции (см. раздел 14.3.1) он вызывает деструктор класса, 
	производного от класса Shape, в данном случае - деструктор ~MLabel()(я не делал производным MLabel от MShape). 
	Если бы деструктор Shape::~Shape() не был виртуальным, то деструктор MLabel::~MLabel() не был бы вызван и 
	член класса MLabel, имеющий тип string, не был бы корректно уничтожен
	*/
	return p;
}



// ============================================================================ 

bool MClosedPolyline::drawLines(QPainter * painterDevice) const
{
	/* Проверено! Работает  */
	if (!painterDevice)
		return false;

	if (points().size() == 0)
		return false;

	/* вывод открытой последовательности */
	MOpenPolyline::drawLines(painterDevice);
	/* вывод замыкающей линии */
	if (lineColor() != Qt::GlobalColor::transparent)
	{
		if (points().size() >= 2)
		{
			painterDevice->drawLine(points()[points().size() - 1], points()[0]);
		}
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

/* 13.9 Прямоугольник */
MRectangle::MRectangle(QPoint xy, int width, int height)
	: _w(width), _h(height)
{
	if (_w <= 0 || _h <= 0)
	{
		// не положительная сторона
		printError("MRectangle: not the positive side of the rectangle");
	}

	add(xy);  // MShape::add
}

MRectangle::MRectangle(QPoint x, QPoint y)
	: _w(y.x() - x.x()), _h(y.y() - x.y())
{
	if (_w <= 0 || _h <= 0)
	{
		// первая точка не левая верхняя
		printError("MRectangle: first point is not top left");
	}

	add(x);  // MShape::add
}

void MRectangle::drawLines() const
{
	Q_ASSERT(true); // НЕ ДОДЕЛАНО!
	//
	// alpha() = 0 - полностью прозрачена
	// ПОКА (стр. 518) не понятно что вызывается и для чего
	if (fillColor().alpha() != 0) // заполнение
	{
		// fl_color впервые упоминается тут и Задает цвет для всех последующих операций рисования (FLTK)
		// fl_color(fill_color().as_int());
		// fl_rectf (point(0).x,point(0).y,w ,h); // функция для рисования заполненного прямоугольника
	}
	// не понятно что за метод color() скорее всего это текущий цвет
	//if (color().alpha() != 0) // линии поверх заполнения
	//{
		// fl_color(fill_color().as_int());
		// fl_rect (point(0).x,point(0).y,w ,h); // функция для рисования пустого прямоугольника
	//}
}

MLines::MLines(const QList<QPair<QPoint, QPoint>> & lst)
{
	for (const auto p : lst)
	{
		add(p);
	}
}

bool MLines::drawLines(QPainter * painterDevice) const
{
	if (!painterDevice)
		return false;

	if (points().size() == 0)
		return false;

	if (lineColor() != Qt::GlobalColor::transparent)
	{
		painterDevice->setPen(linePen());

		for (int i = 1; i < numberOfPoints(); i += 2)
		{
			painterDevice->drawLine(points()[i - 1], points()[i]);
		}
	}

	return true;
}

void MLines::add(const QPair<QPoint, QPoint>& lineByPoints)
{
	MShape::add(lineByPoints.first);
	MShape::add(lineByPoints.second);
}


MAxis::MAxis(Orientation d, QPoint xy, int length, int numberOfNotches, QString & label)
{
	if (length <= 0)
	{
		qDebug().noquote() << "Wrong length";
		return;
	}

	switch (d)
	{
	case MAxis::x:
	{
		/* линия оси */
		MShape::add(xy);
		MShape::add(QPoint{ xy.x() + length, xy.y() });
		/* добавление делений */
		if (numberOfNotches > 0)
		{
			int dist = length / numberOfNotches;
			int x = xy.x() + dist;
			for (int i = 0; i < numberOfNotches; ++i)
			{
				_noches.add(QPair<QPoint, QPoint>{QPoint{ x, xy.y() }, QPoint{ x,xy.y() - 5 }});
				x += dist;
			}
		}
		/* метка под линией */
		_label = MLabel{ QPoint{xy.x(), xy.y() + 10},label };

		break;
	}
	case MAxis::y:
	{
		/* ось y, идущая вверх */
		MShape::add(xy);
		MShape::add(QPoint{ xy.x(), xy.y() - length });
		/* добавление делений */
		if (numberOfNotches > 0)
		{
			int dist = length / numberOfNotches;
			int y = xy.y() - dist;
			for (int i = 0; i < numberOfNotches; ++i)
			{
				_noches.add(QPair<QPoint, QPoint>{QPoint{ xy.x(), y }, QPoint{ xy.x() + 5, y }});
				y -= dist;
			}
		}
		/* метка вверху */
		_label = MLabel{ QPoint{xy.x() - 10, xy.y() - length},label };
		break;
	}
	case MAxis::z:
		break;
	default:
		break;
	}
}

bool MAxis::drawLines(QPainter * painterDevice) const
{
	if (!painterDevice)
		return false;

	if (points().size() == 0)
		return false;

	MShape::drawLines(painterDevice);
	_noches.drawLines(painterDevice);

	painterDevice->setPen(Qt::GlobalColor::blue);
	painterDevice->drawText(_label._xy, _label._labelText);

	return true;
}

void MAxis::move(int xx, int xy)
{
}

void MAxis::setLineColor(const QColor & color)
{
	MShape::setLineColor(color);
	_noches.setLineColor(color);
}
