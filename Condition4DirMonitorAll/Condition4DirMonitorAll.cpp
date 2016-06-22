#include "Condition4DirMonitorAll.h"

#include <QMutexLocker>

#include "../JobResolver/JobResolver.h"

Condition4DirMonitorAll::Condition4DirMonitorAll(void)
{
	m_QFileSystemWatcher = new QFileSystemWatcher;
	connect(m_QFileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(directoryChanged(QString)), Qt::QueuedConnection);

	m_xmlEleName = "MonitorDirAll";
}

Condition4DirMonitorAll::~Condition4DirMonitorAll(void)
{
	if (m_QFileSystemWatcher)
	{
		m_QFileSystemWatcher->disconnect();
		delete m_QFileSystemWatcher;
	}
}

void Condition4DirMonitorAll::directoryChanged( QString chgDir )
{
	((JobResolver*)_pJobResolver)->addDirMoniterAll4lList(chgDir);

	{
		QMutexLocker locker(&m_mutex4Job2DirList);
		QMultiHash<QString , QList<QDir> >::iterator iter = m_hash4Job2DirList.begin();
		for (;iter != m_hash4Job2DirList.end();iter++) 
		{
			QList<QDir> curDirLst = iter.value();
			if (curDirLst.contains(chgDir))
			{
				QString needExecJob = iter.key();
				emit signalExecJobOnCondition(needExecJob);
			}
		}
	}
}


QString Condition4DirMonitorAll::createNewConditionJob( QString strJobId )
{
	if (!((JobResolver*)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not DirMoniterAll Job!";

	QList<QDir> lstDir = ((JobResolver*)_pJobResolver)->getConditionDirMoniterAll(strJobId);

	if (lstDir.isEmpty()) return QString("DirMoniterAll '%1' fail!").arg(strJobId);
	for (int i = 0;i < lstDir.size();i++)
	{
		m_QFileSystemWatcher->addPath(lstDir[i].absolutePath());
	}

	{
		QMutexLocker locker(&m_mutex4Job2DirList);
		m_hash4Job2DirList.insertMulti(strJobId,lstDir);
	}

	return "Successful";
}

QString Condition4DirMonitorAll::deleteExistConditionJob( QString strJobId )
{
	if (!((JobResolver*)_pJobResolver)->isJob4Type(strJobId, m_xmlEleName)) return "Not DirMoniterAll Job!";

	{
		QMutexLocker locker(&m_mutex4Job2DirList);
		QMultiHash<QString , QList<QDir> >::iterator iter = m_hash4Job2DirList.find(strJobId);
		while (iter != m_hash4Job2DirList.end() && iter.key() == strJobId) 
		{
			QList<QDir> needDelDirLst = iter.value();
			for (int i = 0;i < needDelDirLst.size();i++)
			{
				m_QFileSystemWatcher->removePath(needDelDirLst[i].absolutePath());
			}
			++iter;
		}
		m_hash4Job2DirList.remove(strJobId);
	}

	return "Successful";
}
