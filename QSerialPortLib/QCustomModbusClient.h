#pragma once

#include <QObject>

#include "qserialportlib_global.h"
#include "commonDefines.h"

#include <QMutex>
#include <QSemaphore>
#include <QReadWriteLock>

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

	void setParameter(const CommunicationSettings &settings);				//���ò���
	void setParameter(const QString &strPortName, const int &nBaudRate, const int &nDataBits, const int &nStopBits,
					 const int &nParity, const int &nOverTime, const int &nRetryTimes);

	bool connectModbusClient(const CommunicationSettings &settings);        //����modbus�ͻ���
	bool connectModbusClient(const QString &strPortName, const int &nBaudRate, const int &nDataBits, const int &nStopBits,
		const int &nParity, const int &nOverTime, const int &nRetryTimes);

	void disconnectModbusClient();											//�Ͽ�modbus�ͻ���

	bool constructRequest(QModbusDataUnit& dataUnit, int regType, int nStartAddress, int nValue);		//�齨���͵���Ϣ
	QModbusDataUnit constructRequest(const int &regType, const int &nStartAddress, const unsigned short &nValue);
	QModbusDataUnit constructRequest(const int &regType, const int &nStartAddress, const QVector<quint16> &nDatas);

	int currentError();														//��ǰ�Ĵ���
	int currentState();                                                     //��ǰ��״̬

	bool readRequest(const int &regType, const int &nStartAddress, const unsigned short &nValue,
					 const int &nServerAddr);
	bool writeRequest(const int &regType, const int &nStartAddress, const QVector<quint16> &nDatas,
							const int &nServerAddr);

signals:
	void sig_setParam(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
					 int nParity, int nOverTime, int nRetryTimes);
	void sig_connectClient(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
							int nParity, int nOverTime, int nRetryTimes);
	void sig_disconnectClient();
	void sig_readRequest(int regType, int nStartAddress, unsigned short nValue, int nServerAddr);
	void sig_writeRequest(int nRegType, int nStartAddress, QVector<quint16> vecDatas, int nServerAddr);       
	void sig_replyReady(QModbusReply *pReply);

public slots:
	void slot_threadStart();     //�߳̿�ʼ�Ĳ�
	void slot_setParam(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
					  int nParity, int nOverTime, int nRetryTimes);
	void slot_connectClient(QString strPortName, int nBaudRate, int nDataBits, int nStopBits,
							int nParity, int nOverTime, int nRetryTimes);
	void slot_disconnectClient();

	void slot_readRequest(int regType, int nStartAddress, unsigned short nValue, int nServerAddr);
	void slot_writeRequest(int nRegType, int nStartAddress, QVector<quint16> vecDatas, int nServerAddr);

	void slot_reply();

private:
	QModbusClient *m_pModbusClient;      //modbus�ͻ��ˣ�����ָ�򴮿ڻ���TCP
	QModbusReply  *m_pModebusReply;      //modbus��������󣬷���˷��ص���Ϣ

	QThread *m_pThread;					 //�ͻ��˵��߳�

	QMutex m_mutexSetParam;              //���ò�������
	QSemaphore m_semSetParam;            //���ò������ź�

	QMutex m_mutexConnect;				 //���ӵ���
	QSemaphore m_semConnect;             //���ӵ��ź�
	bool   m_bConnectFlag;               //���ӵı�־

	QMutex m_mutexDisconnect;			 //�Ͽ�����
	QSemaphore m_semDisconnect;        //�Ͽ����ź�

	QMutex m_mutexReadRequest;			 //�����ݵ���
	QMutex m_mutexWriteRequest;			 //д���ݵ���
	bool   m_bCommunicating;             //����ͨѶ��־λ

	QReadWriteLock m_rwlockCommunicatingState; //�ı�ͨ��״̬����
};
