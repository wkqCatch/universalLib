#pragma once

#include <QString>

enum CommunicationMode { FreeProtocol, ModbusRtuClient, ModbusRtuServer };    //通讯模式

struct CommunicationSettings                       //Modbus的设置参数
{
	QString strSerialPortName;                  //串口名称
	int nParity;								//奇偶校验
	int nBaudRate;                              //波特率
	int nDataBits;                              //数据位数
	int nStopBits;                              //停止位数
	int nReplyOverTime;                         //等待答复超时定时
	int nRetryTimes;                            //重发次数
	int nCommunicationMode;						//通讯协议模式
	uchar ucStationNum;                         //站号  做从站的时候用到
};
