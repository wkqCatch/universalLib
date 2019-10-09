#include "client.h"
#include "QDialogTest.h"
#include <QtWidgets/QApplication>

#include <QFile>
#include <QProcess>
#include <QSerialPort>

#include <QDebug>
#include <QElapsedTimer>

#include "../QUniversalFrameLib/QCustomMessageBox.h"
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")

#include "../QSerialPortLib/QCustomModbusClient.h"
#pragma comment(lib, "../X64/Debug/QSerialPortLib.lib")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFile qssFile(":/FullBlack/FullBlack.qss");

	if (qssFile.open(QFile::ReadOnly))
	{
		QString strStyleSheet = qssFile.readAll();
		a.setStyleSheet(strStyleSheet);
		qssFile.close();
	}

	qDebug() << "hello world" << endl;
	QElapsedTimer tim;
	tim.start();
	while (tim.elapsed() < 3000)
	{
	}

	CommunicationSettings settings = { "COM5", QSerialPort::NoParity, QSerialPort::Baud9600, QSerialPort::Data8,
									QSerialPort::OneStop, 520, "192", 1000, 3 };

	QCustomModbusClient modbusClient(settings);
	bool bResult = modbusClient.connectModbusClient();
	if (!bResult)
	{
	}

	qDebug() << "nihao,zhongguo" << endl;

	QDialogTest dialogTest;
	dialogTest.show();

	int a = 0; 
	int b = 0;

	return a.exec();
}