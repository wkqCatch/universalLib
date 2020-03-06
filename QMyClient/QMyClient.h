#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_QMyClient.h"

#include <opencv2/opencv.hpp>

using namespace cv;

class QCustomTableWidget;
class QCameraManager;
class QCameraSettingDlg;
class QCameraSelectDlg;
class QMyClient : public QMainWindow
{
	Q_OBJECT

public:
	QMyClient(QWidget *parent = Q_NULLPTR);
	~QMyClient();

protected:
	void moveEvent(QMoveEvent *event) override;

public slots:
	void slot_showCameraSettingDlg();
	void slot_newDocument();
	void slot_dealImg();
	void slot_receiveMat(const Mat* pMat);
	void slot_selectedSeedPoint(int nX, int nY);

signals:
	void sig_mainWindowBeMoved();
	void sig_cameraManagerChanged();
	void sig_requestShowDealMat(const Mat *pMat);
	
private:
	Ui::QMyClientClass ui;

	QCameraSettingDlg *m_pCameraSettingDlg;
	QCameraManager *m_pCameraManager;

	Mat				m_matDeal;
};
