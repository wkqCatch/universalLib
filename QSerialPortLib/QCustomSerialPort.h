#pragma once

#include "qserialportlib_global.h"

#include <QObject>
#include <QMutex>
#include <QSemaphore>
#include <QSerialPort>

class QThread;
class QSerialPort;
class QSERIALPORTLIB_EXPORT QCustomSerialPort: public QObject
{
	Q_OBJECT

public:
	QCustomSerialPort(const QString &strName = "", QObject *pParent = nullptr);		//�ɂ��봮�����Q
	virtual ~QCustomSerialPort();

	bool isOpen() const;
	void close();
	void clear();
	bool open(QSerialPort::OpenMode openMode);

	qint64 write(const char *pData, qint64 nLength = -1);
	qint64 write(QByteArray byteArray);

	void setPortName(const QString &strName);
	bool setBaudRate(qint32 nBaudRate, QSerialPort::Directions direction);
	bool setDataBits(QSerialPort::DataBits dataBits);
	bool setParity(QSerialPort::Parity parity);
	bool setStopBits(QSerialPort::StopBits stopBits);

signals:
	void sigSetPortName(const QString &strName);
	void sigSetBaudRate(qint32 nBaudRate, qint32);
	void sigSetDataBits(qint32 ndataBits);
	void sigSetParity(qint32 nParity);
	void sigSetStopBits(qint32 nStopBits);
	void sigClose();											//�P�]����
	void sigOpen(qint32 nOpenMode);							    //���_����
	void sigClear();											//������
	void sigWrite(const char *pData, qint64 nLength);			//�l�͔���
	void sigDataReady(QByteArray);								//�����ѽ����պ��ˣ��l���ȥ

public slots:
	//�O�ò�����, direction:ԓ�������Ը�׃���ܺͰl�͞鲻ͬ�Ĳ�����
	void slotSetPortName(const QString &strName);
	void slotSetBaudRate(qint32 nBaudRate, qint32 nDirection);
	void slotSetDataBits(qint32 dataBits);
	void slotSetParity(qint32 nParity);
	void slotSetStopBits(qint32 nStopBits);

	void slotClose();											//�P�]����
	void slotClear();											//������
	void slotWrite(const char *pData, qint64 nLength);			//�l�͔���
	void slotOpen(qint32 nOpenMode);							//���_��ʽ

	void slotDataReady();										//���������ڣ��ʂ��xȡ

private:
	QString			 m_strPortName;				//������(COM1, COM2, COM3, ......)
	QThread			*m_pThread;					//ԓ���ڵľ���ָ�
	QSerialPort		*m_pSerialPort;				//���ڌ���ָ�

	QMutex			 m_lockClose;				//�P�]���ڵ��i
	QSemaphore		 m_semClose;				//�P�]���ڵ���̖

	QMutex			 m_lockClear;				//������ڵ��i
	QSemaphore		 m_semClear;				//������ڵ���̖

	QMutex			 m_lockWrite;				//���������i
	QSemaphore		 m_semWrite;				//����������̖
	qint64			 m_nWriteLength;			//���������L��
	QMutex			 m_lockWriteLength;			//��׃�����L�ȵ��i

	QMutex			 m_lockOpen;				//���_���ڵ��i		����iס��������
	QSemaphore		 m_semOpen;					//���_���ڵ���̖��		��춲�����ɺ�o����̖��
	bool			 m_bOpenResult;				//�Ƿ��ѽ����_����

	QMutex			 m_lockSetPortName;			//�O�ô��������i
	QSemaphore		 m_semSetPortName;			//�O�ô���������̖

	QMutex			 m_lockSetBaudRate;			//�O�ò����ʵ��i
	QSemaphore		 m_semSetBaudRate;			//�O�ò����ʵ���̖
	bool			 m_bSetBaudRateResult;		//�O�ò����ʵĽY��

	QMutex			 m_lockSetDataBits;			//�O�Ô���λ���i
	QSemaphore		 m_semSetDataBits;			//�O�Ô���λ����̖
	bool			 m_bSetDataBitsResult;		//�O�Ô���λ�ĽY��

	QMutex			 m_lockSetParity;			//�O����żУ���i
	QSemaphore		 m_semSetParity;			//�O����żУ����̖
	bool			 m_bSetParityResult;		//�O����żУ�ĽY��

	QMutex			 m_lockSetStopBits;			//�O��ֹͣλ���i
	QSemaphore		 m_semSetStopBits;			//�O��ֹͣλ����̖
	bool			 m_bSetStopBitsResult;		//�O��ֹͣλ�ĽY��

	QMutex			 m_lockInBuffer;			//�յ��Ĕ������i					
	QString			 m_strInBuffer;				//�յ��Ĕ����惦
	QString			 m_strReply;				//�յ�������đ���

	QMutex			 m_lockExpect;				//���ڴ��Ĕ������i
	QString			 m_strExpectReply;			//���ڴ��Ĕ�������
	QRegExp			 m_rxExpectReply;			//�i�ڴ������t���_ʽ

	QMutex			 m_lockEcho;				//������i
	QSemaphore		 m_semEcho;					//�������̖
	bool			 m_bEchoRegExp;				//�Ƿ񌦷����M�����t���_ʽ̎��

	bool m_bEchoFlag;							//������Iλ
	mutable QMutex m_lockEchoFlag;				//������I�i

	void setEchoFlag(bool b)					//�O�÷�����Iλ
	{
		QMutexLocker lk(&m_lockEchoFlag);
		m_bEchoFlag = b;
	}

	bool getEchoFlag() const					//�@�÷�����Iλ
	{
		QMutexLocker lk(&m_lockEchoFlag);
		return m_bEchoFlag;
	}
};
