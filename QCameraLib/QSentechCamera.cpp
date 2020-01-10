#include "QSentechCamera.h"
#include "QSentechCallbackThread.h"

#include <PvDevice.h>
#include <PvPipeline.h>
#include <PvStream.h>
#include <PvAcquisitionStateManager.h>
#include <PvBufferConverter.h>

#include <QElapsedTimer>
#include <QThread>

#include <QDebug>

#define SenColorPixelType PvPixelRGB8
#define ColorChannels      3

#define SenGrayPixelType  PvPixelMono8
#define GrayChannels	  1

QSentechCamera::QSentechCamera(QObject *parent)
	: QAbstractCamera(parent)
	, m_pDevice(nullptr)
	, m_pStream(nullptr)
	, m_pPipeline(nullptr)
	, m_pAcquisitionStateManager(nullptr)
	, m_pCallbackThread(nullptr)
	, m_pUser(nullptr)
	, m_Listener(nullptr)
	, m_pGenParameterArray(nullptr)
	, m_enumInterfaceType(EBUS)
	, m_convertedImage{ new PvBuffer(), nullptr, 0, false }
	, m_plFrameRate(nullptr)
	, m_plFrameRateAverage(nullptr)
	, m_pBufferConventer(nullptr)
{
	m_pDevice = new PvDevice();
	m_pStream = new PvStream();
	m_pPipeline = new PvPipeline(m_pStream);

	m_pBufferConventer = new PvBufferConverter(16);
}

QSentechCamera::~QSentechCamera()
{
	if(isConnected())
	{
		disconnectDevice();
	}

	UnregisterCallback();
	if (m_pAcquisitionStateManager != nullptr)
	{
		delete m_pAcquisitionStateManager;
		m_pAcquisitionStateManager = nullptr;
	}

	delete m_pDevice;
	m_pDevice = nullptr;

	delete m_pPipeline;
	m_pPipeline = nullptr;

	delete m_pStream;
	m_pStream = nullptr;

	if(m_pBufferConventer)
	{
		delete m_pBufferConventer;
		m_pBufferConventer = nullptr;
	}

	freeMemoryForImage();

	delete m_convertedImage.pBuffer;
	m_convertedImage.pBuffer = nullptr;
}

bool QSentechCamera::connectDevice(const PvDeviceInfo * pDeviceInfo, int nAccessType)
{
	if (pDeviceInfo == nullptr)
	{
		return false;
	}

	// Device connection, packet size negociation and stream opening
	PvResult opResult = PvResult::Code::NOT_CONNECTED;

	// Just in case we came here still connected...
	disconnectDevice();

	// Connect device
	opResult = m_pDevice->Connect(pDeviceInfo, static_cast<PvAccessType>(nAccessType));
	if (!opResult.IsOK())
	{
		qDebug() << opResult.GetCodeString().GetAscii() << endl;
		disconnectDevice();
		return false;
	}

	// Perform automatic packet size negociation
	opResult = m_pDevice->NegotiatePacketSize(0, 1476);

	// Open stream - and retry if it fails
	for(;;)
	{
		opResult = m_pStream->Open(pDeviceInfo->GetIPAddress());
		if(opResult.IsOK())
		{
			break;
		}

		QThread::msleep(1000);  //or QElapseTimer  
	}

	// Now that the stream is opened, set the destination on the device
	opResult = m_pDevice->SetStreamDestination(m_pStream->GetLocalIPAddress(), m_pStream->GetLocalPort());
	if(!opResult.IsOK())
	{
		disconnectDevice();
		return false;
	}

	PvGenParameterArray *pStreamParamArray = m_pStream->GetParameters();
	m_plFrameRate = dynamic_cast<PvGenFloat*>(pStreamParamArray->Get("AcquisitionRate"));
	m_plFrameRateAverage = dynamic_cast<PvGenFloat *>(pStreamParamArray->Get("AcquisitionRateAverage"));

	// Create acquisition state manager
	if(m_pAcquisitionStateManager != nullptr)
	{
		disconnectDevice();
		return false;
	}
	m_pAcquisitionStateManager = new PvAcquisitionStateManager(m_pDevice, m_pStream);

	if(!openPipeline())
	{
		disconnectDevice();
		return false;
	}

	m_pGenParameterArray = m_pDevice->GetGenParameters();
	if(!updateDeviceParam())
	{
		disconnectDevice();
		return false;
	}
	
	return true;
}

bool QSentechCamera::connectDevice(const QString & strInfo, int nAccessType)
{
	if (strInfo.isEmpty())
	{
		return false;
	}

	// Device connection, packet size negociation and stream opening
	PvResult opResult = PvResult::Code::NOT_CONNECTED;

	// Just in case we came here still connected...
	disconnectDevice();

	PvString pvStringTemp;
	QString2PvString(strInfo, pvStringTemp);

	// Connect device
	opResult = m_pDevice->Connect(pvStringTemp, static_cast<PvAccessType>(nAccessType));
	if (!opResult.IsOK())
	{
		disconnectDevice();
		return false;
	}

	// Perform automatic packet size negociation
	opResult = m_pDevice->NegotiatePacketSize(0, 1476);

	// Open stream - and retry if it fails
	for (;;)
	{
		opResult = m_pStream->Open(pvStringTemp);
		if (opResult.IsOK())
		{
			break;
		}

		QThread::msleep(1000);  //or QElapseTimer  
	}

	// Now that the stream is opened, set the destination on the device
	opResult = m_pDevice->SetStreamDestination(m_pStream->GetLocalIPAddress(), m_pStream->GetLocalPort());
	if (!opResult.IsOK())
	{
		disconnectDevice();
		return false;
	}

	PvGenParameterArray *pStreamParamArray = m_pStream->GetParameters();
	m_plFrameRate = dynamic_cast<PvGenFloat*>(pStreamParamArray->Get("AcquisitionRate"));
	m_plFrameRateAverage = dynamic_cast<PvGenFloat *>(pStreamParamArray->Get("AcquisitionRateAverage"));

	// Create acquisition state manager
	if (m_pAcquisitionStateManager != nullptr)
	{
		disconnectDevice();
		return false;
	}
	m_pAcquisitionStateManager = new PvAcquisitionStateManager(m_pDevice, m_pStream);

	if (!openPipeline())
	{
		disconnectDevice();
		return false;
	}

	m_pGenParameterArray = m_pDevice->GetGenParameters();
	if (!updateDeviceParam())
	{
		disconnectDevice();
		return false;
	}

	return true;
}

bool QSentechCamera::isConnected() const
{
	return m_pDevice->IsConnected();
}

bool QSentechCamera::isIPEngine() const
{
	return m_pDevice->IsIPEngine();
}

void QSentechCamera::disconnectDevice()
{
	// If streaming, stop streaming
	closePipeline();

	// Release acquisition state manager
	if(m_pAcquisitionStateManager != nullptr)
	{
		delete m_pAcquisitionStateManager;
		m_pAcquisitionStateManager = nullptr;
	}

	m_pDevice->Disconnect();

	m_pStream->Close();

	m_pGenParameterArray = nullptr;
	m_nImageWidth = 0;
	m_nImageHeight = 0;
}

bool QSentechCamera::openPipeline()
{
	// Create display thread
	m_pCallbackThread = new QSentechCallbackThread(this);

	// Start threads
	m_pCallbackThread->start();
	//m_pCallbackThread->setPriority(QThread::NormalPriority);

	// Start pipeline
	PvResult lResult = m_pPipeline->Start();
	if(!lResult.IsOK())
	{
		return false;
	}

	return true;
}

void QSentechCamera::closePipeline()
{
	// Stop display thread
	if(m_pCallbackThread != nullptr)
	{
		m_pCallbackThread->requestInterruption();
		m_pCallbackThread->wait();

		delete m_pCallbackThread;
		m_pCallbackThread = nullptr;
	}

	// Stop stream thread
	if(m_pPipeline->IsStarted())
	{
		m_pPipeline->Stop();
	}
}

PvPipeline * QSentechCamera::getPipeline() const
{
	return m_pPipeline;
}

bool QSentechCamera::startAcquisition()
{
	if(isStartedAcquisition())
	{
		return false;
	}

	if(!allocateMemoryForImage())
	{
		return false;
	}

	PvInt64 nPayloadSizeValue = getPayloadSize();
	// If payload size is valid, force buffers re-alloc - better than 
	// adjusting as images are comming in
	if(nPayloadSizeValue > 0)
	{
		m_pPipeline->SetBufferSize(static_cast<PvUInt32>(nPayloadSizeValue));
		//m_pPipeline->SetBufferCount(16);
	}
	else
	{
		return false;
	}

	// Never hurts to start streaming on a fresh pipeline/stream...
	m_pPipeline->Reset();

	// Reset stream statistics
	m_pStream->GetParameters()->ExecuteCommand("Reset");

	if(m_pAcquisitionStateManager != nullptr)
	{
		m_pAcquisitionStateManager->Start();
	}

	return true;
}

void QSentechCamera::stopAcquisition()
{
	if(m_pAcquisitionStateManager != nullptr)
	{
		m_pAcquisitionStateManager->Stop();
	}
}

bool QSentechCamera::isStartedAcquisition() const
{
	if(m_pAcquisitionStateManager == nullptr)
	{
		return false;
	}

	return (m_pAcquisitionStateManager->GetState() == PvAcquisitionStateLocked);
}

QString QSentechCamera::PvString2QString(const PvString & strSource)
{
	return QString(strSource.GetAscii());
}

void QSentechCamera::QString2PvString(const QString & strSource, PvString & strTarget)
{
	PvString strTemp(strSource.toLatin1().data());

	strTarget = strTemp;
}

void QSentechCamera::PvString2QString(const PvString & strSource, QString & strTarget)
{
	QString strTemp(strSource.GetAscii());

	strTarget = strTemp;
}

PvGenParameterArray * QSentechCamera::getGenParameter() const
{
	return m_pDevice->GetGenParameters();
}

PvGenParameterArray * QSentechCamera::getGenLink() const
{
	return m_pDevice->GetGenLink();
}

PvGenParameterArray * QSentechCamera::getStreamParameter() const
{
	return m_pStream->GetParameters();
}

qint64 QSentechCamera::getPayloadSize()
{
	if(!isConnected())
	{
		return 0;
	}

	PvGenInteger *pPayloadSize = m_pDevice->GetGenParameters()->GetInteger("PayloadSize");

	PvInt64 lPayloadSizeValue = 0;
	if(pPayloadSize != nullptr)
	{
		pPayloadSize->GetValue(lPayloadSizeValue);
	}

	return lPayloadSizeValue;
}

void QSentechCamera::onImageCallback(PvBuffer * pBuffer)
{
	if(m_Listener)
	{
		m_Listener->Invoke(pBuffer, m_pUser);
	}
}

bool QSentechCamera::updateDeviceParam()
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	bool bResult = false;

	bResult = getIntegerParamFromDevice(WIDTHFEATURE, m_nImageWidth);
	if(!bResult)
	{
		return false;
	}
	getIntegerRangeFromDevice(WIDTHFEATURE, m_nMinWidth, m_nMaxWidth);

	getIntegerParamFromDevice(OFFSETX, m_nOffsetX);
	getIntegerRangeFromDevice(OFFSETX, m_nMinOffsetX, m_nMaxOffsetX);

	bResult = getIntegerParamFromDevice(HEIGHTFEATURE, m_nImageHeight);
	if (!bResult)
	{
		return false;
	}
	getIntegerRangeFromDevice(HEIGHTFEATURE, m_nMinHeight, m_nMaxHeight);

	getIntegerParamFromDevice(OFFSETY, m_nOffsetY);
	getIntegerRangeFromDevice(OFFSETY, m_nMinOffsetY, m_nMaxOffsetY);

	getFloatParamFromDevice(EXPOSURETIMEFEATURE, m_fExposureTime);
	getFloatRangeFromDevice(EXPOSURETIMEFEATURE, m_fMinExposureTime, m_fMaxExposureTime);

	setBooleanParamToDevice(ACQUISITIONRATEENABLEFEATURE, true);

	getFloatParamFromDevice(ACQUISITIONRATEFEATURE, m_fAcquisitionFrameRate);
	getFloatRangeFromDevice(ACQUISITIONRATEFEATURE, m_fMinAcquisitionRate, m_fMaxAcquisitionRate);

	getEnumEntryListFromDevice(BALANCEWHITEAUTOFEATURE, m_listBalanceWhiteAuto);
	getEnumValueFromDevice(BALANCEWHITEAUTOFEATURE, m_strBalanceWhiteAuto);

	getEnumEntryListFromDevice(TRIGGERSOURCEFEATURE, m_listTriggerSource);
	getEnumValueFromDevice(TRIGGERSOURCEFEATURE, m_strTriggerSource);

	QString strTriggerMode;
	getEnumValueFromDevice(TRIGGERMODEFEATURE, strTriggerMode);
	if(strTriggerMode == "On")
	{
		m_bTriggerMode = true;
	}
	else
	{
		m_bTriggerMode = false;
	}

	getEnumEntryListFromDevice(PIXELFORMATFEATURE, m_listPixelFormat);
	bResult = getEnumValueFromDevice(PIXELFORMATFEATURE, m_strPixelFormat);
	if (!bResult)
	{
		return false;
	}
	judgeColor();

	return true;
}

bool QSentechCamera::getBooleanParamFromDevice(const QString & strParamName, bool & bValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	PvResult lResult = m_pGenParameterArray->GetBooleanValue(pvstrParamName, bValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::setBooleanParamToDevice(const QString & strParamName, bool bValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	PvResult lResult = m_pGenParameterArray->SetBooleanValue(pvstrParamName, bValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::imageConventer(PvBuffer * pBuffer)
{
	PvPixelType pixelTypeSrc = pBuffer->GetImage()->GetPixelType();
	PvPixelType pixelTypeDst = SenColorPixelType;
	if(!m_bColor)
	{
		pixelTypeDst = SenGrayPixelType;
	}

	if(pixelTypeSrc != pixelTypeDst)
	{
		//PvBufferConverter bufferConverter(16);

		if(m_pBufferConventer->IsConversionSupported(pixelTypeSrc, pixelTypeDst))
		{
			m_mutexOperateBuffer.lock();
			m_pBufferConventer->Convert(pBuffer, m_convertedImage.pBuffer);
			m_mutexOperateBuffer.unlock();
		}
		else
		{
			return false;
		}
	}
	else
	{
		m_mutexOperateBuffer.lock();
		memcpy(m_convertedImage.pBuffer->GetDataPointer(), pBuffer->GetDataPointer(), m_convertedImage.ullImageSize);
		m_mutexOperateBuffer.unlock();
	}

	if(m_convertedImage.bRefreshDealImg)
	{
		m_convertedImage.bRefreshDealImg = false;
		memcpy(m_convertedImage.pDealImage, m_convertedImage.pBuffer->GetDataPointer(), m_convertedImage.ullImageSize);
		emit sig_takeAPhotoCompleted();
	}

	return true;
}

bool QSentechCamera::getIntegerParamFromDevice(const QString & strParamName, qint64 & paramValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	PvResult lResult = m_pGenParameterArray->GetIntegerValue(pvstrParamName, paramValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::getIntegerParamFromDevice(const QString & strParamName, qint32 & paramValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	qint64 llParamValue;
	PvResult lResult = m_pGenParameterArray->GetIntegerValue(pvstrParamName, llParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	paramValue = static_cast<qint32>(llParamValue);

	return true;
}

bool QSentechCamera::getIntegerRangeFromDevice(const QString & strParamName, qint64 & llMinValue, qint64 & llMaxValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	PvResult lResult = m_pGenParameterArray->GetIntegerRange(pvstrParamName, llMinValue, llMaxValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::getIntegerRangeFromDevice(const QString & strParamName, qint32 & llMinValue, qint32 & llMaxValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	qint64 llMinValueTemp;
	qint64 llMaxValueTemp;
	PvResult lResult = m_pGenParameterArray->GetIntegerRange(pvstrParamName, llMinValueTemp, llMaxValueTemp);
	if (!lResult.IsOK())
	{
		return false;
	}

	llMinValue = static_cast<qint32>(llMinValueTemp);
	llMaxValue = static_cast<qint32>(llMaxValueTemp);

	return true;
}

bool QSentechCamera::setIntegerParamToDevice(const QString & strParamName, qint64 llParameValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	PvResult lResult = m_pGenParameterArray->SetIntegerValue(pvstrParamName, llParameValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::getFloatParamFromDevice(const QString & strParamName, double & dParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	PvResult lResult = m_pGenParameterArray->GetFloatValue(pvstrParamName, dParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::getFloatParamFromDevice(const QString & strParamName, float & fParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	double dParamValue = 0;
	PvResult lResult = m_pGenParameterArray->GetFloatValue(pvstrParamName, dParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	fParamValue = static_cast<float>(dParamValue);

	return true;
}

bool QSentechCamera::getFloatRangeFromDevice(const QString & strParamName, double & dMinValue, double & dMaxValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	PvResult lResult = m_pGenParameterArray->GetFloatRange(pvstrParamName, dMinValue, dMaxValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::getFloatRangeFromDevice(const QString & strParamName, float & fMinValue, float & fMaxValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);

	double dMinValueTemp;
	double dMaxValueTemp;
	PvResult lResult = m_pGenParameterArray->GetFloatRange(pvstrParamName, dMinValueTemp, dMaxValueTemp);
	if (!lResult.IsOK())
	{
		return false;
	}

	fMinValue = static_cast<float>(dMinValueTemp);
	fMaxValue = static_cast<float>(dMaxValueTemp);

	return true;
}

bool QSentechCamera::setFloatParamToDevice(const QString & strParamName, double dParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	PvResult lResult = m_pGenParameterArray->SetFloatValue(pvstrParamName, dParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::getEnumEntryListFromDevice(const QString & strParamName, QList<QString>& listParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	listParamValue.clear();
	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	PvGenEnum *pEnum = m_pGenParameterArray->GetEnum(pvstrParamName);
	if(pEnum == nullptr)
	{
		return false;
	}
	PvResult lResult;
	qint64 llEntryNum = 0;
	pEnum->GetEntriesCount(llEntryNum);
	for (int nCounter = 0; nCounter < llEntryNum; nCounter++)
	{
		const PvGenEnumEntry *pEnumEntry = nullptr;
		lResult = pEnum->GetEntryByIndex(nCounter, &pEnumEntry);
		if(!lResult.IsOK())
		{
			return false;
		}
		PvString strEntry;
		lResult = pEnumEntry->GetName(strEntry);
		if(!lResult.IsOK())
		{
			return false;
		}
		QString strTargetEntry;
		PvString2QString(strEntry, strTargetEntry);
		listParamValue << strTargetEntry;
	}

	return true;
}

bool QSentechCamera::getEnumValueFromDevice(const QString & strParamName, QString & strParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	PvString pvsstrParamValue;
	PvResult lResult = m_pGenParameterArray->GetEnumValue(pvstrParamName, pvsstrParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}
	PvString2QString(pvsstrParamValue, strParamValue);

	return true;
}

bool QSentechCamera::setEnumValueToDevice(const QString & strParamName, QString strParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	PvString pvstrParamValue;
	QString2PvString(strParamName, pvstrParamName);
	QString2PvString(strParamValue, pvstrParamValue);
	PvResult lResult = m_pGenParameterArray->SetEnumValue(pvstrParamName, pvstrParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	return true;
}

bool QSentechCamera::excuteCommandToDevice(const QString & strParamName)
{
	if(m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	QString2PvString(strParamName, pvstrParamName);
	PvResult lResult = m_pGenParameterArray->ExecuteCommand(pvstrParamName);
	if(!lResult.IsOK())
	{
		return false;
	}

	return false;
}

bool QSentechCamera::getStringParamFromDevice(const QString & strParamName, QString & strParamValue)
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	PvString pvstrParamName;
	PvString pvstrParamValue;
	QString2PvString(strParamName, pvstrParamName);
	PvResult lResult = m_pGenParameterArray->GetString(pvstrParamName, pvstrParamValue);
	if (!lResult.IsOK())
	{
		return false;
	}

	PvString2QString(pvstrParamValue, strParamValue);

	return true;
}

void QSentechCamera::setInterfaceType(InterfaceType interfaceType)
{
	m_enumInterfaceType = interfaceType;
}

QSentechCamera::InterfaceType QSentechCamera::getInterfaceType() const
{
	return m_enumInterfaceType;
}

bool QSentechCamera::allocateMemoryForImage()
{
	if (m_pGenParameterArray == nullptr)
	{
		return false;
	}

	bool bResult = false;

	bResult = getIntegerParamFromDevice(WIDTHFEATURE, m_nImageWidth);
	if (!bResult)
	{
		return false;
	}

	bResult = getIntegerParamFromDevice(HEIGHTFEATURE, m_nImageHeight);
	if (!bResult)
	{
		return false;
	}

	bResult = getEnumValueFromDevice(PIXELFORMATFEATURE, m_strPixelFormat);
	if (!bResult)
	{
		return false;
	}
	judgeColor();

	freeMemoryForImage();

	PvImage *pImage = m_convertedImage.pBuffer->GetImage();
	PvResult lResult;

	if(m_bColor)
	{
		m_convertedImage.ullImageSize = m_nImageWidth * m_nImageHeight * ColorChannels;
		lResult = pImage->Alloc(m_nImageWidth, m_nImageHeight, SenColorPixelType);
	}
	else
	{
		m_convertedImage.ullImageSize = m_nImageWidth * m_nImageHeight * GrayChannels;
		lResult = pImage->Alloc(m_nImageWidth, m_nImageHeight, SenGrayPixelType);
	}

	if (lResult.IsOK())
	{
		m_convertedImage.pDealImage = new quint8[m_convertedImage.ullImageSize];
		memset(m_convertedImage.pBuffer->GetDataPointer(), 0, m_convertedImage.ullImageSize);
		memset(m_convertedImage.pDealImage, 0, m_convertedImage.ullImageSize);
	}	
	else
	{
		freeMemoryForImage();
		return false;
	}

	return true;
}

void QSentechCamera::freeMemoryForImage()
{
	m_convertedImage.pBuffer->Free();
	m_convertedImage.ullImageSize = 0;

	if(m_convertedImage.pDealImage)
	{
		delete []m_convertedImage.pDealImage;
		m_convertedImage.pDealImage = nullptr;
	}
}

const quint8 * QSentechCamera::getImageBuffer() const
{
	return m_convertedImage.pBuffer->GetDataPointer();
}

void QSentechCamera::operateBufferLock()
{
	m_mutexOperateBuffer.lock();
}

void QSentechCamera::operateBufferUnlock()
{
	m_mutexOperateBuffer.unlock();
}

void QSentechCamera::detachLock()
{
	m_mutexDetachShowDlg.lock();
}

void QSentechCamera::detachUnlock()
{
	m_mutexDetachShowDlg.unlock();
}

quint8 * QSentechCamera::getDealImgBuffer() const
{
	return m_convertedImage.pDealImage;
}

void QSentechCamera::getAcquistionRate(double & dFPS)
{
	m_plFrameRate->GetValue(dFPS);
}

void QSentechCamera::takeAPhoto()
{
	m_convertedImage.bRefreshDealImg = true;
}

void QSentechCamera::slot_takeAPhoto()
{
	m_convertedImage.bRefreshDealImg = true;
}
