#pragma once
#include "Condition4Timer_Global.h"

#include <map>
#include <string.h>

#include <QString>
#include <QStringList>
#include <QMultiHash>
#include <QMutex>
#include <QTimer>
#include <QObject>

#include "../common/ConditionInterface.h"

typedef enum UPDATA_CONDITION_STEP
{
	HOUR,
	DAY

}UPDATA_CONDITION_STEP;

using namespace std; 

class CONDITION4TIMER_IMPEXP Condition4Timer : public ConditionInterface
{
	Q_OBJECT

public:
	Condition4Timer(void);
	virtual ~Condition4Timer(void);

	QString createNewConditionJob(QString);
	QString deleteExistConditionJob(QString);

public slots:
	void slotHandleHeartbeat();

protected:
	QString startHeartbeat(int ibeatTime = 1000);
	QString stopHeartbeat();
	QString updataConditionList();
	QStringList getConditionTime(QString);

private:
	QMutex m_Mutex4Tim2Job;
	QMultiHash<QString , QString> m_hashTim2Job;

	QMutex m_Mutex4Job;
	QStringList m_list4Job;

	QTimer *m_Timer4Heartbeat;
	int m_ibeatTime;

	QString m_updataCondition4Day;
	QString m_updataCondition4Hour;

	UPDATA_CONDITION_STEP m_ConditionStep;
};

