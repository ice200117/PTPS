#pragma once
#include "Condition4DirMonitorAll_Global.h"

#include <QObject>
#include <QMutex>
#include <QMultiHash>
#include <QFileSystemWatcher>
#include <QDir>
#include <QList>
#include <QString>

#include "../common/ConditionInterface.h"

class CONDITION4DIRMONITORALL_IMPEXP Condition4DirMonitorAll : public ConditionInterface
{
	Q_OBJECT

public:
	Condition4DirMonitorAll(void);
	virtual ~Condition4DirMonitorAll(void);

	QString createNewConditionJob(QString);
	QString deleteExistConditionJob(QString);
	
public slots:
	void directoryChanged(QString);

private:
	QMutex m_mutex4Job2DirList;
	QMultiHash<QString , QList<QDir> > m_hash4Job2DirList;

	QFileSystemWatcher *m_QFileSystemWatcher;
};
