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
	int getCameraNum() const;									//获取相机个数

	QSentechCamera* getSpecificCamera(int nIndex) const;		//获取指定相机指针

	void cameraVectorUpdate(const QVector<QSentechCamera*> &vecCamera); //相机向量更新

public slots:
	void slot_findAllInterface();								//查询所有的NIC接口
	void slot_connectAllDevice();								//连接所有的硬件相机
	bool slot_connectSpecificInterface(const QString &strMac);	//连接指定网口的相机
	void slot_deleteAllDevice();								//清理所有相机
	void slot_deleteSpecificDevice(QSentechCamera* pCamera);	//清理指定的相机

signals:
	void sig_findInterfaceCompleted();
	void sig_connectAllDeviceCompleted();						//连接所有硬件完成信号
	void sig_deleteAllDeviceComplete();							//删除所有应将完成信号

private:
	PvSystem *m_pSystem;
	bool      m_bFindInterceCompleted;

	QVector<QSentechCamera*> m_vecSentechCamera;

	QThread *m_pThread;											//线程
};
