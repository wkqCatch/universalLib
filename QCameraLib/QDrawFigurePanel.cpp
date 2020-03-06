#include "QDrawFigurePanel.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMoveEvent>
#include <QMenu>

QDrawFigurePanel::QDrawFigurePanel(QWidget *parent)
	: QWidget(parent)
	, m_nKindOfRectfInOperating(-1)
	, m_nIndexOfRectfInOperating(0)
	, m_bDrawingMode(false)
	, m_bStartDrawing(false)
	, m_resizeMode(noMode)
	, m_bStartResizing(false)
	, m_bRectfBeSelected(false)
	, m_selectedAnchorPos(QCustomRectF::enotAnchor)
	, m_pCustomRightMenu(nullptr)
	, m_pactShowPixelValue(nullptr)
	, m_pactClearAllMarkPoints(nullptr)
	, m_bCancelMode(false)
	, m_bGetPixelValueMode(false)
	, m_currentPixelValueInfo{ 0, 0, false, 0, 0, 0, QPoint(0, 0) }
{
	m_colorBackground.setRgbF(0, 0, 0, 0.006);
	m_vecAllKindsOfRectF.clear();

	m_vecMarkPoints.clear();

	setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	setMouseTracking(false);

	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QDrawFigurePanel::customContextMenuRequested, this, &QDrawFigurePanel::slot_showPopMenu);

	m_pCustomRightMenu = new QMenu(this);

	m_pactShowPixelValue = m_pCustomRightMenu->addAction(QStringLiteral("获取像素值"));
	connect(m_pactShowPixelValue, &QAction::triggered, this, &QDrawFigurePanel::slot_enterGetPixelValueMode);

	m_pactClearAllMarkPoints = m_pCustomRightMenu->addAction(QStringLiteral("清除标记点"));
	connect(m_pactClearAllMarkPoints, &QAction::triggered, this, &QDrawFigurePanel::slot_clearAllMarkPoints);
}

QDrawFigurePanel::~QDrawFigurePanel()
{
}

void QDrawFigurePanel::enterDrawingMode(int nKindOfRectF)
{
	if (m_bGetPixelValueMode)
	{
		return;
	}

	if (nKindOfRectF > -1 && nKindOfRectF < m_vecAllKindsOfRectF.size())
	{
		m_bDrawingMode = true;
		m_nKindOfRectfInOperating = nKindOfRectF;
		setCursor(Qt::CrossCursor);
	}
}

void QDrawFigurePanel::addAKindOfRectF(const QKindOfRectF &kindOfRectF)
{
	m_vecAllKindsOfRectF.append(kindOfRectF);
}

void QDrawFigurePanel::addAKindOfRectF(QColor penColor, int nPenWidth, int nFontSize)
{
	m_vecAllKindsOfRectF.append(QKindOfRectF(penColor, nPenWidth, nFontSize));
}

void QDrawFigurePanel::deleteKindOfRectF(int nIndex)
{
	if (nIndex < 0 || nIndex > m_vecAllKindsOfRectF.size() - 1)
	{
		return;
	}

	m_vecAllKindsOfRectF.remove(nIndex);
}

void QDrawFigurePanel::addRectfForSpecificKind(int nKindOfRectF)
{
	if (nKindOfRectF < 0 || nKindOfRectF > m_vecAllKindsOfRectF.size() - 1)
	{
		return;
	}

	m_vecAllKindsOfRectF[nKindOfRectF].addRectF(QCustomRectF());
}

void QDrawFigurePanel::addRectfForSpecificKind(int nKindOfRectF, QCustomRectF customRectF)
{
	if (nKindOfRectF < 0 || nKindOfRectF > m_vecAllKindsOfRectF.size() - 1)
	{
		return;
	}

	m_vecAllKindsOfRectF[nKindOfRectF].addRectF(customRectF);
}

void QDrawFigurePanel::setDrawAllAnchor(bool bDrawAnchor)
{
	for (int nCounter = 0; nCounter < m_vecAllKindsOfRectF.size(); nCounter++)
	{
		m_vecAllKindsOfRectF[nCounter].setDrawAnchorFlag(bDrawAnchor);
	}
}

QCustomRectF QDrawFigurePanel::getSpecificRectF(int nKind, int nIndex)
{
	if (nKind < 0 || nKind > m_vecAllKindsOfRectF.size() - 1 || nIndex < 0 ||
		nIndex > m_vecAllKindsOfRectF.at(nKind).getSizeOfRectf())
	{
		return QCustomRectF();
	}

	return m_vecAllKindsOfRectF[nKind].getSpecificRectF(nIndex);
}

void QDrawFigurePanel::slot_updateImgRegion(int nOffsetX, int nOffsetY, int nWidth, int nHeight)
{
	move(nOffsetX, nOffsetY);
	resize(nWidth, nHeight);
}

void QDrawFigurePanel::slot_updateImgPos(int nX, int nY)
{
	move(nX, nY);
}

void QDrawFigurePanel::slot_showPopMenu(const QPoint & pt)
{
	if (m_bDrawingMode || m_bCancelMode)
	{
		m_bCancelMode = false;
		return;
	}

	m_pCustomRightMenu->popup(QCursor::pos());
}

void QDrawFigurePanel::slot_clearAllMarkPoints()
{
	m_vecMarkPoints.clear();
}

void QDrawFigurePanel::slot_enterGetPixelValueMode()
{
	if (m_bDrawingMode)
	{
		return;
	}

	m_bGetPixelValueMode = true;
	//setCursor(Qt::PointingHandCursor);
	setMouseTracking(true);

	m_ptCurrent = mapFromGlobal(QCursor::pos());
	emit sig_requestPixelValue(m_ptCurrent);
}

void QDrawFigurePanel::slot_receiveRequestedPixelValue(int nX, int nY, bool bColor, uchar ucChannal1,
	uchar ucChannel2, uchar ucChannel3)
{
	m_currentPixelValueInfo.nX = nX;
	m_currentPixelValueInfo.nY = nY;
	m_currentPixelValueInfo.bColor = bColor;
	m_currentPixelValueInfo.ucChannel1 = ucChannal1;
	m_currentPixelValueInfo.ucChannel2 = ucChannel2;
	m_currentPixelValueInfo.ucChannel3 = ucChannel3;
	m_currentPixelValueInfo.pt = m_ptCurrent;

	update();
}

void QDrawFigurePanel::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.fillRect(rect(), m_colorBackground);

	for (int nRectCounter = 0; nRectCounter < m_vecAllKindsOfRectF.size(); ++nRectCounter)
	{
		m_vecAllKindsOfRectF[nRectCounter].paint(painter);
	}

	if (m_bGetPixelValueMode)
	{
		if (m_currentPixelValueInfo.bColor)
		{
			painter.drawText(QRect(m_ptCurrent + QPoint(12, 0), QSize(180, 50)), Qt::AlignLeft,
				QString("X:%1 Y:%2\nrgb:%3 %4 %5").arg(m_currentPixelValueInfo.nX).arg(m_currentPixelValueInfo.nY)
				.arg(m_currentPixelValueInfo.ucChannel1).arg(m_currentPixelValueInfo.ucChannel2).arg(m_currentPixelValueInfo.ucChannel3));
		}
		else
		{
			painter.drawText(QRect(m_ptCurrent + QPoint(12, 0), QSize(180, 50)), Qt::AlignLeft,
				QString("X:%1 Y:%2\ngray:%3").arg(m_currentPixelValueInfo.nX).arg(m_currentPixelValueInfo.nY)
				.arg(m_currentPixelValueInfo.ucChannel1));
		}
	}

	for(int nMarkCounter = 0; nMarkCounter < m_vecMarkPoints.size(); nMarkCounter++)
	{
		painter.drawEllipse(m_vecMarkPoints[nMarkCounter].pt, 1, 1);

		if(m_vecMarkPoints[nMarkCounter].bColor)
		{
			painter.drawText(QRect(m_vecMarkPoints[nMarkCounter].pt + QPoint(12, 0), QSize(180, 50)), Qt::AlignLeft,
				QString("X:%1 Y:%2\nrgb:%3 %4 %5").arg(m_vecMarkPoints[nMarkCounter].nX).arg(m_vecMarkPoints[nMarkCounter].nY)
				.arg(m_vecMarkPoints[nMarkCounter].ucChannel1).arg(m_vecMarkPoints[nMarkCounter].ucChannel2).arg(m_vecMarkPoints[nMarkCounter].ucChannel3));
		}
		else
		{
			painter.drawText(QRect(m_vecMarkPoints[nMarkCounter].pt + QPoint(12, 0), QSize(180, 50)), Qt::AlignLeft,
				QString("X:%1 Y:%2\ngray:%3").arg(m_vecMarkPoints[nMarkCounter].nX).arg(m_vecMarkPoints[nMarkCounter].nY)
				.arg(m_vecMarkPoints[nMarkCounter].ucChannel1));
		}
	}
}

void QDrawFigurePanel::mousePressEvent(QMouseEvent * event)
{
	if (m_bDrawingMode)
	{
		if (event->button() == Qt::LeftButton)
		{
			if (m_vecAllKindsOfRectF.size() > 0 && m_nKindOfRectfInOperating < m_vecAllKindsOfRectF.size())
			{
				m_ptPress = event->pos();
				m_ptCurrent = m_ptPress;
				m_bStartDrawing = true;
				m_resizeMode = noMode;
				m_bRectfBeSelected = false;
				m_bStartResizing = false;
				setDrawAllAnchor(false);

				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].addRectF(QCustomRectF(m_ptPress, QSize(0, 0)));
				m_nIndexOfRectfInOperating = m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].getSizeOfRectf() - 1;

				setCursor(Qt::BlankCursor);

				update();
			}
		}
		else if (event->button() == Qt::RightButton)
		{
			m_bDrawingMode = false;
			m_bStartDrawing = false;
			setCursor(Qt::ArrowCursor);
			m_bCancelMode = true;
		}
	}
	else
	{
		if (event->button() == Qt::LeftButton)
		{
			if (m_bGetPixelValueMode)
			{
				PixelValueInfo valueInfoTemp = m_currentPixelValueInfo;
				m_vecMarkPoints << valueInfoTemp;

				emit sig_sendSelectedPixelPoint(valueInfoTemp.nX, valueInfoTemp.nY,
					valueInfoTemp.ucChannel1, valueInfoTemp.ucChannel2, valueInfoTemp.ucChannel3);

				return;
			}

			for (int nCounter = 0; nCounter < m_vecAllKindsOfRectF.size(); nCounter++)
			{
				m_vecAllKindsOfRectF[nCounter].setSelected(false);
			}

			for (int nCounter = 0; nCounter < m_vecAllKindsOfRectF.size(); nCounter++)
			{
				if (m_vecAllKindsOfRectF[nCounter].judgeRectFbyPoint(event->pos()))
				{
					m_nKindOfRectfInOperating = nCounter;
					m_nIndexOfRectfInOperating = m_vecAllKindsOfRectF[nCounter].getSelectedIndex();
					m_selectedRectfBackup = m_vecAllKindsOfRectF[nCounter].getSpecificRectF(m_nIndexOfRectfInOperating);
					m_selectedAnchorPos = m_vecAllKindsOfRectF[nCounter].getSelectedAnchorPos();
					if (m_selectedAnchorPos == QCustomRectF::enotAnchor)
					{
						m_resizeMode = byMove;
					}
					else
					{
						m_resizeMode = byAnchor;
					}

					switch (m_selectedAnchorPos)
					{
					case QCustomRectF::etopLeft:
					case QCustomRectF::ebottomRight:
						setCursor(Qt::SizeFDiagCursor);
						break;

					case QCustomRectF::emidTop:
					case QCustomRectF::emidBottom:
						setCursor(Qt::SizeVerCursor);
						break;

					case QCustomRectF::etopRight:
					case QCustomRectF::ebottomLeft:
						setCursor(Qt::SizeBDiagCursor);
						break;

					case QCustomRectF::emidRight:
					case QCustomRectF::emidLeft:
						setCursor(Qt::SizeHorCursor);
						break;

					default:
						break;
					}

					m_bRectfBeSelected = true;
					m_bStartDrawing = false;
					m_ptPress = event->pos();
					m_ptCurrent = m_ptPress;
					return;
				}
			}

			m_bRectfBeSelected = false;
			m_nKindOfRectfInOperating = -1;
			m_nIndexOfRectfInOperating = 0;
			update();
		}
		else if (event->button() == Qt::RightButton)
		{
			if (m_bGetPixelValueMode)
			{
				m_bGetPixelValueMode = false;
				m_bCancelMode = true;

				setMouseTracking(false);

				update();
			}
		}
	}
}

void QDrawFigurePanel::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (m_bDrawingMode && m_bStartDrawing)
		{
			m_bStartDrawing = false;
			m_ptRelease = event->pos();

			m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].normalizedSpecificRectF(m_nIndexOfRectfInOperating);
			m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].calculateSpecificRectfAnchor(m_nIndexOfRectfInOperating);
			setDrawAllAnchor(true);

			setCursor(Qt::CrossCursor);
			update();
		}
		else
		{
			if (m_bRectfBeSelected)
			{
				m_bRectfBeSelected = false;
				setCursor(Qt::ArrowCursor);
				update();
			}

			if (m_bStartResizing)
			{
				m_bStartResizing = false;
				setDrawAllAnchor(true);
				m_ptRelease = event->pos();

				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].normalizedSpecificRectF(m_nIndexOfRectfInOperating);
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].calculateSpecificRectfAnchor(m_nIndexOfRectfInOperating);
				setCursor(Qt::ArrowCursor);
				update();
			}
		}
	}
	else if (event->button() == Qt::RightButton)
	{
	}
}

void QDrawFigurePanel::mouseMoveEvent(QMouseEvent * event)
{
	m_ptCurrent = event->pos();

	if (m_bGetPixelValueMode)
	{
		emit sig_requestPixelValue(m_ptCurrent);

		if (m_ptCurrent.x() > rect().right() - 130)
		{
			m_ptCurrent.setX(rect().right() - 130);
		}

		if (m_ptCurrent.y() > rect().bottom() - 30)
		{
			m_ptCurrent.setY(rect().bottom() - 30);
		}

		return;
	}

	if (m_bRectfBeSelected)
	{
		for (int nCounter = 0; nCounter < m_vecAllKindsOfRectF.size(); nCounter++)
		{
			m_vecAllKindsOfRectF[nCounter].setSelected(false);
		}

		m_bRectfBeSelected = false;
		m_bStartResizing = true;
		setDrawAllAnchor(false);

		if (m_selectedAnchorPos == QCustomRectF::enotAnchor)
		{
			setCursor(Qt::ClosedHandCursor);
		}
	}

	if (m_ptCurrent.x() < 0)
	{
		m_ptCurrent.setX(0);
	}

	if (m_ptCurrent.y() < 0)
	{
		m_ptCurrent.setY(0);
	}

	if (m_ptCurrent.x() > rect().right())
	{
		m_ptCurrent.setX(rect().right());
	}

	if (m_ptCurrent.y() > rect().bottom())
	{
		m_ptCurrent.setY(rect().bottom());
	}

	if (m_bStartDrawing)
	{
		m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfWidth(m_nIndexOfRectfInOperating, m_ptCurrent.x() - m_ptPress.x());
		m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfHeight(m_nIndexOfRectfInOperating, m_ptCurrent.y() - m_ptPress.y());

		update();
	}

	if (m_bStartResizing)
	{
		switch (m_resizeMode)
		{
		case QDrawFigurePanel::noMode:

			break;

		case QDrawFigurePanel::byAnchor:
			switch (m_selectedAnchorPos)
			{
			case QCustomRectF::etopLeft:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopLeft(m_nIndexOfRectfInOperating, m_ptCurrent);
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomRight(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.bottomRight());
				break;

			case QCustomRectF::emidTop:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopLeft(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.x(), m_ptCurrent.y());
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomRight(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.bottomRight());
				break;

			case QCustomRectF::etopRight:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopRight(m_nIndexOfRectfInOperating, m_ptCurrent);
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomLeft(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.bottomLeft());
				break;

			case QCustomRectF::emidRight:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopLeft(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.topLeft());
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomRight(m_nIndexOfRectfInOperating,
					m_ptCurrent.x(), m_selectedRectfBackup.bottom());
				break;

			case QCustomRectF::ebottomRight:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopLeft(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.topLeft());
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomRight(m_nIndexOfRectfInOperating,
					m_ptCurrent);
				break;

			case QCustomRectF::emidBottom:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopLeft(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.topLeft());
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomRight(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.right(), m_ptCurrent.y());
				break;

			case QCustomRectF::ebottomLeft:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopRight(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.topRight());
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomLeft(m_nIndexOfRectfInOperating,
					m_ptCurrent);
				break;

			case QCustomRectF::emidLeft:
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfTopLeft(m_nIndexOfRectfInOperating,
					m_ptCurrent.x(), m_selectedRectfBackup.y());
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].setRectfBottomRight(m_nIndexOfRectfInOperating,
					m_selectedRectfBackup.bottomRight());
				break;

			case QCustomRectF::enotAnchor:
				break;

			default:
				break;
			}
			break;

		case QDrawFigurePanel::byMove:
			m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].translateRectF(m_nIndexOfRectfInOperating,
				m_ptCurrent.x() - m_ptPress.x(), m_ptCurrent.y() - m_ptPress.y());

			if (m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].getRectfLeft(m_nIndexOfRectfInOperating) < 0)
			{
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].moveRectfLeft(m_nIndexOfRectfInOperating, 0);
			}

			if (m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].getRectfTop(m_nIndexOfRectfInOperating) < 0)
			{
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].moveRectfTop(m_nIndexOfRectfInOperating, 0);
			}

			if (m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].getRectfRight(m_nIndexOfRectfInOperating) > rect().right())
			{
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].moveRectfRight(m_nIndexOfRectfInOperating, rect().right());
			}

			if (m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].getRectfBottom(m_nIndexOfRectfInOperating) > rect().bottom())
			{
				m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].moveRectfBottom(m_nIndexOfRectfInOperating, rect().bottom());
			}

			m_ptPress = m_ptCurrent;
			break;

		default:
			break;
		}

		update();
	}
}

void QDrawFigurePanel::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Delete)
	{
		if (m_nKindOfRectfInOperating < 0 || m_nKindOfRectfInOperating > m_vecAllKindsOfRectF.size() - 1 ||
			m_bStartDrawing || m_bStartResizing || !m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].getIsSelectedFlag())
		{
			return;
		}

		m_vecAllKindsOfRectF[m_nKindOfRectfInOperating].deleteRectF(m_nIndexOfRectfInOperating);
		m_nKindOfRectfInOperating = -1;
		m_nIndexOfRectfInOperating = 0;

		for (int nCounter = 0; nCounter < m_vecAllKindsOfRectF.size(); nCounter++)
		{
			m_vecAllKindsOfRectF[nCounter].setSelected(false);
		}

		update();
	}
}