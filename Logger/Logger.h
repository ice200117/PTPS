#pragma once

#include "Logger_Global.h"

#include <QMutex>
#include <QAtomicPointer>
#include <QString>

class LOGGER_IMPEXP Logger
{
public:
	virtual ~Logger(void);

	QString createFirstLoggerFile( QString strLoggerPath );
	QString writeInfo(QString strInfo);
	static Logger &getInstance(void)
	{
		return *s_instance;
	}

private:
	QString getLoggerFileName(QString qsLastFileNamePath);
	QString createNewLoggerFile(QString qsLoggerName);

	Logger(void);//禁止构造函数
	Logger(const Logger &);//禁止拷贝构造函数
	Logger & operator=(const Logger &);//禁止赋值拷贝函数
	
	static QMutex s_mutexLogger;//实例互斥锁

	static QAtomicPointer<Logger> s_instance;/*!<使用原子指针,默认初始化为0。*/

	QString m_strLoggerFilePath;
	QString m_strLoggerPath;
};