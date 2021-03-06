#pragma once
#include "JobResolver_Global.h"

#include <QString>
#include <QHash>
#include <QMap>
#include <QMutex>
#include <QDomElement>
#include <QDir>
#include <QList>

#include "../common/Task.hpp"

class QDomNode;
class QDomElement;

class JOBRESOLVER_IMPEXP JobResolver
{
public:
	JobResolver(void);
	virtual ~JobResolver(void);

	//************************************
	// Method:    getResolveResOnTaskList
	// FullName:  JobResolver::getResolveResOnTaskList
	// Access:    public 
	// Returns:   QList<Task *>
	// Qualifier:
	// Parameter: QString strJobID
	//解析XML串，生成Task列表
	//************************************
	QList<Task *> getResolveResOnTaskList( QString strJobID );

	//************************************
	// Method:    getConditionTypeFromXML
	// FullName:  JobResolver::getConditionTypeFromXML
	// Access:    public 
	// Returns:   QString
	// Qualifier:
	// Parameter: QString
	//得到XML串的监听类型
	//************************************
	QString getConditionTypeFromXML(QString);

	bool doesJobExist( QString strJobID );
	bool doesProductExist( QString strJobID );

	//************************************
	// Method:    isJob4Type
	// FullName:  JobResolver::isJob4Type
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: QString strJobID
	// Parameter: QString strType
	//得到XML串里是否包含strType
	//************************************
	bool isJob4Type( QString strJobID, QString strType );

	//************************************
	// Method:    upDataJobXmlList
	// FullName:  JobResolver::upDataJobXmlList
	// Access:    public 
	// Returns:   QString
	// Qualifier:
	//更新XML文件
	//************************************
	QString upDataJobXmlList();

	QStringList getConditionTimeEachDay( QString strJobID );
	QStringList getConditionTimeEachHour( QString strJobID );
	QDir getConditionDirMoniter(QString strJobID);
	QList<QDir> getConditionDirMoniterAll(QString strJobID);
	qlonglong getConditionOnceMillisecond(QString strJobID);
	qlonglong getConditionCycleMillisecond(QString strJobID);

	//************************************
	// Method:    addDirMoniterAll4lList
	// FullName:  JobResolver::addDirMoniterAll4lList
	// Access:    public 
	// Returns:   QString
	// Qualifier:
	// Parameter: QString qdirNew
	//增加文件的监听列表
	//************************************
	QString addDirMoniterAll4lList(QString qdirNew);

	//************************************
	// Method:    addDirMoniterAll4lList
	// FullName:  JobResolver::addDirMoniterAll4lList
	// Access:    public 
	// Returns:   QString
	// Qualifier:
	// Parameter: QString qdirNew
	//增加文件的监听列表
	//************************************
	QString addNewJobXmlFile(QString strContent);

	//************************************
	// Method:    addDirMoniterAll4lList
	// FullName:  JobResolver::addDirMoniterAll4lList
	// Access:    public 
	// Returns:   QString
	// Qualifier:
	// Parameter: QString qdirNew
	//增加文件的监听列表
	//************************************
	QString getContentStr( QString strContent , QString strType );

protected:
	QString initJobXmlList();
	QString initProductXmlList();

	QString getFileContent(QString strFile,QString &strContent);
	QString getProductContent( QString strProduct,QDomElement &strContent );

	QList<QDir> getAllDir(QDir);
	
private:
	QString m_strJobTempDir;
	QString m_strProductTempDir;

	QMap<QString,QString> m_mapJobID2XmlFile;
	QMutex m_mutexJobID2XmlFile;

	QMap<QString,QDomElement> m_mapPdtID2DomEle;
	QMutex m_mutexPdtID2DomEle;

	QString m_SplitMarker4Timer;
	QString m_SplitMarker4Para;

	////////////////////////////////////////////////////
	QMutex m_mutex4DirMoniterAll;
	QList<QString> m_lstDirMoniterAll;
};