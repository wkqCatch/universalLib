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
	void slot_connectAllDeviceCompleted();		//������̨����������������
	void slot_updateTitleOnTime();				//��ʱˢ�±���
	void slot_refreshCamera();					//ˢ�����
	void accept() override;						//����ѡ��
	void reject() override;						//������ѡ��

signals:
	void sig_connectAllDevice();								//������̨�����ϵ��������
	void sig_deleteAllDevice();									//ɾ�����������ŵ����
	void sig_deleteSpecificDevice(QSentechCamera * pCamera);   //ɾ��ָ�������

private:
	QCustomDialogTitleBar *m_pCustomTitlebar;
	QCameraManager *m_pCameraManager;

	QTimer		   *m_pConnectingTimer;         //���Ӷ�ʱ��
};

