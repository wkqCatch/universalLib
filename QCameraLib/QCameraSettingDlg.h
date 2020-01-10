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

	void setCameraManager(QCameraManager *pCameraManager);		//�������������

	void specificControlInAcquisition(bool bEnable);			//�ض��Ŀؼ��ڲɼ��ͷǲɼ�ģʽ�µ�״̬

public slots:
	void slot_updateAllControl(int nIndex);						//�������пؼ�
	void slot_pixelTypeChanged(QString strPixelType);			//���ظ�ʽ
	void slot_whiteBalanceChanged(QString strWhiteBalance);		//��ƽ��
	void slot_triggerModeStateChanged(int nState);				//����ģʽ״̬�ı�
	void slot_triggerSourceChanged(QString strTriggerSource);	//����Դ�ı�
	void slot_triggerCamera();									//�����������
	void slot_exposureTimeChanged();							//�ع�ʱ��ı�
	void slot_acquisitionRateChanged();							//�ɼ�Ƶ�ʸı�
	void slot_acquisitionControl(bool bState);					//�ɼ�����
	void slot_programerChanged(bool bState);					//������ģʽ����
	void slot_imageWidthChanged();
	void slot_imageHeightChanged();
	void slot_offsetxChanged();
	void slot_offsetyChanged();
	void slot_refreshCamera();
	void slot_cameraDescribeChanged();

private:
	QCameraManager *m_pCameraManager;						//����������
	QSentechCamera *m_pCurrentCamera;						//��ǰ���ָ��
	QCustomDialogTitleBar *m_pTitleBar;						//�Զ���Ի��������
};

