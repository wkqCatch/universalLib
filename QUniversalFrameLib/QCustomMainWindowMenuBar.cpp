#include "QCustomMainWindowMenuBar.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QFrame>
#include <QHboxLayout>
#include <QToolButton>
#include <QToolBar>
#include <QEvent>
#include <QCursor>
#include <QMouseEvent>

QCustomMainWindowMenuBar::QCustomMainWindowMenuBar(QMainWindow *pMainWindow, int nMenuBarHeight)
	: QObject(pMainWindow)
	, m_plbAppIcon(nullptr)
	, m_plbAppTitle(nullptr)
	, m_ptbLanguageSetting(nullptr)
	, m_ptbMinimize(nullptr)
	, m_ptbSkinSetting(nullptr)
	, m_nMenubarHeight(nMenuBarHeight)
	, m_pmenuLanguageSetting(nullptr)
	, m_pmenuSkinSetting(nullptr)
	, m_ptbClose(nullptr)
	, m_ptbMaximize(nullptr)
	, m_bMaximizeFlag(false)
	, m_pMainWindow(pMainWindow)
	, m_pMenubar(nullptr)
	, m_bMovingMode(false)
	, m_ptCursorPreview()
{
	if (pMainWindow == nullptr)
	{
		return;
	}

	//以下是创建程序的图标和名称的代码
	pMainWindow->setWindowFlag(Qt::FramelessWindowHint, true);
	pMainWindow->setWindowState(Qt::WindowMaximized);
	m_bMaximizeFlag = true;
	pMainWindow->installEventFilter(this);

 	QMenuBar *pMenuBar = pMainWindow->menuBar();
	m_pMenubar = pMenuBar;
 	QFont menuBarFont = pMenuBar->font();
 	menuBarFont.setPixelSize(m_nMenubarHeight);
 	pMenuBar->setFont(menuBarFont);
	pMenuBar->installEventFilter(this);

	QFrame *pIconAndTitleFrame = new QFrame();
	pIconAndTitleFrame->setAttribute(Qt::WA_TranslucentBackground, true);

	m_plbAppIcon = new QLabel();
	m_plbAppIcon->setAttribute(Qt::WA_TranslucentBackground, true);

	m_plbAppTitle = new QLabel();
	m_plbAppTitle->setFixedWidth(250);
	m_plbAppTitle->setAttribute(Qt::WA_TranslucentBackground, true);

	QHBoxLayout *pIconAndTitleLayout = new QHBoxLayout(pIconAndTitleFrame);
	pIconAndTitleLayout->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);
	pIconAndTitleLayout->setContentsMargins(6, 0, 0, 0);
	pIconAndTitleLayout->setSpacing(3);

	pIconAndTitleLayout->addWidget(m_plbAppIcon);
	pIconAndTitleLayout->addWidget(m_plbAppTitle);
	pIconAndTitleLayout->addStretch();

	pMenuBar->setCornerWidget(pIconAndTitleFrame, Qt::TopLeftCorner);

	//以下是创建程序基础操作的代码(换肤，最小化，关闭)
	QFrame *pToolButtonFrame = new QFrame(pMenuBar);
	pToolButtonFrame->setAttribute(Qt::WA_TranslucentBackground, true);

	m_ptbLanguageSetting = new QToolButton();
	m_ptbLanguageSetting->setAutoRaise(true);
	m_ptbLanguageSetting->setToolTip(QStringLiteral("语言"));
	m_ptbLanguageSetting->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbLanguageSetting->setIcon(QIcon(":/MenuBarRc/LanguageSetting"));
	m_pmenuLanguageSetting = new QMenu(m_ptbLanguageSetting);
	m_pmenuLanguageSetting->addAction("simple chinese");
	m_pmenuLanguageSetting->addAction("complex chinese");
	m_pmenuLanguageSetting->addAction("english");
	m_ptbLanguageSetting->setMenu(m_pmenuLanguageSetting);
	m_ptbLanguageSetting->setPopupMode(QToolButton::InstantPopup);

	m_ptbSkinSetting = new QToolButton();
	m_ptbSkinSetting->setAutoRaise(true);
	m_ptbSkinSetting->setToolTip(QStringLiteral("皮肤"));
	m_ptbSkinSetting->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbSkinSetting->setIcon(QIcon(":/MenuBarRc/SkinSetting"));
	m_pmenuSkinSetting = new QMenu(m_ptbSkinSetting);
	m_pmenuSkinSetting->addAction("dark light");
	m_pmenuSkinSetting->addAction("cool blue");
	m_pmenuSkinSetting->addAction("dark yellow");
	m_ptbSkinSetting->setMenu(m_pmenuSkinSetting);
	m_ptbSkinSetting->setPopupMode(QToolButton::InstantPopup);

	m_ptbMinimize = new QToolButton();
	m_ptbMinimize->setAutoRaise(true);
	m_ptbMinimize->setToolTip(QStringLiteral("最小化"));
	m_ptbMinimize->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbMinimize->setIcon(QIcon(":/MenuBarRc/Minimize"));

	m_ptbMaximize = new QToolButton();
	m_ptbMaximize->setAutoRaise(true);
	m_ptbMaximize->setToolTip(QStringLiteral("向下还原"));
	m_ptbMaximize->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore"));

	m_ptbClose = new QToolButton();
	m_ptbClose->setAutoRaise(true);
	m_ptbClose->setToolTip(QStringLiteral("关闭"));
	m_ptbClose->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbClose->setIcon(QIcon(":/MenuBarRc/Close"));

	QHBoxLayout *pToolButtonLayout = new QHBoxLayout(pToolButtonFrame);
	pToolButtonLayout->setAlignment(Qt::AlignHCenter | Qt::AlignLeft);
	pToolButtonLayout->setContentsMargins(0, 4, 0, 0);
	pToolButtonLayout->setSpacing(3);

	pToolButtonLayout->addStretch();
	pToolButtonLayout->addWidget(m_ptbSkinSetting);
	pToolButtonLayout->addWidget(m_ptbLanguageSetting);
	pToolButtonLayout->addWidget(m_ptbMinimize);
	pToolButtonLayout->addWidget(m_ptbMaximize);
	pToolButtonLayout->addWidget(m_ptbClose);

	pMenuBar->setCornerWidget(pToolButtonFrame, Qt::TopRightCorner);

	connect(m_ptbMinimize, &QToolButton::clicked, pMainWindow, &QMainWindow::showMinimized);
	connect(m_ptbClose, &QToolButton::clicked, pMainWindow, &QMainWindow::close);
	connect(m_ptbMaximize, &QToolButton::clicked, this, &QCustomMainWindowMenuBar::slotShowNormalOrMaximize);
}

QCustomMainWindowMenuBar::~QCustomMainWindowMenuBar()
{
}

void QCustomMainWindowMenuBar::setAppIcon(QString strAppIcon)
{
	if (m_plbAppIcon == nullptr)
	{
		return;
	}

	m_plbAppIcon->setPixmap(QPixmap(strAppIcon).scaled(m_nMenubarHeight, m_nMenubarHeight));
}

void QCustomMainWindowMenuBar::setAppTitle(QString strAppTitle)
{
	if (m_plbAppTitle == nullptr)
	{
		return;
	}

	m_plbAppTitle->setText(strAppTitle);
	QFont appTitleFont = m_plbAppTitle->font();
	appTitleFont.setPixelSize(m_nMenubarHeight * 0.7);
	appTitleFont.setItalic(true);
	m_plbAppTitle->setFont(appTitleFont);
}

void QCustomMainWindowMenuBar::enableMaximize(bool bMaximize)
{
	m_ptbMaximize->setEnabled(bMaximize);
	if (bMaximize)
	{
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore"));
	}
	else
	{
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore_disable"));
	}
}

void QCustomMainWindowMenuBar::enableMinimize(bool bMinimize)
{
	m_ptbMinimize->setEnabled(bMinimize);
}

bool QCustomMainWindowMenuBar::eventFilter(QObject * watched, QEvent * event)
{
	if (m_bMaximizeFlag)
	{
		return QObject::eventFilter(watched, event);
	}

	if (watched == m_pMenubar)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QPoint pt = dynamic_cast<QMouseEvent*>(event)->pos();

			m_ptCursorPreview = dynamic_cast<QMouseEvent*>(event)->globalPos();

			if (m_pMenubar->actionAt(pt) == nullptr)
			{
				m_bMovingMode = true;
				m_pMenubar->setCursor(Qt::ClosedHandCursor);

				return true;
			}
		}
		else if (event->type() == QEvent::MouseButtonRelease)
		{
			QPoint pt = dynamic_cast<QMouseEvent*>(event)->pos();
			if (m_pMenubar->actionAt(pt) == nullptr)
			{
				m_bMovingMode = false;
				m_pMenubar->setCursor(Qt::ArrowCursor);

				return true;
			}
		}
		else if (event->type() == QEvent::MouseMove)
		{
			if (m_bMovingMode)
			{
				QPoint cursorPt = dynamic_cast<QMouseEvent*>(event)->globalPos();
				QPoint windowPt = m_pMainWindow->pos();

				int nDeltaX = cursorPt.x() - m_ptCursorPreview.x();
				int nDeltaY = cursorPt.y() - m_ptCursorPreview.y();
				m_ptCursorPreview = cursorPt;

				windowPt.setX(windowPt.x() + nDeltaX);
				windowPt.setY(windowPt.y() + nDeltaY);
				
				m_pMainWindow->move(windowPt);

				return true;
			}
		}
	}

	return QObject::eventFilter(watched, event);
}

void QCustomMainWindowMenuBar::slotShowNormalOrMaximize()
{
	if (m_bMaximizeFlag)
	{
		m_bMaximizeFlag = false;
		m_pMainWindow->showNormal();
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/maximize"));
		m_ptbMaximize->setToolTip(QStringLiteral("最大化"));
	}
	else
	{
		m_bMaximizeFlag = true;
		m_pMainWindow->showMaximized();
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore"));
		m_ptbMaximize->setToolTip(QStringLiteral("向下还原"));
	}
}