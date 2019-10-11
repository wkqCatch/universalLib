#pragma once

#include <QObject>
#include <QPoint>

#include "quniversalframelib_global.h"

class QMainWindow;
class QLabel;
class QToolButton;
class QMenu;
class QMenuBar;
class QUNIVERSALFRAMELIB_EXPORT QCustomMainWindowMenuBar : public QObject
{
	Q_OBJECT

public:
	explicit QCustomMainWindowMenuBar(QMainWindow *pMainWindow, int nMenuBarHeight);
	~QCustomMainWindowMenuBar();

	void setAppIcon(QString strAppIcon);
	void setAppTitle(QString strAppTitle);
	void enableMaximize(bool bMaximize);
	void enableMinimize(bool bMinimize);

	public slots:
	void slotShowNormalOrMaximize();

	virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
	QMainWindow *m_pMainWindow;     //������ָ��
	QMenuBar *m_pMenubar;           //�˵���ָ��

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

	bool m_bMovingMode;                  //�Ƿ����ƶ�����ģʽ
	QPoint m_ptCursorPreview;            //�ƶ�ʱ����¼�����һ��λ��
};
