#include "QCustomMessageBox.h"
#include "QCustomDialogTitleBar.h"

#include <QPushButton>

QCustomMessageBox::QCustomMessageBox(QWidget *parent, QString strBoxContentIcon, QString strBoxContentText)
	: QDialog(parent)
	, m_pCustomDlgTitleBar(nullptr)
{
	setupUi(this);

	m_pFrameDisplay->setAttribute(Qt::WA_TranslucentBackground, true);

	m_pCustomDlgTitleBar = new QCustomDialogTitleBar(this, m_pFrameMessageBoxTitleBar, 20);
	m_pCustomDlgTitleBar->setTitleIcon(":/MessageBoxRc/DlgIcon");
	m_pCustomDlgTitleBar->hideMaximize(true);
	m_pCustomDlgTitleBar->hideMinimize(true);

	m_plbContentIcon->setPixmap(QPixmap(strBoxContentIcon).scaled(36, 36));
	QFont contentTextFont = m_plbContentText->font();
	contentTextFont.setPixelSize(18);
	m_plbContentText->setFont(contentTextFont);
	m_plbContentText->setText(strBoxContentText);

	translateUI();

	connect(m_pdbbButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(m_pdbbButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

QCustomMessageBox::~QCustomMessageBox()
{
	if (m_pCustomDlgTitleBar != nullptr)
	{
		delete m_pCustomDlgTitleBar;
		m_pCustomDlgTitleBar = nullptr;
	}
}

QDialog::DialogCode QCustomMessageBox::customMessageBox(QWidget * pParent, messageBoxType boxType, QString strContentText)
{
	QString strContentIconPath;
	QString strTitleName;
	switch (boxType)
	{
		case QCustomMessageBox::question:
			strContentIconPath = ":/MessageBoxRc/questionIcon";
			strTitleName = QStringLiteral("问题");
			break;

		case QCustomMessageBox::information:
			strContentIconPath = ":/MessageBoxRc/informationIcon";
			strTitleName = QStringLiteral("提示");
			break;

		case QCustomMessageBox::success:
			strContentIconPath = ":/MessageBoxRc/successIcon";
			strTitleName = QStringLiteral("成功");
			break;

		case QCustomMessageBox::successOnTimer:
			strContentIconPath = ":/MessageBoxRc/successIcon";
			strTitleName = QStringLiteral("成功");
			break;

		case QCustomMessageBox::warning:
			strContentIconPath = ":/MessageBoxRc/warningIcon";
			strTitleName = QStringLiteral("警告");
			break;

		case QCustomMessageBox::error:
			strContentIconPath = ":/MessageBoxRc/errorIcon";
			strTitleName = QStringLiteral("错误");
			break;

		default:
			break;
	}

	QCustomMessageBox messageBox(pParent, strContentIconPath, strContentText);
	messageBox.getCustomDialogTitleBar()->setTitleName(strTitleName);

	return static_cast<QDialog::DialogCode>(messageBox.exec());
}

void QCustomMessageBox::translateUI()
{
	QPushButton *ppbYesButton = m_pdbbButtonBox->button(QDialogButtonBox::Ok);
	if(ppbYesButton != nullptr)
	{
		ppbYesButton->setText(QStringLiteral("确 认"));
		//ppbYesButton->setFixedWidth(69);
		ppbYesButton->setAutoDefault(true);
		ppbYesButton->setDefault(true);
	}

	QPushButton *ppbCancelButton = m_pdbbButtonBox->button(QDialogButtonBox::Cancel);
	if(ppbCancelButton != nullptr)
	{
		ppbCancelButton->setText(QStringLiteral("取 消"));
		//ppbCancelButton->setFixedWidth(69);
		ppbCancelButton->setAutoDefault(true);
		ppbCancelButton->setDefault(false);
	}
}

QCustomDialogTitleBar * QCustomMessageBox::getCustomDialogTitleBar() const
{
	return m_pCustomDlgTitleBar;
}
