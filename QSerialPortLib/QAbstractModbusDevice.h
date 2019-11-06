#pragma once

#include <QObject>
#include <QList>

class QAbstractModbusDevice : public QObject
{
	Q_OBJECT

public:
	enum OperateMode { readOnly, writeOnly, readWrite };
	enum DataMode { coils, holdregister };
	struct DeviceRegister
	{
		QString strName;
		int nStartAddr;
		int nEndAddr;
		OperateMode opMode;
		DataMode daMode;
	};
	
	QAbstractModbusDevice(QObject *parent);
	virtual ~QAbstractModbusDevice();

	QStringList getRegisterStrings() const;
	DeviceRegister getCurrentDeviceReg(const QString &strName) const;

protected:
	QList<DeviceRegister> m_listRegister;

protected:
	virtual void construcRegisterPair();      //×é½¨¼Ä´æÆ÷¶Ô
};
