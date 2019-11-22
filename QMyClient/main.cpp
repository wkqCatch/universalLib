#include "QMyClient.h"
#include <QtWidgets/QApplication>

#include <QFile>

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

	QMyClient w;
	w.showMaximized();

	return a.exec();
}
