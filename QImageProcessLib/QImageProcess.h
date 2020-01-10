#pragma once

#include <QObject>

#include "QSmartMat.h"

__declspec(dllexport) QString Cvstring2QString(const String &cvStringParam);  //cv::String与QString的相互转换
__declspec(dllexport) String QString2Cvstring(const QString &qstringParam);

__declspec(dllexport) QSmartMat loadSmartMatDirectly(const QString &strPath, int nFlags = 1);
__declspec(dllexport) Mat loadMatDirectly(const QString &strPath, int nFlags = 1);

__declspec(dllexport) QSmartMat loadSmartMatSelect(QWidget *pParent, const QString &strLookPath, int nFlags = 1);
__declspec(dllexport) Mat loadMatSelect(QWidget *pParent, const QString &strLookPath, int nFlags = 1);

__declspec(dllexport) void showImageByCv(const Mat &mat, const QString &strWindowName, int nFlags = 1);
__declspec(dllexport) void showImageByCv(const QSmartMat &smartMat, const QString &strWindowName, int nFlags = 1);

__declspec(dllexport) void saveImageToDiskDirectly(const Mat &mat, const QString &strName);
__declspec(dllexport) void saveImageToDiskDirectly(const QSmartMat &mat, const QString &strName);

__declspec(dllexport) void saveImageToDiskSelect(QWidget *pParent, const Mat &mat, const QString &strPath);
__declspec(dllexport) void saveImageToDiskSelect(QWidget *pParent, const QSmartMat &mat, const QString &strPath);
