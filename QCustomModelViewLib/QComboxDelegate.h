#pragma once

#include <QStyledItemDelegate>
#include <QComboBox>

#include "qcustommodelviewlib_global.h"

class QCUSTOMMODELVIEWLIB_EXPORT QComboxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	QComboxDelegate(QObject *parent = nullptr);
	virtual ~QComboxDelegate();

	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

	void setComboxContentList(const QStringList& listComboxContent);      //…Ë÷√comboxµƒƒ⁄»›

private:
	QStringList m_listComboxContent;

signals:
	void sig_ComboBoxActived(const QString &strText);
};
