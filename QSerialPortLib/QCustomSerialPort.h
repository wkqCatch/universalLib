#pragma once

#include "qserialportlib_global.h"

#include <QObject>
#include <QMutex>
#include <QSemaphore>

class QThread;
class QSerialPort;
class QSERIALPORTLIB_EXPORT QCustomSerialPort: public QObject
{
	Q_OBJECT
	
public:
	QCustomSerialPort(const QString &strName = "", QObject *pParent = nullptr);		//�ɂ��봮�����Q
	virtual ~QCustomSerialPort();

	bool isOpened() const;
	void close();
	void clear();
	bool open(int nOpenMode);

	int currentError() const;      //��ǰ����

	qint64 write(const char *pData, qint64 nLength = -1);
	qint64 write(QByteArray byteArray);
	
	bool SetSerialParam(const QString &strPortName = "", const int &nBaudRate = 9600, const int &ucDirection = 3,
						const int &ucDataBits = 8, const int &ucStopBits = 1, const int &ucParity = 0);

signals:
	void sig_setSerialParam(QString, int, int, int, int, int);
	void sig_Close();									//�P�]����
	void sig_Open(qint32);							    //���_����
	void sig_Clear();									//������
	void sig_Write(const char *, qint64);				//�l�͔���

	void sig_DataReady(QByteArray);						//�����ѽ����պ��ˣ��l���ȥ

public slots:
	//�O�ò�����, direction:ԓ�������Ը�׃���ܺͰl�͞鲻ͬ�Ĳ�����
	void slot_setSerialParam(QString, int, int, int, int, int);
	void slot_Close();											//�P�]����
	void slot_Clear();											//������
	void slot_Write(const char *pData, qint64 nLength);			//�l�͔���
	void slot_Open(qint32 nOpenMode);							//���_��ʽ

	void slot_DataReady();										//���������ڣ��ʂ��xȡ

private:
	QThread			*m_pThread;					//ԓ���ڵľ���ָ�
	QSerialPort		*m_pSerialPort;				//���ڌ���ָ�

	QMutex           m_mutexSetSerialParam;     //���ô��в�������
	QSemaphore       m_semSetSerialParam;       //���ô��в������ź�
	bool             m_bSetSerialParamResult;   //���ô��в����Ľ��

	QMutex			 m_mutexOpen;				//���_���ڵ��i			����iס��������
	QSemaphore		 m_semOpen;					//���_���ڵ���̖��		��춲�����ɺ�o����̖��
	bool			 m_bOpenResult;				//�Ƿ��ѽ����_����

	QMutex			 m_mutexClose;				//�P�]���ڵ��i
	QSemaphore		 m_semClose;				//�P�]���ڵ���̖

	QMutex			 m_mutexClear;				//������ڵ��i
	QSemaphore		 m_semClear;				//������ڵ���̖

	QMutex			 m_mutexWrite;				//���������i
	QSemaphore		 m_semWrite;				//����������̖
	qint64			 m_nWriteLength;			//���������L��
	QMutex			 m_mutexWriteLength;		//��׃�����L�ȵ��i

	QMutex			 m_mutexInBuffer;			//�յ��Ĕ������i					
	QString			 m_strInBuffer;				//�յ��Ĕ����惦
	QString			 m_strReply;				//�յ�������đ���

	QMutex			 m_mutexExpect;				//���ڴ��Ĕ������i
	QString			 m_strExpectReply;			//���ڴ��Ĕ�������
	QRegExp			 m_rxExpectReply;			//�i�ڴ������t���_ʽ

	QMutex			 m_mutexEcho;				//������i
	QSemaphore		 m_semEcho;					//�������̖
	bool			 m_bEchoRegExp;				//�Ƿ񌦷����M�����t���_ʽ̎��

	bool m_bEchoFlag;							//������Iλ
	mutable QMutex m_mutexEchoFlag;				//������I�i

	void setEchoFlag(bool b)					//�O�÷�����Iλ
	{
		QMutexLocker lk(&m_mutexEchoFlag);
		m_bEchoFlag = b;
	}

	bool getEchoFlag() const					//�@�÷�����Iλ
	{
		QMutexLocker lk(&m_mutexEchoFlag);
		return m_bEchoFlag;
	}
};
