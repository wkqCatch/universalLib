#pragma once

#include "qimageprocesslib_global.h"

#include <opencv2/opencv.hpp>

using namespace cv;

#include <QObject>

class QIMAGEPROCESSLIB_EXPORT QSmartMat
{
public:
	QSmartMat();
	QSmartMat(const Mat &matData);
	QSmartMat(int nRows, int nCols, int nType);
	QSmartMat(int nRows, int nCols, int nType, const Scalar& scalar);
	QSmartMat(int nRows, int nCols, int nType, void *pData);
	~QSmartMat();

	void updateMatBase(const Mat& matData);
	Mat getMatBase() const;

	bool isEmpty();							//base mat �Ƿ��ǿյ�
	
private:
	Mat m_matBase;							//mat����
	Mat m_matRoi;							//����Ȥ����
};
