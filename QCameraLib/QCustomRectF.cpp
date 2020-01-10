#include "QCustomRectF.h"

QCustomRectF::QCustomRectF()
	: QRectF()
	, m_nAnchorSize(ANCHORSIZE)
	, m_anchorPos(enotAnchor)
{
	calculateAnchor();
}

QCustomRectF::QCustomRectF(qreal dx, qreal dy, qreal dWidth, qreal dHeight)
	: QRectF(dx, dy, dWidth, dHeight)
	, m_nAnchorSize(ANCHORSIZE)
	, m_anchorPos(enotAnchor)
{
	calculateAnchor();
}

QCustomRectF::QCustomRectF(const QPointF & ptTopLeft, const QPointF & ptBottomRight)
	: QRectF(ptTopLeft, ptBottomRight)
	, m_nAnchorSize(ANCHORSIZE)
	, m_anchorPos(enotAnchor)
{
	calculateAnchor();
}

QCustomRectF::QCustomRectF(const QPointF & ptTopLeft, const QSizeF & sizef)
	: QRectF(ptTopLeft, sizef)
	, m_nAnchorSize(ANCHORSIZE)
	, m_anchorPos(enotAnchor)
{
	calculateAnchor();
}

QCustomRectF::~QCustomRectF()
{

}

void QCustomRectF::setAnchorSize(int nAnchorDiameter)
{
	m_nAnchorSize = nAnchorDiameter;
}

int QCustomRectF::getAnchorSize() const
{
	return m_nAnchorSize;
}

void QCustomRectF::setRectFText(QString strText)
{
	m_strRectFText = strText;
}

QString QCustomRectF::getRectFText() const
{
	return m_strRectFText;
}

void QCustomRectF::calculateAnchor()
{
	int nHalfAnchorSize = m_nAnchorSize / 2;

	int nLeft = static_cast<int>(left());
	int nRight = static_cast<int>(right());
	int nTop = static_cast<int>(top()); 
	int nBottom = static_cast<int>(bottom());
	int nWidth = static_cast<int>(width());
	int nHeight = static_cast<int>(height());

	m_arrayAnchor[0].setTopLeft(QPointF(nLeft - nHalfAnchorSize, nTop - nHalfAnchorSize));
	m_arrayAnchor[0].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[1].setTopLeft(QPointF(nLeft + nWidth / 2 - nHalfAnchorSize, nTop - nHalfAnchorSize));
	m_arrayAnchor[1].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[2].setTopLeft(QPointF(nRight - nHalfAnchorSize, nTop - nHalfAnchorSize));
	m_arrayAnchor[2].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[3].setTopLeft(QPointF(nRight - nHalfAnchorSize, nTop + nHeight / 2 - nHalfAnchorSize));
	m_arrayAnchor[3].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[4].setTopLeft(QPointF(nRight - nHalfAnchorSize, nBottom - nHalfAnchorSize));
	m_arrayAnchor[4].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[5].setTopLeft(QPointF(nLeft + nWidth / 2 - nHalfAnchorSize, nBottom - nHalfAnchorSize));
	m_arrayAnchor[5].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[6].setTopLeft(QPointF(nLeft - nHalfAnchorSize, nBottom - nHalfAnchorSize));
	m_arrayAnchor[6].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));

	m_arrayAnchor[7].setTopLeft(QPointF(nLeft - nHalfAnchorSize, nTop + nHeight / 2 - nHalfAnchorSize));
	m_arrayAnchor[7].setSize(QSizeF(m_nAnchorSize , m_nAnchorSize));
}

void QCustomRectF::setAnchorPos(AnchorPos curAnchorPos)
{
	m_anchorPos = curAnchorPos;
}

QCustomRectF::AnchorPos QCustomRectF::getAnchorPos() const
{
	return m_anchorPos;
}

const QRectF * QCustomRectF::getAnchorArray() const
{
	return m_arrayAnchor;
}

void QCustomRectF::normalizedCustomRectF()
{
	QRectF rec = normalized();

	setX(rec.x());
	setY(rec.y());
	setWidth(rec.width());
	setHeight(rec.height());
}
