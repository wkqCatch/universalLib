#pragma once

#include <QString>

enum HardwareType { Serial, Tcp };                 //modbus使用的硬件的类型(串行总线或网线)

struct CommunicationSettings                       //Modbus的设置参数
{
	QString strSerialPortName;                  //串口名称
	int nParity;                                //奇偶校验
	int nBaudRate;                              //波特率
	int nDataBits;                              //数据位数
	int nStopBits;                              //停止位数
	int nNetworkPort;                           //网络口号
	QString strNetworkAddress;                  //网络口地址
	int nTimeOut;                               //等待答复超时定时
	int nNumOfRetries;                          //重发次数
	HardwareType enumType;                      //硬件类型
};
