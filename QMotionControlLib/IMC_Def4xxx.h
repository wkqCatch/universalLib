
#ifndef _IMC_DEF_HEADER_
#define _IMC_DEF_HEADER_

#include <windows.h>

#pragma once

typedef PVOID IMC_HANDLE;

typedef float IMCF32; //
typedef double IMCF64; //
//typedef float IMCFLOAT; //不同的系统定义不同精度的浮点类型；
typedef double IMCFLOAT; //不同的系统定义不同精度的浮点类型；
typedef char IMC8; //
typedef unsigned char IMCU8; //
typedef short IMC16; //
typedef unsigned short IMCU16; //
typedef long int IMC32; //
typedef unsigned long int IMCU32; //


//G代码错误代码
#define	GIMC_SUCCESS					0
#define	GIMC_INVALID_HANDLE				1	//无效的句柄
#define	GIMC_INVALID_STRING_ADDRESS		2	//输入的字符串地址无效
#define	GIMC_INVALID_AXIS				3	//无效的轴号
#define	GIMC_LACK_PARAM					4	//缺少参数
#define	GIMC_ERROR_PARAM				5	//参数错误
#define	GIMC_ERROR_LINE					6	//行号错误
#define	GIMC_ERROR_FILE					7	//文件错误
#define	GIMC_NO_INIT					8	//没有初始化

enum IMC_STATUS {
	IMC_OK=0,				//成功
	IMC_SEND_FAIL,			//数据发送失败
	IMC_READ_FAIL,			//数据接收失败
	IMC_TIME_OUT,			//数据发送接收超时
	IMC_DEVICE_NOT_OPEN,	//设备没有打开
	IMC_DEVICE_NOT_FOUND,	//设备没有找到,用于打开设备时
	IMC_INVALID_HANDLE,		//无效的设备句柄
	IMC_INVALID_PARAM,		//无效的参数
	IMC_INVALID_AXIS,		//无效的轴号
	IMC_INVALID_FIFO,		//无效的FIFO
	IMC_FIFO_FULL,			//FIFO满
	IMC_FIFO_NULL,			//FIFO空
	IMC_PARAM_READ_ONLY,	//只读参数
	IMC_OUT_OF_RANGE,		//传递进来的函数参数值超出范围
	IMC_CHECK_ERROR,		//校验错误
	IMC_VERSION_ERROR,		//函数库版本与硬件版本不匹配
	IMC_OTHER_ERROR,		//其他错误值
	IMC_PASSWORD_ERROR,		//密码错误
	IMC_RBFIFO_EMPTY,		//RBFIFO空
	IMC_REG_ERROR,		//IMC寄存器地址错误，ADDA函数返回此错误
};

//
#define IMC_BIT(bit)	(1 << (bit))
//error寄存器各bit对应的错误信息
#define IMC_ERR_PLIM 		IMC_BIT(0)	//(0x0001)正向硬极限越界
#define IMC_ERR_NLIM 		IMC_BIT(1)	//(0x0002)负向硬极限越界
#define IMC_ERR_PSOF 		IMC_BIT(2)	//(0x0004)正向软极限越界
#define IMC_ERR_NSOF 		IMC_BIT(3)	//(0x0008)负向软极限越界
#define IMC_ERR_STOP 		IMC_BIT(4)	//(0x0010)急停输入
#define IMC_ERR_ALM 		IMC_BIT(6)	//(0x0040)伺服错误报警
#define IMC_ERR_POSERRLIM 	IMC_BIT(7)	//(0x0080)位置误差超限
#define IMC_ERR_CWD 		IMC_BIT(11)	//(0x0800)网络通信看门狗溢出错误
#define IMC_ERR_INSERR 		IMC_BIT(12)	//(0x1000)指令错误
#define IMC_ERR_VELLIM 		IMC_BIT(13)	//(0x2000)速度超限
#define IMC_ERR_ACCLIM 		IMC_BIT(14)	//(0x4000)加速度超限
#define IMC_ERR_DELPOS 		IMC_BIT(15)	//(0x8000)指令位置异常
//*******************************************************************************************************************
//网卡信息
typedef struct {
	char description[16][256];	//网卡描述
}NIC_INFO,*PNIC_INFO;

//*******************************************************************************************************************
#define IMC_REG_BIT_W16		1		
#define IMC_REG_BIT_W32		2
#define IMC_REG_BIT_W48		3
typedef struct _WR_MUL_DES_{
	WORD addr;	//参数地址
	WORD axis;	//轴号
	WORD len;	//参数长度（单位：字（16位宽）, 其值为1、2、3； 1:表示一个字（short） 2:表示2个字（long) 3:表示3个字（））
	WORD data[4];//写或读回的数据
}WR_MUL_DES, *pWR_MUL_DES;
//*******************************************************************************************************************
enum FIFO_SEL{
	SEL_IFIFO,
	SEL_QFIFO,
	SEL_PFIFO1,
	SEL_PFIFO2,
	SEL_CFIFO,
};

//事件类型
enum IMC_EventType{
	IMC_Allways,		//“无条件执行”

	IMC_Edge_Zero,		//“边沿型条件执行”——当上一条无条件执行的事件结果变为0时
	IMC_Edge_NotZero,	//“边沿型条件执行”——当上一条无条件执行的事件结果变为非0时
	IMC_Edge_Great, 	//“边沿型条件执行”——当上一条无条件执行的事件结果变为大于时
 	IMC_Edge_GreatEqu, 	//“边沿型条件执行”——当上一条无条件执行的事件结果变为大于等于时
	IMC_Edge_Little,	//“边沿型条件执行”——当上一条无条件执行的事件结果变为小于时
	IMC_Edge_Carry,		//“边沿型条件执行”——当上一条无条件执行的事件结果变为溢出时
	IMC_Edge_NotCarry, 	//“边沿型条件执行”——当上一条无条件执行的事件结果变为无溢出时

	IMC_IF_Zero,		//“电平型条件执行”——当上一条无条件执行的事件结果若为0
	IMC_IF_NotZero, 	//“电平型条件执行”——当上一条无条件执行的事件结果若为非0
	IMC_IF_Great,		//“电平型条件执行”——当上一条无条件执行的事件结果若大于
	IMC_IF_GreatEqu, 	//“电平型条件执行”——当上一条无条件执行的事件结果若大于等于
	IMC_IF_Little, 		//“电平型条件执行”——当上一条无条件执行的事件结果若小于
	IMC_IF_Carry,		//“电平型条件执行”——当上一条无条件执行的事件结果若溢出
	IMC_IF_NotCarry		//“电平型条件执行”——当上一条无条件执行的事件结果若无溢出
};

//事件指令
enum IMC_EVENT_CMD{
	CMD_ADD32,		//两个32bit参数相加 
	CMD_ADD32i,		//32bit参数 加 32bit立即数
	CMD_ADD48,		//两个48bit参数相加 
	CMD_ADD48i,		//48bit参数 加 48bit立即数
	CMD_CMP32,		//两个 32bit参数相比较
	CMD_CMP32i,		//32bit参数 与 32bit立即数 相比较
	CMD_CMP48,		//两个 48bit参数相比较
	CMD_CMP48i,		//48bit参数 与 48bit立即数 相比较
	CMD_SCA32,		//32bit参数缩放，倍率(48bit)为另一参数
	CMD_SCA32i,		//32bit参数缩放，倍率(48bit)为立即数
	CMD_SCA48,		//48bit参数缩放，倍率(48bit)为另一参数
	CMD_SCA48i,		//48bit参数缩放，倍率(48bit)为立即数
	CMD_MUL32L,		//32bit参数 乘以 32bit参数 其结果取低 32bit
	CMD_MUL32iL,	//32bit参数 乘以 立即数 其结果取低 32bit
	CMD_MUL32A,		//32bit参数 乘以 32bit参数 其结果取低 48bit
	CMD_MUL32iA,	//32bit参数 乘以 立即数 其结果取低 48bit
	CMD_COP16,		//拷贝 16bit参数
	CMD_COP32,		//拷贝 32bit参数
	CMD_COP48,		//拷贝 48bit参数
	CMD_SET16,		//设置 16bit参数
	CMD_SET32,		//设置 32bit参数
	CMD_SET48,		//设置 48bit参数
	CMD_OR16,		//参数 OR 参数
	CMD_OR16i,		//参数 OR 立即数
	CMD_OR16B,		//参数 OR 参数  其结果转换为BOOL类型
	CMD_OR16iB,		//参数 OR 立即数  其结果转换为BOOL类型
	CMD_AND16,		//参数 AND 参数
	CMD_AND16i,		//参数 AND 立即数
	CMD_AND16B,		//参数 AND 参数  其结果转换为BOOL类型
	CMD_AND16iB,	//参数 AND 立即数  其结果转换为BOOL类型
	CMD_XOR16,		//参数 OR 参数
	CMD_XOR16i,		//参数 OR 立即数
	CMD_XOR16B,		//参数 OR 参数 其结果转换为BOOL类型
	CMD_XOR16iB		//参数 OR 立即数 其结果转换为BOOL类型
};

typedef struct _EVENT_INFO_ {
	short EventCMD;  //操作码，即枚举类型IMC_EVENT_CMD中的值
	short EventType; //执行类型，即枚举类型IMC_EventType中的值
	short Src1_loc;	//指向操作数1的参数地址
	short Src1_axis;	//操作数1所属的轴号
	union{  			//用一个联合体来组织操作数2
		struct {
			short Src2_loc;	//指向操作数2的参数地址
			short Src2_axis;//操作数2所属的轴号
			int reserve;	//保留
		}param;
		struct {
			short data;		//16位宽的常数
			short reserve1;	//保留
			int reserve2;	//保留
		}data16;
		struct {
			int data;		//32位宽的常数
			int reserve;	//保留
		}data32;
		__int64 data48;		//48位宽的常数
	}Src2;
	short dest_loc;			//指向存储目标的参数地址
	short dest_axis;		//目标参数所属的轴号
	int reserve;			//保留
}EventInfo, *PEventInfo;

//*******************************************************************************************************************

typedef struct _PFIFO_SEG_DATA_{
	int datanum;			//SegEndData数组中有效数据个数,即参与路径运动的轴数
	int SegEndData[16];
	int CenterX;		//圆弧路径圆心的横坐标
	int CenterY;		//圆弧路径圆心的纵坐标
	int dir;	//0:顺时针方向，  -1：逆时针方向
}PFIFOSegData,*PPFIFOSegData;

typedef struct _PFIFO_SEG_INFO_{
	int SegTgVel;		//目标速度
	int SegEndVel;	//终点速度
	PFIFOSegData data;	//段数据
}PFIFOSegInfo, *PPFIFOSegInfo;
//*******************************************************************************************************************


#endif