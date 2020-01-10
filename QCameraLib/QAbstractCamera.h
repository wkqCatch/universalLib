#pragma once

#include "qcameralib_global.h"

#include <QObject>

//各个参数名称
//integer
#define	WIDTHFEATURE				"Width"
#define OFFSETX						"OffsetX"
#define HEIGHTFEATURE				"Height"
#define OFFSETY						"OffsetY"

//string
#define DEVICEVENDORNAMEFEATURE		"DeviceVendorName"
#define DEVICEMODELNAMEFEATURE	    "DeviceModelName"

//float
#define EXPOSURETIMEFEATURE	        "ExposureTime"
#define ACQUISITIONRATEFEATURE	    "AcquisitionFrameRate"

//enum
#define BALANCEWHITEAUTOFEATURE		"BalanceWhiteAuto"
#define PIXELFORMATFEATURE			"PixelFormat"
#define TRIGGERSOURCEFEATURE		"TriggerSource"
#define TRIGGERMODEFEATURE			"TriggerMode"

//boolean
#define	ACQUISITIONRATEENABLEFEATURE "AcquisitionFrameRateEnable"   //允许更改采集频率

class QCAMERALIB_EXPORT QAbstractCamera : public QObject
{
	Q_OBJECT

public:
	QAbstractCamera(QObject *pParent = nullptr);
	virtual ~QAbstractCamera();

	void setDeviceIP(const QString &strDeviceIP);
	const QString& getDeviceIP();
	void setDeviceMAC(const QString &strDeviceMAC);
	const QString& getDeviceMAC();
	void setDeviceSerialNum(const QString &strDeviceSerialNum);
	const QString& getDeviceSerialNum();
	void setDeviceDescribe(const QString &strDeviceDescribe);
	const QString& getDeviceDescribe();

	void setDeviceVendorName(const QString &strVendorName);
	const QString& getDeviceVendorName() const;						//获取厂商名字
	void setDeviceModelName(const QString &strModelName);				
	const QString& getDeviceModelName() const;					   //获取模型名字

	void setInterfaceIP(const QString &strInterfaceIP);
	const QString& getInterfaceIP();
	void setInterfaceMAC(const QString &strInterfaceMAC);
	const QString& getInterfaceMAC();

	static bool setNewIPByAddOne(QString &strOldIP, QString &strNewIP);

	int getImageWidth() const;							//获取相机图像的宽度
	void setImageWidth(int nWidth);						//设置相机图像的宽度
	int getMinWidth() const;							//获取最小宽度
	void setMinWidth(int nMinWidth);
	int getMaxWidth() const;
	void setMaxWidth(int nMaxWidth);

	int getOffsetX() const;
	void setOffsetX(int nOffsetX);
	int getMinOffsetX() const;
	void setMinOffsetX(int nMinOffsetX);
	int getMaxOffsetX() const;
	void setMaxOffsetX(int nMaxOffsetX);

	int getOffsetY() const;
	void setOffsetY(int nOffsetY);
	int getMinOffsetY() const;
	void setMinOffsetY(int nMinOffsetY);
	int getMaxOffsetY() const;
	void setMaxOffsetY(int nMaxOffsetY);

	int getImageHeight() const;							//获取相机图像的高度
	void setImageHeight(int nHeight);					//设置相机图像的高度
	int getMinHeight() const;
	void setMinHeight(int nMinHeight);
	int getMaxHeight() const;
	void setMaxHeight(int nMaxHeight);

	float	getExposureTime() const;					//获取曝光时间
	void    setExposureTime(float fExposureTime);       //设置曝光时间
	float   getMinExposureTime() const;					//获取最小曝光时间
	void    setMinExposureTime(float fMinExposureTime);
	float   getMaxExposureTime() const;
	void    setMaxExposureTime(float fMaxExposureTime);

	float   getAcquisitionFrameRate() const;			//获取采集频率
	void    setAcquisitionFrameRate(float fFrameRate);  //设置采集频率
	float	getMinAcquisitionRate() const;
	void	setMinAcquisitionRate(float fMinAcquisitionRate);
	float   getMaxAcquisitionRate() const;
	void	setMaxAcquisitionRate(float fMaxAcquisitionRate);

	void	judgeColor();								//判断是否是彩色图像
	bool    isColor() const;                            //是否是彩色模式

	QList<QString> getBalanceAutoList() const;							//获取白平衡名称列表
	QString        getBalanceWhiteAuto() const;							//获取当前白平衡模式
	void           setBalanceWhiteAuto(QString strBalanceWhiteAuto);	//设置白平衡

	QList<QString> getPixelFormatList() const;					//获取像素格式列表
	QString        getPixelFormat() const;						//获取像素格式
	void		   setPixelFormat(QString strPixelFormat);		//设置像素格式		

	QList<QString> getTriggerSourceList() const;				//获取触发源的列表
	QString		   getTriggerSource() const;					//获取当前触发源
	void		   setTriggerSource(QString strTriggerSource);	//设置当前触发源

	bool		   isTriggerMode() const;						//是否处于触发模式
	bool		   setTriggerMode(bool bTriggerMode);			//设置是否开启触发模式
	bool		   excuteTriggerSoftware();						//执行软件触发

	virtual bool getBooleanParamFromDevice(const QString &strParamName, bool &bValue);
	virtual bool setBooleanParamToDevice(const QString &strParamName, bool bValue);              //设置bool参数到硬件

	virtual bool getIntegerParamFromDevice(const QString &strParamName, qint64 &llparamValue);   //获取整型参数
	virtual bool getIntegerParamFromDevice(const QString &strParamName, qint32 &nparamValue);
	virtual bool getIntegerRangeFromDevice(const QString &strParamName, qint64 &llMinValue, qint64 &llMaxValue);
	virtual bool getIntegerRangeFromDevice(const QString &strParamName, qint32 &llMinValue, qint32 &llMaxValue);
	virtual bool setIntegerParamToDevice(const QString &strParamName, qint64 llParameValue);     //设置字符型参数

	virtual bool getStringParamFromDevice(const QString &strParamName, QString &strParamValue);  //获取字符型参数

	virtual bool getFloatParamFromDevice(const QString &strParamName, double &dParamValue);      //获取浮点型变量
	virtual bool getFloatParamFromDevice(const QString &strParamName, float &fParamValue);
	virtual bool getFloatRangeFromDevice(const QString &strParamName, double &dMinValue, double &dMaxValue);
	virtual bool getFloatRangeFromDevice(const QString &strParamName, float &fMinValue, float &fMaxValue);
	virtual bool setFloatParamToDevice(const QString &strParamName, double dParamValue);		 //设置浮点型变量

	virtual bool getEnumEntryListFromDevice(const QString &strParamName, QList<QString> &listParamValue);  //获取枚举的字符串集合
	virtual bool getEnumValueFromDevice(const QString &strParamName, QString &strParamValue);			   //获取枚举的字符串值
	virtual bool setEnumValueToDevice(const QString &strParamName, QString strParamValue);				   //设置当前的枚举值

	virtual bool excuteCommandToDevice(const QString &strParamName);									   //执行命令

	virtual bool updateDeviceParam();																	   //更新硬件的各种信息

	void setCountScaledWidth(bool bCount);
	bool isCountScaledWidth() const;

	void setFPS(double dFPS);    //设置PFS
	double getPFS() const;

	void setProgramerPower(bool bState);   //设置开发者权限
	bool isProgramerPower() const;		   //是否是开发者权限

protected:
	QString m_strDeviceIP;					//相机硬件IP
	QString m_strDeviceMAC;					//相机硬件MAC
	QString m_strDeviceSerialNum;			//相机序列号

	QString m_strDeviceDescribe;			//相机描述

	QString m_strDeviceVendorName;			//厂商名字
	QString m_strDeviceModelName;			//模型名字
	
	QString m_strInterfaceIP;				//相机接口IP
	QString m_strInterfaceMAC;				//相机接口MAC

	int		m_nImageWidth;					//图像的宽度
	int     m_nMinWidth;					//最小宽度
	int		m_nMaxWidth;					//最大宽度

	int     m_nOffsetX;						//X方向的偏移
	int     m_nMinOffsetX;
	int		m_nMaxOffsetX;

	int		m_nImageHeight;					//图像的高度
	int		m_nMinHeight;					//最小高度
	int		m_nMaxHeight;					//最大高度

	int		m_nOffsetY;
	int		m_nMinOffsetY;
	int		m_nMaxOffsetY;

	float      m_fExposureTime;				//曝光时间
	float      m_fMinExposureTime;			//最小曝光时间
	float      m_fMaxExposureTime;			//最大曝光时间
	float      m_fAcquisitionFrameRate;		//采集频率
	float      m_fMinAcquisitionRate;		//最小采集频率
	float      m_fMaxAcquisitionRate;		//最大采集频率

	double     m_dFPS;						//实际采集平均频率

	QString    m_strBalanceWhiteAuto;       //白平衡模式
	QList<QString> m_listBalanceWhiteAuto;  //白平衡列表

	QString   m_strPixelFormat;             //当前像素格式
	QList<QString> m_listPixelFormat;       //像素格式列表

	bool      m_bTriggerMode;				//是否是触发模式

	QString   m_strTriggerSource;			//当前触发源
	QList<QString> m_listTriggerSource;		//触发源列表

	bool	  m_bColor;						//是否是彩色相机

	bool	  m_bCountScaledWidth;			//需要计算缩放比列

	bool	  m_bProgramerPower;			//开发者权限
};

