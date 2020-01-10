#pragma once

#include "QAbstractCamera.h"

#include <QMutex>

class PvBuffer;
class ListenerBase 
{
public:
	virtual void Invoke(PvBuffer* pBuffer, void *pUser) = 0;
};

template <class T>
class MemFuncListener : public ListenerBase
{
public:
	MemFuncListener(T* obj, void (T::*cbf)(PvBuffer*, void *)) {
		m_obj = obj;
		m_cbf = cbf;
	};

	virtual void Invoke(PvBuffer* pBuffer, void *pUser)
	{
		(m_obj->*m_cbf)(pBuffer, pUser);
	};

private:
	T* m_obj;
	void (T::*m_cbf)(PvBuffer*, void *);
};

class PvPipeline;
class PvStream;
class PvDevice;
class PvAcquisitionStateManager;
class PvDeviceInfo;
class PvString;
class PvGenParameterArray;
class QSentechCallbackThread;
class PvBufferConverter;
class PvGenFloat;
class QCAMERALIB_EXPORT QSentechCamera : public QAbstractCamera
{
	Q_OBJECT

public:
	enum InterfaceType{NETWORK, EBUS};

	struct convertedImage
	{
		PvBuffer *pBuffer;         //用于显示的缓存
		quint8   *pDealImage;	   //用来进行处理的图像
		qint64    ullImageSize;
		bool	  bRefreshDealImg; //是否刷新待处理的图像缓存
	};

	QSentechCamera(QObject *parent = nullptr);
	~QSentechCamera();

	bool connectDevice(const PvDeviceInfo *pDeviceInfo, int nAccessType = 1);   //连接相机硬件
	bool connectDevice(const QString &strInfo, int nAccessType = 1);
	bool isConnected() const;                                                   //是否已经连接
	bool isIPEngine() const;                                                    //是否用了IP引擎

	void disconnectDevice();                                                    //断开相机连接

	bool openPipeline();                                                        //打开管道
	void closePipeline();														//关闭管道
	PvPipeline* getPipeline() const;											//获取管道

	bool startAcquisition();													//开始获取图像
	void stopAcquisition();                                                     //停止获取图像
	bool isStartedAcquisition() const;                                          //是否已经开始获取

	static QString PvString2QString(const PvString &strSource);						//PvString 转换为 QString

	static void QString2PvString(const QString &strSource, PvString &strTarget);		//QString 转换为 PvString
	static void PvString2QString(const PvString &strSource, QString &strTarget);		//PvString 转换为 QString

	PvGenParameterArray* getGenParameter() const; //Get the parameters used to control the GigE Vision device to which you are connected
	PvGenParameterArray* getGenLink() const;	  //Get the parameters used to define how PvDevice connects to and communicates with the device.
	PvGenParameterArray* getStreamParameter() const; //Get the parameters defining how data is received from a GigE Vision transmitter. 

	qint64 getPayloadSize();														//获取负载

	void onImageCallback(PvBuffer *pBuffer);										//图像回调		

	template <class T>
	void RegisterCallback(T *obj, void (T::*cbf)(PvBuffer*, void *), void *pUser)	//注册回调函数
	{
		UnregisterCallback();
		m_Listener = new MemFuncListener<T>(obj, cbf);
		m_pUser = pUser;
	}

	void UnregisterCallback()														//取消注册回调函数
	{
		if (m_Listener)
		{
			delete m_Listener;
			m_Listener = NULL;
		}
		m_pUser = NULL;
	}

	bool updateDeviceParam() override;

	bool getBooleanParamFromDevice(const QString &strParamName, bool &bValue) override;
	bool setBooleanParamToDevice(const QString &strParamName, bool bValue) override;              //设置bool参数到硬件

	bool getIntegerParamFromDevice(const QString &strParamName, qint64 &paramValue) override;
	bool getIntegerParamFromDevice(const QString &strParamName, qint32 &paramValue) override;
	bool getIntegerRangeFromDevice(const QString &strParamName, qint64 &llMinValue, qint64 &llMaxValue) override;
	bool getIntegerRangeFromDevice(const QString &strParamName, qint32 &llMinValue, qint32 &llMaxValue) override;
	bool setIntegerParamToDevice(const QString &strParamName, qint64 llParameValue) override;

	bool getStringParamFromDevice(const QString &strParamName, QString &strParamValue) override;

	bool getFloatParamFromDevice(const QString &strParamName, double &dParamValue) override;				//获取浮点型变量
	bool getFloatParamFromDevice(const QString &strParamName, float &fParamValue) override;
	bool getFloatRangeFromDevice(const QString &strParamName, double &dMinValue, double &dMaxValue) override;
	bool getFloatRangeFromDevice(const QString &strParamName, float &fMinValue, float &fMaxValue) override;
	bool setFloatParamToDevice(const QString &strParamName, double dParamValue) override;					//设置浮点型变量

	bool getEnumEntryListFromDevice(const QString &strParamName, QList<QString> &listParamValue) override;  //获取枚举的字符串集合
	bool getEnumValueFromDevice(const QString &strParamName, QString &strParamValue) override;			    //获取枚举的字符串值
	bool setEnumValueToDevice(const QString &strParamName, QString strParamValue) override;				    //设置当前的枚举值

	bool excuteCommandToDevice(const QString &strParamName) override;										//执行命令

	void setInterfaceType(InterfaceType interfaceType);     //设置接口类型
	InterfaceType getInterfaceType() const;					//返回接口类型

	bool imageConventer(PvBuffer *pBuffer);					//图像转换
	bool allocateMemoryForImage();							//为转换后的图像获取内存
	void freeMemoryForImage();								//释放转后的图像的内存
	const quint8* getImageBuffer() const;					//获取转换后的图像的指针

	void operateBufferLock();								//操作内存上锁
	void operateBufferUnlock();								//操作内存解锁

	void detachLock();										//取消关联上锁
	void detachUnlock();									//取消关联解锁

	quint8* getDealImgBuffer() const;						//获取待处理的图片指针

	void getAcquistionRate(double &dFPS);	

	void takeAPhoto();										//拍照

signals:
	void sig_takeAPhotoCompleted();							//被处理的图片刷新完成

public slots:
	void slot_takeAPhoto();									//请求刷新被处理的图片

private:
	PvDevice *m_pDevice;									//相机硬件
	PvPipeline *m_pPipeline;								//相机管道
	PvStream  *m_pStream;									//相机流

	convertedImage			   m_convertedImage;			//转换后的图像

	PvBufferConverter         *m_pBufferConventer;			//buffer转换器

	PvAcquisitionStateManager *m_pAcquisitionStateManager;  //相机采集状态管理器

	QSentechCallbackThread    *m_pCallbackThread;           //回调线程

	PvGenParameterArray       *m_pGenParameterArray;        //Genicam的参数数组
	PvGenFloat				  *m_plFrameRate;				//采集频率指针,实时频率
	PvGenFloat				  *m_plFrameRateAverage;		//平均采集频率

	ListenerBase			  *m_Listener;                  //监听函数基类
	void                      *m_pUser;                     //用户指针

	InterfaceType              m_enumInterfaceType;         //接口的类型

	QMutex					   m_mutexOperateBuffer;		//操作buffer所需要的锁

	QMutex					   m_mutexDetachShowDlg;		//断开与显示对话框的关联
};
