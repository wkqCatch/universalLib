#include "QSerialportUI.h"

#include <QStyledItemDelegate>
#include <QSerialPortInfo>
#include <QPalette>
#include <QModbusDevice>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusRtuSerialMaster>
#include <QModbusRtuSerialSlave>

#include "QCustomModbusClient.h"
#include "QCustomModbusServer.h"
#include "../QUniversalFrameLib/QCustomDialogTitleBar.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")
#else
#pragma comment(lib, "../X64/Release/QUniversalFrameLib.lib")
#endif

QSerialportUI::QSerialportUI(QWidget *parent, const CommunicationSettings &settings)
	: QDialog(parent)
	, m_pCustomModbuClient(nullptr)
	, m_pCustomModbusServer(nullptr)
	, m_pCustomTitleBar(nullptr)
	, m_paramSetting(settings)
	, m_communicateMode(unConnect)
{
	setupUi(this);

	m_pCustomModbuClient = new QCustomModbusClient();
	m_pCustomModbusServer = new QCustomModbusServer();

	QList<QSerialPortInfo> serialInfoList = QSerialPortInfo::availablePorts();

	for each (QSerialPortInfo serialInfo in serialInfoList)
	{
		QString strPortName = serialInfo.portName();
		m_pcomboSerialSel->addItem(strPortName);
	}

	m_pCustomTitleBar = new QCustomDialogTitleBar(this, m_pframeTitleBar, 20);
	m_pCustomTitleBar->setTitleName(QStringLiteral("串口设置"));
	m_pCustomTitleBar->setTitleIcon(":/DialogIcon/SerialIcon");
	m_pCustomTitleBar->hideMaximize(true);

	QStyledItemDelegate *pSerialSelectionDelegate = new QStyledItemDelegate();
	m_pcomboSerialSel->setItemDelegate(pSerialSelectionDelegate);

	QStyledItemDelegate *pSerialProtocolDelegate = new QStyledItemDelegate();
	m_pcomboSerialProtocol->setItemDelegate(pSerialProtocolDelegate);

	QStyledItemDelegate *pBaudRateDelegate = new QStyledItemDelegate();
	m_pcomboBaudRate->setItemDelegate(pBaudRateDelegate);

	QStyledItemDelegate *pParityDelegate = new QStyledItemDelegate();
	m_pcomboParity->setItemDelegate(pParityDelegate);

	QStyledItemDelegate *pRegisterType = new QStyledItemDelegate();
	m_pcomboRegisterType->setItemDelegate(pRegisterType);

	updateControl();
	enableModeControl(unConnect);

	connect(m_ppbConnect, QOverload<bool>::of(&QPushButton::clicked), 
					this, QOverload<bool>::of(&QSerialportUI::slot_btConnect_Clicked));
	connect(m_pCustomModbuClient, &QCustomModbusClient::sig_replyReady, this, &QSerialportUI::slot_requestReply);
}

QSerialportUI::~QSerialportUI()
{
	if (m_pCustomModbuClient)
	{
		delete m_pCustomModbuClient;
		m_pCustomModbuClient = nullptr;
	}

	if (m_pCustomModbusServer)
	{
		delete m_pCustomModbusServer;
		m_pCustomModbusServer = nullptr;
	}
}

void QSerialportUI::updateControl()
{
	m_pcomboSerialSel->setCurrentText(m_paramSetting.strSerialPortName);
	m_pcomboBaudRate->setCurrentText(QString::number(m_paramSetting.nBaudRate));
	m_pcomboDataBits->setCurrentText(QString::number(m_paramSetting.nDataBits));
	m_pcomboStopBits->setCurrentText(QString::number(m_paramSetting.nStopBits));
	m_pcomboParity->setCurrentText(m_paramSetting.strParity);

	m_psbReplyOverTime->setValue(m_paramSetting.nReplyOverTime);
	m_psbRetryTimes->setValue(m_paramSetting.nRetryTimes);

	m_psbStationNumber->setValue(m_paramSetting.ucStationNum);
	m_pcomboSerialProtocol->setCurrentText(m_paramSetting.strCommunicationProtocol);
	m_pcomboMasterOrSlave->setCurrentText(m_paramSetting.strMasterOrSlave);
}

void QSerialportUI::updateParam()
{
	m_paramSetting.strSerialPortName = m_pcomboSerialSel->currentText();
	m_paramSetting.nBaudRate = m_pcomboBaudRate->currentText().toInt();
	m_paramSetting.nDataBits = m_pcomboDataBits->currentText().toInt();
	m_paramSetting.nStopBits = m_pcomboStopBits->currentText().toInt();
	m_paramSetting.strParity = m_pcomboParity->currentText();

	m_paramSetting.nReplyOverTime = m_psbReplyOverTime->value();
	m_paramSetting.nRetryTimes = m_psbRetryTimes->value();

	m_paramSetting.ucStationNum = m_psbStationNumber->value();
	m_paramSetting.strCommunicationProtocol = m_pcomboSerialProtocol->currentText();
	m_paramSetting.strMasterOrSlave = m_pcomboMasterOrSlave->currentText();
}

void QSerialportUI::enableParamControl(bool bState)
{
	m_pcomboSerialSel->setEnabled(bState);
	m_pcomboBaudRate->setEnabled(bState);
	m_pcomboDataBits->setEnabled(bState);
	m_pcomboStopBits->setEnabled(bState);
	m_pcomboParity->setEnabled(bState);
	m_psbStationNumber->setEnabled(bState);
	m_pcomboSerialProtocol->setEnabled(bState);
	m_pcomboMasterOrSlave->setEnabled(bState);
	m_psbReplyOverTime->setEnabled(bState);
	m_psbRetryTimes->setEnabled(bState);
}

void QSerialportUI::enableModeControl(CommunicationMode mode)
{
	m_communicateMode = mode;

	switch (mode)
	{
	case QSerialportUI::unConnect:
	case QSerialportUI::ModbusServer:
		m_pcomboRegisterType->setEnabled(false);
		m_psbStartAddress->setEnabled(false);
		m_psbNumOfValue->setEnabled(false);
		m_ppbSendProtocol->setEnabled(false);
		m_prbModbusRead->setEnabled(false);
		m_prbModbusWrite->setEnabled(false);
		m_pleSendCustomData->setEnabled(false);
		m_ppbSendCustomData->setEnabled(false);
		break;

	case QSerialportUI::FreeProtocol:
		m_pcomboRegisterType->setEnabled(false);
		m_psbStartAddress->setEnabled(false);
		m_psbNumOfValue->setEnabled(false);
		m_ppbSendProtocol->setEnabled(false);
		m_prbModbusRead->setEnabled(false);
		m_prbModbusWrite->setEnabled(false);
		m_pleSendCustomData->setEnabled(true);
		m_ppbSendCustomData->setEnabled(true);
		break;

	case QSerialportUI::ModbusClient:
		m_pcomboRegisterType->setEnabled(true);
		m_psbStartAddress->setEnabled(true);
		m_psbNumOfValue->setEnabled(true);
		m_ppbSendProtocol->setEnabled(true);
		m_prbModbusRead->setEnabled(true);
		m_prbModbusWrite->setEnabled(true);
		m_pleSendCustomData->setEnabled(false);
		m_ppbSendCustomData->setEnabled(false);
		break;

	default:
		break;
	}
}

void QSerialportUI::slot_bt_sendModbus_clicked()
{
	if (m_pCustomModbuClient == nullptr || 
		static_cast<QModbusDevice::State>(m_pCustomModbuClient->currentState()) != QModbusDevice::ConnectedState)
	{
		return;
	}

	m_ppbSendProtocol->setEnabled(false);
	m_plbSendResultDetail->setText("");
	if(m_prbModbusRead->isChecked())
	{
		m_pCustomModbuClient->readRequest(m_pcomboRegisterType->currentIndex(), m_psbStartAddress->value(),
										  m_psbNumOfValue->value(), m_psbStationNumber->value());

		m_pteShowMessage->append(QString("TX: Station-%1 Read%2 Addr-%3 Num-%4").arg(m_psbStationNumber->value())\
				.arg(m_pcomboRegisterType->currentText()).arg(m_psbStartAddress->value()).arg(m_psbNumOfValue->value()));
	}
	else
	{
		QVector<quint16> vecDatas;
		vecDatas.append(1);
		vecDatas.append(2);
		vecDatas.append(3);
		vecDatas.append(4);
		vecDatas.append(5);
		vecDatas.append(6);

		m_pCustomModbuClient->writeRequest(m_pcomboRegisterType->currentIndex(), m_psbStartAddress->value(),
										   vecDatas, m_psbStationNumber->value());

		QString strTxData = QString("TX: Station-%1 Write%2 Addr-%3 Data-").arg(m_psbStationNumber->value())\
							.arg(m_pcomboRegisterType->currentText()).arg(m_psbStartAddress->value());

		for (int i = 0; i < vecDatas.length(); i++)
		{
			strTxData.append(QString("%1; ").arg(vecDatas.at(i)));
		}

		m_pteShowMessage->append(strTxData);
	}
}

void QSerialportUI::slot_requestReply(QModbusReply * pReply)
{
	m_ppbSendProtocol->setEnabled(true);

	if(pReply == nullptr)
	{
		m_plbSendResultDetail->setText(QStringLiteral("通信失败"));
		return;
	}
	else
	{
		if (pReply->error() == QModbusDevice::NoError)
		{
			m_plbSendResultDetail->setText(QStringLiteral("发送成功"));

			QModbusDataUnit dataUnit = pReply->result();
			if(m_prbModbusRead->isChecked())
			{
				QVector<quint16> vecDatas = dataUnit.values();

				QString strRxData = QString("RX: Station-%1 Addr-%2 Data-").arg(pReply->serverAddress()).arg(dataUnit.startAddress());

				for (int i = 0; i < vecDatas.length(); i++)
				{
					strRxData.append(QString("%1; ").arg(vecDatas.at(i)));
				}

				m_pteShowMessage->append(strRxData);
				m_pteShowMessage->append("");
			}
			else
			{
				QString strRxData = QString("RX: Station-%1 Addr-%2").arg(pReply->serverAddress()).arg(dataUnit.startAddress());

				m_pteShowMessage->append(strRxData);
				m_pteShowMessage->append("");
			}
		}
		else
		{
			m_plbSendResultDetail->setText(pReply->errorString());
		}

		pReply->deleteLater();
	}
}

void QSerialportUI::slot_btConnect_Clicked(bool bState)
{
	if (bState)
	{
		updateParam();

		if (m_pcomboSerialProtocol->currentText() == QStringLiteral("Modbus RTU"))
		{
			if (m_pcomboMasterOrSlave->currentText() == QStringLiteral("主站"))
			{
				if (m_pCustomModbuClient->connectModbusClient(m_paramSetting))
				{
					m_ppbConnect->setText(QStringLiteral("断 开"));
					m_plbSerialState->setText(QStringLiteral("连接成功"));
					enableParamControl(false);
					enableModeControl(ModbusClient);
				}
				else
				{
					m_plbSerialState->setText(QStringLiteral("连接失败"));

					m_ppbConnect->setChecked(false);
				}
			}
			else if (m_pcomboMasterOrSlave->currentText() == QStringLiteral("从站"))
			{

			}
		}
		else
		{

		}
	}
	else
	{
		m_pCustomModbuClient->disconnectModbusClient();

		m_ppbConnect->setText(QStringLiteral("连 接"));
		m_plbSerialState->setText(QStringLiteral("暂未连接"));
		enableParamControl(true);
		enableModeControl(unConnect);
	}
}