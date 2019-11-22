#include "QMyClient.h"

#include <QSplitter>

#include "../QCustomModelViewLib/QCustomTableWidget.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QCustomModelViewLib.lib")
#else
#pragma comment(lib, "../X64/Release/QCustomModelViewLib.lib")
#endif

QMyClient::QMyClient(QWidget *parent)
	: QMainWindow(parent)
	, m_pCustomTableWidget1(nullptr)
{
	ui.setupUi(this);

	QSplitter *pSplitter = new QSplitter(this);
	setCentralWidget(pSplitter);

	m_pCustomTableWidget1 = new QCustomTableWidget(6, 6, pSplitter);
	m_pCustomTableWidget2 = new QCustomTableWidget(180, 8, pSplitter);

	pSplitter->addWidget(m_pCustomTableWidget1);
	pSplitter->addWidget(m_pCustomTableWidget2);

	for(int nRowCounter = 0; nRowCounter < m_pCustomTableWidget1->rowCount(); nRowCounter++)
	{
		for(int nColCounter = 0; nColCounter < m_pCustomTableWidget1->columnCount(); nColCounter++)
		{
			QTableWidgetItem *pItem = new QTableWidgetItem(QString::number(nRowCounter * nColCounter));
			m_pCustomTableWidget1->setItem(nRowCounter, nColCounter, pItem);
		}
	}

	for (int nRowCounter = 0; nRowCounter < m_pCustomTableWidget2->rowCount(); nRowCounter++)
	{
		for (int nColCounter = 0; nColCounter < m_pCustomTableWidget2->columnCount(); nColCounter++)
		{
			QTableWidgetItem *pItem = new QTableWidgetItem(QString::number(nRowCounter * nColCounter));
			m_pCustomTableWidget2->setItem(nRowCounter, nColCounter, pItem);
		}
	}
}
