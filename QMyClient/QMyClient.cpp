#include "QMyClient.h"

#include <QSplitter>
#include <QDebug>
#include <QRandomGenerator>
#include <QElapsedTimer>


#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QCameraLib.lib")
#else
#pragma comment(lib, "../X64/Release/QCameraLib.lib")
#endif

#include "..\QCameraLib\QSentechCamera.h"
#include "..\QCameraLib\QCameraManager.h"
#include "..\QCameraLib\QCameraSettingDlg.h"
#include "..\QCameraLib\QCameraSelectDlg.h"
#include "..\QCameraLib\QDrawFigurePanel.h"

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
	, m_matDeal()
{
	ui.setupUi(this);

	m_pCameraManager = new QCameraManager();
	
	ui.m_pCameraShow1->getDrawFigurePanel()->addAKindOfRectF(Qt::green);

	connect(this, &QMyClient::sig_mainWindowBeMoved, ui.m_pCameraShow1, &QCameraShowDlg::slot_windowBeMoved);
	connect(this, &QMyClient::sig_mainWindowBeMoved, ui.m_pCameraShow2, &QCameraShowDlg::slot_windowBeMoved);

	connect(ui.m_pCameraShow1, &QCameraShowDlg::sig_sendDealMat, this, &QMyClient::slot_receiveMat);
	connect(this, &QMyClient::sig_requestShowDealMat, ui.m_pCameraShow1, &QCameraShowDlg::slot_requestShowDesignatedMat);
	connect(ui.m_pCameraShow1, &QCameraShowDlg::sig_sendSelectedPixelPoint, this, &QMyClient::slot_selectedSeedPoint);
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

void QMyClient::slot_dealImg()
{
	if(!m_matDeal.empty())
	{
// 		QRandomGenerator randomRow(0);
// 		QRandomGenerator randomCol(1);
// 
// 		for(int nCounter = 0; nCounter < 3000; nCounter++)
// 		{
// 			if(m_matDeal.type() == CV_8UC1)
// 			{
// 				m_matDeal.at<quint8>(randomRow.bounded(m_matDeal.rows - 1), randomCol.bounded(m_matDeal.cols - 1)) = 255;
// 			}
// 			else if(m_matDeal.type() == CV_8UC3)
// 			{
// 				m_matDeal.at<Vec3b>(randomRow.bounded(m_matDeal.rows - 1), randomCol.bounded(m_matDeal.cols - 1)) = Vec3b(255, 255, 255);
// 			}
// 		}
		

		//floodFill(m_matDeal, Point(0, 0), Scalar(255, 0, 0), (Rect*)0, Scalar(10, 10, 10), Scalar(10, 10, 10));

		emit sig_requestShowDealMat(&m_matDeal);
	}
}

void QMyClient::slot_receiveMat(const Mat * pMat)
{
	if(pMat)
	{
		m_matDeal = pMat->clone();
	}
}

void QMyClient::slot_selectedSeedPoint(int nX, int nY)
{
	if (!m_matDeal.empty())
	{
		Mat matMask(m_matDeal.rows + 2, m_matDeal.cols + 2, CV_8UC1, Scalar(0));

		floodFill(m_matDeal, matMask, Point(nX, nY), Scalar(255, 255, 0), 
				 nullptr, Scalar(20, 20, 20), Scalar(20, 20, 20), CV_FLOODFILL_FIXED_RANGE | CV_FLOODFILL_MASK_ONLY | 0x08 | (200 << 8));

		emit sig_requestShowDealMat(&matMask);
	}
}

void QMyClient::slot_showCameraSettingDlg()
{
// 	QCameraSettingDlg cameraSettingDlg(this, m_pCameraManager);
// 	cameraSettingDlg.exec();

//  	QSmartMat mattrix(600, 600, CV_8UC3, Scalar(100, 200, 250));
// 
// 	saveImageToDiskSelect(this, mattrix, QStringLiteral("F:/imageÊµÑéÍ¼"));

	

// 	smartMat.readImgFromDisk();
// 	smartMat.showImg();

	ui.m_pCameraShow1->slot_loadLocalImage("", IMREAD_UNCHANGED);
	ui.m_pCameraShow1->showDrawFigurePanel(true);
	ui.m_pCameraShow1->getDrawFigurePanel()->enterDrawingMode(0);
}