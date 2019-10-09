#include "QCustomSerialPort.h"

#include <QThread>
#include <QDateTime>
#include <QDebug>

QCustomSerialPort::QCustomSerialPort(const QString & strName, QObject * pParent)
	: QObject(pParent)
	, m_strPortName(strName)
	, m_pThread(nullptr)
	, m_pSerialPort(nullptr)
	, m_bOpenResult(false)
	, m_bSetBaudRateResult(false)
	, m_bSetDataBitsResult(false)
	, m_bSetParityResult(false)
	, m_bSetStopBitsResult(false)
	, m_nWriteLength(0)
	, m_bEchoFlag(false)
	, m_strInBuffer()
	, m_strReply()
	, m_strExpectReply()
	, m_rxExpectReply()
	, m_bEchoRegExp(false)
{
	m_pThread = new QThread();
	m_pSerialPort = new QSerialPort();

	//m_pSerialPort->moveToThread(m_pThread);			//將串口對象和該類都移動到線程中
	this->moveToThread(m_pThread);

	connect(this, &QCustomSerialPort::sigSetBaudRate, this, &QCustomSerialPort::slotSetBaudRate);
	connect(this, &QCustomSerialPort::sigSetDataBits, this, &QCustomSerialPort::slotSetDataBits);
	connect(this, &QCustomSerialPort::sigSetParity, this, &QCustomSerialPort::slotSetParity);
	connect(this, &QCustomSerialPort::sigSetStopBits, this, &QCustomSerialPort::slotSetStopBits);
	connect(this, &QCustomSerialPort::sigSetPortName, this, &QCustomSerialPort::slotSetPortName);

	connect(this, &QCustomSerialPort::sigClose, this, &QCustomSerialPort::slotClose);
	connect(this, &QCustomSerialPort::sigClear, this, &QCustomSerialPort::slotClear);
	connect(this, &QCustomSerialPort::sigWrite, this, &QCustomSerialPort::slotWrite);
	connect(this, &QCustomSerialPort::sigOpen, this, &QCustomSerialPort::slotOpen);

	connect(m_pThread, &QThread::finished, m_pSerialPort, &QSerialPort::deleteLater);
	connect(m_pSerialPort, &QSerialPort::readyRead, this, &QCustomSerialPort::slotDataReady);
	//connect(m_pSerialPort, &QSerialPort::readyRead, this, &QCustomSerialPort::slotDataReady, Qt::DirectConnection);

	m_pThread->start();
}

QCustomSerialPort::~QCustomSerialPort()
{
	close();

	m_pThread->quit();
	m_pThread->wait();

	delete m_pThread;
	m_pThread = nullptr;
}

bool QCustomSerialPort::isOpen() const
{
	return m_bOpenResult;
}

void QCustomSerialPort::close()
{
	QMutexLocker locker(&m_lockClose);

	const int nAvailableSem = m_semClose.available();
	if (nAvailableSem > 0)
	{
		m_semClose.tryAcquire(nAvailableSem);
	}

	emit sigClose();

	m_semClose.tryAcquire(1, 5000);
}

void QCustomSerialPort::slotClose()
{
	m_pSerialPort->close();
	m_bOpenResult = false;

	m_semClose.release();
}

void QCustomSerialPort::clear()
{
	QMutexLocker locker(&m_lockClear);

	const int nAvailableSem = m_semClear.available();
	if (nAvailableSem > 0)
	{
		m_semClear.tryAcquire(nAvailableSem);
	}

	emit sigClear();

	m_semClear.tryAcquire(1, 5000);
}

void QCustomSerialPort::slotClear()
{
	m_pSerialPort->clear();

	m_semClear.release();
}

bool QCustomSerialPort::open(QSerialPort::OpenMode openMode)
{
	QMutexLocker locker(&m_lockOpen);

	const int nAvailableSem = m_semOpen.available();
	if (nAvailableSem > 0)
	{
		m_semOpen.tryAcquire(nAvailableSem);
	}

	m_bOpenResult = false;

	emit sigOpen(static_cast<qint32>(openMode));

	const int bWait = m_semOpen.tryAcquire(1, 5000);			//獲取一個信號量，如果到達，表明設置完成了

	return bWait ? m_bOpenResult : false;
}

void QCustomSerialPort::slotOpen(qint32 nOpenMode)
{
	m_bOpenResult = m_pSerialPort->open(static_cast<QSerialPort::OpenMode>(nOpenMode));

	if (m_bOpenResult)
	{
		m_pSerialPort->clear();									//打開后清理串口
	}

	m_semOpen.release();
}

qint64 QCustomSerialPort::write(QByteArray byteArray)
{
	return write(byteArray.data(), byteArray.size());
}

qint64 QCustomSerialPort::write(const char * pData, qint64 nLength)
{
	if (!m_bOpenResult)
	{
		return -1;
	}

	m_lockWrite.lock();

	const int nAvailableSem = m_semWrite.available();
	if (nAvailableSem > 0)
	{
		m_semWrite.tryAcquire(nAvailableSem);
	}

	emit sigWrite(pData, nLength);
	const bool bWait = m_semWrite.tryAcquire(1, 5000);
	m_lockWrite.unlock();

	QMutexLocker locker(&m_lockWriteLength);
	qint64 nReturn = bWait ? m_nWriteLength : 0;

	return nReturn;
}

void QCustomSerialPort::slotWrite(const char * pData, qint64 nLength)
{
	m_lockWriteLength.lock();

	// 	qDebug() << QThread::currentThreadId() << endl;

	m_nWriteLength = -1;
	if (m_pSerialPort->isOpen())
	{
		m_nWriteLength = (nLength < 0) ? m_pSerialPort->write(pData) : m_pSerialPort->write(pData, nLength);
	}

	m_lockWriteLength.unlock();

	m_semWrite.release();
}

void QCustomSerialPort::setPortName(const QString & strName)
{
	QMutexLocker locker(&m_lockSetPortName);

	const int nAvailableSem = m_semSetPortName.available();
	if (nAvailableSem > 0)
	{
		m_semSetPortName.tryAcquire(nAvailableSem);
	}

	emit sigSetPortName(strName);

	m_semSetPortName.tryAcquire(1, 5000);
}

void QCustomSerialPort::slotSetPortName(const QString & strName)
{
	m_pSerialPort->setPortName(strName);

	m_semSetPortName.release();
}

bool QCustomSerialPort::setBaudRate(qint32 nBaudRate, QSerialPort::Directions direction)
{
	QMutexLocker locker(&m_lockSetBaudRate);

	const int nAvailableSem = m_semSetBaudRate.available();		//清除信號量
	if (nAvailableSem > 0)
	{
		m_semSetBaudRate.tryAcquire(nAvailableSem);
	}

	m_bSetBaudRateResult = false;					//清除掉結果

	emit sigSetBaudRate(nBaudRate, static_cast<qint32>(direction));

	const int bWait = m_semSetBaudRate.tryAcquire(1, 5000);			//獲取一個信號量，如果到達，表面設置完成了

	return bWait ? m_bSetBaudRateResult : false;
}

void QCustomSerialPort::slotSetBaudRate(qint32 nBaudRate, qint32 nDirection)
{
	m_bSetBaudRateResult = m_pSerialPort->setBaudRate(nBaudRate, static_cast<QSerialPort::Directions>(nDirection));

	m_semSetBaudRate.release();
}

bool QCustomSerialPort::setDataBits(QSerialPort::DataBits dataBits)
{
	QMutexLocker locker(&m_lockSetDataBits);

	const int nAvailableSem = m_semSetDataBits.available();		//清除信號量
	if (nAvailableSem > 0)
	{
		m_semSetDataBits.tryAcquire(nAvailableSem);
	}

	m_bSetDataBitsResult = false;					//清除掉結果

	emit sigSetDataBits(static_cast<qint32>(dataBits));

	const int bWait = m_semSetDataBits.tryAcquire(1, 5000);		//獲取一個信號量，如果到達，表面設置完成了

	return bWait ? m_bSetDataBitsResult : false;
}

void QCustomSerialPort::slotSetDataBits(qint32 dataBits)
{
	m_bSetDataBitsResult = m_pSerialPort->setDataBits(static_cast<QSerialPort::DataBits>(dataBits));

	m_semSetDataBits.release();
}

bool QCustomSerialPort::setParity(QSerialPort::Parity parity)
{
	QMutexLocker locker(&m_lockSetParity);

	const int nAvailableSem = m_semSetParity.available();		//清除信號量
	if (nAvailableSem > 0)
	{
		m_semSetParity.tryAcquire(nAvailableSem);
	}

	m_bSetParityResult = false;					//清除掉結果

	emit sigSetParity(static_cast<qint32>(parity));

	const int bWait = m_semSetParity.tryAcquire(1, 5000);		//獲取一個信號量，如果到達，表面設置完成了

	return bWait ? m_bSetParityResult : false;
}

void QCustomSerialPort::slotSetParity(qint32 nParity)
{
	m_bSetParityResult = m_pSerialPort->setParity(static_cast<QSerialPort::Parity>(nParity));

	m_semSetParity.release();
}

bool QCustomSerialPort::setStopBits(QSerialPort::StopBits stopBits)
{
	QMutexLocker locker(&m_lockSetStopBits);

	const int nAvailableSem = m_semSetStopBits.available();		//清除信號量
	if (nAvailableSem > 0)
	{
		m_semSetStopBits.tryAcquire(nAvailableSem);
	}

	m_bSetStopBitsResult = false;					//清除掉結果

	emit sigSetStopBits(static_cast<qint32>(stopBits));

	const int bWait = m_semSetStopBits.tryAcquire(1, 5000);		//獲取一個信號量，如果到達，表面設置完成了

	return bWait ? m_bSetStopBitsResult : false;
}

void QCustomSerialPort::slotSetStopBits(qint32 nStopBits)
{
	m_bSetStopBitsResult = m_pSerialPort->setStopBits(static_cast<QSerialPort::StopBits>(nStopBits));

	m_semSetStopBits.release();
}

void QCustomSerialPort::slotDataReady()
{
	QSerialPort *const pCom = m_pSerialPort;

	if (getEchoFlag())
	{
		QMutexLocker bufferLocker(&m_lockInBuffer);
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
		emit sigDataReady(pCom->readAll());
	}
}
