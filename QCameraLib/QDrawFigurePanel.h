#pragma once

#include <QWidget>

#include "QKindOfRectF.h"
#include "QRectFToolset.h"

class QDrawFigurePanel : public QWidget
{
	Q_OBJECT

public:
	enum ResizeMode { noMode, byAnchor, byMove };

	QDrawFigurePanel(QWidget *parent = nullptr);
	~QDrawFigurePanel();

	void enterDrawingMode(int nKindOfRectF);				 //选定一类矩形，进入绘图模式

	void addAKindOfRectF(const QKindOfRectF &kindOfRectF);   //添加一类矩形
	void addAKindOfRectF(QColor penColor, int nPenWidth = 1, int nFontSize = 15);

	void deleteKindOfRectF(int nIndex);						 //删除一类矩形

	void addRectfForSpecificKind(int nKindOfRectF);			 //为指定的矩形类添加矩形框
	void addRectfForSpecificKind(int nKindOfRectF, QCustomRectF customRectF);

	void setDrawAllAnchor(bool bDrawAnchor);				 //设置绘制所有的锚点

	QCustomRectF getSpecificRectF(int nKind, int nIndex);    //获取指定的矩形

public slots:
	void slot_updateImgRegion(int nOffsetX, int nOffsetY, int nWidth, int nHeight);
	void slot_updateImgPos(int nX, int nY);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent *enent) override;

private:
	QVector<QKindOfRectF>	m_vecAllKindsOfRectF;	//自定义矩形种类的合集

	int			  m_nKindOfRectfInOperating;		//当前正在操作的矩形种类
	int			  m_nIndexOfRectfInOperating;		//当前正在操作的矩形序号
	QCustomRectF::AnchorPos m_selectedAnchorPos;	//被选中的锚点位置

	QCustomRectF m_selectedRectfBackup;				//被选中的矩形备份

	bool		  m_bDrawingMode;					//绘图模式
	bool		  m_bStartDrawing;					//开始绘图

	ResizeMode	  m_resizeMode;						//更改尺寸模式
	bool		  m_bStartResizing;					//开始更改尺寸
	bool		  m_bRectfBeSelected;				//有矩形被选中

	QPoint		  m_ptPress;						//鼠标按下点位
	QPoint		  m_ptCurrent;						//鼠标当前点位
	QPoint		  m_ptRelease;						//鼠标释放点位

	QColor		  m_colorBackground;				//背景透明色
};
