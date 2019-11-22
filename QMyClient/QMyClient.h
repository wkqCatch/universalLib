#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QMyClient.h"

class QCustomTableWidget;
class QMyClient : public QMainWindow
{
	Q_OBJECT

public:
	QMyClient(QWidget *parent = Q_NULLPTR);

private:
	Ui::QMyClientClass ui;

	QCustomTableWidget *m_pCustomTableWidget1;
	QCustomTableWidget *m_pCustomTableWidget2;
};
