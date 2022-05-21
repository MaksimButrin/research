#include <qdebug.h>
#include <StroustrupCalc.h>

using namespace std;

int main(int argc, char *argv[])
{
	qDebug() << "StroustrupCalc";

	init();

	//chrono::runChrono();

	//auto result = StrausCalc().calcRun();

	return StrausCalc().calcRun();
	//return 0;

	//Fl_Window window(200, 200, "Window title");
	//Fl_Box box(0, 0, 200, 200, "Hey, I mean, Hello, World!");
	//window.show();
	//return Fl::run();

	return 0;
}