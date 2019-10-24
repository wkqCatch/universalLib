#pragma once

#include <QString>

struct CommunicationSettings                       //Modbus的设置参数
{
	QString strSerialPortName;                  //串口名称
	QString strParity;                          //奇偶校验
	int nBaudRate;                              //波特率
	int nDataBits;                              //数据位数
	int nStopBits;                              //停止位数
	int nReplyOverTime;                         //等待答复超时定时
	int nRetryTimes;                            //重发次数
	uchar ucStationNum;                         //站号
	QString strCommunicationProtocol;           //通讯协议
	QString strMasterOrSlave;                   //主从站选择
};
