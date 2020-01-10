#pragma once

#include <QThread>

#include <QElapsedTimer>

class QSentechCamera;
class QSentechCallbackThread : public QThread
{
	Q_OBJECT

public:
	QSentechCallbackThread(QSentechCamera *pSentechCamera);
	~QSentechCallbackThread();

protected:
	void run() override;

private:
	QSentechCamera *m_pSentechCamera;     //œ‡ª˙÷∏’Î

	QElapsedTimer	    m_timeElapsed;
};
