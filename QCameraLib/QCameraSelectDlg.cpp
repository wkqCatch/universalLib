#include "QCameraSelectDlg.h"

#include "../QUniversalFrameLib/QCustomDialogTitleBar.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")
#else
#pragma comment(lib, "../X64/Release/QUniversalFrameLib.lib")
#endif

#include "QCameraManager.h"

#include <QMouseEvent>
#include <QPalette>
#include <QTimer>

QCameraSelectDlg::QCameraSelectDlg(QWidget *parent)
	: QDialog(parent)
	, m_pCustomTitlebar(nullptr)
	, m_pCameraManager(nullptr)
{
	setupUi(this);

	m_pCustomTitlebar = new QCustomDialogTitleBar(this, m_pframeTitlebar, 20);
	m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中"));
	m_pCustomTitlebar->setTitleIcon(":/new/prefix1/camera");
	m_pCustomTitlebar->hideMinimize(true);
	m_pCustomTitlebar->hideMaximize(true);
	setSizeGripEnabled(true);
}

QCameraSelectDlg::QCameraSelectDlg(QWidget *parent, QCameraManager *pCameraManager)
	: QDialog(parent)
	, m_pCustomTitlebar(nullptr)
	, m_pCameraManager(pCameraManager)
	, m_pConnectingTimer(nullptr)
{
	setupUi(this);

	m_pCustomTitlebar = new QCustomDialogTitleBar(this, m_pframeTitlebar, 20);
	m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后"));
	m_pCustomTitlebar->setTitleIcon(":/new/prefix1/camera");
	m_pCustomTitlebar->hideMinimize(true);
	m_pCustomTitlebar->hideMaximize(true);

	setSizeGripEnabled(true);

	m_pConnectingTimer = new QTimer(this);
	connect(m_pConnectingTimer, &QTimer::timeout, this, &QCameraSelectDlg::slot_updateTitleOnTime);
	m_pConnectingTimer->start(800);

	if (m_pCameraManager)
	{
		connect(this, &QCameraSelectDlg::sig_connectAllDevice,
			    m_pCameraManager, &QCameraManager::slot_connectAllDevice);
		connect(m_pCameraManager, &QCameraManager::sig_connectAllDeviceCompleted,
			    this, &QCameraSelectDlg::slot_connectAllDeviceCompleted);
		connect(this, &QCameraSelectDlg::sig_deleteAllDevice, 
				m_pCameraManager, &QCameraManager::slot_deleteAllDevice);
		connect(this, &QCameraSelectDlg::sig_deleteSpecificDevice, 
				m_pCameraManager, &QCameraManager::slot_deleteSpecificDevice);

		emit sig_connectAllDevice();

		m_ppbRefresh->setEnabled(false);
		m_ppbAccept->setEnabled(false);
		m_ppbReject->setEnabled(false);
		m_pCustomTitlebar->enableClose(false);
	}
}

QCameraSelectDlg::~QCameraSelectDlg()
{
	
}

void QCameraSelectDlg::attachCameraManager(QCameraManager * pCameraManager)
{
	m_pCameraManager = pCameraManager;

	if (m_pCameraManager && m_pCameraManager->getCameraNum() > 0)
	{
		QVector<QCameraShowDlg*> vecCameraShowDlg;
		vecCameraShowDlg << m_pCameraShowDlg0 << m_pCameraShowDlg1 << m_pCameraShowDlg2 << m_pCameraShowDlg3 <<
			m_pCameraShowDlg4 << m_pCameraShowDlg5 << m_pCameraShowDlg6 << m_pCameraShowDlg7;

		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			vecCameraShowDlg.at(nCounter)->attachCamera(m_pCameraManager->getSpecificCamera(nCounter));
			if (!m_pCameraManager->getSpecificCamera(nCounter)->isStartedAcquisition())
			{
				m_pCameraManager->getSpecificCamera(nCounter)->startAcquisition();
			}
		}
	}
}

void QCameraSelectDlg::detachCameraManager()
{
	if (m_pCameraManager)
	{
		QVector<QCameraShowDlg*> vecCameraShowDlg;
		vecCameraShowDlg << m_pCameraShowDlg0 << m_pCameraShowDlg1 << m_pCameraShowDlg2 << m_pCameraShowDlg3 <<
			m_pCameraShowDlg4 << m_pCameraShowDlg5 << m_pCameraShowDlg6 << m_pCameraShowDlg7;

		for (int nCounter = 0; nCounter < vecCameraShowDlg.size(); nCounter++)
		{
			if (vecCameraShowDlg.at(nCounter)->isAttachedCamera())
			{
				vecCameraShowDlg.at(nCounter)->detachCamera();
			}
		}

		m_pCameraManager = nullptr;
	}
}

void QCameraSelectDlg::slot_updateTitleOnTime()
{
	static int nRefreshCounter = 0;   //刷新计数
	switch (nRefreshCounter)
	{
	case 0:
		m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后·"));
		nRefreshCounter++;
		break;

	case 1:
		m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后··"));
		nRefreshCounter++;
		break;

	case 2:
		m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后···"));
		nRefreshCounter++;
		break;

	case 3:
		m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后····"));
		nRefreshCounter++;
		break;

	case 4:
		m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后·····"));
		nRefreshCounter++;
		break;

	case 5:
		m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接中,请稍后······"));
		nRefreshCounter = 0;
		break;

	default:
		break;
	}
}

void QCameraSelectDlg::slot_refreshCamera()
{
	if (m_pCameraManager)
	{
		QVector<QCameraShowDlg*> vecCameraShowDlg;
		vecCameraShowDlg << m_pCameraShowDlg0 << m_pCameraShowDlg1 << m_pCameraShowDlg2 << m_pCameraShowDlg3 <<
			m_pCameraShowDlg4 << m_pCameraShowDlg5 << m_pCameraShowDlg6 << m_pCameraShowDlg7;

		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			if (vecCameraShowDlg.at(nCounter)->isAttachedCamera())
			{
				vecCameraShowDlg.at(nCounter)->detachCamera();
			}
		}

		emit sig_connectAllDevice();

		m_pConnectingTimer->start(800);
		m_ppbRefresh->setEnabled(false);
		m_ppbAccept->setEnabled(false);
		m_pCustomTitlebar->enableClose(false);
		m_ppbReject->setEnabled(false);
		m_pcbCamera0->setText(QStringLiteral("未发现相机"));
		m_pcbCamera0->setCheckable(false);
		m_pcbCamera1->setText(QStringLiteral("未发现相机"));
		m_pcbCamera1->setCheckable(false);
		m_pcbCamera2->setText(QStringLiteral("未发现相机"));
		m_pcbCamera2->setCheckable(false);
		m_pcbCamera3->setText(QStringLiteral("未发现相机"));
		m_pcbCamera3->setCheckable(false);
		m_pcbCamera4->setText(QStringLiteral("未发现相机"));
		m_pcbCamera4->setCheckable(false);
		m_pcbCamera5->setText(QStringLiteral("未发现相机"));
		m_pcbCamera5->setCheckable(false);
		m_pcbCamera6->setText(QStringLiteral("未发现相机"));
		m_pcbCamera6->setCheckable(false);
		m_pcbCamera7->setText(QStringLiteral("未发现相机"));
		m_pcbCamera7->setCheckable(false);
	}
}

void QCameraSelectDlg::accept()
{
	if(m_pCameraManager)
	{
		QVector<QCameraShowDlg*> vecCameraShowDlg;
		vecCameraShowDlg << m_pCameraShowDlg0 << m_pCameraShowDlg1 << m_pCameraShowDlg2 << m_pCameraShowDlg3 <<
			m_pCameraShowDlg4 << m_pCameraShowDlg5 << m_pCameraShowDlg6 << m_pCameraShowDlg7;

		QVector<QCheckBox*> vecCameraCheckBox;
		vecCameraCheckBox << m_pcbCamera0 << m_pcbCamera1 << m_pcbCamera2 << m_pcbCamera3 <<
			m_pcbCamera4 << m_pcbCamera5 << m_pcbCamera6 << m_pcbCamera7;

		QVector<QSentechCamera*> vecCameraTemp;

		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			if (vecCameraShowDlg.at(nCounter)->isAttachedCamera())
			{
				vecCameraShowDlg.at(nCounter)->detachCamera();
			}

			if(vecCameraCheckBox.at(nCounter)->isChecked())
			{
				vecCameraTemp << m_pCameraManager->getSpecificCamera(nCounter);
			}
			else
			{
				emit sig_deleteSpecificDevice(m_pCameraManager->getSpecificCamera(nCounter));
				//delete m_pCameraManager->getSpecificCamera(nCounter);
			}
		}

		m_pCameraManager->cameraVectorUpdate(vecCameraTemp);
	}

	QDialog::accept();
}

void QCameraSelectDlg::reject()
{
	if (m_pCameraManager)
	{
		QVector<QCameraShowDlg*> vecCameraShowDlg;
		vecCameraShowDlg << m_pCameraShowDlg0 << m_pCameraShowDlg1 << m_pCameraShowDlg2 << m_pCameraShowDlg3 <<
			m_pCameraShowDlg4 << m_pCameraShowDlg5 << m_pCameraShowDlg6 << m_pCameraShowDlg7;

		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			if (vecCameraShowDlg.at(nCounter)->isAttachedCamera())
			{
				vecCameraShowDlg.at(nCounter)->detachCamera();
			}
		}

		emit sig_deleteAllDevice();
	}

	QDialog::reject();
}

void QCameraSelectDlg::slot_connectAllDeviceCompleted()
{
	if (m_pCameraManager && m_pCameraManager->getCameraNum() > 0)
	{
		QVector<QCameraShowDlg*> vecCameraShowDlg;
		vecCameraShowDlg << m_pCameraShowDlg0 << m_pCameraShowDlg1 << m_pCameraShowDlg2 << m_pCameraShowDlg3 <<
			m_pCameraShowDlg4 << m_pCameraShowDlg5 << m_pCameraShowDlg6 << m_pCameraShowDlg7;
		QVector<QCheckBox*> vecCameraCheckBox;
		vecCameraCheckBox << m_pcbCamera0 << m_pcbCamera1 << m_pcbCamera2 << m_pcbCamera3 <<
			m_pcbCamera4 << m_pcbCamera5 << m_pcbCamera6 << m_pcbCamera7;

		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			vecCameraShowDlg.at(nCounter)->attachCamera(m_pCameraManager->getSpecificCamera(nCounter));
			if (!m_pCameraManager->getSpecificCamera(nCounter)->isStartedAcquisition())
			{
				m_pCameraManager->getSpecificCamera(nCounter)->startAcquisition();
			}
			vecCameraCheckBox.at(nCounter)->setText(m_pCameraManager->getSpecificCamera(nCounter)->getDeviceMAC());
			vecCameraCheckBox.at(nCounter)->setCheckable(true);
		}
	}

	m_pConnectingTimer->stop();
	m_pCustomTitlebar->setTitleName(QStringLiteral("相机连接完成"));
	m_ppbRefresh->setEnabled(true);
	m_ppbAccept->setEnabled(true);
	m_ppbReject->setEnabled(true);
	m_pCustomTitlebar->enableClose(true);
}