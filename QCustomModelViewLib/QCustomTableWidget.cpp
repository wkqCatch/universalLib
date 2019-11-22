#include "QCustomTableWidget.h"
#include "QTableWidgetCommands.h"

#include <QMenu>
#include <QMouseEvent>
#include <QCursor>
#include <QShortcut>
#include <QHeaderView>
#include <QUndoStack>

QCustomTableWidget::QCustomTableWidget(QWidget *pParent)
	: QTableWidget(pParent)
	, m_pRightKeyMenu(nullptr)
	, m_pactInsert(nullptr)
	, m_pactAdd(nullptr)
	, m_pactDelete(nullptr)
	, m_pactCopy(nullptr)
	, m_pactCut(nullptr)
	, m_pactPaste(nullptr)
	, m_bCopyOrCutFlag(false)
	, m_pUndoStack(nullptr)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::DoubleClicked);

	setFocusPolicy(Qt::NoFocus);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QCustomTableWidget::customContextMenuRequested, this, &QCustomTableWidget::slot_ShowPopupMenu);

	m_pRightKeyMenu = new QMenu(this);

	QIcon insertIcon;
	insertIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/insert_enable"), QIcon::Normal);
	insertIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/insert_disable"), QIcon::Disabled);
	m_pactInsert = m_pRightKeyMenu->addAction(insertIcon, QStringLiteral("插入"));
	m_pactInsert->setShortcut(QKeySequence("Ctrl+Ins"));
	QShortcut *pInsertShortCut = new QShortcut(QKeySequence("Ctrl+Ins"), this);
	connect(pInsertShortCut, &QShortcut::activated, this, &QCustomTableWidget::slot_InsertRows);
	connect(m_pactInsert, &QAction::triggered, this, &QCustomTableWidget::slot_InsertRows);

	QIcon addIcon;
	addIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/add_enable"), QIcon::Normal);
	addIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/add_disable"), QIcon::Disabled);
	m_pactAdd = m_pRightKeyMenu->addAction(addIcon, QStringLiteral("添加"));
	connect(m_pactAdd, &QAction::triggered, this, &QCustomTableWidget::slot_AddRows);

	QIcon deletetIcon;
	deletetIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/delete_enable"), QIcon::Normal);
	deletetIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/delete_disable"), QIcon::Disabled);
	m_pactDelete = m_pRightKeyMenu->addAction(deletetIcon, QStringLiteral("删除"));
	m_pactDelete->setShortcut(QKeySequence::Delete);
	QShortcut *pDeleteShortCut = new QShortcut(QKeySequence::Delete, this);
	connect(pDeleteShortCut, &QShortcut::activated, this, &QCustomTableWidget::slot_DeleteRows);
	connect(m_pactDelete, &QAction::triggered, this, &QCustomTableWidget::slot_DeleteRows);

	QIcon copyIcon;
	copyIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/copy_enable"), QIcon::Normal);
	copyIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/copy_disable"), QIcon::Disabled);
	m_pactCopy = m_pRightKeyMenu->addAction(copyIcon, QStringLiteral("复制"));
	m_pactCopy->setShortcut(QKeySequence::Copy);
	QShortcut *pCopyShortCut = new QShortcut(QKeySequence::Copy, this);
	connect(pCopyShortCut, &QShortcut::activated, this, &QCustomTableWidget::slot_CopyRows);
	connect(m_pactCopy, &QAction::triggered, this, &QCustomTableWidget::slot_CopyRows);

	m_pUndoStack = new QUndoStack(this);

	QIcon cutIcon;
	cutIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/cut_enable"), QIcon::Normal);
	cutIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/cut_disable"), QIcon::Disabled);
	m_pactCut = m_pRightKeyMenu->addAction(cutIcon, QStringLiteral("剪切"));
	m_pactCut->setShortcut(QKeySequence::Cut);
	QShortcut *pCutShortCut = new QShortcut(QKeySequence::Cut, this);
	connect(pCutShortCut, &QShortcut::activated, this, &QCustomTableWidget::slot_CutRows);
	connect(m_pactCut, &QAction::triggered, this, &QCustomTableWidget::slot_CutRows);

	QIcon pasteIcon;
	pasteIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/paste_enable"), QIcon::Normal);
	pasteIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/paste_disable"), QIcon::Disabled);
	m_pactPaste = m_pRightKeyMenu->addAction(pasteIcon, QStringLiteral("粘贴"));
	m_pactPaste->setShortcut(QKeySequence::Paste);
	QShortcut *pPasteShortCut = new QShortcut(QKeySequence::Paste, this);
	connect(pPasteShortCut, &QShortcut::activated, this, &QCustomTableWidget::slot_PasteRows);
	connect(m_pactPaste, &QAction::triggered, this, &QCustomTableWidget::slot_PasteRows);
}

QCustomTableWidget::QCustomTableWidget(int rows, int columns, QWidget * parent)
	: QTableWidget(rows, columns, parent)
	, m_pRightKeyMenu(nullptr)
	, m_pactInsert(nullptr)
	, m_pactAdd(nullptr)
	, m_pactDelete(nullptr)
	, m_pactCopy(nullptr)
	, m_pactCut(nullptr)
	, m_pactPaste(nullptr)
	, m_pactUndo(nullptr)
	, m_pactRedo(nullptr)
	, m_bCopyOrCutFlag(false)
	, m_pUndoStack(nullptr)
	, m_bEditContentFlag(false)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

	horizontalHeader()->setSectionsClickable(false);
	horizontalHeader()->setStretchLastSection(true);

	setFocusPolicy(Qt::ClickFocus);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QCustomTableWidget::customContextMenuRequested, this, &QCustomTableWidget::slot_ShowPopupMenu);

	m_pRightKeyMenu = new QMenu(this);

	QIcon insertIcon;
	insertIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/insert_enable"), QIcon::Normal);
	insertIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/insert_disable"), QIcon::Disabled);
	m_pactInsert = m_pRightKeyMenu->addAction(insertIcon, QStringLiteral("插入"));
	m_pactInsert->setShortcut(QKeySequence("Ctrl+Ins"));
	connect(m_pactInsert, &QAction::triggered, this, &QCustomTableWidget::slot_InsertRows);

	QIcon addIcon;
	addIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/add_enable"), QIcon::Normal);
	addIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/add_disable"), QIcon::Disabled);
	m_pactAdd = m_pRightKeyMenu->addAction(addIcon, QStringLiteral("添加"));
	connect(m_pactAdd, &QAction::triggered, this, &QCustomTableWidget::slot_AddRows);

	QIcon deletetIcon;
	deletetIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/delete_enable"), QIcon::Normal);
	deletetIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/delete_disable"), QIcon::Disabled);
	m_pactDelete = m_pRightKeyMenu->addAction(deletetIcon, QStringLiteral("删除"));
	m_pactDelete->setShortcut(QKeySequence::Delete);
	connect(m_pactDelete, &QAction::triggered, this, &QCustomTableWidget::slot_DeleteRows);

	QIcon copyIcon;
	copyIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/copy_enable"), QIcon::Normal);
	copyIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/copy_disable"), QIcon::Disabled);
	m_pactCopy = m_pRightKeyMenu->addAction(copyIcon, QStringLiteral("复制"));
	m_pactCopy->setShortcut(QKeySequence::Copy);
	connect(m_pactCopy, &QAction::triggered, this, &QCustomTableWidget::slot_CopyRows);

	QIcon cutIcon;
	cutIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/cut_enable"), QIcon::Normal);
	cutIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/cut_disable"), QIcon::Disabled);
	m_pactCut = m_pRightKeyMenu->addAction(cutIcon, QStringLiteral("剪切"));
	m_pactCut->setShortcut(QKeySequence::Cut);
	connect(m_pactCut, &QAction::triggered, this, &QCustomTableWidget::slot_CutRows);

	QIcon pasteIcon;
	pasteIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/paste_enable"), QIcon::Normal);
	pasteIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/paste_disable"), QIcon::Disabled);
	m_pactPaste = m_pRightKeyMenu->addAction(pasteIcon, QStringLiteral("粘贴"));
	m_pactPaste->setShortcut(QKeySequence::Paste);
	connect(m_pactPaste, &QAction::triggered, this, &QCustomTableWidget::slot_PasteRows);

	m_pUndoStack = new QUndoStack(this);

	m_pactUndo = m_pUndoStack->createUndoAction(this, QStringLiteral("撤销"));
	QIcon undoIcon;
	undoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/undo_enable"), QIcon::Normal);
	undoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/undo_disable"), QIcon::Disabled);
	m_pactUndo->setIcon(undoIcon);
	m_pactUndo->setShortcut(QKeySequence::Undo);
	m_pRightKeyMenu->addAction(m_pactUndo);

	m_pactRedo = m_pUndoStack->createRedoAction(this, QStringLiteral("重做"));
	QIcon redoIcon;
	redoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/redo_enable"), QIcon::Normal);
	redoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/redo_disable"), QIcon::Disabled);
	m_pactRedo->setIcon(redoIcon);
	m_pactRedo->setShortcut(QKeySequence::Redo);
	m_pRightKeyMenu->addAction(m_pactRedo);

	connect(this, &QCustomTableWidget::cellChanged, this, &QCustomTableWidget::slot_ContentChanged);
	connect(this, &QCustomTableWidget::cellDoubleClicked, this, &QCustomTableWidget::slot_ContentTempStorage);
}

QCustomTableWidget::~QCustomTableWidget()
{

}

void QCustomTableWidget::InsertRowData(int nRows)
{
	for(int nCounter = 0; nCounter < columnCount(); nCounter++)
	{
		QTableWidgetItem *pTableWidgetItem = new QTableWidgetItem("a");

		setItem(nRows, nCounter, pTableWidgetItem);
	}
}

void QCustomTableWidget::setCopyOrCutStateFlag(bool bState)
{
	m_bCopyOrCutFlag = bState;
}

void QCustomTableWidget::setCopyAndCutContent(const QList<QStringList>& listContent)
{
	m_listCopyAndCutContent = listContent;
}

void QCustomTableWidget::ClearCopyAndCutContent()
{
	m_listCopyAndCutContent.clear();
}

bool QCustomTableWidget::getCopyOrCutFlag() const
{
	return m_bCopyOrCutFlag;
}

void QCustomTableWidget::setEditContentFlag(bool bState)
{
	m_bEditContentFlag = bState;
}

void QCustomTableWidget::keyPressEvent(QKeyEvent * event)
{
	if(event->matches(QKeySequence::Delete))
	{
		slot_DeleteRows();
	}
	else if(event->matches(QKeySequence::Copy))
	{
		slot_CopyRows();
	}
	else if(event->matches(QKeySequence::Cut))
	{
		slot_CutRows();
	}
	else if(event->matches(QKeySequence::Paste))
	{
		slot_PasteRows();
	}
	else if(event->matches(QKeySequence::Undo))
	{
		m_pUndoStack->undo();
	}
	else if(event->matches(QKeySequence::Redo))
	{
		m_pUndoStack->redo();
	}
	
	if(event->modifiers() == Qt::ControlModifier)
	{
		if(event->key() == Qt::Key_Insert)
		{
			slot_InsertRows();
		}
	}

	QTableWidget::keyReleaseEvent(event);
}

void QCustomTableWidget::slot_ShowPopupMenu(const QPoint &pt)
{
	QTableWidgetItem *pTableItem = itemAt(pt);

	if(pTableItem == nullptr)
	{
		m_pactInsert->setEnabled(false);
		m_pactDelete->setEnabled(false);
		m_pactCopy->setEnabled(false);
		m_pactCut->setEnabled(false);
		if(m_listCopyAndCutContent.size() > 0 && rowCount() == 0)
		{
			m_pactPaste->setEnabled(true);
		}
		else
		{
			m_pactPaste->setEnabled(false);
		}
	}
	else
	{
		m_pactInsert->setEnabled(true);
		m_pactDelete->setEnabled(true);
		m_pactCopy->setEnabled(true);
		m_pactCut->setEnabled(true);
		if(m_listCopyAndCutContent.size() > 0)
		{
			m_pactPaste->setEnabled(true);
		}
		else
		{
			m_pactPaste->setEnabled(false);
		}
	}

	m_pRightKeyMenu->popup(QCursor::pos());
}

void QCustomTableWidget::slot_AddRows()
{
	int nRowTemp = rowCount();

	QTableWidgetInsertCommand *pInsertCommand = new QTableWidgetInsertCommand(this, nRowTemp);
	m_pUndoStack->push(pInsertCommand);
}

void QCustomTableWidget::slot_InsertRows()
{
	QList<QTableWidgetSelectionRange> range = selectedRanges();

	if(range.size() < 1)
	{
		return;
	}

	int nRowTemp = currentRow();

	QTableWidgetInsertCommand *pInsertCommand = new QTableWidgetInsertCommand(this, nRowTemp);
	m_pUndoStack->push(pInsertCommand);
}

void QCustomTableWidget::slot_DeleteRows()
{
	QList<QTableWidgetSelectionRange> range = selectedRanges();
	if(range.size() < 1)
	{
		return;
	}

	QList<int> listSelectedRows;

	for(int nListCounter = 0; nListCounter < range.size(); nListCounter++)
	{
		for (int nCounter = range[nListCounter].topRow(); nCounter <= range[nListCounter].bottomRow(); nCounter++)
		{
			listSelectedRows << nCounter;
		}
	}

	std::sort(listSelectedRows.begin(), listSelectedRows.end());

	QList<QStringList> listSelectedContent;

	for (int nCounter = 0; nCounter < listSelectedRows.size(); nCounter++)
	{
		QStringList strList;
		for(int nColumCounter = 0; nColumCounter < columnCount(); nColumCounter++)
		{
			strList << item(listSelectedRows.at(nCounter), nColumCounter)->text();
		}

		listSelectedContent << strList;
	}

	QUndoCommand *pDeleteCommand = new QTableWidgetDeleteCommand(this, listSelectedContent, listSelectedRows);
	m_pUndoStack->push(pDeleteCommand);
}

void QCustomTableWidget::slot_CopyRows()
{
	QList<QTableWidgetSelectionRange> range = selectedRanges();
	if (range.size() < 1)
	{
		return;
	}

	QList<int> listSelectedRows;

	for (int nListCounter = 0; nListCounter < range.size(); nListCounter++)
	{
		for (int nCounter = range[nListCounter].topRow(); nCounter <= range[nListCounter].bottomRow(); nCounter++)
		{
			listSelectedRows << nCounter;
		}
	}

	std::sort(listSelectedRows.begin(), listSelectedRows.end());

	m_listCopyAndCutContent.clear();
	m_bCopyOrCutFlag = false;

	for(int nCopyCounter = 0; nCopyCounter < listSelectedRows.size(); nCopyCounter++)
	{
		QStringList stringListTemp;
		for (int nColumCounter = 0; nColumCounter < columnCount(); nColumCounter++)
		{
			stringListTemp << item(listSelectedRows.at(nCopyCounter), nColumCounter)->text();
		}

		m_listCopyAndCutContent << stringListTemp;
	}
}

void QCustomTableWidget::slot_CutRows()
{
	QList<QTableWidgetSelectionRange> range = selectedRanges();
	if (range.size() < 1)
	{
		return;
	}

	QList<int> listSelectedRows;

	for (int nListCounter = 0; nListCounter < range.size(); nListCounter++)
	{
		for (int nCounter = range[nListCounter].topRow(); nCounter <= range[nListCounter].bottomRow(); nCounter++)
		{
			listSelectedRows << nCounter;
		}
	}

	std::sort(listSelectedRows.begin(), listSelectedRows.end());

	QList<QStringList> listSelectedContent;

	for (int nCounter = 0; nCounter < listSelectedRows.size(); nCounter++)
	{
		QStringList strList;
		for (int nColumCounter = 0; nColumCounter < columnCount(); nColumCounter++)
		{
			strList << item(listSelectedRows.at(nCounter), nColumCounter)->text();
		}

		listSelectedContent << strList;
	}

	QTableWidgetCutCommand *pCutCommand = new QTableWidgetCutCommand(this, listSelectedContent, listSelectedRows);
	m_pUndoStack->push(pCutCommand);
}

void QCustomTableWidget::slot_PasteRows()
{
	if(m_listCopyAndCutContent.size() < 1)
	{
		return;
	}

	if(columnCount() != m_listCopyAndCutContent.at(0).size())   //复制的内容与表格的列数不匹配，不能进行复制
	{
		return;
	}

	QList<QTableWidgetSelectionRange> range = selectedRanges();
	if(rowCount() > 0)
	{
		if (range.size() < 1)
		{
			return;
		}
	}
	
	QList<int> listSelectedRows;

	for (int nListCounter = 0; nListCounter < range.size(); nListCounter++)
	{
		for (int nCounter = range[nListCounter].topRow(); nCounter <= range[nListCounter].bottomRow(); nCounter++)
		{
			listSelectedRows << nCounter;
		}
	}

	std::sort(listSelectedRows.begin(), listSelectedRows.end());

	QList<QStringList> listSelectedContent;

	for (int nCounter = 0; nCounter < listSelectedRows.size(); nCounter++)
	{
		QStringList strList;
		for (int nColumCounter = 0; nColumCounter < columnCount(); nColumCounter++)
		{
			strList << item(listSelectedRows.at(nCounter), nColumCounter)->text();
		}

		listSelectedContent << strList;
	}

	QTableWidgetPasteCommand *pPasteCommand = new QTableWidgetPasteCommand(this, listSelectedContent,
													m_listCopyAndCutContent, listSelectedRows);
	m_pUndoStack->push(pPasteCommand);

// 	slot_DeleteRows();
// 
// 	int nCurrentRow = currentRow();
// 
// 	if(nCurrentRow >= 0)
// 	{
// 		QTableWidgetSelectionRange unSelectionRange(nCurrentRow, 0, nCurrentRow, columnCount() - 1);
// 		setRangeSelected(unSelectionRange, false);
// 	}
// 
// 	if(nCurrentRow < 0)
// 	{
// 		nCurrentRow = 0;
// 	}
// 	else if (nCurrentRow == rowCount() -1 )
// 	{
// 		nCurrentRow++;
// 	}
// 
// 	for(int nListCounter = m_listCopyAndCutContent.size()-1; nListCounter >= 0; nListCounter--)
// 	{
// 		insertRow(nCurrentRow);
// 		for(int nStrCounter = 0; nStrCounter < m_listCopyAndCutContent.at(nListCounter).size(); nStrCounter++)
// 		{
// 			QTableWidgetItem *pWidgetItem = new QTableWidgetItem();
// 			pWidgetItem->setText(m_listCopyAndCutContent.at(nListCounter)[nStrCounter]);
// 			setItem(nCurrentRow, nStrCounter, pWidgetItem);
// 		}
// 	}
// 
//  	setCurrentItem(item(nCurrentRow, 0));
// 
//  	QTableWidgetSelectionRange selectionRange(nCurrentRow, 0, nCurrentRow + m_listCopyAndCutContent.size() - 1, columnCount() - 1);
//  	setRangeSelected(selectionRange, true);
// 
// 	if(m_bCopyOrCutFlag)
// 	{
// 		m_listCopyAndCutContent.clear();
// 		m_bCopyOrCutFlag = false;
// 	}
}

void QCustomTableWidget::slot_ContentChanged(int nRow, int nColumn)
{
	if(!m_bEditContentFlag)
	{
		return;
	}
	m_bEditContentFlag = false;

	QList<QString> strCurrentContent;

	for (int nCounter = 0; nCounter < columnCount(); nCounter++)
	{
		QString strTemp = item(nRow, nCounter)->text();
		strCurrentContent << strTemp;
	}

	QTableWidgetContentChangeCommand *pChangedCommand = new QTableWidgetContentChangeCommand(this, nRow,
																strCurrentContent, m_strRowContentTempStorage);
	m_pUndoStack->push(pChangedCommand);
}

void QCustomTableWidget::slot_ContentTempStorage(int nRow, int nColumn)
{
	m_strRowContentTempStorage.clear();
	m_bEditContentFlag = true;

	for(int nCounter = 0; nCounter < columnCount(); nCounter++)
	{
		QString strTemp = item(nRow, nCounter)->text();
		m_strRowContentTempStorage << strTemp;
	}
}



