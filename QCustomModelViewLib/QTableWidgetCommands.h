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
	QList<QStringList> m_listRowContent;  //每一行的内容
	QList<int>         m_listRowIndex;    //行的序号表
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
	int					  m_nInsertRow;      //插入的行
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
	QList<QStringList>  m_listRowContent;  //每一行的内容
	QList<int>          m_listRowIndex;    //行的序号表
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
	QList<QStringList>  m_listRowContent;			//每一行的内容
	QList<QStringList>  m_listCopyAndCutContent;	//复制和粘贴的内容
	QList<int>          m_listRowIndex;				//行的序号表

	int                 m_nPasteStartRow;			//粘贴的起始行
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
	int					  m_nChangedRow;      //改变的行
	QList<QString>        m_listNewContent;   //改变后的内容
	QList<QString>		  m_listOldContent;   //改变前的内容
};