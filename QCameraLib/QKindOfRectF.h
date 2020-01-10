#pragma once

#include <QObject>
#include <QVector>
#include <QColor>
#include <QPen>
#include <QFont>

#include "QCustomRectF.h"

class QPainter;
class QKindOfRectF
{
public:
	QKindOfRectF(QColor penColor, int nPenWidth, int nFontSize);
	QKindOfRectF();
	~QKindOfRectF();

	//QRectFTool(const QRectFTool &rectFCategory);
	//QRectFTool& operator=(const QRectFTool& rectFCategory);

	void setPenWidth(int nWidth);				   //设置画笔的宽度
	int  getPenWidth() const;

	void   setPenColor(QColor penColor);		   //设置画笔的颜色
	QColor getPenColor() const;		

	void setFontSize(int nFontSize);			   //设置字体大小
	int getFontSize() const;	

	void ClearRectF();							   //清除矩形
	void addRectF(QCustomRectF &rectF);			   //添加矩形
	void deleteRectF(int nIndex);				   //删除指定的矩形

	void setRectfTopLeft(int nIndex, const QPointF &ptTopLeft);			//设置左上角点位
	void setRectfTopLeft(int nIndex, qreal qX, qreal qY);				//设置左上角点位
	void setRectfBottomRight(int nIndex, const QPointF &ptBottomRight);	//设置右下角点位
	void setRectfBottomRight(int nIndex, qreal qX, qreal qY);		

	void setRectfTopRight(int nIndex, const QPointF &ptTopRight);			//设置右上角点位
	void setRectfTopRight(int nIndex, qreal qX, qreal qY);					//设置右上角点位
	void setRectfBottomLeft(int nIndex, const QPointF &ptBottomLeft);		//设置左下角点位
	void setRectfBottomLeft(int nIndex, qreal qX, qreal qY);

	void translateRectF(int nIndex, qreal dX, qreal dY);					//移动矩形

	qreal getRectfLeft(int nIndex) const;				//获取指定矩形的X
	void setRectfLeft(int nIndex, qreal dLeft);
	qreal getRectfTop(int nIndex) const;
	void setRectfTop(int nIndex, qreal dTop);
	qreal getRectfRight(int nIndex) const;
	void setRectfRight(int nIndex, qreal dRight);
	qreal getRectfBottom(int nIndex) const;	
	void setRectfBottom(int nIndex, qreal dBottom);

	void moveRectfLeft(int nIndex, qreal qLeft);
	void moveRectfTop(int nIndex, qreal qTop);
	void moveRectfRight(int nIndex, qreal qRight);
	void moveRectfBottom(int nIndex, qreal qBottom);

	void setRectfX(int nIndex, qreal dX);		    //设置指定矩形的X
	void setRectfY(int nIndex, qreal dY);			//设置指定矩形的Y

	void setRectfWidth(int nIndex, qreal dWidth);
	void setRectfHeight(int nIndex, qreal dHeight);

	void normalizedSpecificRectF(int nIndex);				//规整化指定的矩形
	void calculateSpecificRectfAnchor(int nIndex);			//计算指定矩形的锚点

	QCustomRectF getSpecificRectF(int nIndex);				//返回指定索引的矩形

	bool judgeRectFbyPoint(const QPointF &pt);
	bool getIsSelectedFlag() const;							//返回是否选中的索引号

	int getSelectedIndex() const;							//返回选中的索引号
	QCustomRectF::AnchorPos getSelectedAnchorPos() const;	//返回选中的锚点位置

	void paint(QPainter &painter);

	void setSelected(bool bSelected);				//设置是否被选中
	void setSelectedIndex(int nSelectedIndex);		//设置被选中的索引号

	int getSizeOfRectf() const;						//获得矩形的个数

	void setDrawAnchorFlag(bool bDrawAnchor);		//设置是否绘制锚点标志
	bool getDrawAnchorFlag() const;					//获取是否绘制锚点标志

private:
	QVector<QCustomRectF> m_vecRectF;		//矩形列表
	
	int					  m_nPenWidth;		//画笔宽度
	QColor				  m_penColor;		//画笔颜色

	QPen				  m_pen;			//画笔
	QFont				  m_font;			//字体

	int					  m_nFontSize;		//字体大小

	bool				  m_bSelected;				//是否被选中
	int					  m_nSelectedIndex;			//被选中的矩形索引号
	QCustomRectF::AnchorPos m_posSelectedAnchor;	//被选中的矩形的锚点位置

	bool				  m_bDrawAnchorFlag;	//是否绘制锚点
};
