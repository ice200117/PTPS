#include "Logger.h"

QAtomicPointer<Logger> Logger::s_instance = new Logger;
QMutex Logger::s_mutexLogger;//ÊµÀý»¥³âËø

#include <QMutexLocker>
#include <QTime>
#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

Logger::Logger(void)
{

}

Logger::~Logger( void )
{

}

QString Logger::createFirstLoggerFile( QString strLoggerPath )
{
	QString qsRes;
	if (strLoggerPath.isEmpty()) return "strLoggerPath isEmpty!";
	m_strLoggerPath = strLoggerPath;
	QString qsLoggerName = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss") + "_Header.txt";
	qsRes = createNewLoggerFile(qsLoggerName);
	if ("Successful" != qsRes)
	{
		return qsRes;
	}
	qsRes = writeInfo("PTPS started");
	if ("Successful" != qsRes)
	{
		return qsRes;
	}
	return "Successful";
}

QString Logger::createNewLoggerFile(QString qsLoggerName)
{
	QFileInfo qFI(m_strLoggerPath);
	if (!qFI.exists())
	{
		QDir makeDir;
		makeDir.mkpath(m_strLoggerPath);
	}

	m_strLoggerFilePath = m_strLoggerPath + "/" + qsLoggerName;

	QFile file(m_strLoggerFilePath);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
		return "Logger File create fail!";
	QTextStream out(&file);
	out.setCodec("UTF-8");
	out << "Logger created on " + QDateTime::currentDateTime().toString("yyyy.MM.dd_hh:mm:ss");
	out<< "\r\n";
	file.close();

	return "Successful";
}

QString Logger::getLoggerFileName(QString qsLastFileNamePath)
{
	QFileInfo qfiLastName(qsLastFileNamePath);
	QString qsLastFileBaseName = qfiLastName.fileName();
	QDateTime qdtCurDT = QDateTime::currentDateTime();
	QDateTime qdtFileDT;
	if (qsLastFileBaseName.contains("Header"))
	{
		qdtFileDT = QDateTime::fromString(qsLastFileBaseName,"yyyy'.'MM'.'dd'_'hh'.'mm'.'ss'_Header.txt'");
	}
	else
	{
		qdtFileDT = QDateTime::fromString(qsLastFileBaseName,"yyyy'.'MM'.'dd'_'hh'.'mm'.'ss'.txt'");
	}

	long long  llDiff = qdtCurDT.toTime_t() - qdtFileDT.toTime_t();
	if (abs(llDiff) > 86400)
	{
		QString qsLoggerName = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh.mm.ss") + ".txt";
		createNewLoggerFile(qsLoggerName);
		return m_strLoggerPath + "/" + qsLoggerName;
	}
	else
	{
		return qsLastFileNamePath;
	}
}

QString Logger::writeInfo( QString strInfo )
{
	QMutexLocker locker(&s_mutexLogger);
	
	QString strDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh:mm:ss");

	m_strLoggerFilePath = getLoggerFileName(m_strLoggerFilePath);

	QFile file(m_strLoggerFilePath);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Append))
	{
		return "Logger File not exist!";
	}
	QTextStream out(&file);
	out << QString("%1 : %2").arg(strDateTime).arg(strInfo);
	out<< "\r\n";
	file.close();

	return "Successful";
}