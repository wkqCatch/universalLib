#include "QCustomModbusClient.h"

#include <QModbusRtuSerialMaster>
#include <QModbusTcpClient>

#include <QVariant>
#include <QThread>

QCustomModbusClient::QCustomModbusClient(const CommunicationSettings &mySettings, QObject * parent)
	: QObject(parent)
	, m_pModbusClient(nullptr)
	, m_pModebusReply(nullptr)
	, m_pClientThread(nullptr)
	, m_pModbusDataUnit(nullptr)
{
	m_pModbusDataUnit = new QModbusDataUnit();

	if (mySettings.enumType == Serial)
	{
		m_pModbusClient = new QModbusRtuSerialMaster();
	}
	else
	{
		m_pModbusClient = new QModbusTcpClient();
	}

	m_pClientThread = new QThread();
	this->moveToThread(m_pClientThread);                 //将该类移动到线程里

	setParameter(mySettings);                            //设置参数
}

QCustomModbusClient::~QCustomModbusClient()
{
	m_pClientThread->quit();
	m_pClientThread->wait();

	delete m_pClientThread;
	m_pClientThread = nullptr;

	if (m_pModbusClient)
	{
		m_pModbusClient->disconnectDevice();
		delete m_pModbusClient;
		m_pModbusClient = nullptr;
	}

	if (m_pModbusDataUnit)
	{
		delete m_pModbusDataUnit;
		m_pModbusDataUnit = nullptr;
	}
}

void QCustomModbusClient::setParameter(const CommunicationSettings & settings)
{
	if (m_pModbusClient == nullptr)
	{
		return;
	}

	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialPortNameParameter, settings.strSerialPortName);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialParityParameter, settings.nParity);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, settings.nBaudRate);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, settings.nDataBits);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, settings.nStopBits);
	m_pModbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, settings.nNetworkPort);
	m_pModbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, settings.strNetworkAddress);

	m_pModbusClient->setTimeout(settings.nTimeOut);
	m_pModbusClient->setNumberOfRetries(settings.nNumOfRetries);
}

bool QCustomModbusClient::connectModbusClient()
{
	if (m_pModbusClient == nullptr)
	{
		return false;
	}

	return m_pModbusClient->connectDevice();
}

void QCustomModbusClient::disconnectModbusClient()
{
	m_pModbusClient->disconnectDevice();
}

bool QCustomModbusClient::constructRequest(int regType, int nStartAddress, int nValue)
{
	m_pModbusDataUnit->setRegisterType(static_cast<QModbusDataUnit::RegisterType>(regType));
	m_pModbusDataUnit->setStartAddress(nStartAddress);
	m_pModbusDataUnit->setValueCount(nValue);

	return m_pModbusDataUnit->isValid();
}