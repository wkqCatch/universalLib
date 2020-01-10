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
		PvBuffer *pBuffer;         //������ʾ�Ļ���
		quint8   *pDealImage;	   //�������д����ͼ��
		qint64    ullImageSize;
		bool	  bRefreshDealImg; //�Ƿ�ˢ�´������ͼ�񻺴�
	};

	QSentechCamera(QObject *parent = nullptr);
	~QSentechCamera();

	bool connectDevice(const PvDeviceInfo *pDeviceInfo, int nAccessType = 1);   //�������Ӳ��
	bool connectDevice(const QString &strInfo, int nAccessType = 1);
	bool isConnected() const;                                                   //�Ƿ��Ѿ�����
	bool isIPEngine() const;                                                    //�Ƿ�����IP����

	void disconnectDevice();                                                    //�Ͽ��������

	bool openPipeline();                                                        //�򿪹ܵ�
	void closePipeline();														//�رչܵ�
	PvPipeline* getPipeline() const;											//��ȡ�ܵ�

	bool startAcquisition();													//��ʼ��ȡͼ��
	void stopAcquisition();                                                     //ֹͣ��ȡͼ��
	bool isStartedAcquisition() const;                                          //�Ƿ��Ѿ���ʼ��ȡ

	static QString PvString2QString(const PvString &strSource);						//PvString ת��Ϊ QString

	static void QString2PvString(const QString &strSource, PvString &strTarget);		//QString ת��Ϊ PvString
	static void PvString2QString(const PvString &strSource, QString &strTarget);		//PvString ת��Ϊ QString

	PvGenParameterArray* getGenParameter() const; //Get the parameters used to control the GigE Vision device to which you are connected
	PvGenParameterArray* getGenLink() const;	  //Get the parameters used to define how PvDevice connects to and communicates with the device.
	PvGenParameterArray* getStreamParameter() const; //Get the parameters defining how data is received from a GigE Vision transmitter. 

	qint64 getPayloadSize();														//��ȡ����

	void onImageCallback(PvBuffer *pBuffer);										//ͼ��ص�		

	template <class T>
	void RegisterCallback(T *obj, void (T::*cbf)(PvBuffer*, void *), void *pUser)	//ע��ص�����
	{
		UnregisterCallback();
		m_Listener = new MemFuncListener<T>(obj, cbf);
		m_pUser = pUser;
	}

	void UnregisterCallback()														//ȡ��ע��ص�����
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
	bool setBooleanParamToDevice(const QString &strParamName, bool bValue) override;              //����bool������Ӳ��

	bool getIntegerParamFromDevice(const QString &strParamName, qint64 &paramValue) override;
	bool getIntegerParamFromDevice(const QString &strParamName, qint32 &paramValue) override;
	bool getIntegerRangeFromDevice(const QString &strParamName, qint64 &llMinValue, qint64 &llMaxValue) override;
	bool getIntegerRangeFromDevice(const QString &strParamName, qint32 &llMinValue, qint32 &llMaxValue) override;
	bool setIntegerParamToDevice(const QString &strParamName, qint64 llParameValue) override;

	bool getStringParamFromDevice(const QString &strParamName, QString &strParamValue) override;

	bool getFloatParamFromDevice(const QString &strParamName, double &dParamValue) override;				//��ȡ�����ͱ���
	bool getFloatParamFromDevice(const QString &strParamName, float &fParamValue) override;
	bool getFloatRangeFromDevice(const QString &strParamName, double &dMinValue, double &dMaxValue) override;
	bool getFloatRangeFromDevice(const QString &strParamName, float &fMinValue, float &fMaxValue) override;
	bool setFloatParamToDevice(const QString &strParamName, double dParamValue) override;					//���ø����ͱ���

	bool getEnumEntryListFromDevice(const QString &strParamName, QList<QString> &listParamValue) override;  //��ȡö�ٵ��ַ�������
	bool getEnumValueFromDevice(const QString &strParamName, QString &strParamValue) override;			    //��ȡö�ٵ��ַ���ֵ
	bool setEnumValueToDevice(const QString &strParamName, QString strParamValue) override;				    //���õ�ǰ��ö��ֵ

	bool excuteCommandToDevice(const QString &strParamName) override;										//ִ������

	void setInterfaceType(InterfaceType interfaceType);     //���ýӿ�����
	InterfaceType getInterfaceType() const;					//���ؽӿ�����

	bool imageConventer(PvBuffer *pBuffer);					//ͼ��ת��
	bool allocateMemoryForImage();							//Ϊת�����ͼ���ȡ�ڴ�
	void freeMemoryForImage();								//�ͷ�ת���ͼ����ڴ�
	const quint8* getImageBuffer() const;					//��ȡת�����ͼ���ָ��

	void operateBufferLock();								//�����ڴ�����
	void operateBufferUnlock();								//�����ڴ����

	void detachLock();										//ȡ����������
	void detachUnlock();									//ȡ����������

	quint8* getDealImgBuffer() const;						//��ȡ�������ͼƬָ��

	void getAcquistionRate(double &dFPS);	

	void takeAPhoto();										//����

signals:
	void sig_takeAPhotoCompleted();							//�������ͼƬˢ�����

public slots:
	void slot_takeAPhoto();									//����ˢ�±������ͼƬ

private:
	PvDevice *m_pDevice;									//���Ӳ��
	PvPipeline *m_pPipeline;								//����ܵ�
	PvStream  *m_pStream;									//�����

	convertedImage			   m_convertedImage;			//ת�����ͼ��

	PvBufferConverter         *m_pBufferConventer;			//bufferת����

	PvAcquisitionStateManager *m_pAcquisitionStateManager;  //����ɼ�״̬������

	QSentechCallbackThread    *m_pCallbackThread;           //�ص��߳�

	PvGenParameterArray       *m_pGenParameterArray;        //Genicam�Ĳ�������
	PvGenFloat				  *m_plFrameRate;				//�ɼ�Ƶ��ָ��,ʵʱƵ��
	PvGenFloat				  *m_plFrameRateAverage;		//ƽ���ɼ�Ƶ��

	ListenerBase			  *m_Listener;                  //������������
	void                      *m_pUser;                     //�û�ָ��

	InterfaceType              m_enumInterfaceType;         //�ӿڵ�����

	QMutex					   m_mutexOperateBuffer;		//����buffer����Ҫ����

	QMutex					   m_mutexDetachShowDlg;		//�Ͽ�����ʾ�Ի���Ĺ���
};
