#pragma once

#include <QStringList>
#include <QMultiHash>
#include <QMutex>
#include <QTimer>
#include <QList>

#include "Condition4CycleTimer_Global.h"
#include "../common/ConditionInterface.h"

class CONDITION4CYCLETIMER_IMPEXP Condition4CycleTimer : public ConditionInterface
{
	Q_OBJECT

public:
	Condition4CycleTimer(void);
	virtual ~Condition4CycleTimer(void);

	QString createNewConditionJob(QString);
	QString deleteExistConditionJob(QString);

public slots:
	void handleOnTime();

private:
	QMutex m_Mutex4Job2CycleTimer;
	QMultiHash<QString , QTimer*> m_hashJob2CycleTimer;

	QList<QTimer *> m_listCycleTimer;
};

