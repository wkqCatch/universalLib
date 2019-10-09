#ifndef IMC_PKG_HEAD_H
#define IMC_PKG_HEAD_H

#ifdef IMC_PKG_EXPORTS
#define IMC_PKG_API __declspec(dllexport)
#else
#define IMC_PKG_API __declspec(dllimport)
#endif

#include "IMC_Def4xxx.h"


//�豸����
//������̫����
IMC_PKG_API int WINAPI 
	PKG_IMC_FindNetCard (char  info[16][256],	//�����ҵ�����������
						int* num) ;				//�����ҵ�����������
//�����̫����������
IMC_PKG_API int WINAPI 
	PKG_IMC_GetNetCardNum () ;				//�����ҵ�����������
//��ö�Ӧ��������������
IMC_PKG_API int WINAPI 
	PKG_IMC_GetNetCardName (int index,		//��������	
							char name[256]);//���ض�Ӧ��������������

//�򿪿��ƿ��豸�����豸����ͨ������
IMC_PKG_API IMC_HANDLE WINAPI 
	PKG_IMC_Open (int netcardsel,			//���������������������������صĽ������
						int imcid) ;		//IMC���ƿ���id���ɿ��ƿ��ϵĲ��뿪�����þ���
//�򿪿��ƿ��豸�����豸����ͨ������
IMC_PKG_API IMC_HANDLE WINAPI 
	PKG_IMC_OpenX (int netcardsel, 			//���������������������������صĽ������
						int imcid, 			//IMC���ƿ���id���ɿ��ƿ��ϵĲ��뿪�����þ���
						int timeout,		//ͨ�ų�ʱʱ�䣬��λ����
						int openMode) ;		//��ģʽ��1������ģʽ�� 0���ǻ���ģʽ
//ʹ������򿪿��ƿ��豸�����豸����ͨ������
IMC_PKG_API IMC_HANDLE WINAPI 
	PKG_IMC_OpenUsePassword (int netcardsel, 	//���������������������������صĽ������
						int imcid,  			//IMC���ƿ���id���ɿ��ƿ��ϵĲ��뿪�����þ���
						char *password,			//�����ַ���
						int pwlen);				//���볤��
//�رմ򿪵��豸��
IMC_PKG_API int WINAPI 
	PKG_IMC_Close (IMC_HANDLE Handle);

//��ȡͨ������
IMC_PKG_API int WINAPI 
	PKG_IMC_GetPassword(IMC_HANDLE handle,  	//�豸�����
					char password[128],			//ͨ�����뻺����
					char *pwlen);				//ͨ�����볤��
//����ͨ������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPassword(IMC_HANDLE handle,  	//�豸�����
					char* oldpassword,			//ԭ�豸����
					char pwolen,				//ԭ�豸���볤��
					char* password,				//���豸����
					char pwnlen,				//���豸���볤��
					char rPW[128],				//���ڱ���ͨ������Ļ�����
					char *rpwlen);				//����ͨ�����볤��


//���ú���
IMC_PKG_API int WINAPI PKG_IMC_InitCfg(IMC_HANDLE handle);
//�������FIFO�Ͳ����ĵȴ�ָ�
IMC_PKG_API int WINAPI 
	PKG_IMC_ClearIMC(IMC_HANDLE handle); 	//�豸�����

//�������ı�����������ָ��λ�á�Ŀ��λ�õȸ���λ�ò�����
IMC_PKG_API int WINAPI 
	PKG_IMC_ClearAxis(IMC_HANDLE handle,  	//�豸�����
					int axis);				//��Ҫ�������š�
//����ָ�������Ч��ƽ��������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPulWidth(IMC_HANDLE handle, 	//�豸�����
					unsigned int ns,		//�����ȣ���λΪ����
					int axis);				//��Ҫ���������ȵ����
//����ָ���������ͷ������Ч��ƽ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPulPolar(IMC_HANDLE handle, 	//�豸�����
					int pul,				//�����źŵ���Ч��ƽ�����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
					int dir, 				//�����źŵ���Ч��ƽ�����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
					int axis);				//��Ҫ������Ч��ƽ����š�
//ʹ��/��ֹ���ƿ����ձ���������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEncpEna(IMC_HANDLE handle, 	//�豸�����
					int ena, 				//ʹ�ܱ�־�����㣺ʹ�ܣ� �㣺��ʹ�ܡ�
					int axis);				//��Ҫ��/��ֹ���ƿ����ձ�������������š�
//���ÿ��ƿ����ձ����������ļ���ģʽ�ͼ�������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEncpMode(IMC_HANDLE handle, 	//�豸�����
					int mode, 				//�������ļ���ģʽ���㣺�����ź�ģʽ�� ���㣺����+����ģʽ
					int dir, 				//�������ļ�������
					int axis);				//��Ҫ���õ���š�
//����ָ������ٶȺͼ��ٶ�����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetVelAccLim(IMC_HANDLE handle, //�豸�����
					double vellim, 			//�ٶȼ��ޣ���λΪ����ÿ���롣
					double acclim, 			//���ٶȼ��ޣ���λΪ����ÿƽ�����롣
					int axis);				//��Ҫ�����ٶȺͼ��ٶȼ��޵����
//����ÿ�����ƽ����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetSmooth(IMC_HANDLE handle, 	//�豸�����
						short smooth, 		//ƽ���ȣ�ֵԽ����Խƽ�������˶��켣������Խ��
						int aixs); 			//��ţ�	
//ʹ��/��ָֹ�����������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEna(IMC_HANDLE handle, 		//�豸�����
					int ena, 				//ʹ�ܱ�־�����㣺ʹ�ܣ� �㣺��ʹ�ܡ�
					int axis);				//��Ҫʹ��/��ֹ����������š�
//ʹ��/��ֹӲ����λ����˿ں���������Ч���ԡ�
IMC_PKG_API int WINAPI 
	PKG_IMC_Setlimit (IMC_HANDLE handle, 	//�豸�����
					int plimEna, 			//�Ƿ�ʹ��Ӳ������λ���ܡ����㣺ʹ�ܣ� �㣺��ʹ�ܡ�
					int plimPolar, 			//����λ���ԣ����㣺��Ч�� �㣺�͵�ƽ��Ч��
					int nlimEna, 			//�Ƿ�ʹ��Ӳ������λ���ܡ����㣺ʹ�ܣ� �㣺��ʹ�ܡ�
					int nlimPolar, 			//����λ���ԣ����㣺��Ч�� �㣺�͵�ƽ��Ч��
					int axis);				//��š�
//ʹ���ŷ������������������Ч����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetAlm (IMC_HANDLE handle, 		//�豸�����
					int ena, 				//�Ƿ�ʹ���ŷ��������빦�ܡ����㣺ʹ�ܣ� �㣺��ʹ�ܡ�
					int polar, 				//���ԣ����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
					int axis);				//��š�
//ʹ���ŷ���λ�������������Ч����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetINP(IMC_HANDLE handle,  		//�豸�����
					int ena,  				//�Ƿ�ʹ���ŷ���λ���빦�ܡ����㣺ʹ�ܣ� �㣺��ʹ�ܡ�
					int polar,  			//���ԣ����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
					int axis);				//��š�
//���ü�ͣ����˵���Ч����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetEmstopPolar(IMC_HANDLE handle,	//�豸�����
					int polar); 				//���ԣ����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
/*
//����ͨ������˵���Ч����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetInPolar(IMC_HANDLE handle, 	//�豸�����
					int polar, 				//���ԣ����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
					int inPort);			//����˿ڣ���Χ1 - 32��
*/
//
IMC_PKG_API unsigned int WINAPI 
	PKG_IMC_CmpPolarVal(unsigned int oldpolar, //ԭ���ļ���ֵ
					int newpolar,				//���ԣ����㣺�ߵ�ƽ��Ч�� �㣺�͵�ƽ��Ч��
					int inPort);			//����˿ڣ���Χ1 - 32��

//����ͨ������˵���Ч����
IMC_PKG_API int WINAPI 
	PKG_IMC_SetGinPolar(IMC_HANDLE handle,  //�豸�����
					unsigned int polar); 	//����ֵ����ͨ��PKG_IMC_CmpPolarVal��������õ���

//���÷�������ʱ������Ƿ�ֹͣ�˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_SetStopfilt(IMC_HANDLE handle,  //�豸�����
					int stop,				//����ʱ�Ƿ�ֹͣ���У��㣺��ֹͣ�� ���㣺ֹͣ
					int axis);				//��š�
//���÷�������ʱ������Ƿ��˳��˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_SetExitfilt(IMC_HANDLE handle,  //�豸�����
					int exit,				//����ʱ�Ƿ��˳����У��㣺���˳������㣺�˳�
					int axis);				//��š�
//���þ�̬�����ķ�Χ��
IMC_PKG_API int WINAPI 
	PKG_IMC_SetRecoupRange(IMC_HANDLE handle, //�豸�����
					int range,				//����ֵ��ȡֵ��Χ0 - 32767��
					int axis);				//��š�
//����ͨ�ſ��Ź���
IMC_PKG_API int WINAPI 
	PKG_IMC_SetComdog(IMC_HANDLE handle,	//�豸�����
					int ena,				//�Ƿ�����ͨ�ſ��Ź����㣺���ã� ���㣺����
					int time);				//ι��ʱ�䣬��λ���룬ȡֵ��Χ��0 - 32767
//��ÿ��ƿ��е�������Ϣ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetConfig(IMC_HANDLE handle,  	//�豸�����
					int *steptime, 			//�����ȣ���λΪ����
					int *pulpolar, 			//�������Ч��ƽ���㣺�͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					int *dirpolar, 			//�������Ч��ƽ���㣺�͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					int *encpena, 			//�Ƿ�ʹ�ñ������������㣺���ã� ���㣺ʹ��
					int *encpmode, 			//����������ģʽ
					int *encpdir, 			//��������������
			//		double *encpfactor, 	//����������
					double *vellim, 		//�ٶȼ��ޣ���λΪ����/����
					double *acclim, 		//���ٶȼ��ޣ���λΪ����/ƽ������
					int *drvena, 			//�Ƿ�ʹ�����������㣺��ʹ�ܣ� ���㣺ʹ��
					int *plimena, 			//�Ƿ�ʹ����Ӳ����λ���㣺���ã� ���㣺ʹ��
					int *plimpolar, 		//Ӳ������λ��Ч��ƽ���㣺�͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					int *nlimena, 			//�Ƿ�ʹ�ø�Ӳ����λ���㣺���ã� ���㣺ʹ��
					int *nlimpolar, 		//Ӳ������λ��Ч��ƽ���㣺�͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					int *almena, 			//�Ƿ�ʹ���ŷ��������㣺���ã� ���㣺ʹ��
					int *almpolar, 			//�ŷ�������Ч��ƽ���㣺�͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					int *INPena, 			//�Ƿ�ʹ���ŷ���λ���㣺���ã� ���㣺ʹ��
					int *INPpolar, 			//�ŷ���λ��Ч��ƽ���㣺�͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					int axis);				//��Ҫ��ȡ��Ϣ�����
//�㵽���˶�����
//ʹ��ӵ�ǰλ���ƶ���ָ����Ŀ��λ��
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveAbs(IMC_HANDLE handle, 		//�豸�����
					long pos, 				//Ŀ��λ�ã���λΪ���壻
					double startvel, 		//��ʼ�ٶȣ���λΪ����ÿ���룻
					double endvel, 			//��ֹ�ٶȣ���λΪ����ÿ���룻
					double tgvel, 			//Ŀ���ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��˶���ɺ󣬺����ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int axis); 				//ָ�����
					
//ʹ��ӵ�ǰλ���ƶ���ָ���ľ���
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveDist(IMC_HANDLE handle, 	//�豸�����
					long dist, 				//�ƶ����룬��λΪ���壻
					double startvel, 		//��ʼ�ٶȣ���λΪ����ÿ���룻
					double endvel, 			//��ֹ�ٶȣ���λΪ����ÿ���룻
					double tgvel, 			//Ŀ���ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��˶���ɺ󣬺����ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int axis); 				//ָ����ţ�

//�����ı䵱ǰ����ִ�еĵ㵽���˶����˶��ٶ�
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pvel(IMC_HANDLE handle,		//�豸�����
					double tgvel, 			//Ŀ���ٶȣ���λΪ����ÿ���룻
					int axis);				//��ţ�
//���õ�ǰ�㵽���˶��ļ��ٶȺͼ��ٶ�
IMC_PKG_API int WINAPI 
	PKG_IMC_SetAccel(IMC_HANDLE handle, 	//�豸�����
					double accel, 			//���ٶȣ���λΪ����ÿƽ�����룻
					double decel, 			//���ٶȣ�
					int axis);				//��ţ�
//���õ㵽���˶�ģʽ
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pmode(IMC_HANDLE handle,  	//�豸�����
					int mode, 				//�˶�ģʽ���㣺��ͨģʽ�� ���㣺����ģʽ
					int axis);				//��š�
//��㵽���˶���Ŀ��λ��
IMC_PKG_API int WINAPI 
	PKG_IMC_P2PnewPos(IMC_HANDLE handle,  	//�豸�����
					long tgpos, 			//�µ�Ŀ��λ�ã���λΪ���壻
					int axis);				//��š�
//����ֹͣ�㵽���˶�
IMC_PKG_API int WINAPI 
	PKG_IMC_P2Pstop(IMC_HANDLE handle, 		//�豸�����
					int axis);				//��š�
//ʹ��������ָ�����ٶ�һֱ�˶���ֱ���ٶȱ��ı�Ϊֹ
IMC_PKG_API int WINAPI 
	PKG_IMC_MoveVel(IMC_HANDLE handle,  	//�豸�����
					double startvel, 		//��ʼ�ٶȣ���λΪ����ÿƽ�����룻 
					double tgvel, 			//ָ������˶��ٶȣ���λΪ����ÿƽ�����룻
					int axis);				//��š�

//�岹����
//����������岹�˶������ӳ�䵽X��Y��Z��A��B�������ȶ�Ӧ�ı�ʶ��
IMC_PKG_API int WINAPI 
	PKG_IMC_AxisMap(IMC_HANDLE handle, 		//�豸�����
					int axis[], 			//��Ҫӳ�����ŵ�����
					int num, 				//��Ҫӳ����������
					int fifo);				//���ĸ��岹�ռ����ӳ�䣬��ѡSEL_PFIFO1��SEL_PFIFO2��
//�������ò岹�ռ�
IMC_PKG_API int WINAPI
	PKG_IMC_PFIFOrun (IMC_HANDLE handle, 	//�豸�����
					int fifo);				//�����ĸ��岹�ռ䣬��ѡSEL_PFIFO1��SEL_PFIFO2��
//�����ٶȹ滮��ʽ��
IMC_PKG_API int WINAPI
	PKG_IMC_SetPFIFOvelMode (IMC_HANDLE handle, //�豸�����
					int mode,				//�ٶȹ滮ģʽ
					int fifo);				//�����ĸ��岹�ռ���ٶȹ滮ģʽ����ѡSEL_PFIFO1��SEL_PFIFO2��
//�����ı�岹�ļ��ٶ�
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPFIFOaccel (IMC_HANDLE handle, //�豸�����
					double accel, 			//�岹�ļ��ٶȣ���λΪ����ÿƽ�����룻 
					int fifo);				//�����ĸ��岹�ռ�Ĳ岹�ļ��ٶȣ���ѡSEL_PFIFO1��SEL_PFIFO2��
//����ֱ�߲岹�������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_Line_Pos(IMC_HANDLE handle, 	//�豸�����
					long pos[], 			//����岹�˶������λ�ã���λΪ���壻
					int axisNum, 			//����岹�˶���������
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶���ĩ���ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//����ֱ�߲岹������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_Line_Dist(IMC_HANDLE handle, 	//�豸�����
					long dist[], 			//����岹�˶�������ƶ����룬��λΪ���壻
					int axisNum, 			//����岹�˶���������
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel,			//�岹�˶���ĩ���ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//�������ֱ�߲岹�������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_MulLine_Pos (IMC_HANDLE handle, //�豸�����
					long* pos, 				//��β���岹�˶������λ�ã���λΪ���壻
					int axisNum, 			//����岹�˶���������
					int segNum, 			//�岹�˶��Ķ�����
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶������һ�εĽ����ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//�������ֱ�߲岹������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_MulLine_Dist (IMC_HANDLE handle, //�豸�����
					long* dist, 			//��β���岹�˶�������ƶ����룬��λΪ���壻 
					int axisNum, 			//����岹�˶���������
					int segNum, 			//�岹�˶��Ķ�����
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶������һ�εĽ����ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//Բ���岹�������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_Arc_Pos(IMC_HANDLE handle, 		//�豸�����
					long endx, 				//����Բ���岹��X����յ��λ�ã���λΪ���壻
					long endy, 				//����Բ���岹��Y����յ��λ�ã���λΪ���壻
					long cx, 				//����Բ���岹��X���Բ�ģ���λΪ���壻
					long cy, 				//����Բ���岹��Y���Բ�ģ���λΪ���壻 
					int dir, 				//Բ���˶��ķ���
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶��Ľ����ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo) ;				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//Բ���岹������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_Arc_Dist(IMC_HANDLE handle, 	//�豸�����
					long dist_x, 			//����Բ���岹��X����յ���������ľ��룬��λΪ���壻
					long dist_y, 			//����Բ���岹��Y����յ���������ľ��룬��λΪ���壻
					long dist_cx, 			//����Բ���岹��X���Բ����������ľ��룬��λΪ���壻
					long dist_cy, 			//����Բ���岹��Y���Բ����������ľ��룬��λΪ���壻
					int dir, 				//Բ���˶��ķ���
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶��Ľ����ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//Բ��ֱ�߲岹�������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_ArcLine_Pos(IMC_HANDLE handle, 	//�豸�����
					long endx, 				//����Բ���岹��X����յ��λ�ã���λΪ���壻
					long endy, 				//����Բ���岹��Y����յ��λ�ã���λΪ���壻
					long cx, 				//����Բ���岹��X���Բ�ģ���λΪ���壻
					long cy, 				//����Բ���岹��Y���Բ�ģ���λΪ���壻
					int dir, 				//Բ���˶��ķ��� 
					long pos[], 			//����Բ���岹�˶������λ�ã���λΪ���壻 
					int axisNum, 			//����Բ���岹�˶���������
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶��Ľ����ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2��
//Բ��ֱ�߲岹������˶���
IMC_PKG_API int WINAPI 
	PKG_IMC_ArcLine_Dist(IMC_HANDLE handle, //�豸�����
					long dist_x, 			//����Բ���岹��X����յ���������ľ��룬��λΪ���壻
					long dist_y, 			//����Բ���岹��Y����յ���������ľ��룬��λΪ���壻
					long dist_cx, 			//����Բ���岹��X���Բ����������ľ��룬��λΪ���壻
					long dist_cy, 			//����Բ���岹��Y���Բ����������ľ��룬��λΪ���壻
					int dir, 				//Բ���˶��ķ��� 
					long dist[], 			//����Բ���岹�˶�������ƶ����룬��λΪ���壻
					int axisNum, 			//����Բ���岹�˶���������
					double tgvel, 			//�岹�˶����ٶȣ���λΪ����ÿ���룻
					double endvel, 			//�岹�˶��Ľ����ٶȣ���λΪ����ÿ���룻
					int wait, 				//�Ƿ�ȴ��岹�˶���ɣ������ŷ��ء����㣺�ȴ��˶���ɣ��㣺���ȴ���
					int fifo);				//ָ�������˶�ָ��͵��ĸ�FIFO��ִ�У���ѡSEL_PFIFO1��SEL_PFIFO2�� 
//����ֹͣ�岹�˶�
IMC_PKG_API int WINAPI 
	PKG_IMC_PFIFOstop (IMC_HANDLE handle, 	//�豸�����
					int fifo);				//ֹͣ�ĸ��岹�ռ�Ĳ岹����ѡSEL_PFIFO1��SEL_PFIFO2��
//����ֹͣ�岹�˶�
IMC_PKG_API int WINAPI 
	PKG_IMC_isPstop (IMC_HANDLE handle,  	//�豸�����
					int fifo);				//�ĸ��岹�ռ�Ĳ岹ֹͣ����ѡSEL_PFIFO1��SEL_PFIFO2��
//������շ����岹�ռ���δ��ִ�е�����ָ��
IMC_PKG_API int WINAPI 
	PKG_IMC_PFIFOclear (IMC_HANDLE handle, 	//�豸�����
					int fifo);				//����ĸ��岹�ռ��ָ���ѡSEL_PFIFO1��SEL_PFIFO2��

//���ֺ���
//����ָ���������������˶�
IMC_PKG_API int WINAPI  
	PKG_IMC_HandWheel1(IMC_HANDLE Handle, 	//�豸�����
					double rate, 			//�������ֱ��ʣ�
					int axis);				//���������˶�����ţ�
//����ָ���������������˶�
IMC_PKG_API int WINAPI  
	PKG_IMC_HandWheel2(IMC_HANDLE Handle, 	//�豸�����
					double rate, 			//�������ֱ��ʣ�
					int axis);				//���������˶�����ţ�
//�˳���PKG_IMC_HandWheel2�������õĵ��������˶�
IMC_PKG_API int WINAPI  
	PKG_IMC_ExitHandWheel2(IMC_HANDLE Handle,  //�豸�����
					int axis);				//���������˶�����ţ�
//���ôӶ�������������˶�
IMC_PKG_API int WINAPI  
	PKG_IMC_Gear1 (IMC_HANDLE Handle, 		//�豸�����
					double rate, 			//���ֱ��ʣ�
					int master, 			//�������
					int axis);				//�Ӷ������š�
//���ôӶ�������������˶�
IMC_PKG_API int WINAPI  
	PKG_IMC_Gear2 (IMC_HANDLE Handle, 		//�豸�����
					double rate, 			//���ֱ��ʣ�
					int master, 			//�������
					int axis);				//�Ӷ������š�
//��������������ֻ���ֵ�����
IMC_PKG_API int WINAPI  
	PKG_IMC_ExitGear (IMC_HANDLE Handle, 	//�豸�����
					int axis);				//�Ӷ������š�


//IO���ú���
//������˿ڽ��п���
IMC_PKG_API int WINAPI 
	PKG_IMC_SetOut(IMC_HANDLE handle, 		//�豸�����
					int outPort, 			//����˿ڣ���Χ��1 �C 48��
					int data, 				//��������˿ڵ�״̬�� �㣺�Ͽ�����˿ڣ� ���㣺��ͨ����˿ڡ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��ִ�С�

 //���㺯��
//���õ�ǰ���������ʹ�õĸ��ٶȺ͵��ٶ�
IMC_PKG_API int WINAPI 
	PKG_IMC_SetHomeVel(IMC_HANDLE handle, 	//�豸�����
					double hight, 			//���������ʹ�õĸ��ٶȣ���λΪ����ÿ���룻
					double low, 			//���������ʹ�õĵ��ٶȣ���λΪ����ÿ���룻
					int axis);				//��ţ�
//���ñ����������źŵļ���
IMC_PKG_API int WINAPI 
	PKG_IMC_SetHomeIndexPolar(IMC_HANDLE handle, //�豸�����
					int polar,				//�����źŵļ��ԣ� ���㣺��������Ч�� 0���½�����Ч
					int axis);				//��ţ�

//ʹ����㿪���������
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeORG (IMC_HANDLE Handle,   		//�豸�����
					int orgSW,					//��㿪��ѡ��
					int rundir,					//��ʼ����ʱ�ķ����㣺������ʼ���㣻���㣺������ʼ���㡣
					int stopmode,				//������ԭ����ֹͣ��ʽ���㣺����ֹͣ��ԭ��λ�ã����㣺����ֹͣ��
					int SWtype,					//�㣺�����Ϳ��أ�����ʱ��ͨ�������㣺�����Ϳ��أ�����ʱ�Ͽ�����ԭ�㿪�����͵����ñ�����ʵ��һ�£�������ԭ�㹦�ܲ�������
					int homedir,				//ԭ�㷽�򡣼����ԭ�㿪�صķ������˷����ƶ�ʱ��⵽ԭ�㿪�ز���Ϊ��Ч��⡣�㣺�������ƶ�ʱ���ԭ�㿪�أ����㣺�������ƶ�ʱ���ԭ�㿪�ء�
					int reducer,				//���ٿ���ѡ��
					long pos,					//�������ʱ����㿪�ص�λ��ֵ
					double hightvel,			//����ʱʹ�õĸ��ٶ�
					double lowvel,				//����ʱʹ�õĵ��ٶ�
					int wait,					//�Ƿ�ȴ�������������ٷ���
					int axis);					//���
//ʹ����㿪�غ������ź��������
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeORGIndex (IMC_HANDLE Handle,   	//�豸�����
					int orgSW,					//��㿪��ѡ��
					int rundir,					//��ʼ����ʱ�ķ����㣺������ʼ���㣻���㣺������ʼ���㡣
					int stopmode,				//������ԭ����ֹͣ��ʽ���㣺����ֹͣ��ԭ��λ�ã����㣺����ֹͣ��
					int SWtype,					//�㣺�����Ϳ��أ�����ʱ��ͨ�������㣺�����Ϳ��أ�����ʱ�Ͽ�����ԭ�㿪�����͵����ñ�����ʵ��һ�£�������ԭ�㹦�ܲ�������
					int homedir,				//ԭ�㷽�򡣼����ԭ�㿪�صķ������˷����ƶ�ʱ��⵽ԭ�㿪�ز���Ϊ��Ч��⡣�㣺�������ƶ�ʱ���ԭ�㿪�أ����㣺�������ƶ�ʱ���ԭ�㿪�ء�
					int reducer,				//���ٿ���ѡ��
					long pos,					//�������ʱ�������ź����ڵ�λ��ֵ
					double hightvel,			//����ʱʹ�õĸ��ٶ�
					double lowvel,				//����ʱʹ�õĵ��ٶ�
					int wait,					//�Ƿ�ȴ�������������ٷ���
					int axis);					//���

//
IMC_PKG_API int WINAPI 
	PKG_IMC_SetSReset(IMC_HANDLE Handle,  		//�豸�����
					int ena,					//�Ƿ�ʹ���ŷ���λ�������ʹ�ܺ󣬼�ͣ������ʱ����ͨ��SRST�˿����һ�������ź�
					int steptime,				//����������źŵĿ�ȣ���λΪ125΢��
					int axis);					//���

//�Ѹ���ĵ�ǰλ���趨Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPos (IMC_HANDLE Handle, 		//�豸�����
					long pos, 				//���õ�ָ��ֵ����λΪ���壻
					int axis);				//��š�
//����ֹͣ�����˶�
IMC_PKG_API int WINAPI 
	PKG_IMC_HomeStop (IMC_HANDLE Handle, 	//�豸�����
					int axis);				//��Ҫֹͣ�����˶�����š�

//AD����
//����AD�������ܡ�
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADena(IMC_HANDLE handle,		//�豸�����
	 				int ena,				//ʹ�ܻ��ǽ�ֹ��
					int ch);				//AD����ͨ��
//���ָ��ͨ����AD����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetADdata(IMC_HANDLE handle, 	//�豸�����
	 				double *ADdata,			//���ڻ�ȡADֵ����λ����
					int ch);				//AD����ͨ��
//����ĳ��Ŀ�����AD����ĵ�ѹ�仯��ָ������仯
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADCtrl(IMC_HANDLE handle,  	//�豸���
					double ADstart,			//AD�������ʼֵ
					double ADend,			//AD�������ֵֹ
					int ch,					//AD����ͨ��
	 				int paramloc,			//����AD����ֵ�仯�ļĴ����ĵ�ַ��
					int axis,				//����AD����ֵ�仯�ļĴ�������ţ�
					int paramStart,			//����AD����ֵ�仯�ļĴ�������ʼֵ
					int paramEnd,			//����AD����ֵ�仯�ļĴ�������ֵֹ��
					int id);				//���ƹ���ģ��ID����Χ��0��(���� - 1)��
//����AD����ĵ�ѹ�仯����ĳ��Ŀ����ָ������仯
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADCtrlEX(IMC_HANDLE handle,  //�豸���
					double ADstart, 		//AD�������ʼֵ
					double ADend, 			//AD�������ֵֹ
					int ch, 				//AD����ͨ��
					double tgStart, 		//Ŀ��仯����ʼֵ
					double tgEnd, 			//Ŀ��仯����ֵֹ��
					int tgid,				//Ŀ��ID
					int id);				//���ƹ���ģ��ID����Χ��0��(���� - 1)��
//����AD���ƹ��ܡ�
IMC_PKG_API int WINAPI 
	PKG_IMC_DisADCtrl(IMC_HANDLE handle,   	//�豸���
					int id);				//����ģ��ID����Χ��0��(���� - 1)��

//DA����
//����DA������ܡ�
IMC_PKG_API int WINAPI 
	PKG_IMC_SetDAena(IMC_HANDLE handle,   	//�豸���
		 			int ena,				//ʹ�ܻ��ǽ�ֹ��
					int ch);				//DA���ͨ��
//����DA�Ļ������ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetDAout(IMC_HANDLE handle,		//�豸���
		 			double da, 				//DA�������ѹֵ,��Χ��-10.0V ~ +10.0V
					int ch);				//DA���ͨ��
//����DA�������ָ���ļĴ����ı仯���仯
IMC_PKG_API int WINAPI 
	PKG_IMC_SetDAFollow(IMC_HANDLE handle,  //�豸��� 
					double DAstart, 		//DA���ֵ�仯�������ʼֵ��
					double DAend, 			//DA���ֵ�仯�������ֵֹ
					int ch, 				//DA���ͨ����
	 				int paramloc, 			//DA���ֵ������ƿ��е��ĸ��Ĵ�����ֵ���仯,����Ϊ0ʱ����ֹ�˸����������
					int axis, 				//����ļĴ��������
					int tgStart, 			//����ļĴ����ı仯�������ʼֵ
					int tgEnd);				//����ļĴ����ı仯�������ֵֹ��
//����DA�������ָ���ļĴ����ı仯���仯
IMC_PKG_API int WINAPI 
	PKG_IMC_SetDAFollowEX(IMC_HANDLE handle,//�豸��� 
					double DAstart,  		//DA���ֵ�仯�������ʼֵ��
					double DAend, 			//DA���ֵ�仯�������ֵֹ
					int ch, 				//DA���ͨ����
	 				double tgStart,  		//Ŀ��仯�������ʼֵ
					double tgEnd, 			//Ŀ��仯�������ֵֹ��
					int tgid);				//Ŀ��ID

//PWM����
//����PWM�������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPWMena(IMC_HANDLE handle,   	//�豸���
		 			int ena, 				//ʹ�ܻ��ǽ�ֹ��
					int polar, 				//PWM����������Ч����
					int ch);				//PWM���ͨ��
 //����PWM�Ļ������ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPWMprop(IMC_HANDLE handle,	//�豸���
 	 				double pwm, 			//pwm��ռ�ձ�,��Χ��0 ~ 1.0
					int ch);				//PWM���ͨ��
//����PWM�������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetPWMfreq(IMC_HANDLE handle, 	//�豸���
					double freq, 			//PWM�����Ƶ�ʣ���λΪ����/��
					int ch);				//PWM���ͨ��
 //����PWM�����ռ�ձȸ���ָ���Ĵ����ı仯���仯
IMC_PKG_API int WINAPI 
	PKG_IMC_PWMpropFollow(IMC_HANDLE handle,//�豸���
					int polar,				//PWM����������Ч��ƽ��0���͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					double freq,			//PWM�����Ƶ�ʣ���λΪ����/��
					double PWMstart, 		//PWMռ�ձȸ���ָ���Ĵ�������ı仯�������ʼֵ
					double PWMend, 			//PWMռ�ձȸ���ָ���Ĵ�������ı仯�������ֵֹ
					double offset,			//PWM���ռ�ձȵ�ƫ��ֵ
					int ch,					//PWM���ͨ��
	 				int paramloc, 			//PWMռ�ձȸ���仯�Ŀ��ƿ��еļĴ�����ַ,����Ϊ0ʱ����ֹ�˸����������
					int axis, 				//����ļĴ��������
					int paramStart, 		//����ļĴ����仯�������ʼֵ
					int paramEnd);			//����ļĴ����仯�������ֵֹ
 //����PWM�����ռ�ձȸ���ָ���Ĵ����ı仯���仯
IMC_PKG_API int WINAPI 
	PKG_IMC_PWMpropFollowEX(IMC_HANDLE handle, 	//�豸���
					int polar,				//PWM����������Ч��ƽ��0���͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					double freq,			//PWM�����Ƶ�ʣ���λΪ����/��
					double PWMstart, 		//PWMռ�ձȸ���ָ��Ŀ������ı仯�������ʼֵ
					double PWMend, 			//PWMռ�ձȸ���ָ��Ŀ������ı仯�������ֵֹ
					double offset,			//PWM���ռ�ձȵ�ƫ��ֵ
					int ch,					//PWM���ͨ��
					double tgStart, 		//�����Ŀ��仯�������ʼֵ
					double tgEnd, 			//�����Ŀ��仯�������ֵֹ
					int tgid);				//Ŀ��ID
 //����PWM�����Ƶ�ʸ���ָ���Ĵ����ı仯���仯
IMC_PKG_API int WINAPI 
	PKG_IMC_PWMfreqFollow(IMC_HANDLE handle,//�豸���
					int polar,				//PWM����������Ч��ƽ��0���͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					double prop,			//PWM�����ռ�ձ�,��Χ��0 ~ 1.0
					double freqStart, 		//PWM���Ƶ�ʸ���ָ���Ĵ�������ı仯�������ʼֵ����λΪ����/��
					double freqEnd, 		//PWM���Ƶ�ʸ���ָ���Ĵ�������ı仯�������ֵֹ����λΪ����/��
					double offset,			//PWM���Ƶ�ʵ�ƫ��ֵ
					int ch,					//PWM���ͨ��
	 				int paramloc, 			//PWM���Ƶ�ʸ���仯�Ŀ��ƿ��еļĴ�����ַ,����Ϊ0ʱ����ֹ�˸����������
					int axis, 				//����ļĴ��������
					int paramStart, 		//����ļĴ����仯�������ʼֵ
					int paramEnd);			//����ļĴ����仯�������ֵֹ 
 //����PWM�����Ƶ�ʸ���ָ��Ŀ��ı仯���仯
IMC_PKG_API int WINAPI 
	PKG_IMC_PWMfreqFollowEX(IMC_HANDLE handle, 	//�豸���
					int polar, 				//PWM����������Ч��ƽ��0���͵�ƽ��Ч�� ���㣺�ߵ�ƽ��Ч
					double prop, 			//PWM�����ռ�ձ�,��Χ��0 ~ 1.0
					double freqStart,  		//PWM���Ƶ�ʵı仯�������ʼֵ����λΪ����/��
					double freqEnd,  		//PWM���Ƶ�ʵı仯�������ֵֹ����λΪ����/��
					double offset, 			//PWM���Ƶ�ʵ�ƫ��ֵ
					int ch,					//PWM���ͨ��
					double tgStart, 		//�����Ŀ��仯�������ʼֵ
					double tgEnd, 			//�����Ŀ��仯�������ֵֹ 
					int tgid );				//Ŀ��ID
 //ȡ��PWM������湦�ܡ�
IMC_PKG_API int WINAPI 
	PKG_IMC_DisPWMFollow(IMC_HANDLE handle,  //�豸���
					int ch);				//PWM���ͨ��
 //ʹ�ܲ������ܡ�
IMC_PKG_API int WINAPI 
	PKG_IMC_EnaCompen(IMC_HANDLE handle, 	//�豸���
					int ena, 				//���㣺���ò������ܣ� �㣺���ò������ܡ�
					int axis);				//���
//���ò�������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetCompenInfo(IMC_HANDLE handle,//�豸���
					double startvel,		//��������ʼ�ٶȣ���λΪ����/���롣
					double endvel, 			//������ֹʱ���ٶȣ���λΪ����/���롣
					double tgvel, 			//�������ٶȣ���λΪ����/���롣
					double acc, 			//�����ļ��ٶȣ���λΪ����/ƽ�����롣
					double dec, 			//�����ļ��ٶȣ���λΪ����/ƽ�����롣
					long dist, 				//�����ļ�϶��С����λΪ���塣
					int axis);				//���

//ʹ��λ�ñȽ����
IMC_PKG_API int WINAPI 
	PKG_IMC_EnaCMPOut(IMC_HANDLE handle, 	//�豸���
					int ena,				//���㣺���ñȽ�������ܣ� �㣺���ñȽ�������ܡ�
					int mod, 				//�Ƚ�ģʽ���㣺�ȽϾ��롣 ���㣺�Ƚ�λ��
					int time, 				//�������Ŀ�ȣ���λΪ125uS��Ĭ��ֵΪ8
					int axis);				//���
//���ñȽ������λ�û�λ��
IMC_PKG_API int WINAPI 
	PKG_IMC_SetCMPInfo(IMC_HANDLE handle, 	//�豸���
					int dist, 				//λ�û�λ�ƣ���λΪ���塣
					int axis);				//���
//����λ�ò�����
IMC_PKG_API int WINAPI 
	PKG_IMC_EnaCapture(IMC_HANDLE handle, 	//�豸���
					int ena,				//ʹ�ܻ��ǽ�ֹ̽�벶���ܣ��㣺��ֹ�����㣺ʹ��
					int only, 				//�㣺̽���źŵ�ÿ�����붼���񣻷��㣺ֻ����һ��̽������
					int axis);				//���
//��ȡ̽�벶���λ������
IMC_PKG_API int WINAPI 
	PKG_IMC_GetCapData(IMC_HANDLE handle,  	//�豸���
					int rdnum, 				//��Ҫ��ȡ�����ݸ���
					long *pdata, 			//���ڱ����ȡ�����ݵĻ�����
					int *dataNum, 			//ʵ�ʶ�ȡ�������ݸ���
					int *lastNum, 			//���ƿ���ʣ������ݸ���
					int axis);				//���

//������������
IMC_PKG_API int WINAPI 
	PKG_IMC_SetGantry(IMC_HANDLE handle,  	//�豸���
					double gantrykp, 		//������λ��ƫ������ϵ��������˲���Ϊ0�����ֹƫ��������
					unsigned short limit, 	//������λ��ƫ�����ֵ����������λ��ƫ�����ֵ�����������޴���
					unsigned short errwin,	//��������λ��ƫ�����ֵ����ʼƫ������������������
					int maxis, 				//����������				
					int axis);				//�Ӷ�������
//ȡ����������
IMC_PKG_API int WINAPI 
	PKG_IMC_DisGantry(IMC_HANDLE handle,  	//�豸���
					int axis);				//�Ӷ�������
//����Դ��������Ŀ�������ֵ����Ӧ�ı仯
IMC_PKG_API int WINAPI 
	PKG_IMC_PropFollow(IMC_HANDLE handle,  	//�豸�����
					int srcParam, 			//Դ������ַ
					int srcAxis, 			//Դ�������
					int srcStart, 			//Դ�����仯�������ʼֵ
					int srcEnd, 			//Դ�����仯�������ֵֹ
					int srcOffset, 			//Դ�����仯��ƫ��ֵ
					int tgParam, 			//Ŀ�������ַ
					int tgAxis, 			//Ŀ��������
					int tgStart, 			//Ŀ������仯�������ʼֵ
					int tgEnd, 				//Ŀ������仯�������ֵֹ
					int id);				//��������ģ��ID
//ȡ���������湦��
IMC_PKG_API int WINAPI 
	PKG_IMC_DisPropFollow(IMC_HANDLE handle,  	//�豸�����
					int id);				//��������ģ��ID

//��ȡ״̬����
//��ȡ����
IMC_PKG_API int WINAPI 
	PKG_IMC_GetNaxis(IMC_HANDLE Handle); 	//�豸�����

//��ȡ���ƿ��ͺ�
IMC_PKG_API unsigned int WINAPI 
	PKG_IMC_GetType(IMC_HANDLE Handle); 	//�豸�����
//��ȡ���ƿ�����������˿ڵĸ���
IMC_PKG_API int WINAPI 
	PKG_IMC_GetOutputNum(unsigned int type);//���ƿ��ͺ�
//��ȡ���ƿ�����������˿ڵĸ���
IMC_PKG_API int WINAPI 
	PKG_IMC_GetInputNum(unsigned int type);	//���ƿ��ͺ�
//��ȡ���ƿ�ģ��������ͨ���ĸ���
IMC_PKG_API int WINAPI 
	PKG_IMC_GetADchNum(unsigned int type);	//���ƿ��ͺ�
//��ȡ���ƿ�ģ�������ͨ���ĸ���
IMC_PKG_API int WINAPI 
	PKG_IMC_GetDAchNum(unsigned int type);	//���ƿ��ͺ�
//��ȡ���ƿ�PWM���ͨ���ĸ���
IMC_PKG_API int WINAPI 
	PKG_IMC_GetPWMchNum(unsigned int type);

//���������Ļ�еλ�á�
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetEncp(IMC_HANDLE Handle, 	//�豸�����
	 				long pos[], 			//���ڱ����еλ�õ����飻��λΪ���壻
					int axisnum);			//���ƿ���������
 //����������ָ��λ��
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetCurpos(IMC_HANDLE Handle, 	//�豸�����
	 				long pos[], 			//���ڱ���ָ��λ�õ����飻��λΪ���壻
					int axisnum);			//���ƿ���������
 //��ȡ�߼�λ��
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetLogicpos(IMC_HANDLE Handle,  //�豸�����
					long pos[],  			//���ڱ����߼�λ�õ����飻��λΪ���壻
					int axisnum);			//���ƿ���������
 //��ȡ�߼��ٶ�
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetLogicVel(IMC_HANDLE Handle,  //�豸�����
					double vel[],  			//���ڱ����߼��ٶȵ����飻��λΪ����/���룻
					int axisnum);			//���ƿ���������
 //���������Ĵ���״̬
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetErrorReg(IMC_HANDLE Handle, //�豸�����
	 				unsigned short err[], 	//���ڱ���������Ĵ���״̬���д�������Ӧ��λ����1��
					int axisnum);			//���ƿ���������
 //�����������˶�״̬
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetMoving(IMC_HANDLE Handle, 	//�豸�����
					unsigned short moving[],//���ڱ�����������˶�״̬���㣺��ֹͣ�˶��� ���㣺�����˶���
					int axisnum);			//���ƿ���������
 //���������Ĺ�������˿�״̬
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetAin(IMC_HANDLE Handle,  	//�豸�����
					unsigned short ain[][6],//���ڱ��������Ṧ������˵�״̬
					int axisnum);			//���ƿ���������
 //�������ͨ������˿ڵ�״̬
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetGin(IMC_HANDLE Handle, 		//�豸�����
					unsigned short gin[32]);//���ڱ�������ͨ������˵�״̬��
 //�����������˿ڵ�״̬
 IMC_PKG_API int WINAPI 
	 PKG_IMC_GetGout(IMC_HANDLE Handle, 	//�豸�����
					unsigned short gout[48]);//���ڱ�����������˵�״̬
 
 IMC_PKG_API int WINAPI 
	 PKG_IMC_ClearError(IMC_HANDLE Handle,  //�豸�����
					int axis);				//��Ҫ�����������
//�������ܺ���
 //������������ͣ������ͣ״̬
IMC_PKG_API int WINAPI 
	PKG_IMC_Emstop(IMC_HANDLE Handle, 		//�豸�����
					int isStop);			//��ͣ���ǽ����ͣ�����㣺��ͣ�� �㣺�����ͣ��
//��������������ͣ������ͣ״̬
IMC_PKG_API int WINAPI 
	PKG_IMC_Pause(IMC_HANDLE Handle, 		//�豸�����
					int pause);				//��ͣ���ǽ����ͣ״̬�����㣺��ͣ�� �㣺�����ͣ��
//�����ı��˶��Ľ������ʡ�������������Ϊ0ʱ����ʵ����ͣ���ٴ���Ϊ����������ͣ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetFeedrate (IMC_HANDLE handle, //�豸�����
					double rate); 			//�������ʣ�

//�˳��ȴ��˶����
IMC_PKG_API void WINAPI 
	PKG_IMC_ExitWait();
//���������ش���ʱ��ʹ�ô˺�����ô�����ʾ
IMC_PKG_API const char * WINAPI 
	PKG_IMC_GetFunErrStrA();
IMC_PKG_API const unsigned short * WINAPI 
	PKG_IMC_GetFunErrStrW();
//��ô���Ĵ����Ĵ�����Ϣ˵��
IMC_PKG_API const char * WINAPI 
	PKG_IMC_GetRegErrorStrA(unsigned short err);
IMC_PKG_API const unsigned short * WINAPI 
	PKG_IMC_GetRegErrorStrW(unsigned short err);

//ADD�¼�
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ������ӣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_ADD32(EventInfo *info,	//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis,		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis, 		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ����ֵ������ӣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_ADD32i(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    long data, 							//32λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ������ӣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_ADD48(EventInfo *info,	//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ�� 
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ����ֵ������ӣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_ADD48i(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    __int64 data, 						//64λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����

//CMP�¼�
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ�����������������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_CMP32(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ����ֵ�����������������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_CMP32i(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    long data, 							//32λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ�����������������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_CMP48(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ����ֵ�����������������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_CMP48i(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    __int64 data, 						//64λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����

//SCA�¼�
//��ĳ���Ĵ�����ֵ������һ���Ĵ���ָ���ı��ʣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SCA32(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ����ָ���ı��ʣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SCA32i(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    double data, 							//32λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ������һ���Ĵ���ָ���ı��ʣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SCA48(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ���Գ���ָ���ı��ʣ���������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SCA48i(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    double data, 						//64λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//MUL�¼�
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32L(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32iL(EventInfo *info,//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    long data, 							//32λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32A(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//
IMC_PKG_API int WINAPI PKG_Fill_MUL32iA(EventInfo *info,//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    long data, 							//32λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����

//COP�¼�
//��ĳ��16λ�Ĵ�����ֵ��ֵ��Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_COP16(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ��32λ�Ĵ�����ֵ��ֵ��Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_COP32(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ��48λ�Ĵ�����ֵ��ֵ��Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_COP48(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����

//SET�¼�
//��ָ������ֵ��ֵ��16λĿ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SET16(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short data, 						//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ָ������ֵ��ֵ��32λĿ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SET32(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					long data, 							//32λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ָ������ֵ��ֵ��48λĿ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_SET48(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					__int64 data, 						//64λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����


//OR�¼�
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ���л����㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_OR16(EventInfo *info,	//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ���л����㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_OR16B(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ������ֵ���л����㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_OR16i(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
					short data, 						//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ������ֵ���л����㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_OR16iB(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
					short data, 						//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����

//AND�¼�
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ���������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_AND16(EventInfo *info,  //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ���������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_AND16B(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ������ֵ���������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_AND16i(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
					short data, 						//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ������ֵ���������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_AND16iB(EventInfo *info, //�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
					short data, 						//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����


//XOR�¼�
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ����������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_XOR16(EventInfo *info,	//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ����һ���Ĵ�����ֵ����������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_XOR16B(EventInfo *info,	//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
                    short Src2, short Src2_axis,  		//�Ĵ���2�ĵ�ַ�����Ӧ�����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ������ֵ����������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_XOR16i(EventInfo *info,	//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType, 					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
					short data, 						//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����
//��ĳ���Ĵ�����ֵ��ָ������ֵ����������㣬��������浽Ŀ��Ĵ���
IMC_PKG_API int WINAPI PKG_Fill_XOR16iB(EventInfo *info,//�¼��ṹ��ָ�룬�¼�ָ�����¼�����ָ��ָ��ĵ�ַ��
					short  EventType,					//�¼����ͣ���ö��IMC_EventType�еĳ�Ա��ֵ
					short Src1, short Src1_axis, 		//�Ĵ���1�ĵ�ַ�����Ӧ�����
					short data,							//16λ����
                    short dest, short dest_axis);		//Ŀ��Ĵ����ĵ�ַ�����Ӧ�����


//�ײ㺯����װ
//���ö���Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetMulParam(IMC_HANDLE Handle,	//�豸�����
						WR_MUL_DES pdes[],	//WR_MUL_DES�ṹ�����飻
						int ArrNum,			//pdes��������Ч���ݵĸ�����
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//����16λ�Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParam16(IMC_HANDLE Handle, 	//�豸�����
						short paramloc,		//�Ĵ�����ַ��
						short data,			//16λ��������
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//����32λ�Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParam32(IMC_HANDLE Handle, 	//�豸�����
						short paramloc, 	//�Ĵ�����ַ��
						int data, 			//32λ��������
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//����48λ�Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParam48(IMC_HANDLE Handle, 	//�豸�����
						short paramloc, 	//�Ĵ�����ַ��
						__int64 data, 		//64λ��������
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//���Ĵ���ĳ��λ��ֵ��Ϊָ��ֵ��1����0��
IMC_PKG_API int WINAPI 
	PKG_IMC_SetParamBit(IMC_HANDLE Handle, 	//�豸�����
						short paramloc, 	//�Ĵ�����ַ��
						short bit,			//�Ĵ�����ĳ��λ����Χ 0 �C 15��
						short val, 			//ָ����ֵ, 1����0��
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//���Ĵ���ָ����λ��ֵ��1��Ϊ0������0��Ϊ1
IMC_PKG_API int WINAPI 
	PKG_IMC_TurnParamBit(IMC_HANDLE Handle, //�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short bit, 				//�Ĵ�����ĳ��λ����Χ 0 �C 15��
					int axis,				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//��λ������Ĵ�����ĳЩλ
IMC_PKG_API int WINAPI 
	PKG_IMC_ORXORParam(IMC_HANDLE Handle, 	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short ORdata, 			//��Ĵ�����������ֵ��
					short XORdata, 			//��Ĵ�������������ֵ��
					int axis,				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//����FIFOִ�к���ָ�ֱ���Ĵ�����ĳ��λ��Ϊָ��ֵ��ʱΪֹ
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitParamBit(IMC_HANDLE Handle,	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short bit, 				//�Ĵ�����ĳ��λ����Χ 0 �C 15��
					short val, 				//ָ��ֵ��1��0��
					int timeout, 			//��ʱʱ�䣬��λΪ���룻
					int axis, 				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//����FIFOִ�к���ָ�ֱ�������趨��ʱ��Ϊֹ
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitTime(IMC_HANDLE Handle,		//�豸�����
					int time, 				//�ȴ�ʱ�䣬��λΪ����
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//����FIFOִ�к���ָ�ֱ���Ĵ�����ֵ��Ϊָ��ֵ��ʱΪֹ
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitParam(IMC_HANDLE Handle, 	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short data, 			//ָ����ֵ��
					int timeout, 			//��ʱʱ�䣬��λΪ���룻
					int axis, 				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//����FIFOִ�к���ָ�ֱ���Ĵ�����ֵ��mask����������ֵ��dataֵ��Ȼ�ʱΪֹ
IMC_PKG_API int WINAPI 
	PKG_IMC_WaitParamMask(IMC_HANDLE Handle,//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short mask, 			//��Ĵ������������ֵ
					short data, 			//���ڱȽϵ�ֵ��
					int timeout, 			//��ʱʱ�䣬��λΪ���룻
					int axis, 				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//��ȡ����Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetMulParam(IMC_HANDLE Handle, 	//�豸�����
					WR_MUL_DES pdes[], 		//WR_MUL_DES�ṹ�����飻
					int ArrNum);			//WR_MUL_DES�ṹ���������Ч��Ա������
//��ȡ16λ�Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetParam16(IMC_HANDLE Handle, 	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short* data, 			//16λ���ͱ����ĵ�ַ�����ڱ���16λ�Ĵ�����ֵ��
					int axis);				//��ţ�
//��ȡ16λ�Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetADParam16(IMC_HANDLE Handle, //�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short* data, 			//16λ���ͱ����ĵ�ַ�����ڱ���16λ�Ĵ�����ֵ��
					int axis);				//��ţ�
//��ȡ32λ�Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetParam32(IMC_HANDLE Handle, 	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					int *data, 				//32λ���ͱ����ĵ�ַ�����ڱ���32λ�Ĵ�����ֵ��
					int axis);				//��ţ�
//��ȡ48λ�Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetParam48(IMC_HANDLE Handle, 	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					__int64 *data, 			//64λ���ͱ����ĵ�ַ�����ڱ���48λ�Ĵ�����ֵ��
					int axis);				//��ţ�
//����Ϊģ��������ר�ú���
//���ö���Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADMulParam(IMC_HANDLE Handle,	//�豸�����
						WR_MUL_DES pdes[],	//WR_MUL_DES�ṹ�����飻
						int ArrNum,			//pdes��������Ч���ݵĸ�����
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//����16λ�Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADParam16(IMC_HANDLE Handle, 	//�豸�����
						short paramloc,		//�Ĵ�����ַ��
						short data,			//16λ��������
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//����32λ�Ĵ���Ϊָ��ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADParam32(IMC_HANDLE Handle, 	//�豸�����
						short paramloc, 	//�Ĵ�����ַ��
						int data, 			//32λ��������
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��

//���Ĵ���ĳ��λ��ֵ��Ϊָ��ֵ��1����0��
IMC_PKG_API int WINAPI 
	PKG_IMC_SetADParamBit(IMC_HANDLE Handle, 	//�豸�����
						short paramloc, 	//�Ĵ�����ַ��
						short bit,			//�Ĵ�����ĳ��λ����Χ 0 �C 15��
						short val, 			//ָ����ֵ, 1����0��
						int axis,			//��ţ�
						int fifo);			//ָ������ָ��͵��ĸ�FIFO��
//���Ĵ���ָ����λ��ֵ��1��Ϊ0������0��Ϊ1
IMC_PKG_API int WINAPI 
	PKG_IMC_TurnADParamBit(IMC_HANDLE Handle, //�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short bit, 				//�Ĵ�����ĳ��λ����Χ 0 �C 15��
					int axis,				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//��λ������Ĵ�����ĳЩλ
IMC_PKG_API int WINAPI 
	PKG_IMC_ORXORADParam(IMC_HANDLE Handle, 	//�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short ORdata, 			//��Ĵ�����������ֵ��
					short XORdata, 			//��Ĵ�������������ֵ��
					int axis,				//��ţ�
					int fifo);				//ָ������ָ��͵��ĸ�FIFO��
//��ȡ����Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetADMulParam(IMC_HANDLE Handle, 	//�豸�����
					WR_MUL_DES pdes[], 		//WR_MUL_DES�ṹ�����飻
					int ArrNum);			//WR_MUL_DES�ṹ���������Ч��Ա������
//��ȡ16λ�Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetADParam16(IMC_HANDLE Handle, //�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					short* data, 			//16λ���ͱ����ĵ�ַ�����ڱ���16λ�Ĵ�����ֵ��
					int axis);				//��ţ�
//��ȡ32λ�Ĵ�����ֵ
IMC_PKG_API int WINAPI 
	PKG_IMC_GetADParam32(IMC_HANDLE Handle, //�豸�����
					short paramloc, 		//�Ĵ�����ַ��
					int *data, 				//32λ���ͱ����ĵ�ַ�����ڱ���32λ�Ĵ�����ֵ��
					int axis);				//��ţ�

//�����õ��¼���װ�����ƿ���
IMC_PKG_API int WINAPI 
	PKG_IMC_InstallEvent(IMC_HANDLE Handle, //�豸�����
					EventInfo pEvent[], 		//�¼��ṹ�����飬���¼���亯����䣻
					int EventNum	//�¼�ָ���������
					);
//ֹͣ��װ���¼�����(ж���¼���
IMC_PKG_API int WINAPI 
	PKG_IMC_StopEvent(IMC_HANDLE Handle); //�豸�����

#endif