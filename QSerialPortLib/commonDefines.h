#pragma once

#include <QString>

struct CommunicationSettings                       //Modbus�����ò���
{
	QString strSerialPortName;                  //��������
	QString strParity;                          //��żУ��
	int nBaudRate;                              //������
	int nDataBits;                              //����λ��
	int nStopBits;                              //ֹͣλ��
	int nReplyOverTime;                         //�ȴ��𸴳�ʱ��ʱ
	int nRetryTimes;                            //�ط�����
	uchar ucStationNum;                         //վ��
	QString strCommunicationProtocol;           //ͨѶЭ��
	QString strMasterOrSlave;                   //����վѡ��
};
