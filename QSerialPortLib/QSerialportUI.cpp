#include "QSerialportUI.h"

#include <QStyledItemDelegate>
#include <QSerialPortInfo>
#include <QPalette>
#include <QModbusDevice>
#include <QModbusDataUnit>
#include <QModbusReply>

#include "QCustomModbusClient.h"
#include "QCustomModbusServer.h"
#include "QCustomSerialPort.h"

#include "QCustomModbusClient.h"
#include "QCustomModbusServer.h"
#include "../QUniversalFrameLib/QCustomDialogTitleBar.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")
#else
#pragma comment(lib, "../X64/Release/QUniversalFrameLib.lib")
#endif

QSerialportUI::QSerialportUI(QWidget *parent)
	: QDialog(parent)
	, m_pCustomModbuClient(nullptr)
	, m_pCustomModbusServer(nullptr)
	, m_pSerialPort(nullptr)
	, m_pCustomTitleBar(nullptr)
	, m_communicateMode(FreeProtocol)
{
	setupUi(this);

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

	connect(m_ppbConnect, QOverload<bool>::of(&QPushButton::clicked),
		this, QOverload<bool>::of(&QSerialportUI::slot_btConnect_Clicked));
}

QSerialportUI::~QSerialportUI()
{
	detachSerialPort();
}

void QSerialportUI::updateControl(const CommunicationSettings &settings)
{
	m_communicateMode = static_cast<CommunicationMode>(settings.nCommunicationMode);

	m_pcomboSerialSel->setCurrentText(settings.strSerialPortName);
	m_pcomboBaudRate->setCurrentText(QString::number(settings.nBaudRate));
	m_pcomboDataBits->setCurrentText(QString::number(settings.nDataBits));
	m_pcomboStopBits->setCurrentText(QString::number(settings.nStopBits));
	if(settings.nParity > 0)
	{
		m_pcomboParity->setCurrentIndex(settings.nParity - 1);
	}
	else
	{
		m_pcomboParity->setCurrentIndex(settings.nParity);
	}
	
	m_psbReplyOverTime->setValue(settings.nReplyOverTime);
	m_psbRetryTimes->setValue(settings.nRetryTimes);

	m_psbStationNumber->setValue(settings.ucStationNum);
	m_pcomboSerialProtocol->setCurrentIndex(settings.nCommunicationMode);
}

bool QSerialportUI::updateParam()
{
	CommunicationSettings settings;
	bool bResult = false;

	settings.strSerialPortName = m_pcomboSerialSel->currentText();
	settings.nBaudRate = m_pcomboBaudRate->currentText().toInt();
	settings.nDataBits = m_pcomboDataBits->currentText().toInt();
	settings.nStopBits = m_pcomboStopBits->currentText().toInt();
	if(m_pcomboParity->currentIndex() > 0)
	{
		settings.nParity = m_pcomboParity->currentIndex() + 1;
	}
	else
	{
		settings.nParity = m_pcomboParity->currentIndex();
	}

	settings.nReplyOverTime = m_psbReplyOverTime->value();
	settings.nRetryTimes = m_psbRetryTimes->value();

	settings.ucStationNum = m_psbStationNumber->value();
	settings.nCommunicationMode = m_pcomboSerialProtocol->currentIndex();

	switch (m_communicateMode)
	{
	case FreeProtocol:
		break;

	case ModbusRtuClient:
		if(m_pCustomModbuClient == nullptr)
		{
			break;
		}

		bResult = m_pCustomModbuClient->setParameter(settings);
		break;

	case ModbusRtuServer:
		break;

	default:
		break;
	}

	return false;
}

void QSerialportUI::enableParamControl(bool bState)
{
	m_pcomboSerialSel->setEnabled(bState);
	m_pcomboBaudRate->setEnabled(bState);
	m_pcomboDataBits->setEnabled(bState);
	m_pcomboStopBits->setEnabled(bState);
	m_pcomboParity->setEnabled(bState);
	m_psbStationNumber->setEnabled(bState);
	//m_pcomboSerialProtocol->setEnabled(bState);
	m_psbReplyOverTime->setEnabled(bState);
	m_psbRetryTimes->setEnabled(bState);
}

void QSerialportUI::enableModeControl(CommunicationMode mode)
{
	switch (mode)
	{
	case ModbusRtuServer:
		m_pcomboRegisterType->setEnabled(false);
		m_psbStartAddress->setEnabled(false);
		m_psbNumOfValue->setEnabled(false);
		m_ppbSendProtocol->setEnabled(false);
		m_prbModbusRead->setEnabled(false);
		m_prbModbusWrite->setEnabled(false);
		m_pleSendCustomData->setEnabled(false);
		m_ppbSendCustomData->setEnabled(false);
		break;

	case FreeProtocol:
		m_pcomboRegisterType->setEnabled(false);
		m_psbStartAddress->setEnabled(false);
		m_psbNumOfValue->setEnabled(false);
		m_ppbSendProtocol->setEnabled(false);
		m_prbModbusRead->setEnabled(false);
		m_prbModbusWrite->setEnabled(false);
		m_pleSendCustomData->setEnabled(true);
		m_ppbSendCustomData->setEnabled(true);
		break;

	case ModbusRtuClient:
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

void QSerialportUI::attachModbusClient(QCustomModbusClient * pModbusClient)
{
	if(pModbusClient == nullptr)
	{
		return;
	}

	m_pCustomModbuClient = pModbusClient;
	connect(m_pCustomModbuClient, &QCustomModbusClient::sig_replyReady, this, &QSerialportUI::slot_requestReply);

	CommunicationSettings settingss = m_pCustomModbuClient->getParameter();

	m_communicateMode = static_cast<CommunicationMode>(settingss.nCommunicationMode);

	updateControl(settingss);
	enableModeControl(m_communicateMode);

	if(m_pCustomModbuClient->getCurrentState() == QModbusDevice::ConnectedState)
	{
		m_ppbConnect->setChecked(true);
		m_ppbConnect->setText(QStringLiteral("断 开"));
		m_plbSerialState->setText(QStringLiteral("连接成功"));
		enableParamControl(false);
	}
	else
	{
		enableParamControl(true);
	}
}

void QSerialportUI::attachModbusServer(QCustomModbusServer * pModbusServer)
{
	m_pCustomModbusServer = pModbusServer;
	
}

void QSerialportUI::attachFreeSerialPort(QCustomSerialPort * pSerialPort)
{
	m_pSerialPort = pSerialPort;
	
}

void QSerialportUI::detachSerialPort()
{
	m_pCustomModbuClient = nullptr;
	m_pCustomModbusServer = nullptr;
	m_pCustomTitleBar = nullptr;
}

void QSerialportUI::slot_bt_sendModbus_clicked()
{
	if (m_pCustomModbuClient == nullptr ||
		static_cast<QModbusDevice::State>(m_pCustomModbuClient->getCurrentState()) != QModbusDevice::ConnectedState)
	{
		return;
	}

	m_ppbSendProtocol->setEnabled(false);
	m_plbSendResultDetail->setText("");
	if (m_prbModbusRead->isChecked())
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

	if (pReply == nullptr)
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
			if (m_prbModbusRead->isChecked())
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

		if (m_communicateMode == ModbusRtuClient)
		{
			if(m_pCustomModbuClient == nullptr)
			{
				return;
			}

			if (m_pCustomModbuClient->connectModbusClient())
			{
				m_ppbConnect->setText(QStringLiteral("断 开"));
				m_plbSerialState->setText(QStringLiteral("连接成功"));
				enableParamControl(false);
				enableModeControl(ModbusRtuClient);
			}
			else
			{
				m_plbSerialState->setText(QStringLiteral("连接失败"));

				m_ppbConnect->setChecked(false);
			}
		}
		else
		{

		}
	}
	else
	{
		if(m_pCustomModbuClient == nullptr)
		{
			return;
		}

		m_pCustomModbuClient->disconnectModbusClient();

		m_ppbConnect->setText(QStringLiteral("连 接"));
		m_plbSerialState->setText(QStringLiteral("暂未连接"));
		enableParamControl(true);
		enableModeControl(ModbusRtuServer);
	}
}