#pragma once

#include <QObject>

#include "qserialportlib_global.h"
#include "commonDefines.h"

#include <QMutex>
#include <QSemaphore>
#include <QReadWriteLock>
#include <QMap>

class QModbusClient;
class QModbusRtuSerialMaster;
class QModbusReply;
class QThread;
class QModbusDataUnit;
class QSERIALPORTLIB_EXPORT QCustomModbusClient : public QObject
{
	Q_OBJECT

public:
	explicit QCustomModbusClient(QObject *parent = nullptr);
	~QCustomModbusClient();

	bool setParameter(const CommunicationSettings &settings);				 //设置参数
	bool setParameter(const QString &strPortName, const int &nBaudRate, const int &nDataBits, const int &nStopBits,
					 const int &nParity, const int &nOverTime, const int &nRetryTimes);
	
	bool connectModbusClient();                                             //连接modbus客户端  

	void disconnectModbusClient();											//断开modbus客户端

	bool constructRequest(QModbusDataUnit& dataUnit, int regType, int nStartAddress, int nValue);		//组建发送的消息
	QModbusDataUnit constructRequest(const int &regType, const int &nStartAddress, const unsigned short &nValue);
	QModbusDataUnit constructRequest(const int &regType, const int &nStartAddress, const QVector<quint16> &nDatas);

	bool readRequest(const int &regType, const int &nStartAddress, const unsigned short &nValue,
					 const int &nServerAddr);
	bool writeRequest(const int &regType, const int &nStartAddress, const QVector<quint16> &nDatas,
					  const int &nServerAddr);

	int getCurrentError() const;								//当前的错误
	int getCurrentState() const;                              //当前的状态
	CommunicationSettings getParameter() const;         //获取串口参数

signals:
	void sig_setParam(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
					 int nParity, int nOverTime, int nRetryTimes);
	void sig_connectClient();
	void sig_disconnectClient();
	void sig_readRequest(int regType, int nStartAddress, unsigned short nValue, int nServerAddr);
	void sig_writeRequest(int nRegType, int nStartAddress, QVector<quint16> vecDatas, int nServerAddr);       
	void sig_replyReady(QModbusReply *pReply);

public slots:
	void slot_threadStart();     //线程开始的槽
	void slot_setParam(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
					  int nParity, int nOverTime, int nRetryTimes);
	void slot_connectClient();
	void slot_disconnectClient();

	void slot_readRequest(int regType, int nStartAddress, unsigned short nValue, int nServerAddr);
	void slot_writeRequest(int nRegType, int nStartAddress, QVector<quint16> vecDatas, int nServerAddr);

	void slot_reply();

private:
	QModbusClient *m_pModbusClient;      //modbus客户端，可能指向串口或者TCP
	QModbusReply  *m_pModebusReply;      //modbus发送请求后，服务端返回的消息

	QThread *m_pThread;					 //客户端的线程

	QMutex m_mutexSetParam;              //设置参数的锁
	QSemaphore m_semSetParam;            //设置参数的信号
	bool m_bSetParamFlag;                //设置参数是否成功标志

	QMutex m_mutexConnect;				 //连接的锁
	QSemaphore m_semConnect;             //连接的信号
	bool   m_bConnectFlag;               //连接的标志

	QMutex m_mutexDisconnect;			 //断开的锁
	QSemaphore m_semDisconnect;          //断开的信号

	QMutex m_mutexReadRequest;			 //读数据的锁
	QMutex m_mutexWriteRequest;			 //写数据的锁
	bool   m_bCommunicating;             //正在通讯标志位

	QReadWriteLock m_rwlockCommunicatingState; //改变通信状态的锁

	QMap<QString, int> m_mapRegisterPair;       //寄存器对
};
