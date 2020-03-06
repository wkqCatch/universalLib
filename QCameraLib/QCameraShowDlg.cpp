#include "QCameraShowDlg.h"

#include <QPainter>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QTimer>

#include "QDrawFigurePanel.h"
#include <QHBoxLayout>
#include <QMouseEvent>

#include "../QUniversalFrameLib/QCustomMessageBox.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")
#else
#pragma comment(lib, "../X64/Release/QUniversalFrameLib.lib")
#endif

#define MAXDISPLAYRATE 26

#include "../QImageProcessLib/QImageProcess.h"

QCameraShowDlg::QCameraShowDlg(QWidget *parent)
	: QWidget(parent)
	, m_pCameraDevice(nullptr)
	, m_nOffsetX(0)
	, m_nOffsetY(0)
	, m_nScaledWidth(0)
	, m_nScaledHeight(0)
	, m_showDlgSize(0, 0)
	, m_pDrawFigurePanel(nullptr)
	, m_dAcquisitionRate(0.0)
	, m_bShowDynamicImg(false)
	, m_pTimerTakeAPhotoTimeout(nullptr)
	, m_originalMat()
	, m_showMat()
	, m_dRatio(0.0)
{
	m_pDrawFigurePanel = new QDrawFigurePanel(this);
	connect(this, &QCameraShowDlg::sig_updateImgRegion, m_pDrawFigurePanel, &QDrawFigurePanel::slot_updateImgRegion);
	connect(m_pDrawFigurePanel, &QDrawFigurePanel::sig_requestPixelValue, 
						  this, &QCameraShowDlg::slot_responseRequestPixelValue);
	connect(this, &QCameraShowDlg::sig_sendRequestedPixelValue, 
			m_pDrawFigurePanel, &QDrawFigurePanel::slot_receiveRequestedPixelValue);
	connect(m_pDrawFigurePanel, &QDrawFigurePanel::sig_sendSelectedPixelPoint, 
						  this, &QCameraShowDlg::slot_receiveSelectedPixelValue);

	connect(this, QOverload<>::of(&QCameraShowDlg::sig_refreshShowImg), this, QOverload<>::of(&QCameraShowDlg::update));

	m_nDisplayRate = 1000 / MAXDISPLAYRATE;

	m_pTimerTakeAPhotoTimeout = new QTimer(this);
	m_pTimerTakeAPhotoTimeout->setSingleShot(true);
	m_pTimerTakeAPhotoTimeout->setInterval(1000);

	connect(m_pTimerTakeAPhotoTimeout, &QTimer::timeout, this, &QCameraShowDlg::slot_takeAPhotoTimeout);
}

QCameraShowDlg::~QCameraShowDlg()
{

}

void QCameraShowDlg::onImageCallback(PvBuffer * pBuffer, void * pUser)
{
	if (m_pCameraDevice != nullptr)
	{
		m_pCameraDevice->imageConventer(pBuffer);
		if (m_elapsedTimer.elapsed() < m_nDisplayRate)
		{
			return;
		}
		else
		{
			if(m_bShowDynamicImg)
			{
				m_pCameraDevice->getAcquistionRate(m_dAcquisitionRate);
				emit sig_refreshShowImg();
			}

			m_elapsedTimer.restart();
		}
	}
}

void QCameraShowDlg::attachCamera(QSentechCamera * pCamera)
{
	if (pCamera != nullptr && m_pCameraDevice == nullptr)
	{
		m_pCameraDevice = pCamera;

		m_pCameraDevice->detachLock();

		m_elapsedTimer.start();
		m_pCameraDevice->RegisterCallback(this, &QCameraShowDlg::onImageCallback, nullptr);
		connect(m_pCameraDevice, &QSentechCamera::sig_takeAPhotoCompleted, this, &QCameraShowDlg::slot_requestTakeAPhotoCompleted);

		m_pCameraDevice->setCountScaledWidth(true);
		m_bShowDynamicImg = true;

		m_pCameraDevice->detachUnlock();
	}
}

void QCameraShowDlg::detachCamera()
{
	if (m_pCameraDevice != nullptr)
	{
		m_pCameraDevice->detachLock();

		m_pCameraDevice->stopAcquisition();
		m_pCameraDevice->UnregisterCallback();

		disconnect(m_pCameraDevice, &QSentechCamera::sig_takeAPhotoCompleted, this, &QCameraShowDlg::slot_requestTakeAPhotoCompleted);

		m_bShowDynamicImg = false;

		m_pCameraDevice->detachUnlock();

		m_pCameraDevice = nullptr;
	}

	m_elapsedTimer.invalidate();

	m_nScaledWidth = 0;
	m_nScaledHeight = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
}

void QCameraShowDlg::countImgScaled(int nWidth, int nHeight)
{
	if (nWidth == 0 || nHeight == 0 || m_showDlgSize.width() == 0 || m_showDlgSize.height() == 0)
	{
		return;
	}

	double nWidthScaleTemp = (double)(nWidth) / m_showDlgSize.width();
	double nHeightScaleTemp = (double)(nHeight) / m_showDlgSize.height();
	if (nWidthScaleTemp > nHeightScaleTemp)
	{
		m_nScaledHeight = nHeight / nWidthScaleTemp;
		m_nOffsetX = 0;
		m_nOffsetY = (m_showDlgSize.height() - m_nScaledHeight) / 2;
		m_nScaledWidth = m_showDlgSize.width();

		m_dRatio = ((double)nWidth) / m_nScaledWidth;
	}
	else
	{
		m_nScaledWidth = nWidth / nHeightScaleTemp;
		m_nOffsetX = (m_showDlgSize.width() - m_nScaledWidth) / 2;
		m_nOffsetY = 0;
		m_nScaledHeight = m_showDlgSize.height();

		m_dRatio = ((double)nHeight) / m_nScaledHeight;
	}
}

void QCameraShowDlg::showDrawFigurePanel(bool bShow)
{
	if (bShow)
	{
		m_pDrawFigurePanel->show();
	}
	else
	{
		m_pDrawFigurePanel->hide();
	}
}

bool QCameraShowDlg::isAttachedCamera() const
{
	return !(m_pCameraDevice == nullptr);
}

QDrawFigurePanel * QCameraShowDlg::getDrawFigurePanel() const
{
	return m_pDrawFigurePanel;
}

void QCameraShowDlg::slot_requestTakeAPhoto()
{
	if(m_pCameraDevice && m_pCameraDevice->isStartedAcquisition())
	{
		m_pCameraDevice->takeAPhoto();
		if(m_pCameraDevice->isTriggerMode())
		{
			m_pCameraDevice->excuteTriggerSoftware();
		}

		m_pTimerTakeAPhotoTimeout->start();
	}
}

void QCameraShowDlg::slot_requestShowDynamicImage()
{
	if(m_pCameraDevice)
	{
		m_pCameraDevice->setCountScaledWidth(true);
		m_bShowDynamicImg = true;
	}
}

void QCameraShowDlg::slot_takeAPhotoTimeout()
{
	QCustomMessageBox::customMessageBox(this, QCustomMessageBox::error, QStringLiteral("相机掉线或未连接!"));
}

void QCameraShowDlg::slot_requestShowDesignatedMat(const Mat * pMat)
{
	if(pMat == nullptr)
	{
		return;
	}

	m_showMat = pMat->clone();

	if(m_showMat.channels() > 1)
	{
		cvtColor(m_showMat, m_showMat, CV_BGR2RGB);
	}

	m_bShowDynamicImg = false;

	update();
}

void QCameraShowDlg::slot_requestShowOriginalMat()
{
	if (m_originalMat.empty())
	{
		return;
	}

	m_showMat = m_originalMat.clone();

	if (m_showMat.channels() > 1)
	{
		cvtColor(m_showMat, m_showMat, CV_BGR2RGB);
	}

	m_bShowDynamicImg = false;

	update();
}

void QCameraShowDlg::slot_loadLocalImage(const QString & strPath, int nFlags)
{
	m_originalMat = loadMatSelect(this, strPath, nFlags);
	if(m_originalMat.channels() == 1)
	{
		if(m_originalMat.depth() != CV_8U)
		{
			m_originalMat.convertTo(m_originalMat, CV_8UC1);
		}
	}
	else if(m_originalMat.channels() == 3)
	{
		if(m_originalMat.depth() != CV_8U)
		{
			m_originalMat.convertTo(m_originalMat, CV_8UC3);
		}
	}
	else if(m_originalMat.channels() == 4)
	{
		cvtColor(m_originalMat, m_originalMat, CV_BGRA2BGR);

		if (m_originalMat.depth() != CV_8U)
		{
			m_originalMat.convertTo(m_originalMat, CV_8UC3);
		}
	}
	else
	{
		return;
	}

	emit sig_sendDealMat(&m_originalMat);

	slot_requestShowOriginalMat();
}

void QCameraShowDlg::slot_responseRequestPixelValue(const QPoint & pt)
{
	if (m_showMat.empty())
	{
		return;
	}

	int nX = static_cast<int>(pt.x() * m_dRatio);
	int nY = static_cast<int>(pt.y() * m_dRatio);

	if(nX < 0 || nX > m_showMat.cols - 1 || nY < 0 || nY > m_showMat.rows - 1)
	{
		return;
	}

	bool bColor = false;

	if(m_showMat.type() == CV_8UC1)
	{
		uchar ucChannel1 = m_showMat.at<uchar>(nY, nX);
		emit sig_sendRequestedPixelValue(nX, nY, bColor, ucChannel1, 0, 0);
	}
	else if(m_showMat.type() == CV_8UC3)
	{
		bColor = true;
		Vec3b vecValue = m_showMat.at<Vec3b>(nY, nX);
		emit sig_sendRequestedPixelValue(nX, nY, bColor, vecValue[0], vecValue[1], vecValue[2]);
	}
}

void QCameraShowDlg::slot_receiveSelectedPixelValue(int nX, int nY, uchar ucChannale1, uchar ucChannel2, uchar ucChannel3)
{
	emit sig_sendSelectedPixelPoint(nX, nY);
}

void QCameraShowDlg::slot_windowBeMoved()
{
	QPoint ptGlobal = mapToGlobal(QPoint(m_nOffsetX, m_nOffsetY));
	if (m_nScaledWidth > 0 && m_nScaledHeight > 0)
	{
		emit sig_updateImgRegion(ptGlobal.x(), ptGlobal.y(), m_nScaledWidth, m_nScaledHeight);
	}
}

void QCameraShowDlg::slot_requestTakeAPhotoCompleted()
{
	if(m_pCameraDevice != nullptr && m_pCameraDevice->getDealImgBuffer() != nullptr)
	{
		m_originalMat = Mat(m_pCameraDevice->getImageHeight(), m_pCameraDevice->getImageWidth(),
				m_pCameraDevice->isColor() ? CV_8UC3 : CV_8UC1, m_pCameraDevice->getDealImgBuffer()).clone();

		if (m_originalMat.channels() > 1)
		{
			cvtColor(m_originalMat, m_originalMat, CV_RGB2BGR);
		}

		emit sig_sendDealMat(&m_originalMat);   //发送出去的都是原始图像

		slot_requestShowOriginalMat();
	}
	
	m_pTimerTakeAPhotoTimeout->stop();
}

void QCameraShowDlg::paintEvent(QPaintEvent * pPaintEvent)
{
	QPainter painter(this);

	if(m_bShowDynamicImg)
	{
		if (m_pCameraDevice != nullptr && m_pCameraDevice->getImageBuffer() != nullptr)
		{
			if (m_nScaledHeight == 0 || m_nScaledWidth == 0 || m_pCameraDevice->isCountScaledWidth())
			{
				countImgScaled(m_pCameraDevice->getImageWidth(), m_pCameraDevice->getImageHeight());

				QPoint ptGlobal = mapToGlobal(QPoint(m_nOffsetX, m_nOffsetY));
				if (m_nScaledWidth > 0 && m_nScaledHeight > 0)
				{
					emit sig_updateImgRegion(ptGlobal.x(), ptGlobal.y(), m_nScaledWidth, m_nScaledHeight);
				}

				m_pCameraDevice->setCountScaledWidth(false);
			}

			if (m_pCameraDevice->isColor())
			{
				m_pCameraDevice->operateBufferLock();

				QImage imageTemp = QImage(m_pCameraDevice->getImageBuffer(), m_pCameraDevice->getImageWidth(),
						m_pCameraDevice->getImageHeight(), QImage::Format_RGB888);
				QPixmap showPixmap = QPixmap::fromImage(imageTemp).scaled(m_showDlgSize, Qt::KeepAspectRatio);

				painter.drawPixmap(m_nOffsetX, m_nOffsetY, showPixmap);
				painter.drawText(m_nOffsetX + 10, m_nOffsetY + 18, QString("FPS: %1").arg(m_dAcquisitionRate));

				m_pCameraDevice->operateBufferUnlock();
			}
			else
			{
				m_pCameraDevice->operateBufferLock();

				QImage imageTemp = QImage(m_pCameraDevice->getImageBuffer(), m_pCameraDevice->getImageWidth(),
						m_pCameraDevice->getImageHeight(), QImage::Format_Grayscale8);
				QPixmap showPixmap = QPixmap::fromImage(imageTemp).scaled(m_showDlgSize, Qt::KeepAspectRatio);

				painter.drawPixmap(m_nOffsetX, m_nOffsetY, showPixmap);
				painter.drawText(m_nOffsetX + 10, m_nOffsetY + 18, QString("FPS: %1").arg(m_dAcquisitionRate));

				m_pCameraDevice->operateBufferUnlock();
			}
		}
	}
	else
	{
		if(!m_showMat.empty())
		{
			countImgScaled(m_showMat.cols, m_showMat.rows);

			QPoint ptGlobal = mapToGlobal(QPoint(m_nOffsetX, m_nOffsetY));
			if (m_nScaledWidth > 0 && m_nScaledHeight > 0)
			{
				emit sig_updateImgRegion(ptGlobal.x(), ptGlobal.y(), m_nScaledWidth, m_nScaledHeight);
			}

			if(m_showMat.channels() == 3)
			{
				QImage imageTemp = QImage(m_showMat.data, m_showMat.cols, m_showMat.rows, m_showMat.step, QImage::Format_RGB888);
				QPixmap showPixmap = QPixmap::fromImage(imageTemp).scaled(m_showDlgSize, Qt::KeepAspectRatio);

				painter.drawPixmap(m_nOffsetX, m_nOffsetY, showPixmap);
				painter.drawText(m_nOffsetX + 10, m_nOffsetY + 18, QString("width:") + QString::number(m_showMat.cols) + 
				QString("  height:") + QString::number(m_showMat.rows) + QStringLiteral("  depth:8  channel:3"));
			}
			else if(m_showMat.channels() == 1)
			{
				QImage imageTemp = QImage(m_showMat.data, m_showMat.cols, m_showMat.rows, m_showMat.step, QImage::Format_Grayscale8);
				QPixmap showPixmap = QPixmap::fromImage(imageTemp).scaled(m_showDlgSize, Qt::KeepAspectRatio);

				painter.drawPixmap(m_nOffsetX, m_nOffsetY, showPixmap);
				painter.drawText(m_nOffsetX + 10, m_nOffsetY + 18, QString("width:") + QString::number(m_showMat.cols) +
					QString("  height:") + QString::number(m_showMat.rows) + QStringLiteral("  depth:8  channel:1"));
			}
		}
	}
}

void QCameraShowDlg::resizeEvent(QResizeEvent * pResizeEvent)
{
	m_showDlgSize = pResizeEvent->size();

	if(m_pCameraDevice)
	{
		countImgScaled(m_pCameraDevice->getImageWidth(), m_pCameraDevice->getImageHeight());
	}

	QPoint ptGlobal = mapToGlobal(QPoint(m_nOffsetX, m_nOffsetY));
	if (m_nScaledWidth > 0 && m_nScaledHeight > 0)
	{
		emit sig_updateImgRegion(ptGlobal.x(), ptGlobal.y(), m_nScaledWidth, m_nScaledHeight);
	}
}