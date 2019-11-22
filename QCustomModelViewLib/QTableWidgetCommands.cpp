#include "QTableWidgetCommands.h"

#include "QCustomTableWidget.h"

QTableWidgetDeleteCommand::QTableWidgetDeleteCommand(QCustomTableWidget *pTableWidget,
													 QList<QStringList> &listRowContent, QList<int> &listRowIndex)
	: QUndoCommand()
{
	m_pTableWidget = pTableWidget;
	m_listRowContent = listRowContent;
	m_listRowIndex = listRowIndex;
}

QTableWidgetDeleteCommand::~QTableWidgetDeleteCommand()
{

}

void QTableWidgetDeleteCommand::undo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for(int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	for(int nIndexCounter = 0; nIndexCounter < m_listRowIndex.size(); nIndexCounter++)
	{
		m_pTableWidget->insertRow(m_listRowIndex.at(nIndexCounter));

		int nColumCountTemp = m_listRowContent.at(nIndexCounter).size();

		for(int nContentCounter = 0; nContentCounter < nColumCountTemp; nContentCounter++)
		{
			QTableWidgetItem *pWidgetItem = new QTableWidgetItem();
			pWidgetItem->setText(m_listRowContent.at(nIndexCounter).at(nContentCounter));

			m_pTableWidget->setItem(m_listRowIndex.at(nIndexCounter), nContentCounter, pWidgetItem);
		}
	}

	for(int nUndoRowCounter = 0; nUndoRowCounter < m_listRowIndex.size(); nUndoRowCounter++)
	{
		QTableWidgetSelectionRange selectedRange(m_listRowIndex.at(nUndoRowCounter), 0,
												m_listRowIndex.at(nUndoRowCounter), m_pTableWidget->columnCount() - 1);
		m_pTableWidget->setRangeSelected(selectedRange, true);
	}
}

void QTableWidgetDeleteCommand::redo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	int nFirstItemRowTemp = m_listRowIndex.at(0);

	for (int nDeleteCounter = m_listRowIndex.size() - 1; nDeleteCounter >= 0; nDeleteCounter--)
	{
		m_pTableWidget->removeRow(m_listRowIndex.at(nDeleteCounter));
	}

	if (m_pTableWidget->rowCount() < 1)
	{
		return;
	}

	if (nFirstItemRowTemp < m_pTableWidget->rowCount())
	{
		m_pTableWidget->setCurrentItem(m_pTableWidget->item(nFirstItemRowTemp, 0));
	}
	else
	{
		m_pTableWidget->setCurrentItem(m_pTableWidget->item(m_pTableWidget->rowCount() - 1, 0));
	}
}

QTableWidgetInsertCommand::QTableWidgetInsertCommand(QCustomTableWidget * pTableWidget, int nInsertRows)
{
	m_pTableWidget = pTableWidget;
	m_nInsertRow = nInsertRows;
}

QTableWidgetInsertCommand::~QTableWidgetInsertCommand()
{

}

void QTableWidgetInsertCommand::undo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> range = m_pTableWidget->selectedRanges();

	for (int nCounter = 0; nCounter < range.size(); nCounter++)
	{
		m_pTableWidget->setRangeSelected(range[nCounter], false);
	}

	m_pTableWidget->removeRow(m_nInsertRow);

	if (m_pTableWidget->rowCount() < 1)
	{
		return;
	}

	if (m_nInsertRow < m_pTableWidget->rowCount())
	{
		m_pTableWidget->setCurrentItem(m_pTableWidget->item(m_nInsertRow, 0));
	}
	else
	{
		m_pTableWidget->setCurrentItem(m_pTableWidget->item(m_pTableWidget->rowCount() - 1, 0));
	}
}

void QTableWidgetInsertCommand::redo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> range = m_pTableWidget->selectedRanges();

	for (int nCounter = 0; nCounter < range.size(); nCounter++)
	{
		m_pTableWidget->setRangeSelected(range[nCounter], false);
	}

	m_pTableWidget->insertRow(m_nInsertRow);

	m_pTableWidget->InsertRowData(m_nInsertRow);

	m_pTableWidget->setCurrentItem(m_pTableWidget->item(m_nInsertRow, 0));
}

QTableWidgetCutCommand::QTableWidgetCutCommand(QCustomTableWidget * pTableWidget, QList<QStringList>& listRowContent, QList<int>& listRowIndex)
{
	m_pTableWidget = pTableWidget;
	m_listRowContent = listRowContent;
	m_listRowIndex = listRowIndex;
}

QTableWidgetCutCommand::~QTableWidgetCutCommand()
{

}

void QTableWidgetCutCommand::undo()
{
	m_pTableWidget->setEditContentFlag(false);

	m_pTableWidget->ClearCopyAndCutContent();

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	for (int nIndexCounter = 0; nIndexCounter < m_listRowIndex.size(); nIndexCounter++)
	{
		m_pTableWidget->insertRow(m_listRowIndex.at(nIndexCounter));

		int nColumCountTemp = m_listRowContent.at(nIndexCounter).size();

		for (int nContentCounter = 0; nContentCounter < nColumCountTemp; nContentCounter++)
		{
			QTableWidgetItem *pWidgetItem = new QTableWidgetItem();
			pWidgetItem->setText(m_listRowContent.at(nIndexCounter).at(nContentCounter));

			m_pTableWidget->setItem(m_listRowIndex.at(nIndexCounter), nContentCounter, pWidgetItem);
		}
	}

	for (int nUndoRowCounter = 0; nUndoRowCounter < m_listRowIndex.size(); nUndoRowCounter++)
	{
		QTableWidgetSelectionRange selectedRange(m_listRowIndex.at(nUndoRowCounter), 0,
			m_listRowIndex.at(nUndoRowCounter), m_pTableWidget->columnCount() - 1);
		m_pTableWidget->setRangeSelected(selectedRange, true);
	}
}

void QTableWidgetCutCommand::redo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	m_pTableWidget->ClearCopyAndCutContent();
	m_pTableWidget->setCopyAndCutContent(m_listRowContent);
	m_pTableWidget->setCopyOrCutStateFlag(true);

	int nFirstItemRowTemp = m_listRowIndex.at(0);

	for (int nDeleteCounter = m_listRowIndex.size() - 1; nDeleteCounter >= 0; nDeleteCounter--)
	{
		m_pTableWidget->removeRow(m_listRowIndex.at(nDeleteCounter));
	}

	if (m_pTableWidget->rowCount() < 1)
	{
		return;
	}

	if (nFirstItemRowTemp < m_pTableWidget->rowCount())
	{
		m_pTableWidget->setCurrentItem(m_pTableWidget->item(nFirstItemRowTemp, 0));
	}
	else
	{
		m_pTableWidget->setCurrentItem(m_pTableWidget->item(m_pTableWidget->rowCount() - 1, 0));
	}
}

QTableWidgetPasteCommand::QTableWidgetPasteCommand(QCustomTableWidget * pTableWidget, QList<QStringList>& listRowContent,
												  QList<QStringList>& listCopyAndCutContent, QList<int>& listRowIndex)
{
	m_pTableWidget = pTableWidget;
	m_listRowContent = listRowContent;
	m_listCopyAndCutContent = listCopyAndCutContent;
	m_listRowIndex = listRowIndex;
	m_nPasteStartRow = 0;
}

QTableWidgetPasteCommand::~QTableWidgetPasteCommand()
{

}

void QTableWidgetPasteCommand::undo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	for (int nDeleteCounter = m_nPasteStartRow + m_listCopyAndCutContent.size() - 1; nDeleteCounter >= m_nPasteStartRow; nDeleteCounter--)
	{
		m_pTableWidget->removeRow(nDeleteCounter);
	}
	
	for (int nIndexCounter = 0; nIndexCounter < m_listRowIndex.size(); nIndexCounter++)
	{
		m_pTableWidget->insertRow(m_listRowIndex.at(nIndexCounter));

		int nColumCountTemp = m_listRowContent.at(nIndexCounter).size();

		for (int nContentCounter = 0; nContentCounter < nColumCountTemp; nContentCounter++)
		{
			QTableWidgetItem *pWidgetItem = new QTableWidgetItem();
			pWidgetItem->setText(m_listRowContent.at(nIndexCounter).at(nContentCounter));

			m_pTableWidget->setItem(m_listRowIndex.at(nIndexCounter), nContentCounter, pWidgetItem);
		}
	}

	for (int nUndoRowCounter = 0; nUndoRowCounter < m_listRowIndex.size(); nUndoRowCounter++)
	{
		QTableWidgetSelectionRange selectedRange(m_listRowIndex.at(nUndoRowCounter), 0,
			m_listRowIndex.at(nUndoRowCounter), m_pTableWidget->columnCount() - 1);
		m_pTableWidget->setRangeSelected(selectedRange, true);
	}

	if (m_pTableWidget->getCopyOrCutFlag())
	{
		m_pTableWidget->setCopyAndCutContent(m_listCopyAndCutContent);
	}
}

void QTableWidgetPasteCommand::redo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	int nFirstItemRowTemp = 0;
	if(m_listRowIndex.size() > 0)
	{
		nFirstItemRowTemp = m_listRowIndex.at(0);
	}
	
	for (int nDeleteCounter = m_listRowIndex.size() - 1; nDeleteCounter >= 0; nDeleteCounter--)
	{
		m_pTableWidget->removeRow(m_listRowIndex.at(nDeleteCounter));
	}

	bool bLastRowFlag = false;

	if(m_pTableWidget->rowCount() > 0)
	{
		if (nFirstItemRowTemp < m_pTableWidget->rowCount())
		{
			m_pTableWidget->setCurrentItem(m_pTableWidget->item(nFirstItemRowTemp, 0));
		}
		else
		{
			bLastRowFlag = true;
			m_pTableWidget->setCurrentItem(m_pTableWidget->item(m_pTableWidget->rowCount() - 1, 0));
		}
	}

	int nCurrentRow = m_pTableWidget->currentRow();

	if (nCurrentRow >= 0)
	{
		QTableWidgetSelectionRange unSelectionRange(nCurrentRow, 0, nCurrentRow, m_pTableWidget->columnCount() - 1);
		m_pTableWidget->setRangeSelected(unSelectionRange, false);
	}

	if (nCurrentRow < 0)
	{
		nCurrentRow = 0;
	}
	else if (bLastRowFlag)
	{
		nCurrentRow++;
	}

	for (int nListCounter = m_listCopyAndCutContent.size() - 1; nListCounter >= 0; nListCounter--)
	{
		m_pTableWidget->insertRow(nCurrentRow);
		for (int nStrCounter = 0; nStrCounter < m_listCopyAndCutContent.at(nListCounter).size(); nStrCounter++)
		{
			QTableWidgetItem *pWidgetItem = new QTableWidgetItem();
			pWidgetItem->setText(m_listCopyAndCutContent.at(nListCounter)[nStrCounter]);
			m_pTableWidget->setItem(nCurrentRow, nStrCounter, pWidgetItem);
		}
	}

	m_nPasteStartRow = nCurrentRow;
	m_pTableWidget->setCurrentItem(m_pTableWidget->item(nCurrentRow, 0));

	QTableWidgetSelectionRange selectionRange(nCurrentRow, 0, nCurrentRow + m_listCopyAndCutContent.size() - 1, 
												m_pTableWidget->columnCount() - 1);
	m_pTableWidget->setRangeSelected(selectionRange, true);

	if (m_pTableWidget->getCopyOrCutFlag())
	{
		m_pTableWidget->ClearCopyAndCutContent();
	}
}

QTableWidgetContentChangeCommand::QTableWidgetContentChangeCommand(QCustomTableWidget * pTableWidget, int & nChangedRow, 
															QList<QString>& listNewContent, QList<QString>& listOldContent)
{
	m_pTableWidget = pTableWidget;
	m_nChangedRow = nChangedRow;
	m_listNewContent = listNewContent;
	m_listOldContent = listOldContent;
}

QTableWidgetContentChangeCommand::~QTableWidgetContentChangeCommand()
{

}

void QTableWidgetContentChangeCommand::undo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	for(int nCounter = 0; nCounter < m_pTableWidget->columnCount(); nCounter++)
	{
		m_pTableWidget->item(m_nChangedRow, nCounter)->setText(m_listOldContent.at(nCounter));
	}

	m_pTableWidget->setCurrentCell(m_nChangedRow, 0);
}

void QTableWidgetContentChangeCommand::redo()
{
	m_pTableWidget->setEditContentFlag(false);

	QList<QTableWidgetSelectionRange> listSelectedRange = m_pTableWidget->selectedRanges();

	for (int nRangeCounter = 0; nRangeCounter < listSelectedRange.size(); nRangeCounter++)
	{
		m_pTableWidget->setRangeSelected(listSelectedRange.at(nRangeCounter), false);
	}

	for (int nCounter = 0; nCounter < m_pTableWidget->columnCount(); nCounter++)
	{
		m_pTableWidget->item(m_nChangedRow, nCounter)->setText(m_listNewContent.at(nCounter));
	}

	m_pTableWidget->setCurrentCell(m_nChangedRow, 0);
}
