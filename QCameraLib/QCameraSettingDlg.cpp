#include "QCameraSettingDlg.h"
#include "QCameraManager.h"
#include "QSentechCamera.h"

#include "../QUniversalFrameLib/QCustomDialogTitleBar.h"

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QUniversalFrameLib.lib")
#else
#pragma comment(lib, "../X64/Release/QUniversalFrameLib.lib")
#endif

QCameraSettingDlg::QCameraSettingDlg(QWidget *parent, QCameraManager *pCameraManager)
	: QDialog(parent)
	, m_pTitleBar(nullptr)
	, m_pCameraManager(pCameraManager)
	, m_pCurrentCamera(nullptr)
{
	setupUi(this);
	
	m_pTitleBar = new QCustomDialogTitleBar(this, m_pFrameTitleBar, 20);
	m_pTitleBar->setTitleName(QStringLiteral("相机设置"));
	m_pTitleBar->setTitleIcon(":/new/prefix1/camera");
	m_pTitleBar->hideMaximize(true);
	m_pTitleBar->hideMinimize(true);
	
	setSizeGripEnabled(true);

	connect(m_pcobCurrentCamera, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &QCameraSettingDlg::slot_updateAllControl);

	if(m_pCameraManager != nullptr)
	{
		for(int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			m_pcobCurrentCamera->addItem(QString::number(nCounter));
		}
	}

	if(m_pcobCurrentCamera->count() > 0)
	{
		m_pcobCurrentCamera->setCurrentIndex(0);
	}
}

QCameraSettingDlg::~QCameraSettingDlg()
{

}

void QCameraSettingDlg::setCameraManager(QCameraManager * pCameraManager)
{
	m_pCameraManager = pCameraManager;

	if (m_pCameraManager != nullptr)
	{
		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			m_pcobCurrentCamera->addItem(QString::number(nCounter));
		}
	}

	if (m_pcobCurrentCamera->count() > 0)
	{
		m_pcobCurrentCamera->setCurrentIndex(0);
	}
}

void QCameraSettingDlg::specificControlInAcquisition(bool bEnable)
{
	m_pcobPixelType->setEnabled(bEnable);
	m_psbImageWidth->setEnabled(bEnable);
	m_psbImageHeight->setEnabled(bEnable);
	m_pcbTriggerMode->setEnabled(bEnable);
}

void QCameraSettingDlg::slot_pixelTypeChanged(QString strPixelType)
{
	if(m_pCurrentCamera && !strPixelType.isEmpty())
	{
		if(m_pCurrentCamera->setEnumValueToDevice(PIXELFORMATFEATURE, strPixelType))
		{
			m_pCurrentCamera->setPixelFormat(strPixelType);
		}
		else
		{
			m_pcobPixelType->setCurrentText(m_pCurrentCamera->getPixelFormat());
		}
	}
}

void QCameraSettingDlg::slot_whiteBalanceChanged(QString strWhiteBalance)
{
	if (m_pCurrentCamera && !strWhiteBalance.isEmpty())
	{
		if (m_pCurrentCamera->setEnumValueToDevice(BALANCEWHITEAUTOFEATURE, strWhiteBalance))
		{
			m_pCurrentCamera->setBalanceWhiteAuto(strWhiteBalance);
		}
		else
		{
			m_pcobWhiteBalance->setCurrentText(m_pCurrentCamera->getBalanceWhiteAuto());
		}
	}
}

void QCameraSettingDlg::slot_triggerModeStateChanged(int nState)
{
	if(m_pCurrentCamera)
	{
		Qt::CheckState enumState = static_cast<Qt::CheckState>(nState);
		if (enumState == Qt::Checked)
		{
			if (m_pCurrentCamera->setTriggerMode(true))
			{
				m_ppbTrigger->setEnabled(true);
			}
			else
			{
				m_pcbTriggerMode->setChecked(false);
				m_pcbTriggerMode->setEnabled(false);
			}
		}
		else if(enumState == Qt::Unchecked)
		{
			if(m_pCurrentCamera->setTriggerMode(false))
			{
				m_ppbTrigger->setEnabled(false);
			}
			else
			{
				m_pcbTriggerMode->setChecked(true);
				m_pcbTriggerMode->setEnabled(false);
			}
		}
	}
}

void QCameraSettingDlg::slot_triggerSourceChanged(QString strTriggerSource)
{
	if (m_pCurrentCamera && !strTriggerSource.isEmpty())
	{
		if (m_pCurrentCamera->setEnumValueToDevice(TRIGGERSOURCEFEATURE, strTriggerSource))
		{
			m_pCurrentCamera->setPixelFormat(strTriggerSource);
		}
		else
		{
			m_pcobTriggerSource->setCurrentText(m_pCurrentCamera->getTriggerSource());
		}
	}
}

void QCameraSettingDlg::slot_triggerCamera()
{
	if (m_pCurrentCamera)
	{
		m_pCurrentCamera->excuteTriggerSoftware();
	}
}

void QCameraSettingDlg::slot_exposureTimeChanged()
{
	if(m_pCurrentCamera)
	{
		int nExposureValue = m_psbExposureTime->value();

		if (m_pCurrentCamera->setFloatParamToDevice(EXPOSURETIMEFEATURE, nExposureValue))
		{
			m_pCurrentCamera->setExposureTime(nExposureValue);
		}
		else
		{
			m_psbExposureTime->setValue(m_pCurrentCamera->getExposureTime());
		}
	}
}

void QCameraSettingDlg::slot_acquisitionRateChanged()
{
	if (m_pCurrentCamera)
	{
		int nAcquisitionRate = m_psbAcquisitionRate->value();

		if (m_pCurrentCamera->setFloatParamToDevice(ACQUISITIONRATEFEATURE, nAcquisitionRate))
		{
			m_pCurrentCamera->setAcquisitionFrameRate(nAcquisitionRate);
		}
		else
		{
			m_psbAcquisitionRate->setValue(m_pCurrentCamera->getAcquisitionFrameRate());
		}
	}
}

void QCameraSettingDlg::slot_acquisitionControl(bool bState)
{
	if(m_pCurrentCamera)
	{
		if(bState)
		{
			m_ppbAcquisitionControl->setText(QStringLiteral("停止采集"));
			m_pCurrentCamera->startAcquisition();
			specificControlInAcquisition(false);
		}
		else
		{
			m_ppbAcquisitionControl->setText(QStringLiteral("开始采集"));
			m_pCurrentCamera->stopAcquisition();
			specificControlInAcquisition(true);
		}
	}
}

void QCameraSettingDlg::slot_programerChanged(bool bState)
{
	if(m_pCurrentCamera)
	{
		if (bState)
		{
			m_pCurrentCamera->setProgramerPower(true);
			m_ppbAcquisitionControl->setEnabled(true);
			if (m_ppbAcquisitionControl->isChecked())
			{
				specificControlInAcquisition(false);
			}
			else
			{
				specificControlInAcquisition(true);
			}
		}
		else
		{
			m_pCurrentCamera->setProgramerPower(false);
			m_ppbAcquisitionControl->setEnabled(false);
			specificControlInAcquisition(false);
		}
	}
}

void QCameraSettingDlg::slot_imageWidthChanged()
{
	if (m_pCurrentCamera)
	{
		int nImageWidth = m_psbImageWidth->value();

		if (m_pCurrentCamera->setIntegerParamToDevice(WIDTHFEATURE, nImageWidth))
		{
			m_pCurrentCamera->setImageWidth(nImageWidth);
			int nMinOffsetX = 0;
			int nMaxOffsetX = 0;
			m_pCurrentCamera->getIntegerRangeFromDevice(OFFSETX, nMinOffsetX, nMaxOffsetX);
			m_pCurrentCamera->setMinOffsetX(nMinOffsetX);
			m_pCurrentCamera->setMaxOffsetX(nMaxOffsetX);
			m_psbXOffset->setMinimum(nMinOffsetX);
			m_psbXOffset->setMaximum(nMaxOffsetX);
			m_pCurrentCamera->setCountScaledWidth(true);
		}
		else
		{
			m_psbImageWidth->setValue(m_pCurrentCamera->getImageWidth());
		}
	}
}

void QCameraSettingDlg::slot_imageHeightChanged()
{
	if (m_pCurrentCamera)
	{
		int nImageHeight = m_psbImageHeight->value();

		if (m_pCurrentCamera->setIntegerParamToDevice(HEIGHTFEATURE, nImageHeight))
		{
			m_pCurrentCamera->setImageHeight(nImageHeight);
			int nMinOffsetY = 0;
			int nMaxOffsetY = 0;
			m_pCurrentCamera->getIntegerRangeFromDevice(OFFSETY, nMinOffsetY, nMaxOffsetY);
			m_pCurrentCamera->setMinOffsetY(nMinOffsetY);
			m_pCurrentCamera->setMaxOffsetY(nMaxOffsetY);
			m_psbYOffset->setMinimum(nMinOffsetY);
			m_psbYOffset->setMaximum(nMaxOffsetY);
			m_pCurrentCamera->setCountScaledWidth(true);
		}
		else
		{
			m_psbImageHeight->setValue(m_pCurrentCamera->getImageHeight());
		}
	}
}

void QCameraSettingDlg::slot_offsetxChanged()
{
	if (m_pCurrentCamera)
	{
		int nOffsetX = m_psbXOffset->value();

		if (m_pCurrentCamera->setIntegerParamToDevice(OFFSETX, nOffsetX))
		{
			m_pCurrentCamera->setOffsetX(nOffsetX);
			int nMinWidth = 0;
			int nMaxWidth = 0;
			m_pCurrentCamera->getIntegerRangeFromDevice(WIDTHFEATURE, nMinWidth, nMaxWidth);
			m_pCurrentCamera->setMinWidth(nMinWidth);
			m_pCurrentCamera->setMaxWidth(nMaxWidth);
			m_psbImageWidth->setMinimum(nMinWidth);
			m_psbImageWidth->setMaximum(nMaxWidth);
		}
		else
		{
			m_psbXOffset->setValue(m_pCurrentCamera->getOffsetX());
		}
	}
}

void QCameraSettingDlg::slot_offsetyChanged()
{
	if (m_pCurrentCamera)
	{
		int nOffsetY = m_psbYOffset->value();

		if (m_pCurrentCamera->setIntegerParamToDevice(OFFSETY, nOffsetY))
		{
			m_pCurrentCamera->setOffsetY(nOffsetY);
			int nMinHeight = 0;
			int nMaxHeight = 0;
			m_pCurrentCamera->getIntegerRangeFromDevice(HEIGHTFEATURE, nMinHeight, nMaxHeight);
			m_pCurrentCamera->setMinHeight(nMinHeight);
			m_pCurrentCamera->setMaxHeight(nMaxHeight);
			m_psbImageHeight->setMinimum(nMinHeight);
			m_psbImageHeight->setMaximum(nMaxHeight);
		}
		else
		{
			m_psbYOffset->setValue(m_pCurrentCamera->getOffsetY());
		}
	}
}

void QCameraSettingDlg::slot_refreshCamera()
{
	m_pcobCurrentCamera->clear();

	if (m_pCameraManager != nullptr)
	{
		for (int nCounter = 0; nCounter < m_pCameraManager->getCameraNum(); nCounter++)
		{
			m_pcobCurrentCamera->addItem(QString::number(nCounter));
		}
	}

	if (m_pcobCurrentCamera->count() > 0)
	{
		m_pcobCurrentCamera->setCurrentIndex(0);
	}
}

void QCameraSettingDlg::slot_cameraDescribeChanged()
{
	if (m_pCurrentCamera)
	{
		m_pCurrentCamera->setDeviceDescribe(m_pleCameraDescribe->text());
	}
}

void QCameraSettingDlg::slot_updateAllControl(int nIndex)
{
	if(m_pCameraManager == nullptr || nIndex < 0 || nIndex > m_pCameraManager->getCameraNum() - 1)
	{
		return;
	}

	m_pCurrentCamera = nullptr;

	QSentechCamera *pCamera = m_pCameraManager->getSpecificCamera(nIndex);

	m_pleCameraDescribe->setText(pCamera->getDeviceDescribe());
	m_pleCameraIPAddr->setText(pCamera->getDeviceIP());
	m_pleCameraMACAddr->setText(pCamera->getDeviceMAC());
	m_pleCameraVendor->setText(pCamera->getDeviceVendorName());
	m_pleCameraModel->setText(pCamera->getDeviceModelName());
	m_pleInterfaceIP->setText(pCamera->getInterfaceIP());
	m_pleInterfaceMAC->setText(pCamera->getInterfaceMAC());

	m_pcobPixelType->clear();
	m_pcobPixelType->addItems(pCamera->getPixelFormatList());
	m_pcobPixelType->setCurrentText(pCamera->getPixelFormat());

	m_pcobWhiteBalance->clear();
	m_pcobWhiteBalance->addItems(pCamera->getBalanceAutoList());
	m_pcobWhiteBalance->setCurrentText(pCamera->getBalanceWhiteAuto());

	m_psbImageWidth->setMinimum(pCamera->getMinWidth());
	m_psbImageWidth->setMaximum(pCamera->getMaxWidth());
	m_psbImageWidth->setValue(pCamera->getImageWidth());

	m_psbXOffset->setMinimum(pCamera->getMinOffsetX());
	m_psbXOffset->setMaximum(pCamera->getMaxOffsetX());
	m_psbXOffset->setValue(pCamera->getOffsetX());

	m_psbImageHeight->setMinimum(pCamera->getMinHeight());
	m_psbImageHeight->setMaximum(pCamera->getMaxHeight());
	m_psbImageHeight->setValue(pCamera->getImageHeight());

	m_psbYOffset->setMinimum(pCamera->getMinOffsetY());
	m_psbYOffset->setMaximum(pCamera->getMaxOffsetY());
	m_psbYOffset->setValue(pCamera->getOffsetY());

	if (pCamera->isStartedAcquisition())
	{
		m_ppbAcquisitionControl->setChecked(true);
		m_ppbAcquisitionControl->setText(QStringLiteral("停止采集"));
	}
	else
	{
		m_ppbAcquisitionControl->setChecked(false);
		m_ppbAcquisitionControl->setText(QStringLiteral("开始采集"));
	}

	if(pCamera->isProgramerPower())
	{
		m_pcbProgramerMode->setChecked(true);
		m_ppbAcquisitionControl->setEnabled(true);
		if (m_ppbAcquisitionControl->isChecked())
		{
			specificControlInAcquisition(false);
		}
		else
		{
			specificControlInAcquisition(true);
		}
	}
	else
	{
		m_pcbProgramerMode->setChecked(false);
		m_ppbAcquisitionControl->setEnabled(false);
		specificControlInAcquisition(false);
	}

	if(pCamera->isTriggerMode())
	{
		m_pcbTriggerMode->setChecked(true);
		m_ppbTrigger->setEnabled(true);
	}
	else
	{
		m_pcbTriggerMode->setChecked(false);
		m_ppbTrigger->setEnabled(false);
	}

	if(pCamera->getInterfaceType() == QSentechCamera::EBUS)
	{
		m_pleNICType->setText("EBus");
	}
	else
	{
		m_pleNICType->setText("NetWork");
	}

	m_pcobTriggerSource->clear();
	m_pcobTriggerSource->addItems(pCamera->getTriggerSourceList());
	m_pcobTriggerSource->setCurrentText(pCamera->getTriggerSource());

	m_psbExposureTime->setMinimum(pCamera->getMinExposureTime());
	m_psbExposureTime->setMaximum(pCamera->getMaxExposureTime());
	m_psbExposureTime->setValue(static_cast<int>(pCamera->getExposureTime()));

	m_psbAcquisitionRate->setMinimum(pCamera->getMinAcquisitionRate() + 1);
	m_psbAcquisitionRate->setMaximum(pCamera->getMaxAcquisitionRate());
	m_psbAcquisitionRate->setValue(static_cast<int>(pCamera->getAcquisitionFrameRate()));

	m_pCurrentCamera = pCamera;
}
