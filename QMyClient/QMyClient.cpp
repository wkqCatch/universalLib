#include "QMyClient.h"

#include <QSplitter>
#include <QDebug>

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QCameraLib.lib")
#else
#pragma comment(lib, "../X64/Release/QCameraLib.lib")
#endif

#include "..\QCameraLib\QSentechCamera.h"
#include "..\QCameraLib\QCameraManager.h"
#include "..\QCameraLib\QCameraSettingDlg.h"
#include "..\QCameraLib\QCameraSelectDlg.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QImageProcessLib.lib")
#else
#pragma comment(lib, "../X64/Release/QImageProcessLib.lib")
#endif

#include "..\QImageProcessLib\QSmartMat.h"
#include "..\QImageProcessLib\QImageProcess.h"

QMyClient::QMyClient(QWidget *parent)
	: QMainWindow(parent)
	, m_pCameraManager(nullptr)
	, m_pCameraSettingDlg(nullptr)
{
	ui.setupUi(this);

	m_pCameraManager = new QCameraManager();

	connect(this, &QMyClient::sig_mainWindowBeMoved, ui.m_pCameraShow1, &QCameraShowDlg::slot_windowBeMoved);
	connect(this, &QMyClient::sig_mainWindowBeMoved, ui.m_pCameraShow2, &QCameraShowDlg::slot_windowBeMoved);
}

QMyClient::~QMyClient()
{
	if (m_pCameraManager)
	{
		delete m_pCameraManager;
		m_pCameraManager = nullptr;
	}
}

void QMyClient::moveEvent(QMoveEvent * event)
{
	emit sig_mainWindowBeMoved();
}

void QMyClient::slot_newDocument()
{
	QDialog::DialogCode dlgCode;

	if (m_pCameraManager)
	{
		if (ui.m_pCameraShow1->isAttachedCamera())
		{
			ui.m_pCameraShow1->detachCamera();
		}

		if (ui.m_pCameraShow2->isAttachedCamera())
		{
			ui.m_pCameraShow2->detachCamera();
		}

		QCameraSelectDlg pSelectDlg(this, m_pCameraManager);
		dlgCode = static_cast<QDialog::DialogCode>(pSelectDlg.exec());
	}

	if (dlgCode == QDialog::Accepted && m_pCameraManager)
	{
		if (m_pCameraManager->getCameraNum() > 0)
		{
			QVector<QCameraShowDlg*> vecCameraShowDlg;
			vecCameraShowDlg << ui.m_pCameraShow1 << ui.m_pCameraShow2;

			for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
			{
				vecCameraShowDlg.at(nCounter)->attachCamera(m_pCameraManager->getSpecificCamera(nCounter));
				m_pCameraManager->getSpecificCamera(nCounter)->startAcquisition();
			}
		}
	}
}

void QMyClient::slot_showCameraSettingDlg()
{
// 	QCameraSettingDlg cameraSettingDlg(this, m_pCameraManager);
// 	cameraSettingDlg.exec();

 	QSmartMat mattrix(600, 600, CV_8UC3, Scalar(100, 200, 250));

	saveImageToDiskSelect(this, mattrix, QStringLiteral("F:/image µ—ÈÕº"));

	

// 	smartMat.readImgFromDisk();
// 	smartMat.showImg();


}