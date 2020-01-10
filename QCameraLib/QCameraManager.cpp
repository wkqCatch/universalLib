#include "QCameraManager.h"
#include "QSentechCamera.h"

#include <PvSystem.h>
#include <PvDevice.h>

#include <QDebug>
#include <QThread>

QCameraManager::QCameraManager(QObject *parent)
	: QObject(parent)
	, m_pSystem(nullptr)
	, m_bFindInterceCompleted(false)
{
	m_pSystem = new PvSystem();
	m_vecSentechCamera.clear();

	m_pThread = new QThread();
	this->moveToThread(m_pThread);
	m_pThread->start();
}

QCameraManager::~QCameraManager()
{
	if (m_pThread)
	{
		m_pThread->quit();
		m_pThread->wait();
		delete m_pThread;
		m_pThread = nullptr;
	}

	slot_deleteAllDevice();

	if(m_pSystem)
	{
		delete m_pSystem;
		m_pSystem;
	}
}

const QVector<QSentechCamera*>& QCameraManager::getCameraVector() const
{
	return m_vecSentechCamera;
}

int QCameraManager::getCameraNum() const
{
	return m_vecSentechCamera.size();
}

QSentechCamera * QCameraManager::getSpecificCamera(int nIndex) const
{
	if(nIndex < 0 || nIndex > m_vecSentechCamera.size() - 1)
	{
		return nullptr;
	}
	
	return m_vecSentechCamera.at(nIndex);
}

void QCameraManager::cameraVectorUpdate(const QVector<QSentechCamera*> &vecCamera)
{
	m_vecSentechCamera.clear();
	m_vecSentechCamera = vecCamera;
}

void QCameraManager::slot_deleteAllDevice()
{
	for (int nCounter = 0; nCounter < m_vecSentechCamera.size(); nCounter++)
	{
		delete m_vecSentechCamera.at(nCounter);
		m_vecSentechCamera[nCounter] = nullptr;
	}

	m_vecSentechCamera.clear();

	emit sig_deleteAllDeviceComplete();
}

void QCameraManager::slot_deleteSpecificDevice(QSentechCamera* pCamera)
{
	if(pCamera)
	{
		delete pCamera;
		pCamera = nullptr;
	}
}

void QCameraManager::slot_connectAllDevice()
{
	slot_deleteAllDevice();

	m_pSystem->Find();

	int nInferfaceCount = m_pSystem->GetInterfaceCount();

	for (int nCounter = 0; nCounter < m_pSystem->GetInterfaceCount(); nCounter++)
	{
		PvInterface *pInterface = m_pSystem->GetInterface(nCounter);
		if(pInterface->GetDeviceCount() > 0)
		{
			QString strNewIP;
			QString strOldIP = pInterface->GetIPAddress();

			if(QAbstractCamera::setNewIPByAddOne(strOldIP, strNewIP))
			{
				PvString pvstrNewIP;
				PvResult lResult;

				PvDeviceInfo *pDeviceInfo = pInterface->GetDeviceInfo(0);
				QSentechCamera::QString2PvString(strNewIP, pvstrNewIP);
				QString strMacAddr = QSentechCamera::PvString2QString(pDeviceInfo->GetMACAddress());
				lResult = PvDevice::SetIPConfiguration(pDeviceInfo->GetMACAddress(), pvstrNewIP);
				if(lResult.IsOK())
				{
					QSentechCamera *pSentechCamera = new QSentechCamera();
					if (pSentechCamera->connectDevice(strNewIP))
					{
						pSentechCamera->setInterfaceIP(pSentechCamera->PvString2QString(pInterface->GetIPAddress()));
						pSentechCamera->setInterfaceMAC(pSentechCamera->PvString2QString(pInterface->GetMACAddress()));

						pSentechCamera->setInterfaceType(static_cast<QSentechCamera::InterfaceType>(pInterface->GetType()));

						pSentechCamera->setDeviceMAC(QSentechCamera::PvString2QString(pDeviceInfo->GetMACAddress()));
						pSentechCamera->setDeviceIP(strNewIP);
						pSentechCamera->setDeviceSerialNum(QSentechCamera::PvString2QString(pDeviceInfo->GetSerialNumber()));
						pSentechCamera->setDeviceVendorName(QSentechCamera::PvString2QString(pDeviceInfo->GetVendor()));
						pSentechCamera->setDeviceModelName(QSentechCamera::PvString2QString(pDeviceInfo->GetModel()));

						m_vecSentechCamera.append(pSentechCamera);
					}
					else
					{
						delete pSentechCamera;
						pSentechCamera = nullptr;
					}
				}
			}
		}
	}

	emit sig_connectAllDeviceCompleted();
}

bool QCameraManager::slot_connectSpecificInterface(const QString &strMac)
{
	if (!m_bFindInterceCompleted)
	{
		return false;
	}

	int nInferfaceCount = m_pSystem->GetInterfaceCount();

	for (int nCounter = 0; nCounter < m_pSystem->GetInterfaceCount(); nCounter++)
	{
		PvInterface *pInterface = m_pSystem->GetInterface(nCounter);

		QString strInterfaceMAC = QSentechCamera::PvString2QString(pInterface->GetMACAddress());
		if(strInterfaceMAC == strMac)
		{
			if (pInterface->GetDeviceCount() > 0)
			{
				QString strNewIP;
				QString strOldIP = pInterface->GetIPAddress();

				if (QAbstractCamera::setNewIPByAddOne(strOldIP, strNewIP))
				{
					PvString pvstrNewIP;
					PvResult lResult;

					PvDeviceInfo *pDeviceInfo = pInterface->GetDeviceInfo(0);
					if(pDeviceInfo == nullptr)
					{
						return false;
					}
					QSentechCamera::QString2PvString(strNewIP, pvstrNewIP);
					QString strMacAddr = QSentechCamera::PvString2QString(pDeviceInfo->GetMACAddress());
					lResult = PvDevice::SetIPConfiguration(pDeviceInfo->GetMACAddress(), pvstrNewIP);
					if (lResult.IsOK())
					{
						QSentechCamera *pSentechCamera = new QSentechCamera();
						if (pSentechCamera->connectDevice(strNewIP))
						{
							pSentechCamera->setInterfaceIP(pSentechCamera->PvString2QString(pInterface->GetIPAddress()));
							pSentechCamera->setInterfaceMAC(pSentechCamera->PvString2QString(pInterface->GetMACAddress()));

							pSentechCamera->setDeviceMAC(QSentechCamera::PvString2QString(pDeviceInfo->GetMACAddress()));
							pSentechCamera->setDeviceIP(strNewIP);
							pSentechCamera->setDeviceSerialNum(QSentechCamera::PvString2QString(pDeviceInfo->GetSerialNumber()));
							pSentechCamera->setDeviceVendorName(QSentechCamera::PvString2QString(pDeviceInfo->GetVendor()));
							pSentechCamera->setDeviceModelName(QSentechCamera::PvString2QString(pDeviceInfo->GetModel()));

							m_vecSentechCamera.append(pSentechCamera);
							return true;
						}
						else
						{
							delete pSentechCamera;
							pSentechCamera = nullptr;
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

void QCameraManager::slot_findAllInterface()
{
	m_pSystem->Find();
	m_bFindInterceCompleted = true;
	emit sig_findInterfaceCompleted();
}

