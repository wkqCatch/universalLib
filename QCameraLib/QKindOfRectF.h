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

	void setPenWidth(int nWidth);				   //���û��ʵĿ��
	int  getPenWidth() const;

	void   setPenColor(QColor penColor);		   //���û��ʵ���ɫ
	QColor getPenColor() const;		

	void setFontSize(int nFontSize);			   //���������С
	int getFontSize() const;	

	void ClearRectF();							   //�������
	void addRectF(QCustomRectF &rectF);			   //��Ӿ���
	void deleteRectF(int nIndex);				   //ɾ��ָ���ľ���

	void setRectfTopLeft(int nIndex, const QPointF &ptTopLeft);			//�������Ͻǵ�λ
	void setRectfTopLeft(int nIndex, qreal qX, qreal qY);				//�������Ͻǵ�λ
	void setRectfBottomRight(int nIndex, const QPointF &ptBottomRight);	//�������½ǵ�λ
	void setRectfBottomRight(int nIndex, qreal qX, qreal qY);		

	void setRectfTopRight(int nIndex, const QPointF &ptTopRight);			//�������Ͻǵ�λ
	void setRectfTopRight(int nIndex, qreal qX, qreal qY);					//�������Ͻǵ�λ
	void setRectfBottomLeft(int nIndex, const QPointF &ptBottomLeft);		//�������½ǵ�λ
	void setRectfBottomLeft(int nIndex, qreal qX, qreal qY);

	void translateRectF(int nIndex, qreal dX, qreal dY);					//�ƶ�����

	qreal getRectfLeft(int nIndex) const;				//��ȡָ�����ε�X
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

	void setRectfX(int nIndex, qreal dX);		    //����ָ�����ε�X
	void setRectfY(int nIndex, qreal dY);			//����ָ�����ε�Y

	void setRectfWidth(int nIndex, qreal dWidth);
	void setRectfHeight(int nIndex, qreal dHeight);

	void normalizedSpecificRectF(int nIndex);				//������ָ���ľ���
	void calculateSpecificRectfAnchor(int nIndex);			//����ָ�����ε�ê��

	QCustomRectF getSpecificRectF(int nIndex);				//����ָ�������ľ���

	bool judgeRectFbyPoint(const QPointF &pt);
	bool getIsSelectedFlag() const;							//�����Ƿ�ѡ�е�������

	int getSelectedIndex() const;							//����ѡ�е�������
	QCustomRectF::AnchorPos getSelectedAnchorPos() const;	//����ѡ�е�ê��λ��

	void paint(QPainter &painter);

	void setSelected(bool bSelected);				//�����Ƿ�ѡ��
	void setSelectedIndex(int nSelectedIndex);		//���ñ�ѡ�е�������

	int getSizeOfRectf() const;						//��þ��εĸ���

	void setDrawAnchorFlag(bool bDrawAnchor);		//�����Ƿ����ê���־
	bool getDrawAnchorFlag() const;					//��ȡ�Ƿ����ê���־

private:
	QVector<QCustomRectF> m_vecRectF;		//�����б�
	
	int					  m_nPenWidth;		//���ʿ��
	QColor				  m_penColor;		//������ɫ

	QPen				  m_pen;			//����
	QFont				  m_font;			//����

	int					  m_nFontSize;		//�����С

	bool				  m_bSelected;				//�Ƿ�ѡ��
	int					  m_nSelectedIndex;			//��ѡ�еľ���������
	QCustomRectF::AnchorPos m_posSelectedAnchor;	//��ѡ�еľ��ε�ê��λ��

	bool				  m_bDrawAnchorFlag;	//�Ƿ����ê��
};
