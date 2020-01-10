#include "QAbstractCamera.h"
#include <PvBuffer.h>

QAbstractCamera::QAbstractCamera(QObject *pParent)
	: QObject(pParent)
	, m_nImageWidth(0)
	, m_nMinWidth(0)
	, m_nMaxWidth(0)
	, m_nOffsetX(0)
	, m_nMinOffsetX(0)
	, m_nMaxOffsetX(0)
	, m_nOffsetY(0)
	, m_nMinOffsetY(0)
	, m_nMaxOffsetY(0)
	, m_nImageHeight(0)
	, m_nMinHeight(0)
	, m_nMaxHeight(0)
	, m_fExposureTime(0.0f)
	, m_fMinExposureTime(0.0f)
	, m_fMaxExposureTime(0.0f)
	, m_fAcquisitionFrameRate(0.0f)
	, m_fMinAcquisitionRate(0.0f)
	, m_fMaxAcquisitionRate(0.0f)
	, m_bColor(false)
	, m_bTriggerMode(false)
	, m_bCountScaledWidth(false)
	, m_dFPS(0.0)
	, m_bProgramerPower(false)
{
	
}

QAbstractCamera::~QAbstractCamera()
{

}

void QAbstractCamera::setDeviceIP(const QString & strDeviceIP)
{
	m_strDeviceIP = strDeviceIP;
}

const QString & QAbstractCamera::getDeviceIP()
{
	// TODO: 在此处插入 return 语句
	return m_strDeviceIP;
}

void QAbstractCamera::setDeviceMAC(const QString & strDeviceMAC)
{
	m_strDeviceMAC = strDeviceMAC;
}

const QString & QAbstractCamera::getDeviceMAC()
{
	// TODO: 在此处插入 return 语句
	return m_strDeviceMAC;
}

void QAbstractCamera::setDeviceSerialNum(const QString & strDeviceSerialNum)
{
	m_strDeviceSerialNum = strDeviceSerialNum;
}

const QString & QAbstractCamera::getDeviceSerialNum()
{
	// TODO: 在此处插入 return 语句
	return m_strDeviceSerialNum;
}

void QAbstractCamera::setDeviceDescribe(const QString & strDeviceDescribe)
{
	m_strDeviceDescribe = strDeviceDescribe;
}

const QString & QAbstractCamera::getDeviceDescribe()
{
	// TODO: 在此处插入 return 语句
	return m_strDeviceDescribe;
}

void QAbstractCamera::setInterfaceIP(const QString & strInterfaceIP)
{
	m_strInterfaceIP = strInterfaceIP;
}

const QString & QAbstractCamera::getInterfaceIP()
{
	// TODO: 在此处插入 return 语句
	return m_strInterfaceIP;
}

void QAbstractCamera::setInterfaceMAC(const QString & strInterfaceMAC)
{
	m_strInterfaceMAC = strInterfaceMAC;
}

const QString & QAbstractCamera::getInterfaceMAC()
{
	// TODO: 在此处插入 return 语句
	return m_strInterfaceMAC;
}

bool QAbstractCamera::setNewIPByAddOne(QString & strOldIP, QString & strNewIP)
{
	int nFirst = strOldIP.indexOf(QChar('.'), 0);
	if(nFirst < 0)
	{
		return false;
	}

	int nSecond = strOldIP.indexOf(QChar('.'), nFirst + 1);
	if(nSecond < 0)
	{
		return false;
	}

	int nThird = strOldIP.indexOf(QChar('.'), nSecond + 1);
	if(nThird < 0)
	{
		return false;
	}

	bool bOK = false;

	QString strFirstNum = strOldIP.mid(0, nFirst);
	int nFirstNum = strFirstNum.toUInt(&bOK);
	if(!bOK)
	{
		return false;
	}

	QString strSecondNum = strOldIP.mid(nFirst + 1, nSecond - nFirst - 1);
	int nSecondNum = strSecondNum.toUInt(&bOK);
	if(!bOK)
	{
		return false;
	}

	QString strThirdNum = strOldIP.mid(nSecond + 1, nThird - nSecond - 1);
	int nThirdNum = strThirdNum.toUInt(&bOK);
	if(!bOK)
	{
		return false;
	}

	QString strForthNum = strOldIP.mid(nThird + 1);
	int nForthNum = strForthNum.toUInt(&bOK);
	if(!bOK)
	{
		return false;
	}

	nForthNum++;
	if(nForthNum > 254)
	{
		nForthNum -= 2;
	}

	strNewIP = strFirstNum + '.' + strSecondNum + '.' + strThirdNum + '.' + QString::number(nForthNum);	

	return true;
}

int QAbstractCamera::getImageWidth() const
{
	return m_nImageWidth;
}

void QAbstractCamera::setImageWidth(int nWidth)
{
	m_nImageWidth = nWidth;
}

int QAbstractCamera::getMinWidth() const
{
	return m_nMinWidth;
}

void QAbstractCamera::setMinWidth(int nMinWidth)
{
	m_nMinWidth = nMinWidth;
}

int QAbstractCamera::getMaxWidth() const
{
	return m_nMaxWidth;
}

void QAbstractCamera::setMaxWidth(int nMaxWidth)
{
	m_nMaxWidth = nMaxWidth;
}

int QAbstractCamera::getOffsetX() const
{
	return m_nOffsetX;
}

void QAbstractCamera::setOffsetX(int nOffsetX)
{
	m_nOffsetX = nOffsetX;
}

int QAbstractCamera::getMinOffsetX() const
{
	return m_nMinOffsetX;
}

void QAbstractCamera::setMinOffsetX(int nMinOffsetX)
{
	m_nMinOffsetX = nMinOffsetX;
}

int QAbstractCamera::getMaxOffsetX() const
{
	return m_nMaxOffsetX;
}

void QAbstractCamera::setMaxOffsetX(int nMaxOffsetX)
{
	m_nMaxOffsetX = nMaxOffsetX;
}

int QAbstractCamera::getOffsetY() const
{
	return m_nOffsetY;
}

void QAbstractCamera::setOffsetY(int nOffsetY)
{
	m_nOffsetY = nOffsetY;
}

int QAbstractCamera::getMinOffsetY() const
{
	return m_nMinOffsetY;
}

void QAbstractCamera::setMinOffsetY(int nMinOffsetY)
{
	m_nMinOffsetY = nMinOffsetY;
}

int QAbstractCamera::getMaxOffsetY() const
{
	return m_nMaxOffsetY;
}

void QAbstractCamera::setMaxOffsetY(int nMaxOffsetY)
{
	m_nMaxOffsetY = nMaxOffsetY;
}

int QAbstractCamera::getImageHeight() const
{
	return m_nImageHeight;
}

void QAbstractCamera::setImageHeight(int nHeight)
{
	m_nImageHeight = nHeight;
}

int QAbstractCamera::getMinHeight() const
{
	return m_nMinHeight;
}

void QAbstractCamera::setMinHeight(int nMinHeight)
{
	m_nMinHeight = nMinHeight;
}

int QAbstractCamera::getMaxHeight() const
{
	return m_nMaxHeight;
}

void QAbstractCamera::setMaxHeight(int nMaxHeight)
{
	m_nMaxHeight = nMaxHeight;
}

bool QAbstractCamera::getIntegerParamFromDevice(const QString & strParamName, qint64 & paramValue)
{
	return false;
}

bool QAbstractCamera::getIntegerParamFromDevice(const QString & strParamName, qint32 & paramValue)
{
	return false;
}

bool QAbstractCamera::getIntegerRangeFromDevice(const QString & strParamName, qint64 & llMinValue, qint64 & llMaxValue)
{
	return false;
}

bool QAbstractCamera::getIntegerRangeFromDevice(const QString & strParamName, qint32 & llMinValue, qint32 & llMaxValue)
{
	return false;
}

bool QAbstractCamera::setIntegerParamToDevice(const QString & strParamName, qint64 llParameValue)
{
	return false;
}

void QAbstractCamera::setDeviceVendorName(const QString & strVendorName)
{
	m_strDeviceVendorName = strVendorName;
}

const QString& QAbstractCamera::getDeviceVendorName() const
{
	return m_strDeviceVendorName;
}

void QAbstractCamera::setDeviceModelName(const QString & strModelName)
{
	m_strDeviceModelName = strModelName;
}

const QString& QAbstractCamera::getDeviceModelName() const
{
	return m_strDeviceModelName;
}

bool QAbstractCamera::getStringParamFromDevice(const QString & strParamName, QString & strParamValue)
{
	return false;
}

bool QAbstractCamera::getFloatParamFromDevice(const QString & strParamName, double & dParamValue)
{
	return false;
}

bool QAbstractCamera::getFloatParamFromDevice(const QString & strParamName, float & fParamValue)
{
	return false;
}

bool QAbstractCamera::getFloatRangeFromDevice(const QString & strParamName, double & dMinValue, double & dMaxValue)
{
	return false;
}

bool QAbstractCamera::getFloatRangeFromDevice(const QString & strParamName, float & fMinValue, float & fMaxValue)
{
	return false;
}

bool QAbstractCamera::setFloatParamToDevice(const QString & strParamName, double dParamValue)
{
	return false;
}

bool QAbstractCamera::getEnumEntryListFromDevice(const QString & strParamName, QList<QString>& listParamValue)
{
	return false;
}

bool QAbstractCamera::getEnumValueFromDevice(const QString & strParamName, QString & strParamValue)
{
	return false;
}

bool QAbstractCamera::setEnumValueToDevice(const QString & strParamName, QString strParamValue)
{
	return false;
}

bool QAbstractCamera::excuteCommandToDevice(const QString & strParamName)
{
	return false;
}

float QAbstractCamera::getExposureTime() const
{
	return m_fExposureTime;
}

void QAbstractCamera::setExposureTime(float fExposureTime)
{
	m_fExposureTime = fExposureTime;
}

float QAbstractCamera::getMinExposureTime() const
{
	return m_fMinExposureTime;
}

void QAbstractCamera::setMinExposureTime(float fMinExposureTime)
{
	m_fMinExposureTime = fMinExposureTime;
}

float QAbstractCamera::getMaxExposureTime() const
{
	return m_fMaxExposureTime;
}

void QAbstractCamera::setMaxExposureTime(float fMaxExposureTime)
{
	m_fMaxExposureTime = fMaxExposureTime;
}

float QAbstractCamera::getAcquisitionFrameRate() const
{
	return m_fAcquisitionFrameRate;
}

void QAbstractCamera::setAcquisitionFrameRate(float fFrameRate)
{
	m_fAcquisitionFrameRate = fFrameRate;
}

float QAbstractCamera::getMinAcquisitionRate() const
{
	return m_fMinAcquisitionRate;
}

void QAbstractCamera::setMinAcquisitionRate(float fMinAcquisitionRate)
{
	m_fMinAcquisitionRate = fMinAcquisitionRate;
}

float QAbstractCamera::getMaxAcquisitionRate() const
{
	return m_fMaxAcquisitionRate;
}

void QAbstractCamera::setMaxAcquisitionRate(float fMaxAcquisitionRate)
{
	m_fMaxAcquisitionRate = fMaxAcquisitionRate;
}

void QAbstractCamera::judgeColor()
{
	if(m_strPixelFormat.startsWith("Mono"))
	{
		m_bColor = false;
	}
	else
	{
		m_bColor = true;           //彩色相机
	}
}

bool QAbstractCamera::isColor() const
{
	return m_bColor;
}

QList<QString> QAbstractCamera::getBalanceAutoList() const
{
	return m_listBalanceWhiteAuto;
}

QString QAbstractCamera::getBalanceWhiteAuto() const
{
	return m_strBalanceWhiteAuto;
}

void QAbstractCamera::setBalanceWhiteAuto(QString strBalanceWhiteAuto)
{
	m_strBalanceWhiteAuto = strBalanceWhiteAuto;
}

QList<QString> QAbstractCamera::getPixelFormatList() const
{
	return m_listPixelFormat;
}

QString QAbstractCamera::getPixelFormat() const
{
	return m_strPixelFormat;
}

void QAbstractCamera::setPixelFormat(QString strPixelFormat)
{
	m_strPixelFormat = strPixelFormat;
}

QList<QString> QAbstractCamera::getTriggerSourceList() const
{
	return m_listTriggerSource;
}

QString QAbstractCamera::getTriggerSource() const
{
	return m_strTriggerSource;
}

void QAbstractCamera::setTriggerSource(QString strTriggerSource)
{
	m_strTriggerSource = strTriggerSource;
}

bool QAbstractCamera::isTriggerMode() const
{
	return m_bTriggerMode;
}

bool QAbstractCamera::setTriggerMode(bool bTriggerMode)
{
	bool bResult = false;
	if(bTriggerMode)
	{
		bResult = setEnumValueToDevice("TriggerMode", "On");
	}
	else
	{
		bResult = setEnumValueToDevice("TriggerMode", "Off");
	}

	if(!bResult)
	{
		return false;
	}

	m_bTriggerMode = bTriggerMode;

	return true;
}

bool QAbstractCamera::excuteTriggerSoftware()
{
	if(!m_bTriggerMode)
	{
		return false;
	}

	bool bResult = excuteCommandToDevice("TriggerSoftware");
	if(!bResult)
	{
		return false;
	}

	return true;
}

bool QAbstractCamera::getBooleanParamFromDevice(const QString & strParamName, bool & bValue)
{
	return false;
}

bool QAbstractCamera::setBooleanParamToDevice(const QString & strParamName, bool bValue)
{
	return false;
}

bool QAbstractCamera::updateDeviceParam()
{
	return true;
}

void QAbstractCamera::setCountScaledWidth(bool bCount)
{
	m_bCountScaledWidth = bCount;
}

bool QAbstractCamera::isCountScaledWidth() const
{
	return m_bCountScaledWidth;
}

void QAbstractCamera::setFPS(double dFPS)
{
	m_dFPS = dFPS;
}

double QAbstractCamera::getPFS() const
{
	return m_dFPS;
}

void QAbstractCamera::setProgramerPower(bool bState)
{
	m_bProgramerPower = bState;
}

bool QAbstractCamera::isProgramerPower() const
{
	return m_bProgramerPower;
}
