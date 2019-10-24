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
	enum CommunicationMode{unConnect, FreeProtocol, ModbusClient, ModbusServer};    //ͨѶģʽ

	QSerialportUI(QWidget *parent, const CommunicationSettings &settings);
	~QSerialportUI();

	void updateControl();							 //���¿ؼ�
	void updateParam();								 //���²���
	void enableParamControl(bool bState);			 //��ֹ�����Ŀؼ�
	void enableModeControl(CommunicationMode mode);  //ʹ�ܶ�Ӧģʽ�Ŀؼ�

public slots:
	void slot_btConnect_Clicked(bool);                     //����
	void slot_bt_sendModbus_clicked();                     //modbus��վЭ��ʱ����������
	void slot_requestReply(QModbusReply *pReply);          //�Ѿ����ؽ����

private:
	QCustomModbusClient   *m_pCustomModbuClient;       //modbus��վ
	QCustomModbusServer   *m_pCustomModbusServer;      //modbus��վ

	QCustomDialogTitleBar *m_pCustomTitleBar;          //�Զ������������
	CommunicationSettings  m_paramSetting;             //��������������

	CommunicationMode      m_communicateMode;         //ͨѶģʽ
};
