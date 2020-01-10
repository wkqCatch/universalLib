#pragma once

#include <QObject>
#include <QPoint>
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

	QCustomDialogTitleBar(QDialog *pParent, QFrame *pTitleBar, int nHeight, TitleAlign titleAlign = Left);
	~QCustomDialogTitleBar();

	void setTitleName(QString strName);
	void setTitleIcon(QString strName);
	void hideMaximize(bool bMaximize);
	void hideMinimize(bool bMinimize);
	void enableMinimize(bool bEnable);
	void enableMaximize(bool bEnable);
	void enableClose(bool bEnable);

	public slots:
	void slotShowMaximizeOrNormal();

	virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
	QDialog *m_pdlgCustomDlg;        //�Ի���ָ��
	QFrame *m_pTitleBar;             //������ָ��

	QLabel *m_plbTitleIcon;          //��������ͼ��
	QLabel *m_plbTitleName;          //�Ի��������
	QToolButton *m_ptbMinimize;      //��С����ť
	QToolButton *m_ptbMaximize;      //��󻯰�ť
	QToolButton *m_ptbClose;         //�رհ�ť

	int m_nTitleBarHeight;           //��������
	bool m_bMaximizeFlag;            //�Ƿ���󻯱�־λ

	bool m_bMovingMode;              //�Ƿ����ƶ�����ģʽ
	QPoint m_ptCursorPreview;        //�����ƶ�ǰָ��
};
