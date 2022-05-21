#include "InOut.h"
#include <QDebug> 
#include <QDir> 

using namespace std;


namespace nsInOut
{



void InOut::run()
{
	qDebug().noquote() << QString("Please input number 0-10");

	int n = 0;
	while (cin >> n && (n < 0 || n > 10))
	{
			qDebug().noquote() << QString("Wrong number");
	}

	qDebug().noquote() << QString("Correct number");

	//while (cin >> n)
	//{
	//	if (n < 0 || n > 10)
	//	{
	//		qDebug().noquote() << QString("Wrong number");
	//	}
	//	else
	//	{
	//		qDebug().noquote() << QString("Correct number");
	//		break;
	//	}
	//}
}

void InOut::readWriteFile()
{
	
	QDir dir(QDir::currentPath());
	QString absPath = dir.absoluteFilePath("../../../../etc/");
	QString inFileName = QFileInfo(absPath + "inFile.txt").canonicalFilePath();


	qDebug().noquote() << QString("File name %1").arg(inFileName);

	ifstream inFile{ inFileName.toStdString() };


	if (!inFile)
	{
		qDebug().noquote() << QString("Error open file for read '%1'").arg(inFileName);
		return;
	}
	else
	{
		qDebug().noquote() << QString("File for read is open");
	}

	QString outFileName = QFileInfo(absPath + "outFile.txt").canonicalFilePath();
	ofstream outFile{ outFileName.toStdString() };

	if (!outFile)
	{
		qDebug().noquote() << QString("Error open file for write '%1'").arg(outFileName);
		return;
	}
	else
	{
		qDebug().noquote() << QString("File for write is open");
	}


	ReadBufer rb;

	while (inFile >> rb.hour >> rb.temp >> rb.abstract)
	{
		if (rb.hour >= 0 && rb.hour <= 23)
		{
			_readBUfer.push_back(rb);
		}
		else
		{
			qDebug().noquote() << "Error read of line";
		}

		if (inFile.eof())
		{
			qDebug().noquote() << "The End of read";
		}
	}

	QString message{"%1: hour: %2; temp: %3; abstract value %4"};
	int i{ 1 };
	for (auto & item : _readBUfer)
	{
		qDebug().noquote() << message.arg(i).arg(item.hour).arg(item.temp).arg(QString::number(item.abstract, 16));
		
		outFile << message.arg(i).arg(item.hour).arg(item.temp).arg(QString::number(item.abstract, 16)).toStdString() << "\n";

		++i;
	}
	


}

void runInOut()
{
	InOut inOut;

	inOut.readWriteFile();

}

}