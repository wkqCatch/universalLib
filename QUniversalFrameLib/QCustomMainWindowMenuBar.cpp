#include "QCustomMainWindowMenuBar.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QLabel>
#include <QFrame>
#include <QHboxLayout>
#include <QToolButton>
#include <QToolBar>

QCustomMainWindowMenuBar::QCustomMainWindowMenuBar(QMainWindow *pMainWindow, int nMenuBarHeight)
	: QObject()
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
{
	if(pMainWindow == nullptr)
	{
		return;
	}

	//�����Ǵ��������ͼ������ƵĴ���KO
	pMainWindow->setWindowFlag(Qt::FramelessWindowHint, true);
	pMainWindow->setWindowState(Qt::WindowMaximized);
	m_bMaximizeFlag = true;

	QMenuBar *pMenuBar = pMainWindow->menuBar(); 
	QFont menuBarFont = pMenuBar->font();
	menuBarFont.setPixelSize(m_nMenubarHeight);
	pMenuBar->setFont(menuBarFont);

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

	//�����Ǵ���������������Ĵ���(��������С�����ر�)
	QFrame *pToolButtonFrame = new QFrame(pMenuBar);
	pToolButtonFrame->setAttribute(Qt::WA_TranslucentBackground, true);

	m_ptbLanguageSetting = new QToolButton();
	m_ptbLanguageSetting->setAutoRaise(true);
	m_ptbLanguageSetting->setToolTip(QStringLiteral("����"));
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
	m_ptbSkinSetting->setToolTip(QStringLiteral("Ƥ��"));
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
	m_ptbMinimize->setToolTip(QStringLiteral("��С��"));
	m_ptbMinimize->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbMinimize->setIcon(QIcon(":/MenuBarRc/Minimize"));

	m_ptbMaximize = new QToolButton();
	m_ptbMaximize->setAutoRaise(true);
	m_ptbMaximize->setToolTip(QStringLiteral("���»�ԭ"));
	m_ptbMaximize->setIconSize(QSize(m_nMenubarHeight, m_nMenubarHeight));
	m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore"));

	m_ptbClose = new QToolButton();
	m_ptbClose->setAutoRaise(true);
	m_ptbClose->setToolTip(QStringLiteral("�ر�"));
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
	if(m_plbAppIcon == nullptr)
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
}

void QCustomMainWindowMenuBar::slotShowNormalOrMaximize()
{
	if (m_bMaximizeFlag)
	{
		m_bMaximizeFlag = false;
		m_pMainWindow->showNormal();
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/maximize"));
		m_ptbMaximize->setToolTip(QStringLiteral("���"));
	}
	else
	{
		m_bMaximizeFlag = true;
		m_pMainWindow->showMaximized();
		m_ptbMaximize->setIcon(QIcon(":/MenuBarRc/restore"));
		m_ptbMaximize->setToolTip(QStringLiteral("���»�ԭ"));
	}
}