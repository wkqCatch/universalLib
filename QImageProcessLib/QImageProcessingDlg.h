#pragma once

#include <QFrame>
#include "ui_QImageProcessingDlg.h"

class QImageProcessingDlg : public QFrame, public Ui::QImageProcessingDlg
{
	Q_OBJECT

public:
	QImageProcessingDlg(QWidget *parent = Q_NULLPTR);
	~QImageProcessingDlg();
};
