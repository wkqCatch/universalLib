#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_client.h"

class QCustomMainWindowMenuBar;
class client : public QMainWindow
{
	Q_OBJECT

public:
	explicit client(QWidget *parent = nullptr);
	~client();

private:
	Ui::clientClass ui;

	QCustomMainWindowMenuBar *pcustomMenuBar;
};
