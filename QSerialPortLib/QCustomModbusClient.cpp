#include "QCustomModbusClient.h"

#include <QModbusDevice>
#include <QModbusRtuSerialMaster>
#include <QModbusTcpClient>
#include <QModbusDataUnit>

#include <QSerialPort>

#include <QVariant>
#include <QThread>

#include <QMetaObject>

QCustomModbusClient::QCustomModbusClient(QObject * parent)
	: QObject(parent)
	, m_pModbusClient(nullptr)
	, m_pModebusReply(nullptr)
	, m_pThread(nullptr)
	, m_bCommunicating(false)
	, m_bConnectFlag(false)
{
	qRegisterMetaType<QVector<quint16>>("QVector<quint16>");

	m_pThread = new QThread();
	
	this->moveToThread(m_pThread);                 //将该类移动到线程里

	connect(m_pThread, &QThread::started, this, &QCustomModbusClient::slot_threadStart);

	connect(this, &QCustomModbusClient::sig_setParam, this, &QCustomModbusClient::slot_setParam);
	connect(this, &QCustomModbusClient::sig_connectClient, this, &QCustomModbusClient::slot_connectClient);
	connect(this, &QCustomModbusClient::sig_disconnectClient, this, &QCustomModbusClient::slot_disconnectClient);

	connect(this, QOverload<int, int, unsigned short, int>::of(&QCustomModbusClient::sig_readRequest), 
		    this, QOverload<int, int, unsigned short, int>::of(&QCustomModbusClient::slot_readRequest));
	connect(this, &QCustomModbusClient::sig_writeRequest, this, &QCustomModbusClient::slot_writeRequest);

	m_pThread->start();
}

QCustomModbusClient::~QCustomModbusClient()
{
	m_pThread->quit();
	m_pThread->wait();

	delete m_pThread;
	m_pThread = nullptr;
}

void QCustomModbusClient::slot_threadStart()
{
	m_pModbusClient = new QModbusRtuSerialMaster();
	m_pModbusClient->moveToThread(m_pThread);
	connect(m_pThread, &QThread::finished, m_pModbusClient, &QCustomModbusClient::deleteLater);
}

bool QCustomModbusClient::setParameter(const CommunicationSettings & settings)
{
	return setParameter(settings.strSerialPortName, settings.nBaudRate, settings.nDataBits, settings.nStopBits,
				settings.nParity, settings.nReplyOverTime, settings.nRetryTimes);
}

bool QCustomModbusClient::setParameter(const QString &strPortName, const int &nBaudRate, const int &nDataBits, const int &nStopBits,
									  const int &nParity, const int &nOverTime, const int &nRetryTimes)
{
	QMutexLocker mutexLocker(&m_mutexSetParam);

	const int nAvailableSems = m_semSetParam.available();
	if (nAvailableSems > 0)
	{
		m_semSetParam.tryAcquire(nAvailableSems);
	}

	m_bSetParamFlag = false;
	emit sig_setParam(strPortName, nBaudRate, nDataBits, nStopBits, nParity, nOverTime, nRetryTimes);

	bool bWait = m_semSetParam.tryAcquire(1, 5000);
	
	return bWait ? m_bSetParamFlag : false;
}

void QCustomModbusClient::slot_setParam(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
										int nParity, int nOverTime, int nRetryTimes)
{
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialPortNameParameter, strPortName);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, nBaudRate);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, nDataBits);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, nStopBits);
	m_pModbusClient->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);

	m_pModbusClient->setTimeout(nOverTime);
	m_pModbusClient->setNumberOfRetries(nRetryTimes);

	if(m_pModbusClient->error() == QModbusDevice::NoError)
	{
		m_bSetParamFlag = true;
	}

	m_semSetParam.release();
}

bool QCustomModbusClient::connectModbusClient()
{
	QMutexLocker mutexLocker(&m_mutexConnect);

	const int nAvailableSems = m_semConnect.available();
	if (nAvailableSems > 0)
	{
		m_semConnect.tryAcquire(nAvailableSems);
	}

	emit sig_connectClient();
	bool bWait = m_semConnect.tryAcquire(1, 5000);

	return bWait ? m_bConnectFlag : false;
}

void QCustomModbusClient::slot_connectClient()
{
	if (m_pModbusClient->state() == QModbusDevice::ConnectedState)
	{
		m_bConnectFlag = true;
		m_semConnect.release();
		return;
	}

	m_bConnectFlag = m_pModbusClient->connectDevice();

	m_semConnect.release();
}

void QCustomModbusClient::disconnectModbusClient()
{
	QMutexLocker mutexLocker(&m_mutexDisconnect);

	const int nAvailableSems = m_semDisconnect.available();
	if (nAvailableSems > 0)
	{
		m_semDisconnect.tryAcquire(nAvailableSems);
	}
	
	emit sig_disconnectClient();

	m_semDisconnect.tryAcquire(1, 5000);
}

void QCustomModbusClient::slot_disconnectClient()
{
	m_pModbusClient->disconnectDevice();

	m_semDisconnect.release();
}

bool QCustomModbusClient::constructRequest(QModbusDataUnit& dataUnit, int regType, int nStartAddress, int nValue)
{
	dataUnit.setRegisterType(static_cast<QModbusDataUnit::RegisterType>(regType));
	dataUnit.setStartAddress(nStartAddress);
	dataUnit.setValueCount(nValue);

	return dataUnit.isValid();
}

QModbusDataUnit QCustomModbusClient::constructRequest(const int &regType, const int & nStartAddress, const unsigned short &nValue)
{
	return QModbusDataUnit(static_cast<QModbusDataUnit::RegisterType>(regType), nStartAddress, nValue);
}

QModbusDataUnit QCustomModbusClient::constructRequest(const int &regType, const int & nStartAddress, const QVector<quint16>& nDatas)
{
	return QModbusDataUnit(static_cast<QModbusDataUnit::RegisterType>(regType), nStartAddress, nDatas);
}

int QCustomModbusClient::getCurrentError() const
{
	return m_pModbusClient->error();
}

int QCustomModbusClient::getCurrentState() const
{
	return static_cast<int>(m_pModbusClient->state());
}

bool QCustomModbusClient::readRequest(const int & regType, const int & nStartAddress, const unsigned short & nValue, const int & nServerAddr)
{
	QMutexLocker mutexLocker(&m_mutexReadRequest);

	if(m_bCommunicating == true)
	{
		return 1;
	}

	m_rwlockCommunicatingState.lockForWrite();
	m_bCommunicating = true;
	m_rwlockCommunicatingState.unlock();

	emit sig_readRequest(regType, nStartAddress, nValue, nServerAddr);

	return 0;
}

void QCustomModbusClient::slot_readRequest(int nregType, int nStartAddress, unsigned short nValue, int nServerAddr)
{
	QModbusDataUnit dataUnit = constructRequest(nregType, nStartAddress, nValue);

	QModbusReply *pReply = m_pModbusClient->sendReadRequest(dataUnit, nServerAddr);
	if(pReply == nullptr)
	{
		emit sig_replyReady(pReply);

		m_rwlockCommunicatingState.lockForWrite();
		m_bCommunicating = false;
		m_rwlockCommunicatingState.unlock();
	}
	else
	{
		if (!pReply->isFinished())
		{
			connect(pReply, &QModbusReply::finished, this, &QCustomModbusClient::slot_reply);
		}
		else
		{
			emit sig_replyReady(pReply);

			m_rwlockCommunicatingState.lockForWrite();
			m_bCommunicating = false;
			m_rwlockCommunicatingState.unlock();
		}
	}
}

void QCustomModbusClient::slot_reply()
{
	QModbusReply * reply = qobject_cast<QModbusReply *>(sender());
	emit sig_replyReady(reply);

	m_rwlockCommunicatingState.lockForWrite();
	m_bCommunicating = false;
	m_rwlockCommunicatingState.unlock();
}

bool QCustomModbusClient::writeRequest(const int & regType, const int & nStartAddress, const QVector<quint16>& nDatas,
											  const int &nServerAddr)
{
	QMutexLocker mutexLocker(&m_mutexWriteRequest);

	if (m_bCommunicating == true)
	{
		return 1;
	}

	m_rwlockCommunicatingState.lockForWrite();
	m_bCommunicating = true;
	m_rwlockCommunicatingState.unlock();

	emit sig_writeRequest(regType, nStartAddress, nDatas, nServerAddr);

	return 0;
}

CommunicationSettings QCustomModbusClient::getParameter() const
{
	CommunicationSettings settings;
	settings.strSerialPortName = m_pModbusClient->connectionParameter(QModbusDevice::SerialPortNameParameter).toString();
	settings.nBaudRate = m_pModbusClient->connectionParameter(QModbusDevice::SerialBaudRateParameter).toInt();
	settings.nDataBits = m_pModbusClient->connectionParameter(QModbusDevice::SerialDataBitsParameter).toInt();
	settings.nStopBits = m_pModbusClient->connectionParameter(QModbusDevice::SerialStopBitsParameter).toInt();
	settings.nParity = m_pModbusClient->connectionParameter(QModbusDevice::SerialParityParameter).toInt();
	settings.nRetryTimes = m_pModbusClient->numberOfRetries();
	settings.nReplyOverTime = m_pModbusClient->timeout();
	settings.ucStationNum = 1;

	return settings;
}

void QCustomModbusClient::slot_writeRequest(int nRegType, int nStartAddress, QVector<quint16> vecDatas, int nServerAddr)
{
	QModbusDataUnit dataUnit = constructRequest(nRegType, nStartAddress, vecDatas);

	QModbusReply *pReply = m_pModbusClient->sendWriteRequest(dataUnit, nServerAddr);
	if (pReply == nullptr)
	{
		emit sig_replyReady(pReply);

		m_rwlockCommunicatingState.lockForWrite();
		m_bCommunicating = false;
		m_rwlockCommunicatingState.unlock();
	}
	else
	{
		if (!pReply->isFinished())
		{
			connect(pReply, &QModbusReply::finished, this, &QCustomModbusClient::slot_reply);
		}
		else
		{
			emit sig_replyReady(pReply);

			m_rwlockCommunicatingState.lockForWrite();
			m_bCommunicating = false;
			m_rwlockCommunicatingState.unlock();
		}
	}
}