#pragma once

#include <QObject>

class QCommunicationManagement : public QObject
{
	Q_OBJECT

public:
	enum CommunicationType { FreeProtocol, ModbusRtuClient, ModbusRtuServer };    //ͨѶ����

	struct SerialPortType
	{
		void *pSerialPort;                   //��Ӧ��ָ��
		CommunicationType enumType;          //ͨѶ����
	};

	QCommunicationManagement(QObject *parent);
	~QCommunicationManagement();

private:
	
};
