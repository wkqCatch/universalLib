#pragma once

#include <QWidget>
#include <QElapsedTimer>
#include "qcameralib_global.h"

#include "QSentechCamera.h"
#include "QDrawFigurePanel.h"

#include <QMutex>

#ifdef _DEBUG
#pragma comment(lib, "../X64/Debug/QImageProcessLib.lib")
#else
#pragma comment(lib, "../X64/Release/QImageProcessLib.lib")
#endif

#include "../QImageProcessLib/QSmartMat.h"

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

	void countImgScaled(int nWidth, int nHeight);			 //计算图像显示时的缩放等

	void showDrawFigurePanel(bool bShow);					 //显示绘图面板

	bool isAttachedCamera() const;							 //是否已经关联相机

	QDrawFigurePanel* getDrawFigurePanel() const;			 //取得绘制图像界面

protected:
	void paintEvent(QPaintEvent *pPaintEvent) override;      //绘图
	void resizeEvent(QResizeEvent *pResizeEvent) override;   //尺寸改变

signals:
	void sig_refreshShowImg();									 //刷新显示的图片
	void sig_takeAPhotoRightNow();								 //刷新待处理的照片
	void sig_updateImgRegion(int nOffsetX, int nOffsetY, int nWidth, int nHeight);

	//注意显示的都是用的RGB顺序，不是BGR
	void sig_sendDealMat(const Mat *pDealMat);					 //发送原始Mat出去
	void sig_sendRequestedPixelValue(int nX, int nY, bool bColor, uchar ucChannal1, uchar ucChannel2, uchar ucChannel3); //发送请求的像素值
	void sig_sendSelectedPixelPoint(int nX, int nY);

public slots:
	void slot_windowBeMoved();								//窗口被移动了，用于更新绘图窗口的坐标
	void slot_requestTakeAPhotoCompleted();					//处理图像刷新完成
	void slot_requestTakeAPhoto();							//请求刷新处理的图像
	void slot_requestShowDynamicImage();					//请求显示动态图像
	void slot_takeAPhotoTimeout();							//请求拍照超时
	void slot_requestShowDesignatedMat(const Mat *pMat);	//显示指定的Mat
	void slot_requestShowOriginalMat();						//请求显示原图像
	void slot_loadLocalImage(const QString &strPath, int nFlags); //加载本地图片
	void slot_responseRequestPixelValue(const QPoint &pt);		  //响应请求像素值信号
	void slot_receiveSelectedPixelValue(int nX, int nY, uchar ucChannale1, uchar ucChannel2, uchar ucChannel3);

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

	bool   m_bShowDynamicImg;								//是否显示动态图像
	
	QTimer *m_pTimerTakeAPhotoTimeout;						//拍照超时定时器，用于侦测相机是否掉线

	Mat m_originalMat;										//原图像矩阵
	Mat m_showMat;											//用于显示的矩阵

	double m_dRatio;										//图像显示的比例与实际图像宽度的比值
};
