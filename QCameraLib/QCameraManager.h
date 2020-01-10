#pragma once

#include <QObject>
#include "qcameralib_global.h"

class PvSystem;
class QSentechCamera;
class QThread;
class QCAMERALIB_EXPORT QCameraManager : public QObject
{
	Q_OBJECT

public:
	QCameraManager(QObject *parent = nullptr);
	~QCameraManager();

	const QVector<QSentechCamera*>& getCameraVector() const;
	int getCameraNum() const;									//��ȡ�������

	QSentechCamera* getSpecificCamera(int nIndex) const;		//��ȡָ�����ָ��

	void cameraVectorUpdate(const QVector<QSentechCamera*> &vecCamera); //�����������

public slots:
	void slot_findAllInterface();								//��ѯ���е�NIC�ӿ�
	void slot_connectAllDevice();								//�������е�Ӳ�����
	bool slot_connectSpecificInterface(const QString &strMac);	//����ָ�����ڵ����
	void slot_deleteAllDevice();								//�����������
	void slot_deleteSpecificDevice(QSentechCamera* pCamera);	//����ָ�������

signals:
	void sig_findInterfaceCompleted();
	void sig_connectAllDeviceCompleted();						//��������Ӳ������ź�
	void sig_deleteAllDeviceComplete();							//ɾ������Ӧ������ź�

private:
	PvSystem *m_pSystem;
	bool      m_bFindInterceCompleted;

	QVector<QSentechCamera*> m_vecSentechCamera;

	QThread *m_pThread;											//�߳�
};
