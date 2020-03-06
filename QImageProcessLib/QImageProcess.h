#pragma once

#include <QObject>

#include "QSmartMat.h"

#define IMAGE_EXPORT __declspec(dllexport)

IMAGE_EXPORT QString Cvstring2QString(const String &cvStringParam);  //cv::String与QString的相互转换
IMAGE_EXPORT String QString2Cvstring(const QString &qstringParam);

IMAGE_EXPORT QSmartMat loadSmartMatDirectly(const QString &strPath, int nFlags = 1);
IMAGE_EXPORT Mat loadMatDirectly(const QString &strPath, int nFlags = 1);

IMAGE_EXPORT QSmartMat loadSmartMatSelect(QWidget *pParent, const QString &strLookPath, int nFlags = 1);
IMAGE_EXPORT Mat loadMatSelect(QWidget *pParent, const QString &strLookPath, int nFlags = 1);

IMAGE_EXPORT void showImageByCv(const Mat &mat, const QString &strWindowName, int nFlags = 1);
IMAGE_EXPORT void showImageByCv(const QSmartMat &smartMat, const QString &strWindowName, int nFlags = 1);

IMAGE_EXPORT void saveImageToDiskDirectly(const Mat &mat, const QString &strName);
IMAGE_EXPORT void saveImageToDiskDirectly(const QSmartMat &mat, const QString &strName);

IMAGE_EXPORT void saveImageToDiskSelect(QWidget *pParent, const Mat &mat, const QString &strPath);
IMAGE_EXPORT void saveImageToDiskSelect(QWidget *pParent, const QSmartMat &mat, const QString &strPath);

