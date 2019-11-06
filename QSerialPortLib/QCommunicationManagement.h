#pragma once

#include <QObject>

class QCommunicationManagement : public QObject
{
	Q_OBJECT

public:
	enum CommunicationType { FreeProtocol, ModbusRtuClient, ModbusRtuServer };    //通讯类型

	struct SerialPortType
	{
		void *pSerialPort;                   //对应的指针
		CommunicationType enumType;          //通讯类型
	};

	QCommunicationManagement(QObject *parent);
	~QCommunicationManagement();

private:
	
};
