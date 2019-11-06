#pragma once

#include <QString>

enum CommunicationMode { FreeProtocol, ModbusRtuClient, ModbusRtuServer };    //ͨѶģʽ

struct CommunicationSettings                       //Modbus�����ò���
{
	QString strSerialPortName;                  //��������
	int nParity;								//��żУ��
	int nBaudRate;                              //������
	int nDataBits;                              //����λ��
	int nStopBits;                              //ֹͣλ��
	int nReplyOverTime;                         //�ȴ��𸴳�ʱ��ʱ
	int nRetryTimes;                            //�ط�����
	int nCommunicationMode;						//ͨѶЭ��ģʽ
	uchar ucStationNum;                         //վ��  ����վ��ʱ���õ�
};
