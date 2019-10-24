#pragma once

#include <QDialog>
#include "./GeneratedFiles/ui_QSerialportUI.h"
#include "qserialportlib_global.h"
#include "commonDefines.h"

#include "QCustomModbusClient.h"
#include "QCustomModbusServer.h"

class QCustomDialogTitleBar;
class QModbusReply;
class QSERIALPORTLIB_EXPORT QSerialportUI : public QDialog, public Ui::QSerialportUI
{
	Q_OBJECT

public:
	enum CommunicationMode{unConnect, FreeProtocol, ModbusClient, ModbusServer};    //通讯模式

	QSerialportUI(QWidget *parent, const CommunicationSettings &settings);
	~QSerialportUI();

	void updateControl();							 //更新控件
	void updateParam();								 //更新参数
	void enableParamControl(bool bState);			 //禁止参数的控件
	void enableModeControl(CommunicationMode mode);  //使能对应模式的控件

public slots:
	void slot_btConnect_Clicked(bool);                     //连接
	void slot_bt_sendModbus_clicked();                     //modbus主站协议时，发送数据
	void slot_requestReply(QModbusReply *pReply);          //已经返回结果了

private:
	QCustomModbusClient   *m_pCustomModbuClient;       //modbus主站
	QCustomModbusServer   *m_pCustomModbusServer;      //modbus从站

	QCustomDialogTitleBar *m_pCustomTitleBar;          //自定义标题栏的类
	CommunicationSettings  m_paramSetting;             //各个参数的设置

	CommunicationMode      m_communicateMode;         //通讯模式
};
