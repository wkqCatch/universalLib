#include "QKindOfRectF.h"

#include <QPainter>

QKindOfRectF::QKindOfRectF(QColor penColor, int nPenWidth, int nFontSize)
	: m_nPenWidth(nPenWidth)
	, m_penColor(penColor)
	, m_bSelected(false)
	, m_nSelectedIndex(0)
	, m_bDrawAnchorFlag(true)
	, m_posSelectedAnchor(QCustomRectF::enotAnchor)
	, m_nFontSize(nFontSize)
{
	m_vecRectF.clear();

	m_pen.setColor(m_penColor);
	m_pen.setWidth(m_nPenWidth);
	m_pen.setStyle(Qt::SolidLine);

	setFontSize(m_nFontSize);
}

QKindOfRectF::QKindOfRectF()
	: m_nPenWidth(1)
	, m_penColor(Qt::green)
	, m_bSelected(false)
	, m_nSelectedIndex(0)
	, m_bDrawAnchorFlag(true)
	, m_posSelectedAnchor(QCustomRectF::enotAnchor)
{
	m_vecRectF.clear();
}

QKindOfRectF::~QKindOfRectF()
{

}

// QRectFTool::QRectFTool(const QRectFCategory & rectFCategory)
// {
// 	m_vecRectF = rectFCategory.m_vecRectF;
// 	m_nPenWidth = rectFCategory.m_nPenWidth;
// 	m_penColor = rectFCategory.m_penColor;
// 	m_nPriority = rectFCategory.m_nPriority;
// }
// QRectFTool & QRectFTool::operator=(const QRectFTool & rectFCategory)
// {
// 	// TODO: 在此处插入 return 语句
// 
// 	if(this != &rectFCategory)
// 	{
// 		m_vecRectF = rectFCategory.m_vecRectF;
// 		m_nPenWidth = rectFCategory.m_nPenWidth;
// 		m_penColor = rectFCategory.m_penColor;
// 		m_nPriority = rectFCategory.m_nPriority;
// 	}
// 	
// 	return *this;
// }

void QKindOfRectF::setPenWidth(int nWidth)
{
	m_nPenWidth = nWidth;
}

int QKindOfRectF::getPenWidth() const
{
	return m_nPenWidth;
}

void QKindOfRectF::setPenColor(QColor penColor)
{
	m_penColor = penColor;
}

QColor QKindOfRectF::getPenColor() const
{
	return m_penColor;
}

void QKindOfRectF::setFontSize(int nFontSize)
{
	m_font.setPixelSize(nFontSize);
	m_nFontSize = nFontSize;
}

int QKindOfRectF::getFontSize() const
{
	return m_nFontSize;
}

void QKindOfRectF::ClearRectF()
{
	m_vecRectF.clear();
}

void QKindOfRectF::addRectF(QCustomRectF & rectF)
{
	rectF.setRectFText(QString::number(m_vecRectF.size()));
	m_vecRectF.append(rectF);
}

void QKindOfRectF::deleteRectF(int nIndex)
{
	if(nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF.remove(nIndex);
}

void QKindOfRectF::setRectfTopLeft(int nIndex, const QPointF &ptTopLeft)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setTopLeft(ptTopLeft);
}

void QKindOfRectF::setRectfTopLeft(int nIndex, qreal qX, qreal qY)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setTopLeft(QPointF(qX, qY));
}

void QKindOfRectF::setRectfBottomRight(int nIndex, const QPointF &ptBottomRight)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setBottomRight(ptBottomRight);
}

void QKindOfRectF::setRectfBottomRight(int nIndex, qreal qX, qreal qY)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setBottomRight(QPointF(qX, qY));
}

void QKindOfRectF::setRectfTopRight(int nIndex, const QPointF & ptTopRight)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setTopRight(ptTopRight);
}

void QKindOfRectF::setRectfTopRight(int nIndex, qreal qX, qreal qY)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setTopRight(QPointF(qX, qY));
}

void QKindOfRectF::setRectfBottomLeft(int nIndex, const QPointF & ptBottomLeft)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setBottomLeft(ptBottomLeft);
}

void QKindOfRectF::setRectfBottomLeft(int nIndex, qreal qX, qreal qY)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setBottomLeft(QPointF(qX, qY));
}

void QKindOfRectF::translateRectF(int nIndex, qreal dX, qreal dY)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].translate(dX, dY);
}

qreal QKindOfRectF::getRectfLeft(int nIndex) const
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return 0;
	}

	return m_vecRectF[nIndex].left();
}

void QKindOfRectF::setRectfLeft(int nIndex, qreal dLeft)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setLeft(dLeft);
}

qreal QKindOfRectF::getRectfTop(int nIndex) const
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return 0;
	}

	return m_vecRectF[nIndex].top();
}

void QKindOfRectF::setRectfTop(int nIndex, qreal dTop)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setTop(dTop);
}

qreal QKindOfRectF::getRectfRight(int nIndex) const
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return 0;
	}

	return m_vecRectF[nIndex].right();
}

void QKindOfRectF::setRectfRight(int nIndex, qreal dRight)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setRight(dRight);
}

qreal QKindOfRectF::getRectfBottom(int nIndex) const
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return 0;
	}

	return m_vecRectF[nIndex].bottom();
}

void QKindOfRectF::setRectfBottom(int nIndex, qreal dBottom)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setBottom(dBottom);
}

void QKindOfRectF::moveRectfLeft(int nIndex, qreal qLeft)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].moveLeft(qLeft);
}

void QKindOfRectF::moveRectfTop(int nIndex, qreal qTop)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].moveTop(qTop);
}

void QKindOfRectF::moveRectfRight(int nIndex, qreal qRight)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].moveRight(qRight);
}

void QKindOfRectF::moveRectfBottom(int nIndex, qreal qBottom)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].moveBottom(qBottom);
}

void QKindOfRectF::setRectfX(int nIndex, qreal dX)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setX(dX);
}

void QKindOfRectF::setRectfY(int nIndex, qreal dY)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setY(dY);
}

void QKindOfRectF::setRectfWidth(int nIndex, qreal dWidth)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setWidth(dWidth);
}

void QKindOfRectF::setRectfHeight(int nIndex, qreal dHeight)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].setHeight(dHeight);
}

void QKindOfRectF::normalizedSpecificRectF(int nIndex)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].normalizedCustomRectF();
}

void QKindOfRectF::calculateSpecificRectfAnchor(int nIndex)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return;
	}

	m_vecRectF[nIndex].calculateAnchor();
}

QCustomRectF QKindOfRectF::getSpecificRectF(int nIndex)
{
	if (nIndex < 0 || nIndex > m_vecRectF.size() - 1)
	{
		return QCustomRectF(0, 0, 0, 0);
	}

	return m_vecRectF[nIndex];
}

bool QKindOfRectF::judgeRectFbyPoint(const QPointF & pt)
{
	for(int nRectFCounter = 0; nRectFCounter <  m_vecRectF.size(); nRectFCounter++)
	{
		const QRectF *pRectF = m_vecRectF[nRectFCounter].getAnchorArray();

		for (int nAnchorCounter = 0; nAnchorCounter < ANCHORNUM; nAnchorCounter++)
		{
			if(pRectF[nAnchorCounter].contains(pt))
			{
				m_nSelectedIndex = nRectFCounter;
				m_posSelectedAnchor = static_cast<QCustomRectF::AnchorPos>(nAnchorCounter);
				m_bSelected = true;
				return true;
			}
		}
	}

	for(int nRectFCounter = 0; nRectFCounter < m_vecRectF.size(); nRectFCounter++)
	{
		if(m_vecRectF[nRectFCounter].contains(pt))
		{
			m_nSelectedIndex = nRectFCounter;
			m_posSelectedAnchor = QCustomRectF::enotAnchor;
			m_bSelected = true;
			return true;
		}
	}

	m_bSelected = false;
	return false;
}

bool QKindOfRectF::getIsSelectedFlag() const
{
	return m_bSelected;
}

int QKindOfRectF::getSelectedIndex() const
{
	return m_nSelectedIndex;
}

QCustomRectF::AnchorPos QKindOfRectF::getSelectedAnchorPos() const
{
	return m_posSelectedAnchor;
}

void QKindOfRectF::paint(QPainter & painter)
{
	m_pen.setWidth(m_nPenWidth);
	painter.setPen(m_pen);
	painter.setFont(m_font);

	for (int nRectFCounter = 0; nRectFCounter < m_vecRectF.size(); nRectFCounter++)
	{
		painter.drawRect(m_vecRectF[nRectFCounter]);
		
		if(m_bDrawAnchorFlag)
		{
			painter.drawText(m_vecRectF[nRectFCounter].topLeft() + QPointF(8, -5), m_vecRectF[nRectFCounter].getRectFText());
			painter.drawRects(m_vecRectF[nRectFCounter].getAnchorArray(), ANCHORNUM);
		}
	}

	if(m_bDrawAnchorFlag)
	{
		if (m_bSelected)
		{
			painter.setBrush(QBrush(m_penColor, Qt::Dense4Pattern));
			painter.drawRects(m_vecRectF[m_nSelectedIndex].getAnchorArray(), ANCHORNUM);
		}
	}
}

void QKindOfRectF::setSelected(bool bSelected)
{
	m_bSelected = bSelected;
}

void QKindOfRectF::setSelectedIndex(int nSelectedIndex)
{
	m_nSelectedIndex = nSelectedIndex;
}

int QKindOfRectF::getSizeOfRectf() const
{
	return m_vecRectF.size();
}

void QKindOfRectF::setDrawAnchorFlag(bool bDrawAnchor)
{
	m_bDrawAnchorFlag = bDrawAnchor;
}

bool QKindOfRectF::getDrawAnchorFlag() const
{
	return m_bDrawAnchorFlag;
}

