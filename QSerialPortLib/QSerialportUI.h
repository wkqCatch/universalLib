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

	void updateControl(const CommunicationSettings &settings);							 //���¿ؼ�
	bool updateParam();								 //���²���
	void enableParamControl(bool bState);			 //��ֹ�����Ŀؼ�
	void enableModeControl(CommunicationMode mode);  //ʹ�ܶ�Ӧģʽ�Ŀؼ�

	void attachModbusClient(QCustomModbusClient *pModbusClient);  
	void attachModbusServer(QCustomModbusServer *pModbusServer);
	void attachFreeSerialPort(QCustomSerialPort *pSerialPort);
	void detachSerialPort();

public slots:
	void slot_btConnect_Clicked(bool);                     //����
	void slot_bt_sendModbus_clicked();                     //modbus��վЭ��ʱ����������
	void slot_requestReply(QModbusReply *pReply);          //�Ѿ����ؽ����

private:
	QCustomModbusClient   *m_pCustomModbuClient;       //modbus��վ
	QCustomModbusServer   *m_pCustomModbusServer;      //modbus��վ
	QCustomSerialPort     *m_pSerialPort;              //�Զ��崮��

	QCustomDialogTitleBar *m_pCustomTitleBar;          //�Զ������������

	CommunicationMode      m_communicateMode;         //ͨѶģʽ
};
