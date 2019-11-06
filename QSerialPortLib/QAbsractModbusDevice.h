#pragma once

#include <QObject>
#include <QMutex>
#include <QSemaphore>

class QThread;
class QCustomSerialPort;
class QAbsractModbusDevice : public QObject
{
	Q_OBJECT

public:
	QAbsractModbusDevice(QCustomSerialPort *pSerialPort = nullptr, QObject *parent = nullptr);
	virtual ~QAbsractModbusDevice();

	QCustomSerialPort* getCurrentSerialPort() const;     //��ȡ��ǰ�Ĵ���
	bool isSerialPortOpened() const;                       //�����Ƿ����

public slots:
	void slot_ReceiveData(QByteArray byData);

private:
	QThread *m_pThread;							//�߳�
	QCustomSerialPort *m_pCustomSerialPort;     //�Զ��崮����

};
