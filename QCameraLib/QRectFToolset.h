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

	void appendRectFTool(QKindOfRectF rectfTool);								//添加一种矩形工具
	void appendRectFTool(int nPenWidth, QColor penColor, int nFontSize);
	void deleteRectFTool(int nIndex);										//删除一种矩形工具
	void clearRectFTool();													//清除所有矩形工具

	void paintEvent(QPainter &painter);					//绘制矩形工具集
	void mousePressEvent(QMouseEvent *pMouseEvent);		//鼠标按下事件
	void mouseReleaseEvent(QMouseEvent *pMouseEvent);	//鼠标释放事件
	void mouseMoveEvent(QMouseEvent *pMouseEvent);		//鼠标移动事件
	void keyPressEvent(QKeyEvent *pKeyEvent);			//键盘按下事件

private:
	QVector<QKindOfRectF> m_vecRectFTool;		//矩形的种类合集

	int m_nCurrentCategory;					//当前选中矩形种类
	int m_nCurrentIndex;					//当前选中矩形种类的索引序号
};
