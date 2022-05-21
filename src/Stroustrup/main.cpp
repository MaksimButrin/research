//#include <QDebug>
//#include <Stroustrup.h>
//
//using namespace std;
//
//int main(int argc, char *argv[])
//{
//	qDebug() << "Stroustrup";
//	cout << "sssss";
//	init();
//
//	//return 0;
//}

// <<<<<<<<<<<<<<<<<<< до 2022/05/07 (повторное начало изучения)
#include "GraphMainWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GraphMainWindow mainwindow;
	mainwindow.show();

	return a.exec();
}





//#include <qdebug.h>
//#include <Stroustrup.h>
//#include <FL/Fl.h>
//#include <FL/Fl_Box.h>
//#include <FL/Fl_Window.h>
//
//
//using namespace std;
//
//int main(int argc, char *argv[])
//{
//	qDebug() << "Stroustrup";
//
//	init();
//
//	//chrono::runChrono();
//
//	//auto result = StrausCalc().calcRun();
//
//	//return StrausCalc().calcRun();
//	//return 0;
//
//	//Fl_Window window(200, 200, "Window title");
//	//Fl_Box box(0, 0, 200, 200, "Hey, I mean, Hello, World!");
//	//window.show();
//	//return Fl::run();
//
//	return 0;
//}