#pragma once

#include "qserialportlib_global.h"

#include <QObject>
#include <QMutex>
#include <QSemaphore>
#include <QSerialPort>

class QThread;
class QSerialPort;
class QSERIALPORTLIB_EXPORT QCustomSerialPort: public QObject
{
	Q_OBJECT

public:
	QCustomSerialPort(const QString &strName = "", QObject *pParent = nullptr);		//可傳入串口名稱
	virtual ~QCustomSerialPort();

	bool isOpen() const;
	void close();
	void clear();
	bool open(QSerialPort::OpenMode openMode);

	qint64 write(const char *pData, qint64 nLength = -1);
	qint64 write(QByteArray byteArray);

	void setPortName(const QString &strName);
	bool setBaudRate(qint32 nBaudRate, QSerialPort::Directions direction);
	bool setDataBits(QSerialPort::DataBits dataBits);
	bool setParity(QSerialPort::Parity parity);
	bool setStopBits(QSerialPort::StopBits stopBits);

signals:
	void sigSetPortName(const QString &strName);
	void sigSetBaudRate(qint32 nBaudRate, qint32);
	void sigSetDataBits(qint32 ndataBits);
	void sigSetParity(qint32 nParity);
	void sigSetStopBits(qint32 nStopBits);
	void sigClose();											//關閉串口
	void sigOpen(qint32 nOpenMode);							    //打開串口
	void sigClear();											//清理串口
	void sigWrite(const char *pData, qint64 nLength);			//發送數據
	void sigDataReady(QByteArray);								//數據已經接收好了，發射出去

public slots:
	//設置波特率, direction:該參數可以改變接受和發送為不同的波特率
	void slotSetPortName(const QString &strName);
	void slotSetBaudRate(qint32 nBaudRate, qint32 nDirection);
	void slotSetDataBits(qint32 dataBits);
	void slotSetParity(qint32 nParity);
	void slotSetStopBits(qint32 nStopBits);

	void slotClose();											//關閉串口
	void slotClear();											//清理串口
	void slotWrite(const char *pData, qint64 nLength);			//發送數據
	void slotOpen(qint32 nOpenMode);							//打開方式

	void slotDataReady();										//數據到串口，準備讀取

private:
	QString			 m_strPortName;				//串口名(COM1, COM2, COM3, ......)
	QThread			*m_pThread;					//該串口的線程指針
	QSerialPort		*m_pSerialPort;				//串口對象指針

	QMutex			 m_lockClose;				//關閉串口的鎖
	QSemaphore		 m_semClose;				//關閉串口的信號

	QMutex			 m_lockClear;				//清除串口的鎖
	QSemaphore		 m_semClear;				//清除串口的信號

	QMutex			 m_lockWrite;				//寫數據的鎖
	QSemaphore		 m_semWrite;				//寫數據的信號
	qint64			 m_nWriteLength;			//寫數據的長度
	QMutex			 m_lockWriteLength;			//改變數據長度的鎖

	QMutex			 m_lockOpen;				//打開串口的鎖		用於鎖住操作範圍
	QSemaphore		 m_semOpen;					//打開串口的信號量		用於操作完成后給出信號量
	bool			 m_bOpenResult;				//是否已經打開串口

	QMutex			 m_lockSetPortName;			//設置串口名的鎖
	QSemaphore		 m_semSetPortName;			//設置串口名的信號

	QMutex			 m_lockSetBaudRate;			//設置波特率的鎖
	QSemaphore		 m_semSetBaudRate;			//設置波特率的信號
	bool			 m_bSetBaudRateResult;		//設置波特率的結果

	QMutex			 m_lockSetDataBits;			//設置數據位的鎖
	QSemaphore		 m_semSetDataBits;			//設置數據位的信號
	bool			 m_bSetDataBitsResult;		//設置數據位的結果

	QMutex			 m_lockSetParity;			//設置奇偶校驗的鎖
	QSemaphore		 m_semSetParity;			//設置奇偶校驗的信號
	bool			 m_bSetParityResult;		//設置奇偶校驗的結果

	QMutex			 m_lockSetStopBits;			//設置停止位的鎖
	QSemaphore		 m_semSetStopBits;			//設置停止位的信號
	bool			 m_bSetStopBitsResult;		//設置停止位的結果

	QMutex			 m_lockInBuffer;			//收到的數據的鎖					
	QString			 m_strInBuffer;				//收到的數據存儲
	QString			 m_strReply;				//收到數據後的應答

	QMutex			 m_lockExpect;				//所期待的數據的鎖
	QString			 m_strExpectReply;			//所期待的數據反饋
	QRegExp			 m_rxExpectReply;			//鎖期待的正則表達式

	QMutex			 m_lockEcho;				//反射的鎖
	QSemaphore		 m_semEcho;					//反射的信號
	bool			 m_bEchoRegExp;				//是否對反射進行正則表達式處理

	bool m_bEchoFlag;							//反射標誌位
	mutable QMutex m_lockEchoFlag;				//反射標誌鎖

	void setEchoFlag(bool b)					//設置反射標誌位
	{
		QMutexLocker lk(&m_lockEchoFlag);
		m_bEchoFlag = b;
	}

	bool getEchoFlag() const					//獲得反射標誌位
	{
		QMutexLocker lk(&m_lockEchoFlag);
		return m_bEchoFlag;
	}
};
