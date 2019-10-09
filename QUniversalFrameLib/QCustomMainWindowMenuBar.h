#pragma once

#include <QObject>

#include "quniversalframelib_global.h"

class QMainWindow;
class QLabel;
class QToolButton;
class QMenu;
class QUNIVERSALFRAMELIB_EXPORT QCustomMainWindowMenuBar: public QObject
{
	Q_OBJECT

public:
	explicit QCustomMainWindowMenuBar(QMainWindow *pMainWindow, int nMenuBarHeight);
	~QCustomMainWindowMenuBar();

	void setAppIcon(QString strAppIcon);
	void setAppTitle(QString strAppTitle);
	void enableMaximize(bool bMaximize);

public slots:
	void slotShowNormalOrMaximize();

private:
	QMainWindow *m_pMainWindow;     //������ָ��

	QLabel *m_plbAppIcon;          //Ӧ�ó���ͼ��
	QLabel *m_plbAppTitle;         //Ӧ�ó�������

	QToolButton *m_ptbLanguageSetting;     //��������
	QMenu *m_pmenuLanguageSetting;         //�������õ����˵�
	QToolButton *m_ptbSkinSetting;         //Ƥ������
	QMenu *m_pmenuSkinSetting;             //Ƥ�����õ����˵�
	QToolButton *m_ptbMinimize;            //��С��
	QToolButton *m_ptbMaximize;            //���
	QToolButton *m_ptbClose;               //�رհ�ť

	int m_nMenubarHeight;                //�˵�����
	bool m_bMaximizeFlag;                //�Ƿ��Ѿ����
};
