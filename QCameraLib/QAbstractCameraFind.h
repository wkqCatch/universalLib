#pragma once

#include <QObject>

class QAbstractCameraFind : public QObject
{
	Q_OBJECT

public:
	QAbstractCameraFind(QObject *parent = nullptr);
	~QAbstractCameraFind();
};
