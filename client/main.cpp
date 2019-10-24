#include "client.h"
#include "QDialogTest.h"
#include <QtWidgets/QApplication>

#include <QFile>
#include <QProcess>
#include <QSerialPort>

#include <QDebug>
#include <QElapsedTimer>

#include "QSerialportUI.h"

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
	
	CommunicationSettings settings;
	settings.strSerialPortName = "COM6";
	settings.nBaudRate = 9600;
	settings.nDataBits = 8;
	settings.nStopBits = 1;
	settings.strParity = QStringLiteral("无校验");
	settings.nReplyOverTime = 1000;
	settings.nRetryTimes = 3;
	settings.ucStationNum = 1;
	settings.strCommunicationProtocol = QStringLiteral("Modbus RTU");
	settings.strMasterOrSlave = QStringLiteral("主站");

	QSerialportUI serialPortUI(nullptr, settings);
	serialPortUI.show();
	
	// 	client myClient;
	// 	myClient.show();

	// 	QDialogTest dlgTest;
	// 	dlgTest.show();

	return a.exec();
}