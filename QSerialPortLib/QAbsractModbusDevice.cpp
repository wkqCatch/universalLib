#include "QAbsractModbusDevice.h"
#include "QCustomSerialPort.h"

#include <QThread>

QAbsractModbusDevice::QAbsractModbusDevice(QCustomSerialPort *pSerialPort, QObject *parent)
	: QObject(parent)
{
	m_pThread = new QThread();
	this->moveToThread(m_pThread);

	if(pSerialPort != nullptr)
	{
		m_pCustomSerialPort = pSerialPort;
		connect(m_pCustomSerialPort, &QCustomSerialPort::sig_DataReady, this, &QAbsractModbusDevice::slot_ReceiveData);
	}
}

QAbsractModbusDevice::~QAbsractModbusDevice()
{
	m_pThread->quit();
	m_pThread->wait();

	delete m_pThread;
	m_pThread = nullptr;
}

bool QAbsractModbusDevice::isSerialPortOpened() const
{
	return m_pCustomSerialPort->isOpened();
}

QCustomSerialPort * QAbsractModbusDevice::getCurrentSerialPort() const
{
	return m_pCustomSerialPort;
}

void QAbsractModbusDevice::slot_ReceiveData(QByteArray byData)
{
}
