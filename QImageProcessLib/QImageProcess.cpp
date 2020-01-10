#include "QImageProcess.h"

#include <QFileDialog>

QString Cvstring2QString(const String & cvStringParam)
{
	return QString::fromLocal8Bit(cvStringParam.c_str());
}

String QString2Cvstring(const QString & qstringParam)
{
	return String(qstringParam.toLocal8Bit().constData());
}

QSmartMat loadSmartMatDirectly(const QString & strPath, int nFlags)
{
	Mat matTemp = imread(QString2Cvstring(strPath), nFlags);

	return QSmartMat(matTemp);
}

Mat loadMatDirectly(const QString & strPath, int nFlags)
{
	return imread(QString2Cvstring(strPath), nFlags);
}

QSmartMat loadSmartMatSelect(QWidget *pParent, const QString &strLookPath, int nFlags)
{
	QString strPath = QFileDialog::getOpenFileName(pParent, QStringLiteral("Ñ¡ÔñÍ¼Æ¬"), 
													strLookPath, "Image Files(*.bmp *.jpg *.png)");

	if(!strPath.isEmpty())
	{
		return QSmartMat(imread(QString2Cvstring(strPath), nFlags));
	}

	return QSmartMat();
}

Mat loadMatSelect(QWidget *pParent, const QString &strLookPath, int nFlags)
{
	QString strPath = QFileDialog::getOpenFileName(pParent, QStringLiteral("Ñ¡ÔñÍ¼Æ¬"), 
													strLookPath, "Image Files(*.bmp *.jpg *.png)");

	if (!strPath.isEmpty())
	{
		return imread(QString2Cvstring(strPath), nFlags);
	}

	return Mat();
}

void showImageByCv(const Mat & mat, const QString & strWindowName, int nFlags)
{
	String cvstrWindowName = QString2Cvstring(strWindowName);
	namedWindow(cvstrWindowName, nFlags);

	imshow(cvstrWindowName, mat);
}

void showImageByCv(const QSmartMat & smartMat, const QString & strWindowName, int nFlags)
{
	QSmartMat &noConstSmartMat = const_cast<QSmartMat&>(smartMat);

	if(!noConstSmartMat.isEmpty())
	{
		String cvstrWindowName = QString2Cvstring(strWindowName);
		namedWindow(cvstrWindowName, nFlags);

		imshow(cvstrWindowName, smartMat.getMatBase());
	}
}

void saveImageToDiskDirectly(const Mat & mat, const QString & strName)
{
	Mat &noConstMat = const_cast<Mat&>(mat);
	if(noConstMat.empty())
	{
		return;
	}

	imwrite(QString2Cvstring(strName), mat);
}

void saveImageToDiskDirectly(const QSmartMat & mat, const QString & strName)
{
	QSmartMat &noConstMat = const_cast<QSmartMat&>(mat);
	if (noConstMat.isEmpty())
	{
		return;
	}

	imwrite(QString2Cvstring(strName), mat.getMatBase());
}

void saveImageToDiskSelect(QWidget *pParent, const Mat & mat, const QString & strPath)
{
	QString strSavePath = QFileDialog::getSaveFileName(pParent, QStringLiteral("±£´æÍ¼Æ¬"), 
														strPath, "Image Files(*.bmp *.jpg *.png)");
	if(strSavePath.isEmpty())
	{
		return;
	}

	imwrite(QString2Cvstring(strSavePath), mat);
}

void saveImageToDiskSelect(QWidget *pParent, const QSmartMat & mat, const QString & strPath)
{
	QString strSavePath = QFileDialog::getSaveFileName(pParent, QStringLiteral("±£´æÍ¼Æ¬"), 
														strPath, "Image Files(*.bmp *.jpg *.png)");
	if (strSavePath.isEmpty())
	{
		return;
	}

	imwrite(QString2Cvstring(strSavePath), mat.getMatBase());
}

