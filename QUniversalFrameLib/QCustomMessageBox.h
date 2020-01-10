#pragma once

#include <QWidget>
#include "./GeneratedFiles/ui_QCustomMessageBox.h"
#include "quniversalframelib_global.h"

#include <QDialog>

class QCustomDialogTitleBar;
class QUNIVERSALFRAMELIB_EXPORT QCustomMessageBox : public QDialog, public Ui::QCustomMessageBox
{
	Q_OBJECT
		
public:
	enum messageBoxType { question, information, success, successOnTimer, warning, error };

	QCustomMessageBox(QWidget *parent, QString strBoxContentIcon, QString strBoxContentText);
	~QCustomMessageBox();

	static QDialog::DialogCode customMessageBox(QWidget *pParent, messageBoxType boxType, QString strContentText);

	void translateUI();   //翻译按钮盒里面的英文

	QCustomDialogTitleBar* getCustomDialogTitleBar() const;

protected:
	QCustomDialogTitleBar *m_pCustomDlgTitleBar;
};
