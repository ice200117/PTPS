#pragma once

#include <QStringList>
#include <QMultiHash>
#include <QMutex>
#include <QTimer>
#include <QList>

#include "Condition4Once_Global.h"

#include "../common/ConditionInterface.h"

class CONDITION4ONCE_IMPEXP Condition4Once : public ConditionInterface
{
	Q_OBJECT

public:
	Condition4Once(void);
	virtual ~Condition4Once(void);

	QString createNewConditionJob(QString);
	QString deleteExistConditionJob(QString);

public slots:
	void handleOnTime();

private:
	QMutex m_Mutex4Job2Timer;
	QMultiHash<QString , QTimer*> m_hashJob2Timer;

	QList<QTimer *> m_listCountdownTimer;
};