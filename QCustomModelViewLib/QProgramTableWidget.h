#pragma once

#include "QCustomTableWidget.h"
#include "qcustommodelviewlib_global.h"

class QComboxDelegate;
class QCUSTOMMODELVIEWLIB_EXPORT QProgramTableWidget : public QCustomTableWidget
{
	Q_OBJECT

public:
	QProgramTableWidget(QWidget *parent);
	QProgramTableWidget(QWidget *parent, int nRows, int nColumns);
	~QProgramTableWidget();

	void initializeCommandPair(const QStringList &listCommand, const QStringList &listParameter);  //初始化命令源

public slots:
	void slot_commandActived(const QString &strText);

private:
	QComboxDelegate    *m_pComboxDelegate;

	QHash<QString, QString> m_hashCommandPair;		//命令对
};
