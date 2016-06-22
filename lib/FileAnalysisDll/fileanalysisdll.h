#ifndef FILEANALYSISDLL_H
#define FILEANALYSISDLL_H

//#include "fileanalysisdll_global.h"
#include <string>
#include "decode.h"
#include "dataanalyze.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
using namespace std;
class /*FILEANALYSISDLL_EXPORT*/ FileAnalysisDll
{
public:
	FileAnalysisDll(QString);
	~FileAnalysisDll();
	bool analysis_files(QString fileName);
	bool getNewFile( QString strMoniterPath ,QStringList &strlstNewFile);

	QString m_strLogPath;
	QString m_strXmlName;

private:
	/**数据库有关操作*/
	//bool OpenDatabase();
	bool ResetDB(QString sDriver,QString sDBName,QString sHost,int iPort,QString sUser,QString sPassword);
	bool OpenDB();
	/**解析各种数据*/
	int  Data2DB4AWS(const QList<struct AWSData>& AWSDataList);//长Z
	int  Data2DB4ASS(const QList<GroundAutoStationSunlightDataRP>& ASSDataList);//日照
	void Data2DB_A0(QList<dbStorage>);//A0
	int Data2DB_A(QList<hour_data>,QList<max_huge_wind_filedata>);//A
	void Data2DB_AI(QList<observe_result>);//AI
	void Data2DB_typhoon(QList<typhoon_forecast>);//台风WX

	void write_log( QString llog );
	

	/**数据库有关项*/
	QSqlDatabase m_db;
	QString m_driver;
	QString m_dbName;
	QString m_host;
	int     m_port;
	QString m_user;
	QString m_passwd;

	

	bool m_bOD;
};

#endif // FILEANALYSISDLL_H
