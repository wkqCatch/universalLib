#pragma once

#include "QAbstractCameraFind.h"

class PvSystem;
class QSentechGigeCamFind : public QAbstractCameraFind
{
	Q_OBJECT

public:
	QSentechGigeCamFind(QObject *parent = nullptr);
	~QSentechGigeCamFind();

	PvSystem *m_pSystem;
};
