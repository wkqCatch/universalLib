#include "client.h"

#include "QCustomMainWindowMenuBar.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
	, pcustomMenuBar(nullptr)
{
	ui.setupUi(this);

	int menuBarHeight = menuBar()->height();

	pcustomMenuBar = new QCustomMainWindowMenuBar(this, 23);
	pcustomMenuBar->enableMaximize(false);
	pcustomMenuBar->setAppIcon(":/client/AppIcon");
	pcustomMenuBar->setAppTitle(QStringLiteral("¿Õµµ°¸aaaaaaa"));
}

client::~client()
{
}