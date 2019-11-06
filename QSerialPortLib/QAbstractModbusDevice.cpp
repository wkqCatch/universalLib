#include "QAbstractModbusDevice.h"

QAbstractModbusDevice::QAbstractModbusDevice(QObject *parent)
	: QObject(parent)
{
	construcRegisterPair();
}

QAbstractModbusDevice::~QAbstractModbusDevice()
{

}

QStringList QAbstractModbusDevice::getRegisterStrings() const
{
	QStringList strList;
	for each (const DeviceRegister& reg in m_listRegister)
	{
		strList << reg.strName;
	}

	return strList;
}

QAbstractModbusDevice::DeviceRegister QAbstractModbusDevice::getCurrentDeviceReg(const QString & strName) const
{
	DeviceRegister reg{""};

	for each (DeviceRegister var in m_listRegister)
	{
		if(var.strName == strName)
		{
			reg = var;
		}
	}

	return reg;
}

void QAbstractModbusDevice::construcRegisterPair()
{

}
