#pragma once

#include "qcustommodelviewlib_global.h"

#include <QTableWidget>

class QCUSTOMMODELVIEWLIB_EXPORT QCustomTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	QCustomTableWidget(QWidget *pParent = nullptr);
	QCustomTableWidget(int rows, int columns, QWidget *parent = nullptr);

	virtual ~QCustomTableWidget();

	
};
