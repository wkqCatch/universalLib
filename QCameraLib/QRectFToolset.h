#pragma once

#include <QObject>
#include <QVector>

#include "QKindOfRectF.h"

class QPainter;
class QMouseEvent;
class QKeyEvent;
class QRectFToolset : public QObject
{
	Q_OBJECT

public:
	QRectFToolset(QObject *parent = nullptr);
	~QRectFToolset();

	void appendRectFTool(QKindOfRectF rectfTool);								//���һ�־��ι���
	void appendRectFTool(int nPenWidth, QColor penColor, int nFontSize);
	void deleteRectFTool(int nIndex);										//ɾ��һ�־��ι���
	void clearRectFTool();													//������о��ι���

	void paintEvent(QPainter &painter);					//���ƾ��ι��߼�
	void mousePressEvent(QMouseEvent *pMouseEvent);		//��갴���¼�
	void mouseReleaseEvent(QMouseEvent *pMouseEvent);	//����ͷ��¼�
	void mouseMoveEvent(QMouseEvent *pMouseEvent);		//����ƶ��¼�
	void keyPressEvent(QKeyEvent *pKeyEvent);			//���̰����¼�

private:
	QVector<QKindOfRectF> m_vecRectFTool;		//���ε�����ϼ�

	int m_nCurrentCategory;					//��ǰѡ�о�������
	int m_nCurrentIndex;					//��ǰѡ�о���������������
};
