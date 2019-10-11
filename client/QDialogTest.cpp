#include "QDialogTest.h"

#include "../QUniversalFrameLib/QCustomDialogTitleBar.h"
#include "../QUniversalFrameLib/QCustomMessageBox.h"
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")

QDialogTest::QDialogTest(QWidget *parent)
	: QDialog(parent)
	, pCustomTitleBar(nullptr)
{
	setupUi(this);

	pCustomTitleBar = new QCustomDialogTitleBar(this, m_pFrameTitleBar, 20);
	pCustomTitleBar->hideMaximize(false);
	pCustomTitleBar->setTitleName("hello");
	pCustomTitleBar->setTitleIcon(":/client/AppIcon");

	setSizeGripEnabled(true);
}

QDialogTest::~QDialogTest()
{
	
}
