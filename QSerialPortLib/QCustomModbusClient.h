#pragma once

#include <QObject>

#include "qserialportlib_global.h"
#include "commonDefines.h"

class QModbusClient;
class QModbusReply;
class QThread;
class QModbusDataUnit;
class QSERIALPORTLIB_EXPORT QCustomModbusClient : public QObject
{
	Q_OBJECT

public:
	explicit QCustomModbusClient(const CommunicationSettings &mySettings, QObject *parent = nullptr);
	~QCustomModbusClient();

	void setParameter(const CommunicationSettings &settings);       //���ò���
	bool connectModbusClient();                                     //����modbus�ͻ���
	void disconnectModbusClient();                                  //�Ͽ�modbus�ͻ���
	bool constructRequest(int regType, int nStartAddress, int nValue); //�齨���͵���Ϣ

signals:
	void sig_sendRequest();                     //��������
	void sig_connectDevice();                   //�����ź�

	public slots:
	//	void slot_sendWriteRequest();

private:
	QModbusClient *m_pModbusClient;      //modbus�ͻ��ˣ�����ָ�򴮿ڻ���TCP
	QModbusReply  *m_pModebusReply;       //modbus��������󣬷���˷��ص���Ϣ

	QThread *m_pClientThread;            //�ͻ��˵��߳�

	QModbusDataUnit *m_pModbusDataUnit;    //Ҫ��������ݵ�Ԫ
};
