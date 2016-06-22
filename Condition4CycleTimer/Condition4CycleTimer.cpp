#include "Condition4CycleTimer.h"

#include "../JobResolver/JobResolver.h"

Condition4CycleTimer::Condition4CycleTimer(void)
{
	m_xmlEleName = "Cycle";
}


Condition4CycleTimer::~Condition4CycleTimer(void)
{
	for (int i = 0;i < m_listCycleTimer.size();i++)
	{
		m_listCycleTimer[i]->stop();
		m_listCycleTimer[i]->disconnect();
		delete m_listCycleTimer[i];
	}
}

QString Condition4CycleTimer::createNewConditionJob(QString strJobId)
{
	if (!((JobResolver *)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not Cycle Job!";

	qlonglong qllTime = ((JobResolver *)_pJobResolver)->getConditionCycleMillisecond(strJobId);
	if (0 == qllTime) return "No Time on Xml!";

	QTimer *newTimer = new QTimer;
	newTimer->setSingleShot(false);
	connect(newTimer,SIGNAL(timeout()),this,SLOT(handleOnTime()),Qt::QueuedConnection);
	newTimer->start(qllTime);

	{
		QMutexLocker locker(&m_Mutex4Job2CycleTimer);
		m_hashJob2CycleTimer.insert(strJobId,newTimer);
	}

	return "Successful";
}

QString Condition4CycleTimer::deleteExistConditionJob(QString strJobId)
{
	if (!((JobResolver *)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not Cycle Job!";
	{
		QMutexLocker locker(&m_Mutex4Job2CycleTimer);
		QMultiHash<QString, QTimer*>::iterator iter = m_hashJob2CycleTimer.find(strJobId);
		while (iter != m_hashJob2CycleTimer.end() && iter.key() == strJobId) 
		{
			QTimer* needDelTimer = iter.value();
			needDelTimer->stop();
			needDelTimer->disconnect();
			delete needDelTimer;

			m_hashJob2CycleTimer.remove(strJobId);

			++iter;
		}
	}
	return "Successful";
}

void Condition4CycleTimer::handleOnTime()
{
	QTimer * actionTimer = (QTimer *)this->sender();
	QString strJobId;
	QMutexLocker locker(&m_Mutex4Job2CycleTimer);
	QMultiHash<QString, QTimer*>::iterator iter = m_hashJob2CycleTimer.begin();
	for (;iter != m_hashJob2CycleTimer.end();iter++) 
	{
		QTimer* needDelTimer = iter.value();
		if (actionTimer == needDelTimer)
		{
			//needDelTimer->stop();
			//needDelTimer->disconnect();
			//delete needDelTimer;

			strJobId = iter.key();

			emit signalExecJobOnCondition(strJobId);
		}
	}
	//m_hashJob2CycleTimer.remove(strJobId);
}