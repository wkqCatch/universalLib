#pragma once

#include <QDialog>
#ifdef _DEBUG
#include ".\x64\Debug\uic\ui_QCameraSettingDlg.h"
#else
#include ".\x64\Release\uic\ui_QCameraSettingDlg.h"
#endif

#include "qcameralib_global.h"

class QSentechCamera;
class QCameraManager;
class QCustomDialogTitleBar;
class QCAMERALIB_EXPORT QCameraSettingDlg : public QDialog, public Ui::QCameraSettingDlg
{
	Q_OBJECT

public:
	QCameraSettingDlg(QWidget *parent, QCameraManager *pCameraManager);
	~QCameraSettingDlg();

	void setCameraManager(QCameraManager *pCameraManager);		//设置相机管理类

	void specificControlInAcquisition(bool bEnable);			//特定的控件在采集和非采集模式下的状态

public slots:
	void slot_updateAllControl(int nIndex);						//更新所有控件
	void slot_pixelTypeChanged(QString strPixelType);			//像素格式
	void slot_whiteBalanceChanged(QString strWhiteBalance);		//白平衡
	void slot_triggerModeStateChanged(int nState);				//触发模式状态改变
	void slot_triggerSourceChanged(QString strTriggerSource);	//触发源改变
	void slot_triggerCamera();									//触发相机拍照
	void slot_exposureTimeChanged();							//曝光时间改变
	void slot_acquisitionRateChanged();							//采集频率改变
	void slot_acquisitionControl(bool bState);					//采集控制
	void slot_programerChanged(bool bState);					//开发者模式开启
	void slot_imageWidthChanged();
	void slot_imageHeightChanged();
	void slot_offsetxChanged();
	void slot_offsetyChanged();
	void slot_refreshCamera();
	void slot_cameraDescribeChanged();

private:
	QCameraManager *m_pCameraManager;						//相机管理对象
	QSentechCamera *m_pCurrentCamera;						//当前相机指针
	QCustomDialogTitleBar *m_pTitleBar;						//自定义对话框标题栏
};

