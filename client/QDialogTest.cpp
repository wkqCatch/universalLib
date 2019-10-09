#include "QDialogTest.h"

#include "../QUniversalFrameLib/QCustomDialogTitleBar.h"
#include "../QUniversalFrameLib/QCustomMessageBox.h"
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")

QDialogTest::QDialogTest(QWidget *parent)
	: QDialog(parent)
	, pCustomTitleBar(nullptr)
{
	setupUi(this);

	pCustomTitleBar = new QCustomDialogTitleBar(this, m_pFrameTitleBar, 20, false);
	pCustomTitleBar->enableMaximize(false);
	pCustomTitleBar->setTitleName("hello");
	pCustomTitleBar->setTitleIcon(":/client/AppIcon");
}

QDialogTest::~QDialogTest()
{
	if (pCustomTitleBar != nullptr)
	{
		delete pCustomTitleBar;
		pCustomTitleBar = nullptr;
	}
}
