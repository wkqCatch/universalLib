#pragma once

#include <QObject>
#include "quniversalframelib_global.h"

class QDialog;
class QFrame;
class QLabel;
class QToolButton;
class QUNIVERSALFRAMELIB_EXPORT QCustomDialogTitleBar : public QObject
{
	Q_OBJECT

public:
	enum TitleAlign { Left, Center };

	QCustomDialogTitleBar(QDialog *pParent, QFrame *pTitleBar, int nHeight, bool bShowMaximize, TitleAlign titleAlign = Left);
	~QCustomDialogTitleBar();

	void setTitleName(QString strName);
	void setTitleIcon(QString strName);
	void enableMaximize(bool bMaximize);

	public slots:
	void slotShowMaximizeOrNormal();

private:
	QDialog *m_pdlgCustomDlg;        //对话框指针

	QLabel *m_plbTitleIcon;          //标题栏的图标
	QLabel *m_plbTitleName;          //对话框的名称
	QToolButton *m_ptbMinimize;      //最小化按钮
	QToolButton *m_ptbMaximize;      //最大化按钮
	QToolButton *m_ptbClose;         //关闭按钮

	int m_nTitleBarHeight;           //标题栏高
	bool m_bMaximizeFlag;            //是否最大化标志位
};
