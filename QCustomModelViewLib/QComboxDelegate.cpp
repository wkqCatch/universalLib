#include "QComboxDelegate.h"
#include <QStyledItemDelegate>

QComboxDelegate::QComboxDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
	
}

QComboxDelegate::~QComboxDelegate()
{

}

QWidget * QComboxDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	QComboBox *pComboEditor = new QComboBox(parent);

	QStyledItemDelegate *pSerialSelectionDelegate = new QStyledItemDelegate();
	pComboEditor->setItemDelegate(pSerialSelectionDelegate);

	pComboEditor->addItems(m_listComboxContent);

	return pComboEditor;
}

void QComboxDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
	QString currentContent = index.model()->data(index, Qt::DisplayRole).toString();

	QComboBox *pComboBox = dynamic_cast<QComboBox*>(editor);
	if(pComboBox)
	{
		pComboBox->setCurrentText(currentContent);
		connect(pComboBox, QOverload<const QString&>::of(&QComboBox::activated), this, &QComboxDelegate::sig_ComboBoxActived);
	}
}

void QComboxDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
	QComboBox *pComboBox = dynamic_cast<QComboBox*>(editor);
	QString strSetContent;
	if(pComboBox)
	{
		strSetContent = pComboBox->currentText();
	}
	
	model->setData(index, strSetContent, Qt::DisplayRole);
}

void QComboxDelegate::updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	editor->setGeometry(option.rect);

	QComboBox *pComboBox = dynamic_cast<QComboBox*>(editor);
	if(pComboBox)
	{
		pComboBox->showPopup();
	}
}

void QComboxDelegate::setComboxContentList(const QStringList& listComboxContent)
{
	m_listComboxContent = listComboxContent;
}
