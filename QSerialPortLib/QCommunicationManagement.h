#pragma once

#include <QObject>

#include "QCustomModbusClient.h"
#include "QCustomModbusServer.h"

class QCommunicationManagement : public QObject
{
	Q_OBJECT

public:
	

	QCommunicationManagement(QObject *parent);
	~QCommunicationManagement();
};
