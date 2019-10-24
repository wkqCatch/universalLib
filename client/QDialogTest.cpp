#include "QDialogTest.h"

#include <QCustomDialogTitleBar.h>
#include <QCustomMessageBox.h>

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