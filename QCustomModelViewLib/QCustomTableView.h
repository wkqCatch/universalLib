#pragma once

#include "qcustommodelviewlib_global.h"
#include <QTableView>

class QCUSTOMMODELVIEWLIB_EXPORT QCustomTableView : public QTableView
{
	Q_OBJECT

public:
	QCustomTableView(QWidget *parent);
	~QCustomTableView();
};
