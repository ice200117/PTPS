#include "Condition4DirMonitor.h"

#include <QMutexLocker>

#include "../JobResolver/JobResolver.h"

#include "../Logger/Logger.h"

Condition4DirMonitor::Condition4DirMonitor(void)
{
	m_QFileSystemWatcher = new QFileSystemWatcher;
	connect(m_QFileSystemWatcher, SIGNAL(directoryChanged(QString)), this,SLOT(directoryChanged(QString)),Qt::QueuedConnection);

	m_xmlEleName = "MonitorDir";
}

Condition4DirMonitor::~Condition4DirMonitor(void)
{
	if (m_QFileSystemWatcher)
	{
		m_QFileSystemWatcher->disconnect();
		delete m_QFileSystemWatcher;
	}
}

//#include <QThread>

void Condition4DirMonitor::directoryChanged(QString chgDir)
{
	//Logger *p = &(Logger::getInstance());
	//p->writeInfo("Condition4DirMonitor on " + QString::number((long)(QThread::currentThread())));

	QMutexLocker locker(&m_Mutex4Job2Dir);
	QMultiHash<QString, QDir>::iterator iter = m_hashJob2Dir.begin();
	for (;iter != m_hashJob2Dir.end();iter++)
	{
		QDir curDir = iter.value();
		if (curDir.absolutePath() == chgDir)
		{
			QString needExecJob = iter.key();
			emit signalExecJobOnCondition(needExecJob);
		}
	}
}

QString Condition4DirMonitor::createNewConditionJob( QString strJobId )
{
	if (!((JobResolver*)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not DirMoniter Job!";
	QDir curDir = ((JobResolver*)_pJobResolver)->getConditionDirMoniter(strJobId);
	if (!curDir.exists()) return QString("Dir '%1' not exist!").arg(curDir.absolutePath());

	m_QFileSystemWatcher->addPath(curDir.absolutePath());

	{
		QMutexLocker locker(&m_Mutex4Job2Dir);
		m_hashJob2Dir.insertMulti(strJobId,curDir);
	}

	return "Successful";
}

QString Condition4DirMonitor::deleteExistConditionJob( QString strJobId )
{
	if (!((JobResolver*)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not DirMoniter Job!";

	{
		QMutexLocker locker(&m_Mutex4Job2Dir);
		QMultiHash<QString, QDir>::iterator iter = m_hashJob2Dir.find(strJobId);
		while (iter != m_hashJob2Dir.end() && iter.key() == strJobId) 
		{
			QDir needDelDir = iter.value();
			m_QFileSystemWatcher->removePath(needDelDir.absolutePath());
			++iter;
		}
		m_hashJob2Dir.remove(strJobId);
	}

	return "Successful";
}
