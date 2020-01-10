#pragma once

#include <QRectF>
#include <QString>

#define ANCHORNUM 8    //ê�����
#define ANCHORSIZE 8   //Ĭ��ê��ߴ�

class QCustomRectF : public QRectF
{
public:
	enum AnchorPos { etopLeft, emidTop, etopRight, emidRight, ebottomRight, emidBottom, ebottomLeft, emidLeft , enotAnchor};

	QCustomRectF();
	QCustomRectF(qreal dx, qreal dy, qreal dWidth, qreal dHeight);
	QCustomRectF(const QPointF &ptTopLeft, const QPointF &ptBottomRight);
	QCustomRectF(const QPointF &ptTopLeft, const QSizeF &sizef);
	~QCustomRectF();

	void setAnchorSize(int nAnchorDiameter);  //����ê��ֱ��
	int getAnchorSize() const;

	void setRectFText(QString strText);		  //���øþ��ε�����
	QString getRectFText() const;			  //��ȡ�þ��ε�����

	void calculateAnchor();					  //����ê������

	void setAnchorPos(AnchorPos curAnchorPos); //���õ�ǰ��anchorλ��
	AnchorPos getAnchorPos() const;			   //��ȡ��ǰanchor��λ��

	const QRectF* getAnchorArray() const;	   //��ȡanchor������ָ��

	void normalizedCustomRectF();			   //����������
	
private:
	QRectF        m_arrayAnchor[ANCHORNUM];		//ê������
	int			  m_nAnchorSize;				//ê��Ĵ�С

	QString		  m_strRectFText;				//�þ�����ʾ������

	AnchorPos	  m_anchorPos;					//��ѡ�е�anchor��λ��
};
