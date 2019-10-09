#pragma once

#include <QString>

enum HardwareType { Serial, Tcp };                 //modbusʹ�õ�Ӳ��������(�������߻�����)

struct CommunicationSettings                       //Modbus�����ò���
{
	QString strSerialPortName;                  //��������
	int nParity;                                //��żУ��
	int nBaudRate;                              //������
	int nDataBits;                              //����λ��
	int nStopBits;                              //ֹͣλ��
	int nNetworkPort;                           //����ں�
	QString strNetworkAddress;                  //����ڵ�ַ
	int nTimeOut;                               //�ȴ��𸴳�ʱ��ʱ
	int nNumOfRetries;                          //�ط�����
	HardwareType enumType;                      //Ӳ������
};
