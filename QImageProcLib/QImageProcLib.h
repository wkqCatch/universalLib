#pragma once

#include "qimageproclib_global.h"

#include <QObject>

class QWidget;
class QIMAGEPROCLIB_EXPORT QImageProcLib : public QObject
{
public:
	QImageProcLib(QObject *pParent);

private:
	QWidget *m_pWidget;
};
