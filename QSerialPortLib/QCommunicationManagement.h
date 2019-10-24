#pragma once

#include <QObject>

class QCommunicationManagement : public QObject
{
	Q_OBJECT

public:
	QCommunicationManagement(QObject *parent);
	virtual ~QCommunicationManagement();

private:

};
