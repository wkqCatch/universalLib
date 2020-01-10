#include "QProgramTableWidget.h"
#include "QComboxDelegate.h"

QProgramTableWidget::QProgramTableWidget(QWidget *parent)
	: QCustomTableWidget(parent)
	, m_pComboxDelegate(nullptr)
{
	m_pComboxDelegate = new QComboxDelegate(this);
	connect(m_pComboxDelegate, &QComboxDelegate::sig_ComboBoxActived, this, &QProgramTableWidget::slot_commandActived);

	setCustomDelegateForColumn(0, m_pComboxDelegate);
}

QProgramTableWidget::QProgramTableWidget(QWidget *parent, int nRows, int nColumns)
	: QCustomTableWidget(nRows, nColumns, parent)
	, m_pComboxDelegate(nullptr)
{

	m_pComboxDelegate = new QComboxDelegate(this);
	connect(m_pComboxDelegate, &QComboxDelegate::sig_ComboBoxActived, this, &QProgramTableWidget::slot_commandActived);

	setCustomDelegateForColumn(0, m_pComboxDelegate);
}

QProgramTableWidget::~QProgramTableWidget()
{
	if(m_pComboxDelegate)
	{
		delete m_pComboxDelegate;
		m_pComboxDelegate = nullptr;
	}
}

void QProgramTableWidget::initializeCommandPair(const QStringList & listCommand, const QStringList & listParameter)
{
	if(listCommand.size() != listParameter.size())
	{
		return;
	}

	for(int nCounter = 0; nCounter < listCommand.size(); nCounter++)
	{
		m_hashCommandPair[listCommand.at(nCounter)] = listParameter.at(nCounter);
	}

	m_pComboxDelegate->setComboxContentList(listCommand);
}

void QProgramTableWidget::slot_commandActived(const QString &strText)
{
	setEditContentFlag(false);

	QString strParameter = m_hashCommandPair.value(strText);
	QTableWidgetItem *pTableItem = item(currentRow(), currentColumn() + 1);

	setCurrentItem(pTableItem);

	if (strParameter != pTableItem->text())
	{
		setEditContentFlag(true);
		pTableItem->setText(strParameter);
	}
}
