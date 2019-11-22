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
};

