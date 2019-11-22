#pragma once

#include "qcustommodelviewlib_global.h"

#include <QTableWidget>
#include <QList>

class QMenu;
class QAction;
class QUndoStack;
class QCUSTOMMODELVIEWLIB_EXPORT QCustomTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	QCustomTableWidget(QWidget *pParent = nullptr);
	QCustomTableWidget(int rows, int columns, QWidget *parent = nullptr);

	virtual ~QCustomTableWidget();
	
public:
	virtual void InsertRowData(int nRows);
	void setCopyOrCutStateFlag(bool bState);
	void setCopyAndCutContent(const QList<QStringList> &listContent);
	void ClearCopyAndCutContent();
	bool getCopyOrCutFlag() const;
	void setEditContentFlag(bool bState);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	
public slots:
	void slot_ShowPopupMenu(const QPoint&);             //��ʾ�����˵�
	void slot_AddRows();                                //�����
	void slot_InsertRows();                             //������
	void slot_DeleteRows();                             //ɾ����
	void slot_CopyRows();                               //������
	void slot_CutRows();                                //������
	void slot_PasteRows();                              //ճ����
	void slot_ContentChanged(int nRow, int nColumn);    //���ݸı�
	void slot_ContentTempStorage(int nRow, int nColumn);//�ݴ�����
	
private:
	QMenu	*m_pRightKeyMenu;							//�Ҽ��˵�  
	QAction *m_pactInsert;                              //���붯��
	QAction *m_pactAdd;									//��Ӷ���
	QAction *m_pactDelete;								//ɾ������
	QAction *m_pactCopy;								//���ƶ���
	QAction *m_pactCut;									//���ж���
	QAction *m_pactPaste;								//ճ������
	QAction *m_pactUndo;                                //��������
	QAction *m_pactRedo;                                //��������

	QList<QStringList> m_listCopyAndCutContent;         //���Ƽ��е�����
	bool			   m_bCopyOrCutFlag;                //����Ϊ���л��߸��Ƶı�־  0:����    1:����

	QUndoStack *m_pUndoStack;                           //����������ջ

	QList<QString> m_strRowContentTempStorage;			//˫��ʱ�ݴ�item������

	bool  m_bEditContentFlag;							//���ڱ༭���ݵı�־λ
};

