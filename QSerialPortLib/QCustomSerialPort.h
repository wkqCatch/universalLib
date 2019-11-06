#pragma once

#include "qserialportlib_global.h"

#include <QObject>
#include <QMutex>
#include <QSemaphore>

class QThread;
class QSerialPort;
class QSERIALPORTLIB_EXPORT QCustomSerialPort: public QObject
{
	Q_OBJECT
	
public:
	QCustomSerialPort(const QString &strName = "", QObject *pParent = nullptr);		//可傳入串口名稱
	virtual ~QCustomSerialPort();

	bool isOpened() const;
	void close();
	void clear();
	bool open(int nOpenMode);

	int currentError() const;      //当前错误

	qint64 write(const char *pData, qint64 nLength = -1);
	qint64 write(QByteArray byteArray);
	
	bool SetSerialParam(const QString &strPortName = "", const int &nBaudRate = 9600, const int &ucDirection = 3,
						const int &ucDataBits = 8, const int &ucStopBits = 1, const int &ucParity = 0);

signals:
	void sig_setSerialParam(QString, int, int, int, int, int);
	void sig_Close();									//關閉串口
	void sig_Open(qint32);							    //打開串口
	void sig_Clear();									//清理串口
	void sig_Write(const char *, qint64);				//發送數據

	void sig_DataReady(QByteArray);						//數據已經接收好了，發射出去

public slots:
	//設置波特率, direction:該參數可以改變接受和發送為不同的波特率
	void slot_setSerialParam(QString, int, int, int, int, int);
	void slot_Close();											//關閉串口
	void slot_Clear();											//清理串口
	void slot_Write(const char *pData, qint64 nLength);			//發送數據
	void slot_Open(qint32 nOpenMode);							//打開方式

	void slot_DataReady();										//數據到串口，準備讀取

private:
	QThread			*m_pThread;					//該串口的線程指針
	QSerialPort		*m_pSerialPort;				//串口對象指針

	QMutex           m_mutexSetSerialParam;     //设置串行参数的锁
	QSemaphore       m_semSetSerialParam;       //设置串行参数的信号
	bool             m_bSetSerialParamResult;   //设置串行参数的结果

	QMutex			 m_mutexOpen;				//打開串口的鎖			用於鎖住操作範圍
	QSemaphore		 m_semOpen;					//打開串口的信號量		用於操作完成后給出信號量
	bool			 m_bOpenResult;				//是否已經打開串口

	QMutex			 m_mutexClose;				//關閉串口的鎖
	QSemaphore		 m_semClose;				//關閉串口的信號

	QMutex			 m_mutexClear;				//清除串口的鎖
	QSemaphore		 m_semClear;				//清除串口的信號

	QMutex			 m_mutexWrite;				//寫數據的鎖
	QSemaphore		 m_semWrite;				//寫數據的信號
	qint64			 m_nWriteLength;			//寫數據的長度
	QMutex			 m_mutexWriteLength;		//改變數據長度的鎖

	QMutex			 m_mutexInBuffer;			//收到的數據的鎖					
	QString			 m_strInBuffer;				//收到的數據存儲
	QString			 m_strReply;				//收到數據後的應答

	QMutex			 m_mutexExpect;				//所期待的數據的鎖
	QString			 m_strExpectReply;			//所期待的數據反饋
	QRegExp			 m_rxExpectReply;			//鎖期待的正則表達式

	QMutex			 m_mutexEcho;				//反射的鎖
	QSemaphore		 m_semEcho;					//反射的信號
	bool			 m_bEchoRegExp;				//是否對反射進行正則表達式處理

	bool m_bEchoFlag;							//反射標誌位
	mutable QMutex m_mutexEchoFlag;				//反射標誌鎖

	void setEchoFlag(bool b)					//設置反射標誌位
	{
		QMutexLocker lk(&m_mutexEchoFlag);
		m_bEchoFlag = b;
	}

	bool getEchoFlag() const					//獲得反射標誌位
	{
		QMutexLocker lk(&m_mutexEchoFlag);
		return m_bEchoFlag;
	}
};
