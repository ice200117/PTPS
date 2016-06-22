#pragma once
#include "MsgReceiver_Global.h"

#include <QThread>
#include <QString>
#include <QList>
#include <QMutex>

class MSGRECEIVER_IMPEXP MsgReceiver : public QThread
{
	Q_OBJECT

public:
	MsgReceiver(void);
	virtual ~MsgReceiver(void);
	void run();

	inline QString getLastError(){return m_strLastError;};

	QString m_WorkerIP;
	QString m_WorkerPort;
	QString m_WorkerID;

	bool m_toDead;

signals:
	QString signalSendNewCommand(QString);

protected:
	QString m_strLastError;
};