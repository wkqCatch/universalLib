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

// 	client myClient;
// 	myClient.show();

	QDialogTest dlgTest;
	dlgTest.show();

	return a.exec();
}