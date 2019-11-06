#pragma once

#include <QDialog>
#include "./GeneratedFiles/ui_QSerialportUI.h"
#include "qserialportlib_global.h"
#include "commonDefines.h"

class QCustomDialogTitleBar;
class QModbusReply;
class QCustomModbusClient;
class QCustomModbusServer;
class QCustomSerialPort;
class QSERIALPORTLIB_EXPORT QSerialportUI : public QDialog, public Ui::QSerialportUI
{
	Q_OBJECT

public:
	QSerialportUI(QWidget *parent);
	~QSerialportUI();

	void updateControl(const CommunicationSettings &settings);							 //更新控件
	bool updateParam();								 //更新参数
	void enableParamControl(bool bState);			 //禁止参数的控件
	void enableModeControl(CommunicationMode mode);  //使能对应模式的控件

	void attachModbusClient(QCustomModbusClient *pModbusClient);  
	void attachModbusServer(QCustomModbusServer *pModbusServer);
	void attachFreeSerialPort(QCustomSerialPort *pSerialPort);
	void detachSerialPort();

public slots:
	void slot_btConnect_Clicked(bool);                     //连接
	void slot_bt_sendModbus_clicked();                     //modbus主站协议时，发送数据
	void slot_requestReply(QModbusReply *pReply);          //已经返回结果了

private:
	QCustomModbusClient   *m_pCustomModbuClient;       //modbus主站
	QCustomModbusServer   *m_pCustomModbusServer;      //modbus从站
	QCustomSerialPort     *m_pSerialPort;              //自定义串口

	QCustomDialogTitleBar *m_pCustomTitleBar;          //自定义标题栏的类

	CommunicationMode      m_communicateMode;         //通讯模式
};
