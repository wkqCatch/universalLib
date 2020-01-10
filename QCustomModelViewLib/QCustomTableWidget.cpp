#include "QCustomTableWidget.h"
#include "QTableWidgetCommands.h"

#include <QMenu>
#include <QMouseEvent>
#include <QCursor>
#include <QShortcut>
#include <QHeaderView>
#include <QUndoStack>
#include <QAbstractButton>
#include <QApplication>
#include <QStylePainter>

QCustomTableWidget::QCustomTableWidget(QWidget *pParent)
	: QTableWidget(pParent)
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
	, m_bNeedUpdateActionFlag(false)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

	horizontalHeader()->setSectionsClickable(false);
	horizontalHeader()->setStretchLastSection(true);

	setFocusPolicy(Qt::StrongFocus);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QCustomTableWidget::customContextMenuRequested, this, &QCustomTableWidget::slot_ShowPopupMenu);

	m_pRightKeyMenu = new QMenu(this);

	QIcon insertIcon;
	insertIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/insert_enable"), QIcon::Normal);
	insertIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/insert_disable"), QIcon::Disabled);
	m_pactInsert = m_pRightKeyMenu->addAction(insertIcon, QStringLiteral("插 入"));
	m_pactInsert->setShortcut(QKeySequence("Ctrl+Ins"));
	m_pactInsert->setAutoRepeat(false);
	//QFont insertFont = m_pactInsert->font();
	//insertFont.setFamily(QStringLiteral("宋体"));
	//insertFont.setBold(true);
	//insertFont.setPixelSize(30);
	//m_pactInsert->setFont(insertFont);
	connect(m_pactInsert, &QAction::triggered, this, &QCustomTableWidget::slot_InsertRows);

	QIcon addIcon;
	addIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/add_enable"), QIcon::Normal);
	addIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/add_disable"), QIcon::Disabled);
	m_pactAdd = m_pRightKeyMenu->addAction(addIcon, QStringLiteral("添 加"));
	m_pactAdd->setAutoRepeat(false);
	connect(m_pactAdd, &QAction::triggered, this, &QCustomTableWidget::slot_AddRows);

	QIcon deletetIcon;
	deletetIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/delete_enable"), QIcon::Normal);
	deletetIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/delete_disable"), QIcon::Disabled);
	m_pactDelete = m_pRightKeyMenu->addAction(deletetIcon, QStringLiteral("删 除"));
	m_pactDelete->setShortcut(QKeySequence::Delete);
	m_pactDelete->setAutoRepeat(false);
	connect(m_pactDelete, &QAction::triggered, this, &QCustomTableWidget::slot_DeleteRows);

	QIcon copyIcon;
	copyIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/copy_enable"), QIcon::Normal);
	copyIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/copy_disable"), QIcon::Disabled);
	m_pactCopy = m_pRightKeyMenu->addAction(copyIcon, QStringLiteral("复 制"));
	m_pactCopy->setAutoRepeat(false);
	m_pactCopy->setShortcut(QKeySequence::Copy);
	connect(m_pactCopy, &QAction::triggered, this, &QCustomTableWidget::slot_CopyRows);

	QIcon cutIcon;
	cutIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/cut_enable"), QIcon::Normal);
	cutIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/cut_disable"), QIcon::Disabled);
	m_pactCut = m_pRightKeyMenu->addAction(cutIcon, QStringLiteral("剪 切"));
	m_pactCut->setAutoRepeat(false);
	m_pactCut->setShortcut(QKeySequence::Cut);
	connect(m_pactCut, &QAction::triggered, this, &QCustomTableWidget::slot_CutRows);

	QIcon pasteIcon;
	pasteIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/paste_enable"), QIcon::Normal);
	pasteIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/paste_disable"), QIcon::Disabled);
	m_pactPaste = m_pRightKeyMenu->addAction(pasteIcon, QStringLiteral("粘 贴"));
	m_pactPaste->setAutoRepeat(false);
	m_pactPaste->setShortcut(QKeySequence::Paste);
	connect(m_pactPaste, &QAction::triggered, this, &QCustomTableWidget::slot_PasteRows);

	m_pUndoStack = new QUndoStack(this);

	m_pactUndo = m_pUndoStack->createUndoAction(this, QStringLiteral("撤 销"));
	QIcon undoIcon;
	undoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/undo_enable"), QIcon::Normal);
	undoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/undo_disable"), QIcon::Disabled);
	m_pactUndo->setIcon(undoIcon);
	m_pactUndo->setShortcut(QKeySequence::Undo);
	m_pactUndo->setAutoRepeat(false);
	m_pRightKeyMenu->addAction(m_pactUndo);

	m_pactRedo = m_pUndoStack->createRedoAction(this, QStringLiteral("重 做"));
	QIcon redoIcon;
	redoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/redo_enable"), QIcon::Normal);
	redoIcon.addPixmap(QPixmap(":/RightKeyMenuIcon/redo_disable"), QIcon::Disabled);
	m_pactRedo->setIcon(redoIcon);
	m_pactRedo->setShortcut(QKeySequence::Redo);
	m_pactRedo->setAutoRepeat(false);
	m_pRightKeyMenu->addAction(m_pactRedo);

	connect(this, &QCustomTableWidget::cellChanged, this, &QCustomTableWidget::slot_ContentChanged);
	connect(this, &QCustomTableWidget::cellDoubleClicked, this, &QCustomTableWidget::slot_ContentTempStorage);

	QAbstractButton* btn = findChild<QAbstractButton*>();
	if (btn)
	{
		btn->setText("NO");
		btn->installEventFilter(this);

		// adjust the width of the vertical header to match the preferred corner button width
		// (unfortunately QAbstractButton doesn't implement any size hinting functionality)
		QStyleOptionHeader opt;
		opt.text = btn->text();
		QSize s = (btn->style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), btn).
			expandedTo(QApplication::globalStrut()));
		if (s.isValid())
		{
			verticalHeader()->setMinimumWidth(s.width());
		}
	}
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
	, m_bNeedUpdateActionFlag(false)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

	horizontalHeader()->setSectionsClickable(false);
	horizontalHeader()->setStretchLastSection(true);

	setFocusPolicy(Qt::StrongFocus);

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

	QAbstractButton* btn = findChild<QAbstractButton*>();
	if (btn)
	{
		btn->setText("NO");
		btn->installEventFilter(this);

		// adjust the width of the vertical header to match the preferred corner button width
		// (unfortunately QAbstractButton doesn't implement any size hinting functionality)
		QStyleOptionHeader opt;
		opt.text = btn->text();
		QSize s = (btn->style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), btn).
			expandedTo(QApplication::globalStrut()));
		if (s.isValid())
		{
			verticalHeader()->setMinimumWidth(s.width());
		}
	}
}

QCustomTableWidget::~QCustomTableWidget()
{
}

void QCustomTableWidget::InsertRowData(int nRows)
{
	for (int nCounter = 0; nCounter < columnCount(); nCounter++)
	{
		QTableWidgetItem *pTableWidgetItem = new QTableWidgetItem("null");

		setItem(nRows, nCounter, pTableWidgetItem);
	}
}

bool QCustomTableWidget::eventFilter(QObject *object, QEvent *event)
{
	if (event->type() == QEvent::Paint)
	{
		QAbstractButton* btn = qobject_cast<QAbstractButton*>(object);
		if (btn)
		{
			// paint by hand (borrowed from QTableCornerButton)
			QStyleOptionHeader opt;
			opt.init(btn);
			QStyle::State state = QStyle::State_None;
			if (btn->isEnabled())
				state |= QStyle::State_Enabled;
			if (btn->isActiveWindow())
				state |= QStyle::State_Active;
			if (btn->isDown())
				state |= QStyle::State_Sunken;
			opt.state = state;
			opt.rect = btn->rect();
			opt.text = btn->text();				// this line is the only difference to QTableCornerButton
			opt.position = QStyleOptionHeader::OnlyOneSection;
			QStylePainter painter(btn);
			painter.drawControl(QStyle::CE_Header, opt);
			return true;						// eat event
		}
	}

	return false;
}

void QCustomTableWidget::clearUndoCommand() const
{
	m_pUndoStack->clear();
}

void QCustomTableWidget::setUndoStackClean() const
{
	m_pUndoStack->setClean();
}

void QCustomTableWidget::addRows()
{
	int nRowTemp = rowCount();

	setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> range = selectedRanges();
	for (int nCounter = 0; nCounter < range.size(); nCounter++)
	{
		setRangeSelected(range[nCounter], false);
	}

	insertRow(nRowTemp);
	InsertRowData(nRowTemp);

	if (item(nRowTemp, 0))
	{
		setCurrentItem(item(nRowTemp, 0));
	}
}

QAction * QCustomTableWidget::getInsertAction() const
{
	return m_pactInsert;
}

QAction * QCustomTableWidget::getAddAction() const
{
	return m_pactAdd;
}

QAction * QCustomTableWidget::getDeleteAction() const
{
	return m_pactDelete;
}

QAction * QCustomTableWidget::getCopyAction() const
{
	return m_pactCopy;
}

QAction * QCustomTableWidget::getCutAction() const
{
	return m_pactCut;
}

QAction * QCustomTableWidget::getPasteAction() const
{
	return m_pactPaste;
}

QAction * QCustomTableWidget::getUndoAction() const
{
	return m_pactUndo;
}

QAction * QCustomTableWidget::getRedoAction() const
{
	return m_pactRedo;
}

void QCustomTableWidget::updateActionState(bool bState)
{
	if(bState)
	{
		m_pactInsert->setEnabled(true);
		m_pactDelete->setEnabled(true);
		m_pactCopy->setEnabled(true);
		m_pactCut->setEnabled(true);
		if (m_listCopyAndCutContent.size() > 0)
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
		m_pactInsert->setEnabled(false);
		m_pactDelete->setEnabled(false);
		m_pactCopy->setEnabled(false);
		m_pactCut->setEnabled(false);
		if (m_listCopyAndCutContent.size() > 0 && rowCount() == 0)
		{
			m_pactPaste->setEnabled(true);
		}
		else
		{
			m_pactPaste->setEnabled(false);
		}
	}
}

void QCustomTableWidget::updateActionState()
{
	QList<QTableWidgetSelectionRange> range = selectedRanges();

	if (range.size() > 0)
	{
		m_pactInsert->setEnabled(true);
		m_pactDelete->setEnabled(true);
		m_pactCopy->setEnabled(true);
		m_pactCut->setEnabled(true);
		if (m_listCopyAndCutContent.size() > 0)
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
		m_pactInsert->setEnabled(false);
		m_pactDelete->setEnabled(false);
		m_pactCopy->setEnabled(false);
		m_pactCut->setEnabled(false);
		if (m_listCopyAndCutContent.size() > 0 && rowCount() == 0)
		{
			m_pactPaste->setEnabled(true);
		}
		else
		{
			m_pactPaste->setEnabled(false);
		}
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

void QCustomTableWidget::setCustomDelegateForRow(int nIndex, QAbstractItemDelegate * pItemDelegate)
{
	if (nIndex < 0 || pItemDelegate == nullptr)
	{
		return;
	}

	QAbstractItemDelegate *pItemDelegateTemp = itemDelegateForRow(nIndex);
	if (pItemDelegateTemp)
	{
		delete pItemDelegateTemp;
		pItemDelegateTemp = nullptr;
	}

	setItemDelegateForRow(nIndex, pItemDelegate);
}

//void QCustomTableWidget::keyPressEvent(QKeyEvent * event)
//{
// 	if (event->matches(QKeySequence::Delete) && !event->isAutoRepeat())
// 	{
// 		slot_DeleteRows();
// 	}
// 	else if (event->matches(QKeySequence::Copy) && !event->isAutoRepeat())
// 	{
// 		slot_CopyRows();
// 	}
// 	else if (event->matches(QKeySequence::Cut) && !event->isAutoRepeat())
// 	{
// 		slot_CutRows();
// 	}
// 	else if (event->matches(QKeySequence::Paste) && !event->isAutoRepeat())
// 	{
// 		slot_PasteRows();
// 	}
// 	else if (event->matches(QKeySequence::Undo) && !event->isAutoRepeat())
// 	{
// 		m_pUndoStack->undo();
// 	}
// 	else if (event->matches(QKeySequence::Redo) && !event->isAutoRepeat())
// 	{
// 		m_pUndoStack->redo();
// 	}
// 
// 	if (event->modifiers() == Qt::ControlModifier)
// 	{
// 		if (event->key() == Qt::Key_Insert && !event->isAutoRepeat())
// 		{
// 			slot_InsertRows();
// 		}
// 	}
//	QTableWidget::keyPressEvent(event);
//}

void QCustomTableWidget::mousePressEvent(QMouseEvent * event)
{
	QTableWidgetItem *pTableItem = itemAt(event->pos());

	if (pTableItem == nullptr)
	{
		updateActionState(false);
	}
	else
	{
		m_bNeedUpdateActionFlag = true;
	}

	QTableWidget::mousePressEvent(event);
}

void QCustomTableWidget::setCustomDelegateForColumn(int nIndex, QAbstractItemDelegate * pItemDelegate)
{
	if (nIndex < 0 || pItemDelegate == nullptr)
	{
		return;
	}

	QAbstractItemDelegate *pItemDelegateTemp = itemDelegateForColumn(nIndex);
	if (pItemDelegateTemp)
	{
		delete pItemDelegateTemp;
		pItemDelegateTemp = nullptr;
	}

	setItemDelegateForColumn(nIndex, pItemDelegate);
}

void QCustomTableWidget::slot_ShowPopupMenu(const QPoint &pt)
{
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

	if (range.size() < 1)
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
			if (item(listSelectedRows.at(nCounter), nColumCounter))
			{
				strList << item(listSelectedRows.at(nCounter), nColumCounter)->text();
			}
			else
			{
				strList << "";
			}
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

	QList<int> listSelectedRows;        //选中的行，随机的

	for (int nListCounter = 0; nListCounter < range.size(); nListCounter++)
	{
		for (int nCounter = range[nListCounter].topRow(); nCounter <= range[nListCounter].bottomRow(); nCounter++)
		{
			listSelectedRows << nCounter;
		}
	}

	std::sort(listSelectedRows.begin(), listSelectedRows.end());   //对选中的行进行排序

	m_listCopyAndCutContent.clear();
	m_bCopyOrCutFlag = false;

	for (int nCopyCounter = 0; nCopyCounter < listSelectedRows.size(); nCopyCounter++)
	{
		QStringList stringListTemp;
		for (int nColumCounter = 0; nColumCounter < columnCount(); nColumCounter++)
		{
			if (item(listSelectedRows.at(nCopyCounter), nColumCounter))
			{
				stringListTemp << item(listSelectedRows.at(nCopyCounter), nColumCounter)->text();
			}
			else
			{
				stringListTemp << "";
			}
		}

		m_listCopyAndCutContent << stringListTemp;
	}

	updateActionState();
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
			if (item(listSelectedRows.at(nCounter), nColumCounter))
			{
				strList << item(listSelectedRows.at(nCounter), nColumCounter)->text();
			}
			else
			{
				strList << "";
			}
		}

		listSelectedContent << strList;
	}

	QTableWidgetCutCommand *pCutCommand = new QTableWidgetCutCommand(this, listSelectedContent, listSelectedRows);
	m_pUndoStack->push(pCutCommand);
}

void QCustomTableWidget::slot_PasteRows()
{
	if (m_listCopyAndCutContent.size() < 1)
	{
		return;
	}

	if (columnCount() != m_listCopyAndCutContent.at(0).size())   //复制的内容与表格的列数不匹配，不能进行复制
	{
		return;
	}

	QList<QTableWidgetSelectionRange> range = selectedRanges();
	if (rowCount() > 0)
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
			if (item(listSelectedRows.at(nCounter), nColumCounter))
			{
				strList << item(listSelectedRows.at(nCounter), nColumCounter)->text();
			}
			else
			{
				strList << "";
			}
		}

		listSelectedContent << strList;
	}

	QTableWidgetPasteCommand *pPasteCommand = new QTableWidgetPasteCommand(this, listSelectedContent,
		m_listCopyAndCutContent, listSelectedRows);
	m_pUndoStack->push(pPasteCommand);
}

void QCustomTableWidget::slot_ContentChanged(int nRow, int nColumn)
{
	if (!m_bEditContentFlag)
	{
		return;
	}
	m_bEditContentFlag = false;

	QList<QString> strCurrentContent;

	for (int nCounter = 0; nCounter < columnCount(); nCounter++)
	{
		QTableWidgetItem *pWidgetItemTemp = item(nRow, nCounter);
		if (pWidgetItemTemp)
		{
			QString strTemp = pWidgetItemTemp->text();
			strCurrentContent << strTemp;
		}
		else
		{
			strCurrentContent << "";
		}
	}

	QTableWidgetContentChangeCommand *pChangedCommand = new QTableWidgetContentChangeCommand(this, nRow,
		strCurrentContent, m_strRowContentTempStorage);
	m_pUndoStack->push(pChangedCommand);
}

void QCustomTableWidget::slot_ContentTempStorage(int nRow, int nColumn)
{
	m_strRowContentTempStorage.clear();
	m_bEditContentFlag = true;

	for (int nCounter = 0; nCounter < columnCount(); nCounter++)
	{
		QTableWidgetItem *pWidgetItemTemp = item(nRow, nCounter);
		if (pWidgetItemTemp)
		{
			QString strTemp = pWidgetItemTemp->text();
			m_strRowContentTempStorage << strTemp;
		}
		else
		{
			m_strRowContentTempStorage << "";
		}
	}
}