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

	QCustomSerialPort* getCurrentSerialPort() const;     //获取当前的串口
	bool isSerialPortOpened() const;                       //串口是否打开了

public slots:
	void slot_ReceiveData(QByteArray byData);

private:
	QThread *m_pThread;							//线程
	QCustomSerialPort *m_pCustomSerialPort;     //自定义串口类

};
