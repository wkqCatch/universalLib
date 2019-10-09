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
	QMainWindow *m_pMainWindow;     //主窗口指针

	QLabel *m_plbAppIcon;          //应用程序图标
	QLabel *m_plbAppTitle;         //应用程序名称

	QToolButton *m_ptbLanguageSetting;     //语言设置
	QMenu *m_pmenuLanguageSetting;         //语言设置弹出菜单
	QToolButton *m_ptbSkinSetting;         //皮肤设置
	QMenu *m_pmenuSkinSetting;             //皮肤设置弹出菜单
	QToolButton *m_ptbMinimize;            //最小化
	QToolButton *m_ptbMaximize;            //最大化
	QToolButton *m_ptbClose;               //关闭按钮

	int m_nMenubarHeight;                //菜单栏高
	bool m_bMaximizeFlag;                //是否已经最大化
};
