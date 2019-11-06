#include "QFatekModbusDevice.h"

QFatekModbusDevice::QFatekModbusDevice(QObject *parent)
	: QAbstractModbusDevice(parent)
{

}

QFatekModbusDevice::~QFatekModbusDevice()
{

}

void QFatekModbusDevice::construcRegisterPair()
{
	DeviceRegister deviceRegY;
	deviceRegY.strName = "Y";
	deviceRegY.nStartAddr = 0;
	deviceRegY.nEndAddr = 255;
	deviceRegY.opMode = readWrite;
	deviceRegY.daMode = coils;
	m_listRegister.append(deviceRegY);

	DeviceRegister deviceRegX;
	deviceRegX.strName = "X";
	deviceRegX.nStartAddr = 1000;
	deviceRegX.nEndAddr = 1255;
	deviceRegX.opMode = readOnly;
	deviceRegX.daMode = coils;
	m_listRegister.append(deviceRegX);

	DeviceRegister deviceRegM;
	deviceRegM.strName = "M";
	deviceRegM.nStartAddr = 2000;
	deviceRegM.nEndAddr = 4001;
	deviceRegM.opMode = readWrite;
	deviceRegM.daMode = coils;
	m_listRegister.append(deviceRegM);

	DeviceRegister deviceRegR;
	deviceRegR.strName = "R";
	deviceRegR.nStartAddr = 0;
	deviceRegR.nEndAddr = 4167;
	deviceRegR.opMode = readWrite;
	deviceRegR.daMode = holdregister;
	m_listRegister.append(deviceRegR);

	DeviceRegister deviceRegD;
	deviceRegD.strName = "R";
	deviceRegD.nStartAddr = 6000;
	deviceRegD.nEndAddr = 8998;
	deviceRegD.opMode = readWrite;
	deviceRegD.daMode = holdregister;
	m_listRegister.append(deviceRegD);
}
