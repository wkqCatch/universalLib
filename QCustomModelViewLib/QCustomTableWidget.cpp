#include "QCustomTableWidget.h"

QCustomTableWidget::QCustomTableWidget(QWidget *pParent)
	: QTableWidget(pParent)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::DoubleClicked);
}

QCustomTableWidget::QCustomTableWidget(int rows, int columns, QWidget * parent)
	: QTableWidget(rows, columns, parent)
{
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setEditTriggers(QAbstractItemView::DoubleClicked);
}

QCustomTableWidget::~QCustomTableWidget()
{

}
