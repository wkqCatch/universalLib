#include "QCustomSerialPort.h"

#include <QThread>
#include <QDateTime>
#include <QDebug>
#include <QSerialPort>

QCustomSerialPort::QCustomSerialPort(const QString & strName, QObject * pParent)
	: QObject(pParent)
	, m_pThread(nullptr)
	, m_pSerialPort(nullptr)
	, m_bOpenResult(false)
	, m_nWriteLength(0)
	, m_bEchoFlag(false)
	, m_strInBuffer()
	, m_strReply()
	, m_strExpectReply()
	, m_rxExpectReply()
	, m_bEchoRegExp(false)
	, m_bSetSerialParamResult(false)
{
	m_pThread = new QThread();
	m_pSerialPort = new QSerialPort();

	this->moveToThread(m_pThread);
	m_pSerialPort->moveToThread(m_pThread);

	connect(this, &QCustomSerialPort::sig_Close, this, &QCustomSerialPort::slot_Close);
	connect(this, &QCustomSerialPort::sig_Clear, this, &QCustomSerialPort::slot_Clear);
	connect(this, &QCustomSerialPort::sig_Write, this, &QCustomSerialPort::slot_Write);
	connect(this, &QCustomSerialPort::sig_Open, this, &QCustomSerialPort::slot_Open);

	connect(m_pSerialPort, &QSerialPort::readyRead, this, &QCustomSerialPort::slot_DataReady);  //实测时可以用currentThreadID来测试

	m_pThread->start();
}

QCustomSerialPort::~QCustomSerialPort()
{
	close();

	m_pThread->quit();
	m_pThread->wait();

	delete m_pThread;
	m_pThread = nullptr;

	delete m_pSerialPort;
	m_pSerialPort = nullptr;
}

bool QCustomSerialPort::isOpened() const
{
	return m_pSerialPort->isOpen();
}

void QCustomSerialPort::close()
{
	QMutexLocker locker(&m_mutexClose);

	const int nAvailableSem = m_semClose.available();
	if (nAvailableSem > 0)
	{
		m_semClose.tryAcquire(nAvailableSem);
	}

	emit sig_Close();

	m_semClose.tryAcquire(1, 5000);
}

void QCustomSerialPort::slot_Close()
{
	m_pSerialPort->close();
	m_bOpenResult = false;

	m_semClose.release();
}

void QCustomSerialPort::clear()
{
	QMutexLocker locker(&m_mutexClear);

	const int nAvailableSem = m_semClear.available();
	if (nAvailableSem > 0)
	{
		m_semClear.tryAcquire(nAvailableSem);
	}

	emit sig_Clear();

	m_semClear.tryAcquire(1, 5000);
}

void QCustomSerialPort::slot_Clear()
{
	m_pSerialPort->clear();

	m_semClear.release();
}

bool QCustomSerialPort::open(int nOpenMode)
{
	QMutexLocker locker(&m_mutexOpen);

	const int nAvailableSem = m_semOpen.available();
	if (nAvailableSem > 0)
	{
		m_semOpen.tryAcquire(nAvailableSem);
	}

	m_bOpenResult = false;

	emit sig_Open(nOpenMode);

	const int bWait = m_semOpen.tryAcquire(1, 5000);			//獲取一個信號量，如果到達，表明設置完成了

	return bWait ? m_bOpenResult : false;
}

void QCustomSerialPort::slot_Open(qint32 nOpenMode)
{
	m_bOpenResult = m_pSerialPort->open(static_cast<QSerialPort::OpenMode>(nOpenMode));

	if (m_bOpenResult)
	{
		m_pSerialPort->clear();									//打開后清理串口
	}

	m_semOpen.release();
}

int QCustomSerialPort::currentError() const
{
	return m_pSerialPort->error();
}

qint64 QCustomSerialPort::write(QByteArray byteArray)
{
	if (!m_pSerialPort->isOpen())
	{
		return -1;
	}

	QMutexLocker mutexLocker(&m_mutexWrite);

	const int nAvailableSem = m_semWrite.available();
	if (nAvailableSem > 0)
	{
		m_semWrite.tryAcquire(nAvailableSem);
	}

	emit sig_Write(byteArray.data(), byteArray.size());
	const bool bWait = m_semWrite.tryAcquire(1, 5000);

	return bWait ? m_nWriteLength : -1;
}

qint64 QCustomSerialPort::write(const char * pData, qint64 nLength)
{
	if (!m_pSerialPort->isOpen())
	{
		return -1;
	}

	QMutexLocker mutexLocker(&m_mutexWrite);

	const int nAvailableSem = m_semWrite.available();
	if (nAvailableSem > 0)
	{
		m_semWrite.tryAcquire(nAvailableSem);
	}

	emit sig_Write(pData, nLength);
	const bool bWait = m_semWrite.tryAcquire(1, 5000);

	return bWait ? m_nWriteLength : -1;
}

void QCustomSerialPort::slot_Write(const char * pData, qint64 nLength)
{
	m_nWriteLength = -1;
	if (m_pSerialPort->isOpen())
	{
		m_nWriteLength = (nLength < 0) ? m_pSerialPort->write(pData) : m_pSerialPort->write(pData, nLength);
	}

	m_semWrite.release();
}

bool QCustomSerialPort::SetSerialParam(const QString& strPortName, const int & nBaudRate, const int &ucDirection,
	const int & ucDataBits, const int & ucStopBits, const int & ucParity)
{
	QMutexLocker mutexLocker(&m_mutexSetSerialParam);

	const int nAvailableSems = m_semSetSerialParam.available();
	if (nAvailableSems > 0)
	{
		m_semSetSerialParam.tryAcquire(nAvailableSems);
	}

	m_bSetSerialParamResult = false;

	emit sig_setSerialParam(strPortName, nBaudRate, ucDirection, ucDataBits, ucStopBits, ucParity);

	const int bWait = m_semSetSerialParam.tryAcquire(1, 5000);

	return bWait? m_bSetSerialParamResult: false;
}

void QCustomSerialPort::slot_setSerialParam(QString strPortName, int nBaudRate, int nDirection, 
											int nDataBits, int nStopBits, int nParity)
{
	m_pSerialPort->setPortName(strPortName);

	m_bSetSerialParamResult = m_pSerialPort->setBaudRate(nBaudRate, static_cast<QSerialPort::Direction>(nDirection));
	if(!m_bSetSerialParamResult)
	{
		m_semSetSerialParam.release();
		return;
	}

	m_bSetSerialParamResult = m_pSerialPort->setDataBits(static_cast<QSerialPort::DataBits>(nDataBits));
	if (!m_bSetSerialParamResult)
	{
		m_semSetSerialParam.release();
		return;
	}

	m_bSetSerialParamResult = m_pSerialPort->setStopBits(static_cast<QSerialPort::StopBits>(nStopBits));
	if(!m_bSetSerialParamResult)
	{
		m_semSetSerialParam.release();
		return;
	}

	m_bSetSerialParamResult = m_pSerialPort->setParity(static_cast<QSerialPort::Parity>(nParity));
	if (!m_bSetSerialParamResult)
	{
		m_semSetSerialParam.release();
	}
}

void QCustomSerialPort::slot_DataReady()
{
	QSerialPort *const pCom = m_pSerialPort;

	if (getEchoFlag())
	{
		QMutexLocker bufferLocker(&m_mutexInBuffer);
		m_strInBuffer.push_back(pCom->readAll());
		m_strReply = m_strInBuffer;
		if (m_bEchoRegExp)
		{
			if (m_strInBuffer.indexOf(m_rxExpectReply) >= 0)
			{
				setEchoFlag(false);
				m_semEcho.release();
			}
		}
		else
		{
			int idx = m_strInBuffer.indexOf(m_strExpectReply);

			if (idx >= 0 && m_strInBuffer.indexOf('\n', idx + 1) >= 0)
			{
				setEchoFlag(false);

				#ifdef _DEBUG
				qDebug() << QDateTime::currentDateTime().toString("HH:mm:ss.zzz ") << m_strReply << " wakeAll\n";
				#endif

				m_semEcho.release();
				return;
			}
		}
	}
	else
	{
		emit sig_DataReady(pCom->readAll());
	}
}
