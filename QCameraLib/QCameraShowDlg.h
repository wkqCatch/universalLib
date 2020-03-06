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

	void onImageCallback(PvBuffer *pBuffer, void *pUser);    //�ص�����
	void attachCamera(QSentechCamera *pCamera);				 //Ϊ�ÿؼ�����һ���Ի���
	void detachCamera();									 //�������

	void countImgScaled(int nWidth, int nHeight);			 //����ͼ����ʾʱ�����ŵ�

	void showDrawFigurePanel(bool bShow);					 //��ʾ��ͼ���

	bool isAttachedCamera() const;							 //�Ƿ��Ѿ��������

	QDrawFigurePanel* getDrawFigurePanel() const;			 //ȡ�û���ͼ�����

protected:
	void paintEvent(QPaintEvent *pPaintEvent) override;      //��ͼ
	void resizeEvent(QResizeEvent *pResizeEvent) override;   //�ߴ�ı�

signals:
	void sig_refreshShowImg();									 //ˢ����ʾ��ͼƬ
	void sig_takeAPhotoRightNow();								 //ˢ�´��������Ƭ
	void sig_updateImgRegion(int nOffsetX, int nOffsetY, int nWidth, int nHeight);

	//ע����ʾ�Ķ����õ�RGB˳�򣬲���BGR
	void sig_sendDealMat(const Mat *pDealMat);					 //����ԭʼMat��ȥ
	void sig_sendRequestedPixelValue(int nX, int nY, bool bColor, uchar ucChannal1, uchar ucChannel2, uchar ucChannel3); //�������������ֵ
	void sig_sendSelectedPixelPoint(int nX, int nY);

public slots:
	void slot_windowBeMoved();								//���ڱ��ƶ��ˣ����ڸ��»�ͼ���ڵ�����
	void slot_requestTakeAPhotoCompleted();					//����ͼ��ˢ�����
	void slot_requestTakeAPhoto();							//����ˢ�´����ͼ��
	void slot_requestShowDynamicImage();					//������ʾ��̬ͼ��
	void slot_takeAPhotoTimeout();							//�������ճ�ʱ
	void slot_requestShowDesignatedMat(const Mat *pMat);	//��ʾָ����Mat
	void slot_requestShowOriginalMat();						//������ʾԭͼ��
	void slot_loadLocalImage(const QString &strPath, int nFlags); //���ر���ͼƬ
	void slot_responseRequestPixelValue(const QPoint &pt);		  //��Ӧ��������ֵ�ź�
	void slot_receiveSelectedPixelValue(int nX, int nY, uchar ucChannale1, uchar ucChannel2, uchar ucChannel3);

private:
	QSentechCamera *m_pCameraDevice;						//���������
	int m_nOffsetX;											//X�����ƫ��
	int m_nOffsetY;											//Y�����ƫ��
	int m_nScaledWidth;										//���ֱ����Ŀ��
	int m_nScaledHeight;									//���ֱ��еĸ߶�
	QSize m_showDlgSize;									//��ʾ�Ի���ĳߴ�

	QElapsedTimer m_elapsedTimer;							//���ڿ���ˢ�µļ�ʱ

	int m_nDisplayRate;										//��ʾƵ��  frames/s

	QDrawFigurePanel *m_pDrawFigurePanel;					//��ͼ��͸�����

	double m_dAcquisitionRate;								//�ɼ�Ƶ��

	bool   m_bShowDynamicImg;								//�Ƿ���ʾ��̬ͼ��
	
	QTimer *m_pTimerTakeAPhotoTimeout;						//���ճ�ʱ��ʱ���������������Ƿ����

	Mat m_originalMat;										//ԭͼ�����
	Mat m_showMat;											//������ʾ�ľ���

	double m_dRatio;										//ͼ����ʾ�ı�����ʵ��ͼ���ȵı�ֵ
};
