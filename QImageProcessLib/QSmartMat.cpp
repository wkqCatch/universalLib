#include "QSmartMat.h"

#include <QFileDialog>

QSmartMat::QSmartMat()
	: m_matBase()
	, m_matRoi()
{
	
}

QSmartMat::QSmartMat(const Mat &matData)
	: m_matBase(matData)
	, m_matRoi()
{

}

QSmartMat::QSmartMat(int nRows, int nCols, int nType)
	: m_matBase(nRows, nCols, nType)
	, m_matRoi()
{

}

QSmartMat::QSmartMat(int nRows, int nCols, int nType, const Scalar & scalar)
	: m_matBase(nRows, nCols, nType, scalar)
	, m_matRoi()
{

}

QSmartMat::QSmartMat(int nRows, int nCols, int nType, void * pData)
	: m_matBase(nRows, nCols, nType, pData)
	, m_matRoi()
{

}

QSmartMat::~QSmartMat()
{

}

void QSmartMat::updateMatBase(const Mat & matData)
{
	m_matBase = matData;
}

Mat QSmartMat::getMatBase() const
{
	return m_matBase;
}

bool QSmartMat::isEmpty()
{
	return m_matBase.empty();
}

