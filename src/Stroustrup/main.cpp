#include <qdebug.h>
#include <Stroustrup.h>

using namespace std;

int main(int argc, char *argv[])
{
	qDebug() << "Stroustrup";

	init();

	//auto result = StrausCalc().calcRun();

	return StrausCalc().calcRun();
}