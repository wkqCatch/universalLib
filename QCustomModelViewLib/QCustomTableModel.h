#pragma once

#include "qcustommodelviewlib_global.h"
#include <QAbstractTableModel>

class QCUSTOMMODELVIEWLIB_EXPORT QCustomTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	QCustomTableModel(QObject *parent);
	virtual ~QCustomTableModel();
};


