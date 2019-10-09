#pragma once

#include <QWidget>
#include "ui_QDialogTest.h"

#include <QDialog>

class QCustomDialogTitleBar;
class QDialogTest : public QDialog, public Ui::QDialogTest
{
	Q_OBJECT

public:
	QDialogTest(QWidget *parent = Q_NULLPTR);
	~QDialogTest();

private:
	QCustomDialogTitleBar *pCustomTitleBar;
};
