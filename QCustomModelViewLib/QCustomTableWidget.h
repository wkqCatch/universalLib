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
	void setCopyOrCutStateFlag(bool bState);
	void setCopyAndCutContent(const QList<QStringList> &listContent);
	void ClearCopyAndCutContent();
	bool getCopyOrCutFlag() const;
	void setEditContentFlag(bool bState);												//设定正在编辑内容的标志位

	void setCustomDelegateForRow(int nIndex, QAbstractItemDelegate *pItemDelegate);		//设置代理
	void setCustomDelegateForColumn(int nIndex, QAbstractItemDelegate *pItemDelegate);	//设置代理

	virtual void InsertRowData(int nRows);												//插入的数据

	bool eventFilter(QObject *object, QEvent *event) override;

	void clearUndoCommand() const;														//清除所有的undo/redo指令
	void setUndoStackClean() const;														//设置undostack清除

	void addRows();																		//添加行，不压栈

	QAction* getInsertAction() const;													//取得插入行的action
	QAction* getAddAction() const;														//取得添加行的action
	QAction* getDeleteAction() const;													//取得删除行的action
	QAction* getCopyAction() const;														//取得复制行的action
	QAction* getCutAction() const;														//取得剪切行的action
	QAction* getPasteAction() const;													//取得粘贴行的action
	QAction* getUndoAction() const;														//取得取消的action
	QAction* getRedoAction() const;														//取得重做的action

	void updateActionState(bool bState);												//更新各个action的状态
	void updateActionState();

protected:
	void mousePressEvent(QMouseEvent *event) override;
	//void keyPressEvent(QKeyEvent *event) override;

public slots:
	void slot_ShowPopupMenu(const QPoint&);             //显示弹出菜单
	void slot_AddRows();                                //添加行
	void slot_InsertRows();                             //插入行
	void slot_DeleteRows();                             //删除行
	void slot_CopyRows();                               //复制行
	void slot_CutRows();                                //剪切行
	void slot_PasteRows();                              //粘贴行
	void slot_ContentChanged(int nRow, int nColumn);    //内容改变
	void slot_ContentTempStorage(int nRow, int nColumn);//暂存内容

private:
	QMenu	*m_pRightKeyMenu;							//右键菜单
	QAction *m_pactInsert;                              //插入动作
	QAction *m_pactAdd;									//添加动作
	QAction *m_pactDelete;								//删除动作
	QAction *m_pactCopy;								//复制动作
	QAction *m_pactCut;									//剪切动作
	QAction *m_pactPaste;								//粘贴动作
	QAction *m_pactUndo;                                //撤销动作
	QAction *m_pactRedo;                                //重做动作

	QList<QStringList> m_listCopyAndCutContent;         //复制剪切的内容
	bool			   m_bCopyOrCutFlag;                //操作为剪切或者复制的标志  0:复制    1:剪切

	QUndoStack *m_pUndoStack;                           //撤销操作的栈

	QList<QString> m_strRowContentTempStorage;			//双击时暂存item的内容

	bool  m_bEditContentFlag;							//正在编辑内容的标志位

	bool  m_bNeedUpdateActionFlag;						//需要刷新action标志位
};
