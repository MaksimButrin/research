#pragma once

#include <iostream>
#include <fstream>
#include <QVector>
#include <QString>


namespace nsInOut
{

struct ReadBufer
{
	int hour;
	double temp;
	int abstract;
};


class InOut
{
public:
	InOut() {}
	~InOut() {}

	void run();
	void readWriteFile();

private:

	QVector<ReadBufer> _readBUfer;

};

void runInOut();

}

