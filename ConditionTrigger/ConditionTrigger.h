#pragma once

#include "ConditionTrigger_Global.h"

#include <map>
#include <string.h>

#include <QString>
#include <QMap>
#include <QTimer>
#include <QList>
#include <QObject>

class ConditionInterface;
class JobResolver;

using namespace std; 

class CONDITIONTRIGGER_IMPEXP ConditionTrigger : public QObject
{
	Q_OBJECT

public:
	ConditionTrigger(void);
	virtual ~ConditionTrigger(void);

	QString createNewConditionJob(QString);
	QString deleteExistConditionJob(QString);

	JobResolver * _pJobResolver;

	QString initConditionTrigger();

signals:
	void signalExecJob(QString);

private:
	QList<ConditionInterface *> m_listConditionObj;

};