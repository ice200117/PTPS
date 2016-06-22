#include "Condition4Once.h"

#include <QObject>

#include "../JobResolver/JobResolver.h"

Condition4Once::Condition4Once(void)
{
	m_xmlEleName = "Once";
}

Condition4Once::~Condition4Once(void)
{
	for (int i = 0;i < m_listCountdownTimer.size();i++)
	{
		m_listCountdownTimer[i]->stop();
		m_listCountdownTimer[i]->disconnect();
		delete m_listCountdownTimer[i];
	}
}

QString Condition4Once::createNewConditionJob( QString strJobId )
{
	if (!((JobResolver *)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not Once Job!";
	
	qlonglong qllTime = ((JobResolver *)_pJobResolver)->getConditionOnceMillisecond(strJobId);
	if (0 == qllTime) return "No Time on Xml!";

	QTimer *newTimer = new QTimer;
	newTimer->setSingleShot(true);
	connect(newTimer,SIGNAL(timeout()),this,SLOT(handleOnTime()),Qt::QueuedConnection);
	newTimer->start(qllTime);

	{
		QMutexLocker locker(&m_Mutex4Job2Timer);
		m_hashJob2Timer.insert(strJobId,newTimer);
	}

	return "Successful";
}

QString Condition4Once::deleteExistConditionJob( QString strJobId )
{
	if (!((JobResolver *)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not Once Job!";
	{
		QMutexLocker locker(&m_Mutex4Job2Timer);
		QMultiHash<QString, QTimer*>::iterator iter = m_hashJob2Timer.find(strJobId);
		while (iter != m_hashJob2Timer.end() && iter.key() == strJobId) 
		{
			QTimer* needDelTimer = iter.value();
			needDelTimer->stop();
			needDelTimer->disconnect();
			delete needDelTimer;

			m_hashJob2Timer.remove(strJobId);

			++iter;
		}
	}
	return "Successful";
}

void Condition4Once::handleOnTime()
{
	QTimer * actionTimer = (QTimer *)this->sender();
	QString strJobId;
	QMutexLocker locker(&m_Mutex4Job2Timer);
	QMultiHash<QString, QTimer*>::iterator iter = m_hashJob2Timer.begin();
	for (;iter != m_hashJob2Timer.end();iter++) 
	{
		QTimer* needDelTimer = iter.value();
		if (actionTimer == needDelTimer)
		{
			needDelTimer->stop();
			needDelTimer->disconnect();
			delete needDelTimer;

			strJobId = iter.key();

			emit signalExecJobOnCondition(strJobId);
		}
	}
	m_hashJob2Timer.remove(strJobId);
}