#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_QMyClient.h"

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

signals:
	void sig_mainWindowBeMoved();
	void sig_cameraManagerChanged();
	
private:
	Ui::QMyClientClass ui;

	QCameraSettingDlg *m_pCameraSettingDlg;
	QCameraManager *m_pCameraManager;
};
