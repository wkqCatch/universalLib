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

	void setParameter(const CommunicationSettings &settings);       //设置参数
	bool connectModbusClient();                                     //连接modbus客户端
	void disconnectModbusClient();                                  //断开modbus客户端
	bool constructRequest(int regType, int nStartAddress, int nValue); //组建发送的消息

signals:
	void sig_sendRequest();                     //发送请求
	void sig_connectDevice();                   //连接信号

	public slots:
	//	void slot_sendWriteRequest();

private:
	QModbusClient *m_pModbusClient;      //modbus客户端，可能指向串口或者TCP
	QModbusReply  *m_pModebusReply;       //modbus发送请求后，服务端返回的消息

	QThread *m_pClientThread;            //客户端的线程

	QModbusDataUnit *m_pModbusDataUnit;    //要请求的数据单元
};
