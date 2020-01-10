#pragma once

#include <QRectF>
#include <QString>

#define ANCHORNUM 8    //锚点个数
#define ANCHORSIZE 8   //默认锚点尺寸

class QCustomRectF : public QRectF
{
public:
	enum AnchorPos { etopLeft, emidTop, etopRight, emidRight, ebottomRight, emidBottom, ebottomLeft, emidLeft , enotAnchor};

	QCustomRectF();
	QCustomRectF(qreal dx, qreal dy, qreal dWidth, qreal dHeight);
	QCustomRectF(const QPointF &ptTopLeft, const QPointF &ptBottomRight);
	QCustomRectF(const QPointF &ptTopLeft, const QSizeF &sizef);
	~QCustomRectF();

	void setAnchorSize(int nAnchorDiameter);  //设置锚点直径
	int getAnchorSize() const;

	void setRectFText(QString strText);		  //设置该矩形的名称
	QString getRectFText() const;			  //获取该矩形的名称

	void calculateAnchor();					  //计算锚点坐标

	void setAnchorPos(AnchorPos curAnchorPos); //设置当前的anchor位置
	AnchorPos getAnchorPos() const;			   //获取当前anchor的位置

	const QRectF* getAnchorArray() const;	   //获取anchor的数组指针

	void normalizedCustomRectF();			   //规整化矩形
	
private:
	QRectF        m_arrayAnchor[ANCHORNUM];		//锚点数组
	int			  m_nAnchorSize;				//锚点的大小

	QString		  m_strRectFText;				//该矩形显示的名字

	AnchorPos	  m_anchorPos;					//被选中的anchor的位置
};
