#pragma once

#include "qcameralib_global.h"

#include <QObject>

//������������
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
#define	ACQUISITIONRATEENABLEFEATURE "AcquisitionFrameRateEnable"   //������Ĳɼ�Ƶ��

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
	const QString& getDeviceVendorName() const;						//��ȡ��������
	void setDeviceModelName(const QString &strModelName);				
	const QString& getDeviceModelName() const;					   //��ȡģ������

	void setInterfaceIP(const QString &strInterfaceIP);
	const QString& getInterfaceIP();
	void setInterfaceMAC(const QString &strInterfaceMAC);
	const QString& getInterfaceMAC();

	static bool setNewIPByAddOne(QString &strOldIP, QString &strNewIP);

	int getImageWidth() const;							//��ȡ���ͼ��Ŀ��
	void setImageWidth(int nWidth);						//�������ͼ��Ŀ��
	int getMinWidth() const;							//��ȡ��С���
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

	int getImageHeight() const;							//��ȡ���ͼ��ĸ߶�
	void setImageHeight(int nHeight);					//�������ͼ��ĸ߶�
	int getMinHeight() const;
	void setMinHeight(int nMinHeight);
	int getMaxHeight() const;
	void setMaxHeight(int nMaxHeight);

	float	getExposureTime() const;					//��ȡ�ع�ʱ��
	void    setExposureTime(float fExposureTime);       //�����ع�ʱ��
	float   getMinExposureTime() const;					//��ȡ��С�ع�ʱ��
	void    setMinExposureTime(float fMinExposureTime);
	float   getMaxExposureTime() const;
	void    setMaxExposureTime(float fMaxExposureTime);

	float   getAcquisitionFrameRate() const;			//��ȡ�ɼ�Ƶ��
	void    setAcquisitionFrameRate(float fFrameRate);  //���òɼ�Ƶ��
	float	getMinAcquisitionRate() const;
	void	setMinAcquisitionRate(float fMinAcquisitionRate);
	float   getMaxAcquisitionRate() const;
	void	setMaxAcquisitionRate(float fMaxAcquisitionRate);

	void	judgeColor();								//�ж��Ƿ��ǲ�ɫͼ��
	bool    isColor() const;                            //�Ƿ��ǲ�ɫģʽ

	QList<QString> getBalanceAutoList() const;							//��ȡ��ƽ�������б�
	QString        getBalanceWhiteAuto() const;							//��ȡ��ǰ��ƽ��ģʽ
	void           setBalanceWhiteAuto(QString strBalanceWhiteAuto);	//���ð�ƽ��

	QList<QString> getPixelFormatList() const;					//��ȡ���ظ�ʽ�б�
	QString        getPixelFormat() const;						//��ȡ���ظ�ʽ
	void		   setPixelFormat(QString strPixelFormat);		//�������ظ�ʽ		

	QList<QString> getTriggerSourceList() const;				//��ȡ����Դ���б�
	QString		   getTriggerSource() const;					//��ȡ��ǰ����Դ
	void		   setTriggerSource(QString strTriggerSource);	//���õ�ǰ����Դ

	bool		   isTriggerMode() const;						//�Ƿ��ڴ���ģʽ
	bool		   setTriggerMode(bool bTriggerMode);			//�����Ƿ�������ģʽ
	bool		   excuteTriggerSoftware();						//ִ���������

	virtual bool getBooleanParamFromDevice(const QString &strParamName, bool &bValue);
	virtual bool setBooleanParamToDevice(const QString &strParamName, bool bValue);              //����bool������Ӳ��

	virtual bool getIntegerParamFromDevice(const QString &strParamName, qint64 &llparamValue);   //��ȡ���Ͳ���
	virtual bool getIntegerParamFromDevice(const QString &strParamName, qint32 &nparamValue);
	virtual bool getIntegerRangeFromDevice(const QString &strParamName, qint64 &llMinValue, qint64 &llMaxValue);
	virtual bool getIntegerRangeFromDevice(const QString &strParamName, qint32 &llMinValue, qint32 &llMaxValue);
	virtual bool setIntegerParamToDevice(const QString &strParamName, qint64 llParameValue);     //�����ַ��Ͳ���

	virtual bool getStringParamFromDevice(const QString &strParamName, QString &strParamValue);  //��ȡ�ַ��Ͳ���

	virtual bool getFloatParamFromDevice(const QString &strParamName, double &dParamValue);      //��ȡ�����ͱ���
	virtual bool getFloatParamFromDevice(const QString &strParamName, float &fParamValue);
	virtual bool getFloatRangeFromDevice(const QString &strParamName, double &dMinValue, double &dMaxValue);
	virtual bool getFloatRangeFromDevice(const QString &strParamName, float &fMinValue, float &fMaxValue);
	virtual bool setFloatParamToDevice(const QString &strParamName, double dParamValue);		 //���ø����ͱ���

	virtual bool getEnumEntryListFromDevice(const QString &strParamName, QList<QString> &listParamValue);  //��ȡö�ٵ��ַ�������
	virtual bool getEnumValueFromDevice(const QString &strParamName, QString &strParamValue);			   //��ȡö�ٵ��ַ���ֵ
	virtual bool setEnumValueToDevice(const QString &strParamName, QString strParamValue);				   //���õ�ǰ��ö��ֵ

	virtual bool excuteCommandToDevice(const QString &strParamName);									   //ִ������

	virtual bool updateDeviceParam();																	   //����Ӳ���ĸ�����Ϣ

	void setCountScaledWidth(bool bCount);
	bool isCountScaledWidth() const;

	void setFPS(double dFPS);    //����PFS
	double getPFS() const;

	void setProgramerPower(bool bState);   //���ÿ�����Ȩ��
	bool isProgramerPower() const;		   //�Ƿ��ǿ�����Ȩ��

protected:
	QString m_strDeviceIP;					//���Ӳ��IP
	QString m_strDeviceMAC;					//���Ӳ��MAC
	QString m_strDeviceSerialNum;			//������к�

	QString m_strDeviceDescribe;			//�������

	QString m_strDeviceVendorName;			//��������
	QString m_strDeviceModelName;			//ģ������
	
	QString m_strInterfaceIP;				//����ӿ�IP
	QString m_strInterfaceMAC;				//����ӿ�MAC

	int		m_nImageWidth;					//ͼ��Ŀ��
	int     m_nMinWidth;					//��С���
	int		m_nMaxWidth;					//�����

	int     m_nOffsetX;						//X�����ƫ��
	int     m_nMinOffsetX;
	int		m_nMaxOffsetX;

	int		m_nImageHeight;					//ͼ��ĸ߶�
	int		m_nMinHeight;					//��С�߶�
	int		m_nMaxHeight;					//���߶�

	int		m_nOffsetY;
	int		m_nMinOffsetY;
	int		m_nMaxOffsetY;

	float      m_fExposureTime;				//�ع�ʱ��
	float      m_fMinExposureTime;			//��С�ع�ʱ��
	float      m_fMaxExposureTime;			//����ع�ʱ��
	float      m_fAcquisitionFrameRate;		//�ɼ�Ƶ��
	float      m_fMinAcquisitionRate;		//��С�ɼ�Ƶ��
	float      m_fMaxAcquisitionRate;		//���ɼ�Ƶ��

	double     m_dFPS;						//ʵ�ʲɼ�ƽ��Ƶ��

	QString    m_strBalanceWhiteAuto;       //��ƽ��ģʽ
	QList<QString> m_listBalanceWhiteAuto;  //��ƽ���б�

	QString   m_strPixelFormat;             //��ǰ���ظ�ʽ
	QList<QString> m_listPixelFormat;       //���ظ�ʽ�б�

	bool      m_bTriggerMode;				//�Ƿ��Ǵ���ģʽ

	QString   m_strTriggerSource;			//��ǰ����Դ
	QList<QString> m_listTriggerSource;		//����Դ�б�

	bool	  m_bColor;						//�Ƿ��ǲ�ɫ���

	bool	  m_bCountScaledWidth;			//��Ҫ�������ű���

	bool	  m_bProgramerPower;			//������Ȩ��
};

