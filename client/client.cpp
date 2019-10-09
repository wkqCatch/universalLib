#include "client.h"

#include "../QUniversalFrameLib/QCustomMainWindowMenuBar.h"
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")

#include "../QMotionControlLib/QIMCMotionControl.h"
#pragma comment(lib, "../X64/Debug/QMotionControlLib.lib")

client::client(QWidget *parent)
	: QMainWindow(parent)
	, pcustomMenuBar(nullptr)
{
	ui.setupUi(this);

	int menuBarHeight = menuBar()->height();

	pcustomMenuBar = new QCustomMainWindowMenuBar(this, 25);
	pcustomMenuBar->setAppIcon(":/client/AppIcon");
	pcustomMenuBar->setAppTitle(QStringLiteral("¿Õµµ°¸aaaaaaa"));
}

client::~client()
{
	if (pcustomMenuBar != nullptr)
	{
		delete pcustomMenuBar;
		pcustomMenuBar = nullptr;
	}
}
