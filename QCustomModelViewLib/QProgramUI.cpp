#include "QProgramUI.h"

#include <QHeaderView>

QProgramUI::QProgramUI(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	
	m_ptbInsertRow->setDefaultAction(m_pProgramTableWidget->getInsertAction());
	m_ptbAddRow->setDefaultAction(m_pProgramTableWidget->getAddAction());
	m_ptbCopy->setDefaultAction(m_pProgramTableWidget->getCopyAction());
	m_ptbCut->setDefaultAction(m_pProgramTableWidget->getCutAction());
	m_ptbPaste->setDefaultAction(m_pProgramTableWidget->getPasteAction());
	m_ptbDelete->setDefaultAction(m_pProgramTableWidget->getDeleteAction());
	m_ptbUndo->setDefaultAction(m_pProgramTableWidget->getUndoAction());
	m_ptbRedo->setDefaultAction(m_pProgramTableWidget->getRedoAction());

	QHeaderView *pVerticalHeader = m_pProgramTableWidget->verticalHeader();
	pVerticalHeader->setSectionResizeMode(QHeaderView::Fixed);

	QHeaderView *pHorizontalHeader = m_pProgramTableWidget->horizontalHeader();
	pHorizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
	pHorizontalHeader->resizeSection(0, 130);
	pHorizontalHeader->resizeSection(1, 250);
	pHorizontalHeader->resizeSection(2, 220);
}

QProgramUI::~QProgramUI()
{

}

void QProgramUI::initializeCommandSource(const QStringList & listCommand, const QStringList & listParameter)
{
	m_pProgramTableWidget->initializeCommandPair(listCommand, listParameter);
}

