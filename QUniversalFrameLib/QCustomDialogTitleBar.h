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
	QDialog *m_pdlgCustomDlg;        //�Ի���ָ��

	QLabel *m_plbTitleIcon;          //��������ͼ��
	QLabel *m_plbTitleName;          //�Ի��������
	QToolButton *m_ptbMinimize;      //��С����ť
	QToolButton *m_ptbMaximize;      //��󻯰�ť
	QToolButton *m_ptbClose;         //�رհ�ť

	int m_nTitleBarHeight;           //��������
	bool m_bMaximizeFlag;            //�Ƿ���󻯱�־λ
};
