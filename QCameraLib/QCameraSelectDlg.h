#pragma once

#include <QDialog>

#ifdef _DEBUG
#include ".\x64\Debug\uic\ui_QCameraSelectDlg.h"
#else
#include ".\x64\Release\uic\ui_QCameraSelectDlg.h"
#endif

//#include "ui_QCameraSelectDlg.h"

#include "qcameralib_global.h"

class QTimer;
class QCameraManager;
class QCustomDialogTitleBar;
class QCAMERALIB_EXPORT QCameraSelectDlg : public QDialog, public Ui::QCameraSelectDlg
{
	Q_OBJECT

public:
	QCameraSelectDlg(QWidget *parent = nullptr);
	QCameraSelectDlg(QWidget *parent, QCameraManager *pCameraManager);
	~QCameraSelectDlg();

	void attachCameraManager(QCameraManager *pCameraManager);
	void detachCameraManager();

protected:

public slots:
	void slot_connectAllDeviceCompleted();		//连接这台电脑上所有相机完成
	void slot_updateTitleOnTime();				//定时刷新标题
	void slot_refreshCamera();					//刷新相机
	void accept() override;						//接受选择
	void reject() override;						//不接受选择

signals:
	void sig_connectAllDevice();								//连接这台电脑上的所有相机
	void sig_deleteAllDevice();									//删除所有连接着的相机
	void sig_deleteSpecificDevice(QSentechCamera * pCamera);   //删除指定的相机

private:
	QCustomDialogTitleBar *m_pCustomTitlebar;
	QCameraManager *m_pCameraManager;

	QTimer		   *m_pConnectingTimer;         //连接定时器
};

