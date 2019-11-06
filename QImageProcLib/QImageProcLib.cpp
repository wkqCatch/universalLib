#include "QImageProcLib.h"

#include <QWidget>

QImageProcLib::QImageProcLib(QObject *pParent)
	: QObject(pParent)
	, m_pWidget(nullptr)
{
	m_pWidget = new QWidget();
}
