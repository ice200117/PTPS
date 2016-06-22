#pragma once
#include "common_global.h"

#include <QObject>
#include <QString>

class COMMON_EXPORT ConditionInterface : public QObject
{
	Q_OBJECT

public:
	~ConditionInterface(){};

	virtual QString createNewConditionJob(QString) = 0;
	virtual QString deleteExistConditionJob(QString) = 0;
	QString getConditionType(){return m_xmlEleName;};

signals:
	void signalExecJobOnCondition(QString);

public:
	void *_pJobResolver;
	QString m_xmlEleName;
};