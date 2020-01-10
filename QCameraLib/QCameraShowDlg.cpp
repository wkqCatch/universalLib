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
	, m_bShowDealImg(false)
	, m_pTimerTakeAPhotoTimeout(nullptr)
{
	m_pDrawFigurePanel = new QDrawFigurePanel(this);
	connect(this, &QCameraShowDlg::sig_updateImgRegion, m_pDrawFigurePanel, &QDrawFigurePanel::slot_updateImgRegion);

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
			m_pCameraDevice->getAcquistionRate(m_dAcquisitionRate);
			emit sig_refreshShowImg();
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

		m_pCameraDevice->detachUnlock();

		m_pCameraDevice = nullptr;
	}

	m_elapsedTimer.invalidate();

	m_nScaledWidth = 0;
	m_nScaledHeight = 0;
	m_nOffsetX = 0;
	m_nOffsetY = 0;
}

void QCameraShowDlg::countImgScaled()
{
	if (m_pCameraDevice == nullptr)
	{
		return;
	}

	if (m_pCameraDevice->getImageWidth() == 0 || m_pCameraDevice->getImageHeight() == 0 ||
		m_showDlgSize.width() == 0 || m_showDlgSize.height() == 0)
	{
		return;
	}

	int nImageWidthTemp = m_pCameraDevice->getImageWidth();
	int nImageHeightTemp = m_pCameraDevice->getImageHeight();

	double nWidthScaleTemp = (double)(nImageWidthTemp) / m_showDlgSize.width();
	double nHeightScaleTemp = (double)(nImageHeightTemp) / m_showDlgSize.height();
	if (nWidthScaleTemp > nHeightScaleTemp)
	{
		m_nScaledHeight = nImageHeightTemp / nWidthScaleTemp;
		m_nOffsetX = 0;
		m_nOffsetY = (m_showDlgSize.height() - m_nScaledHeight) / 2;
		m_nScaledWidth = m_showDlgSize.width();
	}
	else
	{
		m_nScaledWidth = nImageWidthTemp / nHeightScaleTemp;
		m_nOffsetX = (m_showDlgSize.width() - m_nScaledWidth) / 2;
		m_nOffsetY = 0;
		m_nScaledHeight = m_showDlgSize.height();
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

void QCameraShowDlg::slot_requestTakeAPhoto()
{
	if(m_pCameraDevice)
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
	m_bShowDealImg = false;
}

void QCameraShowDlg::slot_takeAPhotoTimeout()
{
	QCustomMessageBox::customMessageBox(this, QCustomMessageBox::error, QStringLiteral("相机掉线或未连接!"));
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
	m_bShowDealImg = true;

	if(m_pCameraDevice)
	{
		emit(m_pCameraDevice->getDealImgBuffer(), m_pCameraDevice->getImageWidth(),
			m_pCameraDevice->getImageHeight(), m_pCameraDevice->isColor() ? 3 : 1);
	}
	
	m_pTimerTakeAPhotoTimeout->stop();
}

void QCameraShowDlg::paintEvent(QPaintEvent * pPaintEvent)
{
	QPainter painter(this);

	if (m_pCameraDevice != nullptr && m_pCameraDevice->getImageBuffer() != nullptr)
	{
		if (m_nScaledHeight == 0 || m_nScaledWidth == 0 || m_pCameraDevice->isCountScaledWidth())
		{
			countImgScaled();
			m_pCameraDevice->setCountScaledWidth(false);
		}

		if (m_pCameraDevice->isColor())
		{
			m_pCameraDevice->operateBufferLock();

			QImage imageTemp;
			if(m_bShowDealImg)
			{
				imageTemp = QImage(m_pCameraDevice->getDealImgBuffer(), m_pCameraDevice->getImageWidth(),
					m_pCameraDevice->getImageHeight(), QImage::Format_RGB888);
			}
			else
			{
				imageTemp = QImage(m_pCameraDevice->getImageBuffer(), m_pCameraDevice->getImageWidth(),
					m_pCameraDevice->getImageHeight(), QImage::Format_RGB888);
			}
			
			QPixmap showPixmap = QPixmap::fromImage(imageTemp).scaled(m_showDlgSize, Qt::KeepAspectRatio);
			painter.drawPixmap(m_nOffsetX, m_nOffsetY, showPixmap);
			painter.drawText(m_nOffsetX + 10, m_nOffsetY + 18, QString("FPS: %1").arg(m_dAcquisitionRate));

			m_pCameraDevice->operateBufferUnlock();
		}
		else
		{
			m_pCameraDevice->operateBufferLock();

			QImage imageTemp;
			if(m_bShowDealImg)
			{
				imageTemp = QImage(m_pCameraDevice->getDealImgBuffer(), m_pCameraDevice->getImageWidth(),
								   m_pCameraDevice->getImageHeight(), QImage::Format_Grayscale8);
			}
			else
			{
				imageTemp = QImage(m_pCameraDevice->getImageBuffer(), m_pCameraDevice->getImageWidth(),
								   m_pCameraDevice->getImageHeight(), QImage::Format_Grayscale8);
			}
			
			QPixmap showPixmap = QPixmap::fromImage(imageTemp).scaled(m_showDlgSize, Qt::KeepAspectRatio);
			painter.drawPixmap(m_nOffsetX, m_nOffsetY, showPixmap);
			painter.drawText(m_nOffsetX + 10, m_nOffsetY + 18, QString("FPS: %1").arg(m_dAcquisitionRate));

			m_pCameraDevice->operateBufferUnlock();
		}
	}
}

void QCameraShowDlg::resizeEvent(QResizeEvent * pResizeEvent)
{
	m_showDlgSize = pResizeEvent->size();
	countImgScaled();

	QPoint ptGlobal = mapToGlobal(QPoint(m_nOffsetX, m_nOffsetY));
	if (m_nScaledWidth > 0 && m_nScaledHeight > 0)
	{
		emit sig_updateImgRegion(ptGlobal.x(), ptGlobal.y(), m_nScaledWidth, m_nScaledHeight);
	}
}