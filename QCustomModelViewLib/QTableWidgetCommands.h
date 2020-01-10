#pragma once

#include <QUndoCommand>

class QCustomTableWidget;
class QTableWidgetDeleteCommand : public QUndoCommand
{
public:
	QTableWidgetDeleteCommand(QCustomTableWidget *pTableWidget, QList<QStringList> &listRowContent, QList<int> &listRowIndex);
	virtual ~QTableWidgetDeleteCommand();

	void undo() override;
	void redo() override;

protected:
	QCustomTableWidget	  *m_pTableWidget;
	QList<QStringList> m_listRowContent;  //ÿһ�е�����
	QList<int>         m_listRowIndex;    //�е���ű�
};

class QTableWidgetInsertCommand : public QUndoCommand
{
public:
	QTableWidgetInsertCommand(QCustomTableWidget *pTableWidget, int nInsertRow);
	virtual ~QTableWidgetInsertCommand();

	void undo() override;
	void redo() override;

protected:
	QCustomTableWidget   *m_pTableWidget;
	int					  m_nInsertRow;      //�������
};

class QTableWidgetCutCommand : public QUndoCommand
{
public:
	QTableWidgetCutCommand(QCustomTableWidget *pTableWidget, QList<QStringList> &listRowContent, QList<int> &listRowIndex);
	virtual ~QTableWidgetCutCommand();

	void undo() override;
	void redo() override;

protected:
	QCustomTableWidget *m_pTableWidget;
	QList<QStringList>  m_listRowContent;  //ÿһ�е�����
	QList<int>          m_listRowIndex;    //�е���ű�
};

class QTableWidgetPasteCommand : public QUndoCommand
{
public:
	QTableWidgetPasteCommand(QCustomTableWidget *pTableWidget, QList<QStringList> &listRowContent,
		QList<QStringList> &listCopyAndCutContent, QList<int> &listRowIndex);
	virtual ~QTableWidgetPasteCommand();

	void undo() override;
	void redo() override;

protected:
	QCustomTableWidget *m_pTableWidget;
	QList<QStringList>  m_listRowContent;			//ÿһ�е�����
	QList<QStringList>  m_listCopyAndCutContent;	//���ƺ�ճ��������
	QList<int>          m_listRowIndex;				//�е���ű�

	int                 m_nPasteStartRow;			//ճ������ʼ��
};

class QTableWidgetContentChangeCommand : public QUndoCommand
{
public:
	QTableWidgetContentChangeCommand(QCustomTableWidget *pTableWidget, int &nChangedRow, QList<QString> &listNewContent,
		QList<QString> &listOldContent);
	virtual ~QTableWidgetContentChangeCommand();

	void undo() override;
	void redo() override;

protected:
	QCustomTableWidget   *m_pTableWidget;
	int					  m_nChangedRow;      //�ı����
	QList<QString>        m_listNewContent;   //�ı�������
	QList<QString>		  m_listOldContent;   //�ı�ǰ������
};