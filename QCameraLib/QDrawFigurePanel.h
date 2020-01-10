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

	void enterDrawingMode(int nKindOfRectF);				 //ѡ��һ����Σ������ͼģʽ

	void addAKindOfRectF(const QKindOfRectF &kindOfRectF);   //���һ�����
	void addAKindOfRectF(QColor penColor, int nPenWidth = 1, int nFontSize = 15);

	void deleteKindOfRectF(int nIndex);						 //ɾ��һ�����

	void addRectfForSpecificKind(int nKindOfRectF);			 //Ϊָ���ľ�������Ӿ��ο�
	void addRectfForSpecificKind(int nKindOfRectF, QCustomRectF customRectF);

	void setDrawAllAnchor(bool bDrawAnchor);				 //���û������е�ê��

	QCustomRectF getSpecificRectF(int nKind, int nIndex);    //��ȡָ���ľ���

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
	QVector<QKindOfRectF>	m_vecAllKindsOfRectF;	//�Զ����������ĺϼ�

	int			  m_nKindOfRectfInOperating;		//��ǰ���ڲ����ľ�������
	int			  m_nIndexOfRectfInOperating;		//��ǰ���ڲ����ľ������
	QCustomRectF::AnchorPos m_selectedAnchorPos;	//��ѡ�е�ê��λ��

	QCustomRectF m_selectedRectfBackup;				//��ѡ�еľ��α���

	bool		  m_bDrawingMode;					//��ͼģʽ
	bool		  m_bStartDrawing;					//��ʼ��ͼ

	ResizeMode	  m_resizeMode;						//���ĳߴ�ģʽ
	bool		  m_bStartResizing;					//��ʼ���ĳߴ�
	bool		  m_bRectfBeSelected;				//�о��α�ѡ��

	QPoint		  m_ptPress;						//��갴�µ�λ
	QPoint		  m_ptCurrent;						//��굱ǰ��λ
	QPoint		  m_ptRelease;						//����ͷŵ�λ

	QColor		  m_colorBackground;				//����͸��ɫ
};
