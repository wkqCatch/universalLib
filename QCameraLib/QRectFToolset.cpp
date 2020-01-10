#include "QRectFToolset.h"

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

QRectFToolset::QRectFToolset(QObject *parent)
	: QObject(parent)
	, m_nCurrentCategory(-1)
	, m_nCurrentIndex(0)
{
	m_vecRectFTool.clear();
}

QRectFToolset::~QRectFToolset()
{

}

void QRectFToolset::appendRectFTool(QKindOfRectF rectfTool)
{
	m_vecRectFTool.append(rectfTool);
}

void QRectFToolset::appendRectFTool(int nPenWidth, QColor penColor, int nFontSize)
{
	m_vecRectFTool.append(QKindOfRectF(penColor, nPenWidth, nFontSize));
}

void QRectFToolset::deleteRectFTool(int nIndex)
{
	if (nIndex < 0 || nIndex > m_vecRectFTool.size() - 1)
	{
		return;
	}

	m_vecRectFTool.remove(nIndex);
}

void QRectFToolset::clearRectFTool()
{
	m_vecRectFTool.clear();
}

void QRectFToolset::paintEvent(QPainter & painter)
{
	for(int nCounter = 0; nCounter < m_vecRectFTool.size(); ++nCounter)
	{
		m_vecRectFTool[nCounter].paint(painter);
	}
}

void QRectFToolset::mousePressEvent(QMouseEvent * pMouseEvent)
{

}

void QRectFToolset::mouseReleaseEvent(QMouseEvent * pMouseEvent)
{

}

void QRectFToolset::mouseMoveEvent(QMouseEvent * pMouseEvent)
{

}

void QRectFToolset::keyPressEvent(QKeyEvent * pKeyEvent)
{

}
