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

	Logger(void);//��ֹ���캯��
	Logger(const Logger &);//��ֹ�������캯��
	Logger & operator=(const Logger &);//��ֹ��ֵ��������
	
	static QMutex s_mutexLogger;//ʵ��������

	static QAtomicPointer<Logger> s_instance;/*!<ʹ��ԭ��ָ��,Ĭ�ϳ�ʼ��Ϊ0��*/

	QString m_strLoggerFilePath;
	QString m_strLoggerPath;
};