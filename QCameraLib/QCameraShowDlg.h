#pragma once

#include <QWidget>
#include <QElapsedTimer>
#include "qcameralib_global.h"

#include "QSentechCamera.h"
#include "QDrawFigurePanel.h"

#include <QMutex>

class QTimer;
class QCAMERALIB_EXPORT QCameraShowDlg : public QWidget
{
	Q_OBJECT

public:
	QCameraShowDlg(QWidget *parent = nullptr);
	virtual ~QCameraShowDlg();

	void onImageCallback(PvBuffer *pBuffer, void *pUser);    //回调函数
	void attachCamera(QSentechCamera *pCamera);				 //为该控件关联一个对话框
	void detachCamera();									 //解除关联

	void countImgScaled();									 //计算图像显示时的缩放等

	void showDrawFigurePanel(bool bShow);					 //显示绘图面板

	bool isAttachedCamera() const;							 //是否已经关联相机

protected:
	void paintEvent(QPaintEvent *pPaintEvent) override;      //绘图
	void resizeEvent(QResizeEvent *pResizeEvent) override;   //尺寸改变

signals:
	void sig_refreshShowImg();									 //刷新显示的图片
	void sig_takeAPhotoRightNow();								 //刷新待处理的照片
	void sig_updateImgRegion(int nOffsetX, int nOffsetY, int nWidth, int nHeight);
	void sig_updateImgPos(int nX, int nY);
	void sig_sendDealImg(const quint8 *pData, int nWidth, int nHeight, int nChannels);    //发送待处理的数据出去

public slots:
	void slot_windowBeMoved();								//窗口被移动了，用于更新绘图窗口的坐标
	void slot_requestTakeAPhotoCompleted();					//处理图像刷新完成
	void slot_requestTakeAPhoto();							//请求刷新处理的图像
	void slot_requestShowDynamicImage();					//请求显示动态图像
	void slot_takeAPhotoTimeout();							//请求拍照超时

private:
	QSentechCamera *m_pCameraDevice;						//关联的相机
	int m_nOffsetX;											//X方向的偏移
	int m_nOffsetY;											//Y方向的偏移
	int m_nScaledWidth;										//保持比例的宽度
	int m_nScaledHeight;									//保持比列的高度
	QSize m_showDlgSize;									//显示对话框的尺寸

	QElapsedTimer m_elapsedTimer;							//用于控制刷新的计时

	int m_nDisplayRate;										//显示频率  frames/s

	QDrawFigurePanel *m_pDrawFigurePanel;					//绘图的透明面板

	double m_dAcquisitionRate;								//采集频率

	bool   m_bShowDealImg;									//是否显示处理的图像

	QTimer *m_pTimerTakeAPhotoTimeout;						//拍照超时定时器，用于侦测相机是否掉线				
};
