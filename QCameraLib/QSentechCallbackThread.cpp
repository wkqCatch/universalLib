#include "QSentechCallbackThread.h"
#include "QSentechCamera.h"

#include <PvBuffer.h>
#include <PvPipeline.h>

#include <QDebug>

QSentechCallbackThread::QSentechCallbackThread(QSentechCamera *pSentechCamera)
	: QThread()
{
	m_pSentechCamera = pSentechCamera;

/*	m_timeElapsed.start();*/
}

QSentechCallbackThread::~QSentechCallbackThread()
{
	if(isRunning())
	{
		requestInterruption();
		wait();
	}
}

void QSentechCallbackThread::run()
{
	if(m_pSentechCamera == nullptr)
	{
		return;
	}

	PvPipeline *pPipeline = m_pSentechCamera->getPipeline();

	for(;;)
	{
		// Check if we were signaled to terminate
		if(isInterruptionRequested())
		{
			break;
		}

		PvBuffer *pBuffer = nullptr;
		PvResult opResult = PvResult::Code::TIMEOUT;

		m_pSentechCamera->detachLock();

		// Try retrieving a buffer, using default timeout
		//PvResult lResult = pPipeline->RetrieveNextBuffer(&pBuffer, 0xFFFFFFFF, &opResult);
		PvResult lResult = pPipeline->RetrieveNextBuffer(&pBuffer, 390, &opResult);
		if(lResult.IsOK())
		{
			if(opResult.IsOK())
			{
				// We now have a valid buffer. This is where you would typically process the buffer.
				m_pSentechCamera->onImageCallback(pBuffer);

// 				 qDebug() << m_timeElapsed.elapsed() << endl;   //测试回调的间隔时间
// 				 m_timeElapsed.restart();
			}

			// Release buffer back to the pipeline
			pPipeline->ReleaseBuffer(pBuffer);
		}
		else
		{

		}

		m_pSentechCamera->detachUnlock();
	}
}
