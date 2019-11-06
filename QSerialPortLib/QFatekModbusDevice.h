#pragma once

#include "QAbstractModbusDevice.h"

class QFatekModbusDevice : public QAbstractModbusDevice
{
	Q_OBJECT

public:
	QFatekModbusDevice(QObject *parent);
	virtual ~QFatekModbusDevice();

protected:
	void construcRegisterPair() override;
};
