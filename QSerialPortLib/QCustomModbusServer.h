#pragma once

#include <QObject>

class QCustomModbusServer : public QObject
{
	Q_OBJECT

public:
	QCustomModbusServer(QObject *parent = nullptr);
	~QCustomModbusServer();
};
