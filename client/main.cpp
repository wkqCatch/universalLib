#include "client.h"
#include "QDialogTest.h"
#include <QtWidgets/QApplication>

#include <QFile>
#include <QProcess>
#include <QSerialPort>

#include <QDebug>
#include <QElapsedTimer>

#include "QSerialportUI.h"
#include "QCustomModbusClient.h"

#include <QTableWidget>

#include <QListView>
#include <QStringListModel>

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
	settings.nBaudRate = 19200;
	settings.nDataBits = 8;
	settings.nStopBits = 1;
	settings.nParity = 0;
	settings.nReplyOverTime = 1000;
	settings.nRetryTimes = 3;
	settings.ucStationNum = 1;
	settings.nCommunicationMode = 0;

// 	QStringList list;
// 	list << "a" << "b" << "c" << "d";
// 	QStringListModel listModel(list);
// 	QListView listView;
// 	listView.setModel(&listModel);
// 	listView.show();

// 	QSerialportUI serialPortUI(nullptr);
// 	serialPortUI.show();

	QTableWidget table(6, 6);
	QTableWidgetItem *item0 = new QTableWidgetItem("hello china");

	//table.setAlternatingRowColors(true);

	table.setItem(0, 0, item0);
	table.setSelectionMode(QAbstractItemView::ExtendedSelection);
	table.setSelectionBehavior(QAbstractItemView::SelectRows);

	table.show();

	QTableWidgetItem *pTim = table.item(0, 0);




// 	table.horizontalHeader()->setDefaultSectionSize(200);
// 	table.horizontalHeader()->setStretchLastSection(true);
// 	table.verticalHeader()->setStretchLastSection(true);
// 	table.setSelectionMode(QAbstractItemView::MultiSelection);
// 	QStringList headerList;
// 	headerList << "A" << "B" << "C";
// 	table.setColumnCount(6);
// 	table.setRowCount(6);
// 	table.setHorizontalHeaderLabels(headerList);
// 	table.show();

	
	// 	client myClient;
	// 	myClient.show();

	// 	QDialogTest dlgTest;
	// 	dlgTest.show();

	return a.exec();
}