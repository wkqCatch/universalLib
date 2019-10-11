#include "QCustomDialogTitleBar.h"

#include <QLabel>
#include <QToolButton>
#include <QDialog>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QCursor>

QCustomDialogTitleBar::QCustomDialogTitleBar(QDialog *pParent, QFrame *pTitleBar, int nHeight, TitleAlign titleAlign)
	: QObject(pParent)
	, m_plbTitleName(nullptr)
	, m_plbTitleIcon(nullptr)
	, m_ptbMinimize(nullptr)
	, m_ptbMaximize(nullptr)
	, m_ptbClose(nullptr)
	, m_nTitleBarHeight(nHeight)
	, m_bMaximizeFlag(false)
	, m_pdlgCustomDlg(pParent)
	, m_pTitleBar(pTitleBar)
	, m_bMovingMode(false)
	, m_ptCursorPreview()
{
	if (pTitleBar == nullptr || pParent == nullptr)
	{
		return;
	}

	pTitleBar->setAttribute(Qt::WA_TranslucentBackground, true);
	pTitleBar->installEventFilter(this);

	QString dlgObjectName = pParent->objectName();
	QString dlgStyleSheet = dlgObjectName + "{border:2px solid rgb(96,96,96); border-radius:6px;}";
	pParent->setStyleSheet(dlgStyleSheet);

	pParent->setWindowFlag(Qt::FramelessWindowHint, true);

	m_plbTitleName = new QLabel();
	m_plbTitleName->setAttribute(Qt::WA_TranslucentBackground, true);
	QFont titleNameFont = m_plbTitleName->font();
	titleNameFont.setBold(true);
	titleNameFont.setPixelSize(nHeight);
	m_plbTitleName->setFont(titleNameFont);

	m_plbTitleIcon = new QLabel();
	m_plbTitleIcon->setAttribute(Qt::WA_TranslucentBackground, true);

	m_ptbMinimize = new QToolButton();
	m_ptbMinimize->setAutoRaise(true);
	m_ptbMinimize->setToolTip(QStringLiteral("最小化"));
	m_ptbMinimize->setIconSize(QSize(nHeight, nHeight));
	m_ptbMinimize->setIcon(QIcon(":/MenuBarRc/Minimize"));

	m_ptbMaximize = new QToolButton();
	m_ptbMaximize->setAutoRaise(true);
	m_ptbMaximize->setToolTip(QStringLiteral("最大化"));
	m_ptbMaximize->setIconSize(QSize(nHeight, nHeight));
	m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/maximize"));
	m_bMaximizeFlag = false;

	m_ptbClose = new QToolButton();
	m_ptbClose->setAutoRaise(true);
	m_ptbClose->setToolTip(QStringLiteral("关闭"));
	m_ptbClose->setIconSize(QSize(nHeight, nHeight));
	m_ptbClose->setIcon(QIcon(":/MenuBarRc/Close"));

	QHBoxLayout *pTitleBarLayout = new QHBoxLayout(pTitleBar);
	pTitleBarLayout->setContentsMargins(3, 0, 0, 0);
	pTitleBarLayout->setSpacing(2);

	switch (titleAlign)
	{
	case QCustomDialogTitleBar::Left:
		if (m_plbTitleIcon != nullptr)
			pTitleBarLayout->addWidget(m_plbTitleIcon);
		pTitleBarLayout->addSpacing(6);
		if (m_plbTitleName != nullptr)
			pTitleBarLayout->addWidget(m_plbTitleName);
		pTitleBarLayout->addStretch();
		break;

	case QCustomDialogTitleBar::Center:
		pTitleBarLayout->addStretch();
		pTitleBarLayout->addSpacing(10);
		if (m_plbTitleIcon != nullptr)
			pTitleBarLayout->addWidget(m_plbTitleIcon);
		pTitleBarLayout->addSpacing(6);
		if (m_plbTitleName != nullptr)
			pTitleBarLayout->addWidget(m_plbTitleName);
		break;

	default:
		break;
	}

	pTitleBarLayout->addStretch();
	pTitleBarLayout->addWidget(m_ptbMinimize);
	pTitleBarLayout->addWidget(m_ptbMaximize);
	pTitleBarLayout->addWidget(m_ptbClose);

	connect(m_ptbMinimize, &QToolButton::clicked, m_pdlgCustomDlg, &QDialog::showMinimized);
	connect(m_ptbClose, &QToolButton::clicked, m_pdlgCustomDlg, &QDialog::close);
	connect(m_ptbMaximize, &QToolButton::clicked, this, &QCustomDialogTitleBar::slotShowMaximizeOrNormal);
}

QCustomDialogTitleBar::~QCustomDialogTitleBar()
{

}

void QCustomDialogTitleBar::setTitleName(QString strName)
{
	if (m_plbTitleName != nullptr)
	{
		m_plbTitleName->setText(strName);
	}
}

void QCustomDialogTitleBar::setTitleIcon(QString strName)
{
	if (m_plbTitleIcon != nullptr)
	{
		m_plbTitleIcon->setPixmap(QPixmap(strName).scaled(m_nTitleBarHeight, m_nTitleBarHeight));
	}
}

void QCustomDialogTitleBar::hideMaximize(bool bMaximize)
{
	if(bMaximize)
	{
		m_ptbMaximize->hide();
	}
}

bool QCustomDialogTitleBar::eventFilter(QObject * watched, QEvent * event)
{
	if(m_bMaximizeFlag)
	{
		return QObject::eventFilter(watched, event);
	}

	if(watched == m_pTitleBar)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QPoint pt = dynamic_cast<QMouseEvent*>(event)->pos();

			m_ptCursorPreview = dynamic_cast<QMouseEvent*>(event)->globalPos();

			m_bMovingMode = true;
			m_pTitleBar->setCursor(Qt::ClosedHandCursor);

			return true;
		}
		else if (event->type() == QEvent::MouseButtonRelease)
		{
			QPoint pt = dynamic_cast<QMouseEvent*>(event)->pos();

			m_bMovingMode = false;
			m_pTitleBar->setCursor(Qt::ArrowCursor);

			return true;
		}
		else if (event->type() == QEvent::MouseMove)
		{
			if (m_bMovingMode)
			{
				QPoint cursorPt = dynamic_cast<QMouseEvent*>(event)->globalPos();
				QPoint windowPt = m_pdlgCustomDlg->pos();

				int nDeltaX = cursorPt.x() - m_ptCursorPreview.x();
				int nDeltaY = cursorPt.y() - m_ptCursorPreview.y();
				m_ptCursorPreview = cursorPt;

				windowPt.setX(windowPt.x() + nDeltaX);
				windowPt.setY(windowPt.y() + nDeltaY);

				m_pdlgCustomDlg->move(windowPt);

				return true;
			}
		}
	}

	return QObject::eventFilter(watched, event);
}

void QCustomDialogTitleBar::slotShowMaximizeOrNormal()
{
	if (m_bMaximizeFlag)
	{
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/maximize"));
		m_ptbMaximize->setToolTip(QStringLiteral("最大化"));
		m_bMaximizeFlag = false;
		m_pdlgCustomDlg->showNormal();
	}
	else
	{
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore"));
		m_ptbMaximize->setToolTip(QStringLiteral("向下还原"));
		m_bMaximizeFlag = true;
		m_pdlgCustomDlg->showMaximized();
	}
}