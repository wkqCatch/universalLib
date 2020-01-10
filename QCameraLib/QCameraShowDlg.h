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

	void onImageCallback(PvBuffer *pBuffer, void *pUser);    //�ص�����
	void attachCamera(QSentechCamera *pCamera);				 //Ϊ�ÿؼ�����һ���Ի���
	void detachCamera();									 //�������

	void countImgScaled();									 //����ͼ����ʾʱ�����ŵ�

	void showDrawFigurePanel(bool bShow);					 //��ʾ��ͼ���

	bool isAttachedCamera() const;							 //�Ƿ��Ѿ��������

protected:
	void paintEvent(QPaintEvent *pPaintEvent) override;      //��ͼ
	void resizeEvent(QResizeEvent *pResizeEvent) override;   //�ߴ�ı�

signals:
	void sig_refreshShowImg();									 //ˢ����ʾ��ͼƬ
	void sig_takeAPhotoRightNow();								 //ˢ�´��������Ƭ
	void sig_updateImgRegion(int nOffsetX, int nOffsetY, int nWidth, int nHeight);
	void sig_updateImgPos(int nX, int nY);
	void sig_sendDealImg(const quint8 *pData, int nWidth, int nHeight, int nChannels);    //���ʹ���������ݳ�ȥ

public slots:
	void slot_windowBeMoved();								//���ڱ��ƶ��ˣ����ڸ��»�ͼ���ڵ�����
	void slot_requestTakeAPhotoCompleted();					//����ͼ��ˢ�����
	void slot_requestTakeAPhoto();							//����ˢ�´����ͼ��
	void slot_requestShowDynamicImage();					//������ʾ��̬ͼ��
	void slot_takeAPhotoTimeout();							//�������ճ�ʱ

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

	bool   m_bShowDealImg;									//�Ƿ���ʾ�����ͼ��

	QTimer *m_pTimerTakeAPhotoTimeout;						//���ճ�ʱ��ʱ���������������Ƿ����				
};
