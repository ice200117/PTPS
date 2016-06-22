#include "fileanalysisdll.h"
#include <QString>
#include <QFileInfo>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#ifndef DBERROR(query)
#define DBERROR(query) qDebug() << "Error:" << query.lastError().databaseText();
#endif DBERROR(query)
FileAnalysisDll::FileAnalysisDll(QString inipath)
{
	QString dbconfigini = inipath;// = QCoreApplication::applicationDirPath() + "/dbconfig.ini";
	QSettings configIni( dbconfigini, QSettings::IniFormat);  
	QString sDriver = configIni.value("/Address/dirver").toString();
	QString sDBName = configIni.value("/Address/dbname").toString();
	QString sHost = configIni.value("/Address/host").toString();
	QString iPort = configIni.value("/Address/port").toString();
	QString sUser = configIni.value("/Address/user").toString();
	QString sPassword = configIni.value("/Address/password").toString();
	m_bOD = ResetDB(sDriver,sDBName,sHost,iPort.toInt(),sUser,sPassword);
	m_strLogPath = "";
	m_strXmlName = "XmlFile.xml";

	if (!m_bOD)
	{
		write_log(QString("数据库连接失败！ %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}

}

FileAnalysisDll::~FileAnalysisDll()
{
	m_db.close();
}

bool FileAnalysisDll::ResetDB( QString sDriver,QString sDBName,QString sHost,int iPort,QString sUser,QString sPassword )
{
	m_driver=sDriver;
	m_dbName=sDBName;
	m_host=sHost;
	m_port=iPort;
	m_user=sUser;
	m_passwd=sPassword;
	if (m_db.isOpen())
	{
		m_db.close();
	}

	m_db = QSqlDatabase::addDatabase(m_driver,"SQLCon");
	return OpenDB();
}

bool FileAnalysisDll::OpenDB()
{
	m_db.setDatabaseName(m_dbName);
	m_db.setHostName(m_host);
	m_db.setPort(m_port);
	if (!m_db.open(m_user, m_passwd)) 
	{
		QSqlError err = m_db.lastError();
		m_db = QSqlDatabase();
		QSqlDatabase::removeDatabase("SQLCon");

		return false;
	}

	return true;
}

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QDir>

bool FileAnalysisDll::getNewFile( QString strMoniterPath ,QStringList &strlstNewFile)
{
	QString configPath = strMoniterPath + "/" + m_strXmlName;
	QFile file_dbconfig(configPath);
	////////////如果没有记录入库文件xml，则新建一个，并写入一条/////////////
	if (!file_dbconfig.open(QFile::ReadOnly | QFile::Text))
	{//新建现在时间的xml
		QDomDocument newDomDoc;
		QDomNode instruction = newDomDoc.createProcessingInstruction("xml","version = \"1.0\" encoding = \" UTF-8\"");  
		newDomDoc.appendChild(instruction);
		QDomElement root = newDomDoc.createElement("IntoDB");
		newDomDoc.appendChild(root);

		//QDomElement titleIcon = newDomDoc.createElement(xmlfilename);
		//QDomText titleIconTxt = newDomDoc.createTextNode(namee);
		//titleIcon.appendChild(titleIconTxt);
		//root.appendChild(titleIcon);

		QFile file(configPath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
		{
			write_log(QString("XML 创建失败！ %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
			return  false;
		}

		QTextStream out(&file);
		out.setCodec("UTF-8");
		newDomDoc.save(out,4,QDomNode::EncodingFromTextStream);
		file.close();
	}

	////////////已经有记录入库文件xml，读取xml/////////////
	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument existXmlDomDoc;
	if (!existXmlDomDoc.setContent(&file_dbconfig, false, &errorStr, &errorLine, &errorColumn))
	{
		write_log(QString("XML 解析失败！ %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		return false;
	}

	file_dbconfig.close();

	int iFileIndex=1;
	QHash<QString,int> tmpXmlConHash;
	QDomElement docElem = existXmlDomDoc.documentElement();
	QDomNode n = docElem.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement(); //将节点转换为元素
		if (!e.isNull())
		{
			//QString staNum = qPrintable(e.tagName());
			QString qstrFileName = e.text();
			tmpXmlConHash.insert(qstrFileName,iFileIndex);
			iFileIndex++;
		}
		n = n.nextSibling();
	}

	/////////////////读取当前目录文件并对比文件//////////////////////////////////
	QDir handleDir(strMoniterPath);
	if (!handleDir.exists()) return false;
	QStringList filter;
	filter<<"*.txt";
	handleDir.setNameFilters(filter);
	QFileInfoList fileInfo = handleDir.entryInfoList(filter);
	for (int iFileIndex = 0;iFileIndex < fileInfo.size();iFileIndex++)
	{
		QFileInfo qCurFI = fileInfo[iFileIndex];
		QString strCurFile = qCurFI.absoluteFilePath();

		if (!tmpXmlConHash.contains(strCurFile))
		{
			tmpXmlConHash.insert(strCurFile,tmpXmlConHash.size());
			strlstNewFile.push_back(qCurFI.absoluteFilePath());
		}
	}

	if (!strlstNewFile.isEmpty())
	{
		/////////////////////save/////////////////
		QDomDocument saveDomDoc;

		QDomNode instruction = saveDomDoc.createProcessingInstruction("xml","version = \"1.0\" encoding = \" UTF-8\"");
		saveDomDoc.appendChild(instruction);

		QDomElement root = saveDomDoc.createElement("IntoDB");
		saveDomDoc.appendChild(root);

		QHash<QString, int>::const_iterator ith = tmpXmlConHash.constBegin();
		while (ith != tmpXmlConHash.constEnd())
		{
			QDomElement tmpEle4FileName = saveDomDoc.createElement("File");
			QDomText titleIconTxt = saveDomDoc.createTextNode(ith.key());
			tmpEle4FileName.appendChild(titleIconTxt);
			root.appendChild(tmpEle4FileName);
			++ith;
		}

		//QDomElement titleIcon = tmpDomDoc.createElement(xmlfilename);
		//QDomText titleIconTxt = tmpDomDoc.createTextNode(namee);
		//titleIcon.appendChild(titleIconTxt);
		//root.appendChild(titleIcon);

		QFile file(configPath);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
		{
			write_log(QString("XML 保存失败！ %1").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
			return  false;
		}

		QTextStream out(&file);
		out.setCodec("UTF-8");
		saveDomDoc.save(out,4,QDomNode::EncodingFromTextStream);
		file.close();
	}

	return true;
}

void FileAnalysisDll::write_log( QString llog )
{
	QString strCurDate = QDate::currentDate().toString("yyyyMMdd");
	QFile file(m_strLogPath + "/Log_" + strCurDate + ".txt");
	if (!file.open(QIODevice::WriteOnly|QIODevice::Append))
	{
		return;
	}
	QTextStream out(&file);
	out << QString("%1" ).arg(llog);
	out<< "\r\n";
	file.close();
}

bool FileAnalysisDll::analysis_files( QString fileName )
{
	if (!m_bOD) return false;
	QFile file(fileName);
	QFileInfo fi(file);
	QList<struct AWSData> AWSDataList;
	QList<GroundAutoStationSunlightDataRP> ASSDataList;
	QList<dbStorage> A0DataList;
	decode d;
	DataAnalyze temp_DataAnalyze;
    int report_num = 0;
	if(fi.fileName().startsWith("Z_SURF_C_BEFZ_",Qt::CaseInsensitive) && fi.fileName().contains("0000_O_AWS_FTM")) // 长Z， 一日多站点
	{
		write_log(QString("开始解析长Z文件%1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		report_num = d.decode_file(fileName, AWSDataList);
		Data2DB4AWS(AWSDataList);
		//QFile::copy(fileName,rootPath + "/Z/" + fi.fileName());
		write_log(QString("长Z文件%1解析成功，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}
	else if(fi.fileName().contains("AWS-SS_DAY"))// 日照， 一日多站点
	{
		write_log(QString("开始解析日照文件%1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		report_num = d.decode_file(fileName, ASSDataList);
		Data2DB4ASS(ASSDataList);
		//QFile::copy(fileName,rootPath + "/AWS/" + fi.fileName());
		write_log(QString("日照文件%1解析成功，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}
	else if(fi.fileName().startsWith("A0",Qt::CaseInsensitive))// A0， 一个站点，多日
	{
		write_log(QString("开始解析A0文件%1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		temp_DataAnalyze.decode_A0(fileName);
		QList<dbStorage> db = temp_DataAnalyze.Get_A0_Data();
		Data2DB_A0(db);
		//QFile::copy(fileName,rootPath + "/A0/" + fi.fileName());
		write_log(QString("A0文件%1解析成功，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}
	else if (fi.fileName().startsWith("AI",Qt::CaseInsensitive))
	{
		write_log(QString("开始解析AI文件%1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		temp_DataAnalyze.decode_AI(fileName);
		QList<observe_result> ors = temp_DataAnalyze.Get_AI_Data();
		Data2DB_AI(ors);
		//QFile::copy(fileName,rootPath + "/AI/" + fi.fileName());
		write_log(QString("AI文件%1解析成功，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}
	else if (fi.fileName().startsWith("WX",Qt::CaseInsensitive))
	{
		write_log(QString("开始解析台风报文文件%1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		temp_DataAnalyze.decode_typhoon(fileName);
		QList<typhoon_forecast> tyf = temp_DataAnalyze.Get_typhoon();
		Data2DB_typhoon(tyf);
		//QFile::copy(fileName,rootPath + "/WX/" + fi.fileName());
		write_log(QString("台风报文文件%1解析成功，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}
	else if (fi.fileName().startsWith("A",Qt::CaseInsensitive))
	{
		write_log(QString("开始解析A文件%1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		temp_DataAnalyze.decode_A(fileName);
		QList<hour_data> hd = temp_DataAnalyze.Get_A_Data();
		QList<max_huge_wind_filedata> mh = temp_DataAnalyze.Get_A_wind_Data();
        //int r = Data2DB_A(hd,mh);
		//QFile::copy(fileName,rootPath + "/A/" + fi.fileName());
		write_log(QString("A文件%1解析成功，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
	}
	else
	{
		write_log(QString("未知文件类型 %1，在%2。").arg(fileName).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")));
		return false;
	}
	return true;
}

int FileAnalysisDll::Data2DB4AWS( const QList<struct AWSData>& AWSDataList )
{
	int cnt = 0;
	if (!m_db.isOpen() || !m_db.isValid())
	{
		return cnt;
	}
	if(AWSDataList.size() == 0)
	{
		return cnt;
	}
	QString date(AWSDataList.at(0).baseInfo.dateTime);
	if(date.size() < 10)
	{
		return cnt;
	}
	//qDebug()<< "dataTime" << AWSDataList.at(0).baseInfo.dateTime;
	//qDebug() <<" date:" << date;
	int year =date.mid(0, 4).toInt();
	int month = date.mid(4, 2).toInt();
	int day = date.mid(6,2).toInt();
	int hour = date.mid(8,2).toInt();
	//qDebug() << "year:"<<year<<" month:"<<month << "day: " << day;
	if(year<1900 || month>12 || month<1 || day>31||day<1 || hour >24 || hour<0)
	{
		return cnt;
	}

	QSqlQuery qry(m_db);
	QSqlQuery qrySel(m_db);

	QString sql;
	QString sqlSel;

	QList<int> stations;

	int const scale = 10;

	sqlSel = QString("SELECT V01000 FROM T_DMS_RD_SURF_RSUAT_ELE WHERE V04001=%1 AND V04002=%2 AND V04003=%3 AND V04004=%4").arg(year).arg(month).arg(day).arg(hour);
	if(!qrySel.exec(sqlSel))
	{
		DBERROR(qrySel);
		return cnt;
	}
	stations.clear();
	while(qrySel.next())
	{
		stations.append(qrySel.value(0).toInt());
	}

	int staid;
	m_db.transaction();
	for(int i=0; i< AWSDataList.size(); i++)
	{
		AWSData s = AWSDataList.at(i);
		staid = QString(s.baseInfo.stationID).toInt();
		if(stations.indexOf(staid) == -1) // insert
		{
			QString cols;
			QString vars;

			//测站基本信息
			//struct BaseInfo{
			//	char stationID[6];
			//	char dateTime[15]; //国际时 yyyyMMddhhmmss
			//	char latitude[7]; //度分秒
			//	char longitude[8]; //度分秒
			//	float elevation; //观测场拔海高度 m
			//	float APSElev; //气压传感器拔海高度 m
			//	char ObWay[2]; //观测方式
			//	char QCI[4]; //质量控制标识
			//	char FCI[4]; //文件更正标识
			//};

			//v05001         decimal(10,4 ) default null comment  '纬度 度', 
			//	v06001         decimal(10,4 ) default null comment  '经度 度', 
			//	v07001         decimal(10,4 ) default null comment  '测站海拔高度 m', 
			//	v07002         decimal(10,4 ) default null comment  '气压传感器海拔高度 m', 
			//	v02001         decimal(10,4 ) default null comment  '观测方式', 
			//	v04005         decimal(10,4 ) default null comment  '资料观测分', 
			//	v04006         decimal(10,4 ) default null comment  '资料观测秒' ,

			cols += QString("V01000, V04001, v04002, v04003, V04004");
			vars += QString("%1, %2, %3, %4, %5").arg(staid).arg(year).arg(month).arg(day).arg(hour);
			////气压数据
			//struct PP{
			//	float locAP; //当前时刻的本站气压 hPa
			//	float SSAP; //当期时刻的海平面气压
			//	float threeHourDiffAP; //3小时变压
			//	float twentyFourHourDiffAP; //24小时变压
			//	float maxAP; //每1小时内的最高本站气压值
			//	char  maxAPTime[5];
			//	float minAP; //每1小时内的最低本站气压值
			//	char  minAPTime[5];
			//};
			///*			v10004         decimal(10,4 ) default null comment '本站气压 hpa' , 
			//			v10005         decimal(10,4 ) default null comment  '海平面气压 hpa', 
			//			v10060_003     decimal(10,4 ) default null comment  '3小时变压 hpa', 
			//			v10060_024     decimal(10,4 ) default null comment  '24小时变压 hpa', 
			//			v10201         decimal(10,4 ) default null comment  '1小时内最高本站气压 hpa', 
			//			v10201_752     decimal(10,4 ) default null comment  '最高本站气压出现时间 时分', 
			//			v10202         decimal(10,4 ) default null comment  '1小时内最低本站气压 hpa', 
			//			v10202_752     decimal(10,4 ) default null comment  '最低本站气压出现时间 时分', */

			cols += QString(", v10004, v10005, v10060_003, v10060_024, v10201, v10201_752, v10202, v10202_752");
			vars += QString(", %1, %2, %3, %4, %5, %6, %7, %8").arg(s.pp.locAP*scale).arg(s.pp.SSAP*scale).arg(s.pp.threeHourDiffAP*scale).arg(s.pp.twentyFourHourDiffAP*scale).arg(s.pp.maxAP*scale).arg(QString(s.pp.maxAPTime).toInt()).arg(s.pp.minAP*scale).arg(QString(s.pp.minAPTime).toInt());


			////温度和湿度数据
			//struct TH{
			//	float AT; //当期时刻的空气温度 ℃
			//	float maxAT; //每1小时内的最高气温
			//	char  maxATTime[5]; //每1小时内最高气温出现时间
			//	float minAT; //每1小时内的最低气温
			//	char  minATTime[5]; //每1小时内最低气温出现时间
			//	float TwentyFourDiffAT; //24小时变温
			//	float TFMaxAT; //过去24小时最高气温
			//	float TFMinAT; //过去24小时最低气温
			//	float dewT; //露点温度
			//	int   HU;   //相对湿度
			//	int   minHU; //每1小时内的最小相对湿度
			//	char  minHUTime[5]; //每1小时内最小相对湿度出现时间
			//	float vaporPressure; //水汽压 hPa
			//};
			//v12001          AT  decimal(10,4 ) default null comment  '气温 ℃', 
			//	v12211       maxAT  decimal(10,4 ) default null comment  '1小时内最高气温 ℃', 
			//	v12211_752   maxATTime   decimal(10,4 ) default null comment  '小时内最高气温出现时间 时分', 
			//	v12212       minAT   decimal(10,4 ) default null comment  '1小时内最低气温 ℃', 
			//	v12212_752   minATTime   decimal(10,4 ) default null comment  '小时内最低气温出现时间 时分', 
			//	v12220_024   TwentyFourDiffAT   decimal(10,4 ) default null comment  '24小时变温 ℃', 
			//	v12016        TFMaxAT  decimal(10,4 ) default null comment  '过去24小时最高气温 ℃', 
			//	v12017        TFMinAT  decimal(10,4 ) default null comment  '过去24小时最低气温 ℃', 
			//	v12003       dewT  decimal(10,4 ) default null comment  '露点温度 ℃', 
			//	v13003       HU  decimal(10,4 ) default null comment  '相对湿度 %', 
			//	v13007       minHU  decimal(10,4 ) default null comment  '最小相对湿度 %', 
			//	v13007_752  minHUTime   decimal(10,4 ) default null comment  '最小相对湿度出现时间 时分', 
			//	v13004      vaporPressure    decimal(10,4 ) default null comment  '水汽压 hpa', 
			cols += QString(", v12001, v12211, v12211_752, v12212, v12212_752, v12220_024, v12016, v12017");
			vars += QString(", %1, %2, %3, %4, %5, %6,%7, %8").arg(s.th.AT*scale).arg(s.th.TFMaxAT*scale).arg(QString(s.th.maxATTime).toInt()).arg(s.th.TFMinAT*scale).arg(QString(s.th.minATTime).toInt()).arg(s.th.TwentyFourDiffAT*scale).arg(s.th.TFMaxAT*scale).arg(s.th.TFMinAT*scale);
			cols += QString(",v12003, v13003, v13007, v13007_752, v13004");
			vars += QString(", %1, %2, %3, %4, %5").arg(s.th.dewT*scale).arg(s.th.HU*scale).arg(s.th.minHU*scale).arg(QString(s.th.minHUTime).toInt()).arg(s.th.vaporPressure*scale);


			////累计降水和蒸发量数据 mm,微量保文中为“，”。微量存数值为888888
			//struct RE{
			//	float oneHourRain; //每1小时内的降水量累积量 mm
			//	float threeHourRain; //过去3小时降水量
			//	float sixHourRain; //过去6小时降水量
			//	float twelveHourRain; //过去12小时降水量
			//	float twentyFourHourRain; //过去24小时降水量
			//	char RJMT[3]; //人工加密观测降水量描述时间周期
			//	float RJMRain; //人工加密观测降水量
			//	float oneHourEvaporation; //小时蒸发量 mm
			//};
			//v13019        oneHourRain  decimal(10,4 ) default null comment  '小时降水量 mm', 
			//	v13024       threeHourRain   decimal(10,4 ) default null comment  '过去3小时降水量 mm', 
			//	v13021       sixHourRain   decimal(10,4 ) default null comment  '过去6小时降水量 mm', 
			//	v13022       twelveHourRain   decimal(10,4 ) default null comment  '过去12小时降水量 mm', 
			//	v13023       twentyFourHourRain  decimal(10,4 ) default null comment  '过去24小时降水量 mm', 
			//	v13025_752   RJMT  decimal(10,4 ) default null comment '人工加密观测降水量描述时间周期（降雪）' , 
			//	v13025       RJMRain  decimal(10,4 ) default null comment  '人工加密观测降水量（降雪） mm', 
			//	v13031       oneHourEvaporation  decimal(10,4 ) default null comment  '1小时内蒸发量 mm', 

			cols += QString(", v13019, v13024, v13021, v13022, v13023, v13025_752, v13025, v13031");
			vars += QString(", %1, %2, %3, %4, %5, %6,%7, %8").arg(s.re.oneHourRain*scale).arg(s.re.threeHourRain*scale).arg(s.re.sixHourRain*scale).arg(s.re.twelveHourRain*scale).arg(s.re.twentyFourHourRain*scale).arg(QString(s.re.RJMT).toInt()).arg(s.re.RJMRain*scale).arg(s.re.oneHourEvaporation*scale);


			//struct WI{ //风观测数据
			//	int   twoMiniteWD; //当前时刻的2分钟平均风向 1°
			//	float twoMiniteWS; //2分钟平均风速 m/s
			//	int   tenMiniteWD;
			//	float tenMiniteWS;
			//	int   maxWD;
			//	float maxWS;
			//	char  maxWST[5]; //每1小时内10分钟最大风速出现时间，时分各两位
			//	int   instantaneousWD; //当前时刻的瞬时风向
			//	float instantaneousWS;
			//	int extremeWD; //每一小时内极大瞬时风速对应的风向
			//	float extremeWS; //每一小时内极大瞬时风速
			//	char extremeWST[5]; //每一小时内极大瞬时风速出现时间
			//	float sixHourExtremeWS; //过去6小时内极大瞬时风速
			//	int sixHourExtremeWD; //过去6小时内极大瞬时风速对应的风向
			//	float twelveHourExtremeWS; //过去12小时内极大瞬时风速
			//	int twelveHourExtremeWD; //过去12小时内极大瞬时风速对应的风向
			//};
			//v11001_002     twoMiniteWD decimal(10,4 ) default null comment  '2分钟风向 度', 
			//	v11002_002   twoMiniteWS   decimal(10,4 ) default null comment  '2分钟平均风速 m/s', 
			//	v11202_010    tenMiniteWD  decimal(10,4 ) default null comment  '10分钟风向 度', 
			//	v11042_010   tenMiniteWS   decimal(10,4 ) default null comment  '10分钟平均风速 m/s', 
			//	v11202       maxWD   decimal(10,4 ) default null comment  '1小时内10分钟最大风速的风向 度', 
			//	v11042       maxWS   decimal(10,4 ) default null comment  '1小时内10分钟最大风速 m/s', 
			//	v11042_752   maxWST   decimal(10,4 ) default null comment  '最大风速出现时间 时分', 
			//	v11001       instantaneousWD   decimal(10,4 ) default null comment  '瞬时风向 度', 
			//	v11002       instantaneousWS   decimal(10,4 ) default null comment  '瞬时风速 m/s', 
			//	v11043       extremeWD  decimal(10,4 ) default null comment  '1小时内的极大风速的风向 度', 
			//	v11041       extremeWS  decimal(10,4 ) default null comment  '1小时内的极大风速 m/s', 
			//	v11041_752   extremeWST  decimal(10,4 ) default null comment  '极大风速出现时间 时分', 
			//	v11044_006    sixHourExtremeWS  decimal(10,4 ) default null comment  '过去6小时极大瞬时风速 m/s', 
			//	v11045_006    sixHourExtremeWD  decimal(10,4 ) default null comment  '过去6小时极大瞬时风向 度', 
			//	v11044_012    twelveHourExtremeWS decimal(10,4 ) default null comment  '过去12小时极大瞬间风速 m/s', 
			//	v11045_012    twelveHourExtremeWD  decimal(10,4 ) default null comment  '过去12小时极大瞬间风向 度', 

			cols += QString(", v11001_002, v11002_002, v11202_010, v11042_010, v11202, v11042_752, v11001, v11002");
			cols += QString(",v11043, v11041, v11041_752, v11044_006, v11045_006, v11044_012, v11045_012");
			vars += QString(", %1, %2, %3, %4, %5, %6,%7, %8").arg(s.wi.tenMiniteWS*scale).arg(s.wi.maxWD*scale).arg(s.wi.maxWS*scale).arg(QString(s.wi.maxWST).toInt()).arg(s.wi.instantaneousWD*scale).arg(s.wi.instantaneousWS*scale).arg(s.wi.extremeWD*scale).arg(s.wi.extremeWS*scale);
			vars += QString(", %1, %2, %3, %4, %5, %6, %7").arg(s.wi.extremeWD*scale).arg(s.wi.extremeWS*scale).arg(QString(s.wi.extremeWST).toInt()).arg(s.wi.sixHourExtremeWS*scale).arg(s.wi.sixHourExtremeWD*scale).arg(s.wi.twelveHourExtremeWS*scale).arg(s.wi.twelveHourExtremeWD*scale);
			//struct DT{ //地温数据
			//	float DST; //当前时刻的地面温度 ℃
			//	float maxDST; //每1小时内的地面最高温度
			//	char  maxDSTTime[5];
			//	float minDST; //每1小时内的地面最低温度
			//	char  minDSTTime[5];
			//	float twelveminDST;
			//	float fivecmDST; //5厘米地温
			//	float tencmDST;
			//	float fifteencmDST;
			//	float twentycmDST;
			//	float fortycmDST;
			//	float eightycmDST;
			//	float oneHundredSixtycmDST;
			//	float threeHundredtwentycmDST;
			//	float grassLandT; //当前时刻草面温度
			//	float maxGrassLandT; //每1小时内草面最高温度
			//	char maxGrassLandTTime[5]; //每1小时内草面最高温度出现时间
			//	float minGrassLandT; //每1小时内草面最高温度
			//	char minGrassLandTTime[5]; //每1小时内草面最高温度出现时间
			//};
			///*v12061_001     decimal(10,4 ) default null comment  '地面温度 ℃', 
			//	v12213_001     decimal(10,4 ) default null comment  '1小时内地面最高温度 ℃', 
			//	v12213_001_752 decimal(10,4 ) default null comment  '地面最高出现时间 时分', 
			//	v12214_001     decimal(10,4 ) default null comment  '1小时内地面最低温度 ℃', 
			//	v12214_001_752 decimal(10,4 ) default null comment  '地面最低温度出现时间 时分', 
			//	v12013         decimal(10,4 ) default null comment  '过去12小时最低地面温度 ℃', 
			//	v12030_005     decimal(10,4 ) default null comment  '5厘米地温 ℃', 
			//	v12030_010     decimal(10,4 ) default null comment  '10厘米地温 ℃', 
			//	v12030_015     decimal(10,4 ) default null comment  '15厘米地温 ℃', 
			//	v12030_020     decimal(10,4 ) default null comment  '20厘米地温 ℃', 
			//	v12030_040     decimal(10,4 ) default null comment  '40厘米地温 ℃', 
			//	v12030_080     decimal(10,4 ) default null comment  '80厘米地温 ℃', 
			//	v12030_160     decimal(10,4 ) default null comment  '160厘米地温 ℃', 
			//	v12030_320     decimal(10,4 ) default null comment  '320厘米地温 ℃', 
			//	v12061_002     decimal(10,4 ) default null comment  '草面（雪面）温度 ℃', 
			//	v12213_002     decimal(10,4 ) default null comment  '草面（雪面）最高温度 ℃', 
			//	v12213_002_752 decimal(10,4 ) default null comment  '草面（雪面）最高温度出现时间 时分', 
			//	v12214_002     decimal(10,4 ) default null comment  '草面（雪面）最低温度 ℃', 
			//	v12214_002_752 decimal(10,4 ) default null comment  '草面（雪面）最低温度出现时间 时分', */
			cols += QString(", v12061_001, v12213_001, v12213_001_752, v12214_001, v12214_001_752, v12013, v12030_005, v12030_010");
			vars += QString(", %1, %2, %3, %4, %5, %6,%7, %8").arg(s.dt.DST*scale).arg(s.dt.maxDST*scale).arg(QString(s.dt.maxDSTTime).toInt()).arg(s.dt.minDST*scale).arg(QString(s.dt.minDSTTime).toInt()).arg(s.dt.twelveminDST*scale).arg(s.dt.fivecmDST*scale).arg(s.dt.tencmDST*scale);
			cols += QString(", v12030_015, v12030_020, v12030_040, v12030_080, v12030_160, v12030_320, v12061_002, v12213_002");
			vars += QString(", %1, %2, %3, %4, %5, %6,%7, %8").arg(s.dt.fifteencmDST*scale).arg(s.dt.twentycmDST*scale).arg(s.dt.fortycmDST*scale).arg(s.dt.eightycmDST*scale).arg(s.dt.oneHundredSixtycmDST*scale).arg(s.dt.threeHundredtwentycmDST*scale).arg(s.dt.grassLandT*scale).arg(s.dt.maxGrassLandT*scale);
			cols += QString(", v12213_002_752, v12214_002, v12214_002_752");
			vars += QString(", %1, %2, %3").arg(QString(s.dt.maxGrassLandTTime).toInt()).arg(s.dt.minGrassLandT*scale).arg(QString(s.dt.minGrassLandTTime).toInt());
			//struct VV{ //自动观测能见度数据 m
			//	float oneMiniteHV; //当前时刻的1分钟平均水平能见度
			//	float tenMiniteHV;
			//	float minHV; //每1小时内的最小能见度
			//	char  minHVTime[5];
			//};
			//v20001_052_001 decimal(10,4 ) default null comment  '1分钟平均水平能见度 m', 
			//	v20001_052_010 decimal(10,4 ) default null comment  '10分钟平均水平能见度 m', 
			//	v20001_006     decimal(10,4 ) default null comment  '1小时内最小能见度 m', 
			//	v20001_006_752 decimal(10,4 ) default null comment  '最小能见度出现时间 时分', 
			cols += QString(",v20001_052_001, v20001_052_010, v20001_006, v20001_006_752");
			vars += QString(", %1, %2, %3, %4").arg(s.vv.oneMiniteHV).arg(s.vv.tenMiniteHV*scale).arg(s.vv.minHV*scale).arg(QString(s.vv.minHVTime).toInt());
			//struct CW{ //人工观测能见度、云、天数据
			//	float RHV; //正点能见度，由人工输入 km
			//	char  TCloudage[4]; //总云量
			//	char  LCloudage[4]; //低云量
			//	char  reportCloudage[4]; //编报云量
			//	int   cloudHeight; //云高 m,正点的低（中）云状云高，由人工输入，为编报iRiXhVV中的h；当无Nh的云时，若无云高值，均写入2500
			//	char  cloudForm[25]; //云状
			//	char  choudCode[4]; //云状编码（云码）
			//	char  currentWeather[3]; //现在天气现象编码
			//	char  pastWeatherT[3]; //过去天气描述时间周期,对于天气报为06，补充天气报为03，加密天气报的00时为12，其他天气（加密）报时次为06，非发天气(加密)报时次，固定编“//”
			//	char  pastW1[2]; //过去天气1
			//	char  pastW2[2];
			//	char  stateOfGround[3];
			//};
			//v20001         decimal(10,4 ) default null comment  '正点观测能见度 m', 
			//	v20010         decimal(10,4 ) default null comment  '正点观测总云量 成', 
			//	v20051         decimal(10,4 ) default null comment  '正点观测低云量 成', 
			//	v20011         decimal(10,4 ) default null comment  '正点编报云量（中低云量） 成', 
			//	v20013         decimal(10,4 ) default null comment  '正点观测云高 m', 
			//	v20012_001     decimal(10,4 ) default null comment  '云状1 编码', 
			//	v20012_002     decimal(10,4 ) default null comment  '云状2 编码', 
			//	v20012_003     decimal(10,4 ) default null comment  '云状3 编码', 
			//	v20012_004     decimal(10,4 ) default null comment  '云状4 编码', 
			//	v20012_005     decimal(10,4 ) default null comment  '云状5 编码', 
			//	v20012_006     decimal(10,4 ) default null comment  '云状6 编码', 
			//	v20012_007     decimal(10,4 ) default null comment  '云状7 编码', 
			//	v20012_008     decimal(10,4 ) default null comment  '云状8 编码', 
			//	v20012_011     decimal(10,4 ) default null comment  '正点观测编报低云状 编码', 
			//	v20012_012     decimal(10,4 ) default null comment  '正点观测编报中云状 编码', 
			//	v20012_013     decimal(10,4 ) default null comment  '正点观测编报高云状 编码', 
			//	v20003         decimal(10,4 ) default null comment  '现在天气现象', 
			//	v20003_999     decimal(10,4 ) default null comment  '过去天气描述时间周期 对于天气报为06，补充天气报为03，加密天气报的00时为12，其他为06', 
			//	v20004         decimal(10,4 ) default null comment  '正点观测过去天气现象1 按《GD-01Ⅲ》规定形成的过去天气编码（W1）', 
			//	v20005         decimal(10,4 ) default null comment  '正点观测过去天气现象2 按《GD-01Ⅲ》规定形成的过去天气编码（W2）', 
			//	v20062         decimal(10,4 ) default null comment  '地面状态 编码', 
			/*cols += QString(",v20001, v20010, v20051, v20011, v20013, ");*/

			//struct SP{ //其他重要天气数据
			//	float  snowDepth; //积雪深度 cm,微量保文中为“，”。微量存数值为888888
			//	float  snowPressure; //雪压 g/(cm*cm)
			//	int  frozenSoilDepth1Upper; //冻土深度第1栏上限值 cm
			//	int  frozenSoilDepth1Lower; //冻土深度第1栏下限值 cm
			//	int  frozenSoilDepth2Upper; //冻土深度第2栏上限值 cm
			//	int  frozenSoilDepth2Lower; //冻土深度第2栏下限值 cm
			//	char  TornadoDisCode[2]; //龙卷、尘卷风距测站距离编码
			//	char  TornadoDirCode[2]; //龙卷、尘卷风距测站方位编码
			//	int  glazeDiameter; //电线积冰（雨凇）直径
			//	int  maxHailDia; //最大冰雹直径
			//};
			//v13233         decimal(10,4 ) default null comment  '积雪深度 cm', 
			//	v13231         decimal(10,4 ) default null comment  '雪压', 
			//	v20270_010     decimal(10,4 ) default null comment  '冻土深度第1栏上限值', 
			//	v20270_011     decimal(10,4 ) default null comment  '冻土深度第1栏下限值', 
			//	v20270_020     decimal(10,4 ) default null comment  '冻土深度第2栏上限值', 
			//	v20270_021     decimal(10,4 ) default null comment  '冻土深度第2栏下限值', 
			//	v20212         decimal(10,4 ) default null comment  '龙卷、尘卷风距测站距离编码', 
			//	v20213         decimal(10,4 ) default null comment  '龙卷、尘卷风距测站方位编码', 
			//	v20218         decimal(10,4 ) default null comment  '电线积冰（雨凇）直径', 
			//	v20402         decimal(10,4 ) default null comment  '最大冰雹直径', 
			cols += QString(",v13233, v13231, v20270_010, v20270_011, v20270_020, v20270_021, v20212, v20213");
			vars += QString(", %1, %2, %3, %4, %5, %6,%7, %8").arg(s.sp.snowDepth*scale).arg(s.sp.snowPressure*scale).arg(s.sp.frozenSoilDepth1Upper*scale).arg(s.sp.frozenSoilDepth1Lower*scale).arg(s.sp.frozenSoilDepth2Upper*scale).arg(s.sp.frozenSoilDepth2Lower*scale).arg(QString(s.sp.TornadoDisCode).toInt()).arg(QString(s.sp.TornadoDirCode).toInt());
			vars += QString(", %1, %2").arg(s.sp.glazeDiameter*scale).arg(s.sp.maxHailDia*scale);
			cols += QString(",v20218, v20402");


			sql = QString("INSERT INTO T_DMS_RD_SURF_RSUAT_ELE(%1) values(%2)").arg(cols).arg(vars);
		}
		else
		{
			QString cols;
			QString where;
			cols += QString("v10004=%1, v10005=%2, v10060_003=%4, v10060_024=%4, v10201=%5, v10201_752=%6, v10202=%7, v10202_752=%8")
				.arg(s.pp.locAP*scale).arg(s.pp.SSAP*scale).arg(s.pp.threeHourDiffAP*scale).arg(s.pp.twentyFourHourDiffAP*scale)
				.arg(s.pp.maxAP*scale).arg(QString(s.pp.maxAPTime).toInt()).arg(s.pp.minAP*scale).arg(QString(s.pp.minAPTime).toInt());

			cols += QString(",v12001=%1, v12211=%2, v12211_752=%3, v12212=%4, v12212_752=%5, v12220_024=%6, v12016=%7, v12017=%8")
				.arg(s.th.AT*scale).arg(s.th.TFMaxAT*scale).arg(QString(s.th.maxATTime).toInt()).arg(s.th.TFMinAT*scale)
				.arg(QString(s.th.minATTime).toInt()).arg(s.th.TwentyFourDiffAT*scale).arg(s.th.TFMaxAT*scale).arg(s.th.TFMinAT*scale);
			cols += QString(",v12003=%1, v13003=%2, v13007=%3, v13007_752=%4, v13004=%5")
				.arg(s.th.dewT*scale).arg(s.th.HU*scale).arg(s.th.minHU*scale).arg(QString(s.th.minHUTime).toInt())
				.arg(s.th.vaporPressure*scale);

			cols += QString(",v13019=%1, v13024=%2, v13021=%3, v13022=%4, v13023=%5, v13025_752=%6, v13025=%7, v13031=%8")
				.arg(s.re.oneHourRain*scale).arg(s.re.threeHourRain*scale).arg(s.re.sixHourRain*scale).arg(s.re.twelveHourRain*scale)
				.arg(s.re.twentyFourHourRain*scale).arg(QString(s.re.RJMT).toInt()).arg(s.re.RJMRain*scale).arg(s.re.oneHourEvaporation*scale);


			cols += QString(", v11001_002=%1, v11002_002=%2, v11202_010=%3, v11042_010=%4, v11202=%5, v11042_752=%6, v11001=%7, v11002=%8")
				.arg(s.wi.tenMiniteWS*scale).arg(s.wi.maxWD*scale).arg(s.wi.maxWS*scale).arg(QString(s.wi.maxWST).toInt())
				.arg(s.wi.instantaneousWD*scale).arg(s.wi.instantaneousWS*scale).arg(s.wi.extremeWD*scale).arg(s.wi.extremeWS*scale);			
			cols += QString(", v11043=%1, v11041=%2, v11041_752=%3, v11044_006=%4, v11045_006=%5, v11044_012=%6, v11045_012=%7")
				.arg(s.wi.extremeWD*scale).arg(s.wi.extremeWS*scale).arg(QString(s.wi.extremeWST).toInt()).arg(s.wi.sixHourExtremeWS*scale)
				.arg(s.wi.sixHourExtremeWD*scale).arg(s.wi.twelveHourExtremeWS*scale).arg(s.wi.twelveHourExtremeWD*scale);

			cols += QString(", v12061_001=%1, v12213_001=%2, v12213_001_752=%3, v12214_001=%4, v12214_001_752=%5, v12013=%6, v12030_005=%7, v12030_010=%8")
				.arg(s.dt.DST*scale).arg(s.dt.maxDST*scale).arg(QString(s.dt.maxDSTTime).toInt()).arg(s.dt.minDST*scale)
				.arg(QString(s.dt.minDSTTime).toInt()).arg(s.dt.twelveminDST*scale).arg(s.dt.fivecmDST*scale).arg(s.dt.tencmDST*scale);
			cols += QString(", v12030_015=%1, v12030_020=%2, v12030_040=%3, v12030_080=%4, v12030_160=%5, v12030_320=%6, v12061_002=%7, v12213_002=%8")
				.arg(s.dt.fifteencmDST*scale).arg(s.dt.twentycmDST*scale).arg(s.dt.fortycmDST*scale).arg(s.dt.eightycmDST*scale)
				.arg(s.dt.oneHundredSixtycmDST*scale).arg(s.dt.threeHundredtwentycmDST*scale).arg(s.dt.grassLandT*scale).arg(s.dt.maxGrassLandT*scale);
			cols += QString(", v12213_002_752=%1, v12214_002=%2, v12214_002_752=%3")
				.arg(QString(s.dt.maxGrassLandTTime).toInt()).arg(s.dt.minGrassLandT*scale).arg(QString(s.dt.minGrassLandTTime).toInt());

			cols += QString(",v20001_052_001=%1, v20001_052_010=%2, v20001_006=%3, v20001_006_752=%4")
				.arg(s.vv.oneMiniteHV).arg(s.vv.tenMiniteHV*scale).arg(s.vv.minHV*scale).arg(QString(s.vv.minHVTime).toInt());

			cols += QString(",v13233=%1, v13231=%2, v20270_010=%3, v20270_011=%4, v20270_020=%5, v20270_021=%6, v20212=%7, v20213=%8")
				.arg(s.sp.snowDepth*scale).arg(s.sp.snowPressure*scale).arg(s.sp.frozenSoilDepth1Upper*scale).arg(s.sp.frozenSoilDepth1Lower*scale)
				.arg(s.sp.frozenSoilDepth2Upper*scale).arg(s.sp.frozenSoilDepth2Lower*scale).arg(QString(s.sp.TornadoDisCode).toInt()).arg(QString(s.sp.TornadoDirCode).toInt());
			cols += QString(", v20218=%1, v20402=%2").arg(s.sp.glazeDiameter*scale).arg(s.sp.maxHailDia*scale);

			where += QString("V01000=%1 AND  V04001=%2 AND v04002=%3 AND v04003=%4 AND V04004=%5 ")
				.arg(staid).arg(year).arg(month).arg(day).arg(hour);
			sql = QString("update T_DMS_RD_SURF_RSUAT_ELE set %1  where %2").arg(cols).arg(where);
		}

		if(qry.exec(sql))
		{
			++cnt;
		}
		else
		{
			qDebug() << "Error:" << qry.lastError().text();
			qDebug() << "sql:" <<sql;
		}
		//staId4Insert;
	}
	m_db.commit();

	// 计算66站平均温度和降水  99966
	//ComputeAverageRain4Hour(year, month, day,hour, 66);
	// 计算36站平均温度和降水  99936
	//ComputeAverageRain4Hour(year, month, day,hour, 36);
	m_db.commit();
	//////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////
	return cnt;
}

int FileAnalysisDll::Data2DB4ASS( const QList<GroundAutoStationSunlightDataRP>& ASSDataList )
{
	int cnt = 0;

	if (!m_db.isOpen() || !m_db.isValid())
	{
		return cnt;
	}

	if(ASSDataList.size() == 0)
	{
		return cnt;
	}

	GroundAutoStationSunlightDataRP s = ASSDataList.at(0);
	if(!s.acWriteReportCenter)
		return cnt;

	int year =s.acWriteYear;
	int month =s.acWriteMonth;
	int day = s.acWriteDay;

	if(year<1900 || month>12 || month<1 || day>31||day<1)
	{
		return cnt;
	}

	QSqlQuery qry(m_db);
	QSqlQuery qrySel(m_db);

	QString sql;
	QString sqlSel;

	QList<int> stations;

	sqlSel = QString("SELECT V01000 FROM t_dms_cd_surf_muday_ele_cn WHERE V04001=%1 AND V04002=%2 AND V04003=%3").arg(year).arg(month).arg(day);
	if(!qrySel.exec(sqlSel))
	{
		DBERROR(qrySel);
		return cnt;
	}
	stations.clear();
	while(qrySel.next())
	{
		stations.append(qrySel.value(0).toInt());
	}

	int staid;
	m_db.transaction();
	for(int i=0; i< ASSDataList.size(); i++)
	{
		GroundAutoStationSunlightDataRP s = ASSDataList.at(i);
		staid = QString(s.acStationNo).toInt();
		if(stations.indexOf(staid) == -1) // insert
		{
			QString cols;
			QString vars;
			cols += QString("V01000, V04001, v04002, v04003");
			cols += QString(", v14032");

			vars += QString("%1, %2, %3, %4 ").arg(staid).arg(year).arg(month).arg(day);
			vars += QString(", %1").arg(s.dSunlightTotal*10);


			sql = QString("INSERT INTO t_dms_cd_surf_muday_ele_cn(%1) values(%2)").arg(cols).arg(vars);
		}
		else
		{
			QString cols;
			QString where;
			cols += QString(" v14032=%1").arg(s.dSunlightTotal*10);
			where += QString("V01000=%1 AND  V04001=%2 AND v04002=%3 AND v04003=%4").arg(staid).arg(year).arg(month).arg(day);
			sql = QString("update t_dms_cd_surf_muday_ele_cn set %1  where %2").arg(cols).arg(where);
		}

		if(qry.exec(sql))
		{
			++cnt;
		}
		else
		{

		}
		//staId4Insert;
	}
	m_db.commit();

	// 计算36站平均日照  99936
	//ComputeAverageSun4Station(year, month, day, 36);
	// 计算66站平均日照  99966
	//ComputeAverageSun4Station(year, month, day, 66);
	m_db.commit();


	return cnt;
}

void FileAnalysisDll::Data2DB_A0( QList<dbStorage> t)
{
	if (!m_db.isOpen() || !m_db.isValid())
	{
		return ;
	}

	QList<dbStorage> tempdbstorage = t;
	if(tempdbstorage.size() == 0)
	{
		return ;
	}
	int year = tempdbstorage.at(0).dbStorage_baseInfo.year.toInt();
	int month = tempdbstorage.at(0).dbStorage_baseInfo.month.toInt();
	int day=1;
	if(year<1900 || month>12 || month<1 || day>31||day<1)
	{
		return ;
	}


	QSqlQuery qry(m_db);
	QSqlQuery qrySel(m_db);

	QString sql;
	QString sqlSel;

	QList<int> days;
	int staid = tempdbstorage.at(0).dbStorage_baseInfo.stationID.toInt();
	sqlSel = QString("SELECT  V04003 FROM t_dms_cd_surf_muday_ele_cn WHERE V01000=%1 AND V04001=%2 AND V04002=%3").arg(staid).arg(year).arg(month);
	if(!qrySel.exec(sqlSel))
	{
		DBERROR(qrySel);
		return ;
	}
	days.clear();
	while(qrySel.next())
	{
		days.append(qrySel.value(0).toInt());
	}

	m_db.transaction();
	for(int i=0; i< tempdbstorage.size(); i++)
	{
		struct dbStorage s = tempdbstorage.at(i);
		day = s.dbStorage_dataTime.date().day();
		if(days.indexOf(day) == -1) // insert
		{
			QString cols;
			QString vars;
			cols += QString("V01000, V04001, v04002, v04003");

			cols += QString(", v12001, v12052, v12052_001, v12053, v12053_001,v12002,v12003");
			cols += QString(", v13203, v13204, v13201");
			cols += QString(", v14032, v04211, v04212");
			cols += QString(", v13003, v13007, v13007_001");
			cols += QString(", v13004");
			cols += QString(", v20010, v20051");
			cols += QString(", v20001");
			cols += QString(", v11002, v11042, v11212, v11041, v11043");
			cols += QString(", v13205, v12001_808, v12016, v12017");
			cols += QString(", TS_YMD");

			vars += QString("%1, %2, %3, %4 ").arg(staid).arg(year).arg(month).arg(day);
			vars += QString(", %1, %2, %3, %4, %5,%6,%7").arg(s.dbStorage_temperature_fileData.daily_average)
				.arg(s.dbStorage_temperature_fileData.daily_maximum)
				.arg(s.dbStorage_temperature_fileData.daily_maximum_time)
				.arg(s.dbStorage_temperature_fileData.daily_minimum)
				.arg(s.dbStorage_temperature_fileData.daily_minimum_time)
				.arg(s.dbStorage_temperature_fileData.daily_wet_temperature)
				.arg(s.dbStorage_temperature_fileData.daily_bulb_temperature);
			vars += QString(", %1, %2, %3").arg(s.dbStorage_rain_fileData.daily_20to8_Precipitation)
				.arg(s.dbStorage_rain_fileData.daily_8to20_Precipitation)
				.arg(s.dbStorage_rain_fileData.daily_20to20_Precipitation);
			vars += QString(", %1, %2, %3").arg(s.dbStorage_sunshine_fileData.daily_sunshine_count)
				.arg(s.dbStorage_sunshine_fileData.daily_sun_rise)
				.arg(s.dbStorage_sunshine_fileData.daily_sun_set);
			vars += QString(", %1, %2, %3").arg(s.dbStorage_relativhumidity_fileData.relativhumidity)
				.arg(s.dbStorage_relativhumidity_fileData.relativhumidity_minnum)
				.arg(s.dbStorage_relativhumidity_fileData.relativhumidity_minnum_time);
			vars += QString(", %1").arg(s.dbStorage_vaporPressure_fileData.vaporPressure);
			vars += QString(", %1, %2").arg(s.dbStorage_cloudy_fileData.totalcloudy)
				.arg(s.dbStorage_cloudy_fileData.lowcloudy);
			vars += QString(", %1").arg(s.dbStorage_visibility_fileData.visibility);
			vars += QString(", %1, %2, %3, %4, %5").arg(s.dbStorage_wind_fileData.average_wind)
				.arg(s.dbStorage_wind_fileData.wind_max)
				.arg(s.dbStorage_wind_fileData.wind_max_direct)
				.arg(s.dbStorage_wind_fileData.wind_extreme)
				.arg(s.dbStorage_wind_fileData.wind_extreme_direct);
			vars += QString(", %1, %2, %3, %4").arg(s.dbStorage_nothing_fileData.daily_8to8_rain)
				.arg(s.dbStorage_nothing_fileData.daily_8to8_temperature)
				.arg(s.dbStorage_nothing_fileData.daily_8to8_maximum_temp)
				.arg(s.dbStorage_nothing_fileData.daily_8to8_minmimu_temp);
			vars += QString(", str_to_date('%1','%Y%m%d') ").arg(year*10000+month*100+day);

			sql = QString("INSERT INTO t_dms_cd_surf_muday_ele_cn(%1) values(%2)").arg(cols).arg(vars);
		}
		else
		{
			QString cols;
			QString where;

			cols += QString(" v12001=%1 , v12052=%2 , v12052_001=%3 , v12053=%4 , v12053_001=%5, v12002=%6, v12003=%7, ")
				.arg(s.dbStorage_temperature_fileData.daily_average)
				.arg(s.dbStorage_temperature_fileData.daily_maximum)
				.arg(s.dbStorage_temperature_fileData.daily_maximum_time)
				.arg(s.dbStorage_temperature_fileData.daily_minimum)
				.arg(s.dbStorage_temperature_fileData.daily_minimum_time)
				.arg(s.dbStorage_temperature_fileData.daily_wet_temperature)
				.arg(s.dbStorage_temperature_fileData.daily_bulb_temperature);

			cols += QString(" v13203=%1 , v13204=%2 , v13201=%3 ,")
				.arg(s.dbStorage_rain_fileData.daily_20to8_Precipitation)
				.arg(s.dbStorage_rain_fileData.daily_8to20_Precipitation)
				.arg(s.dbStorage_rain_fileData.daily_20to20_Precipitation);

			cols += QString(" v14032=%1 , v04211=%2 , v04212=%3 ,")
				.arg(s.dbStorage_sunshine_fileData.daily_sunshine_count)
				.arg(s.dbStorage_sunshine_fileData.daily_sun_rise)
				.arg(s.dbStorage_sunshine_fileData.daily_sun_set);

			cols += QString(" v13003=%1 , v13007=%2 , v13007_001=%3 ,")
				.arg(s.dbStorage_relativhumidity_fileData.relativhumidity)
				.arg(s.dbStorage_relativhumidity_fileData.relativhumidity_minnum)
				.arg(s.dbStorage_relativhumidity_fileData.relativhumidity_minnum_time);

			cols += QString(" v13004=%1 ,").arg(s.dbStorage_vaporPressure_fileData.vaporPressure);

			cols += QString(" v20010=%1 , v20051=%2 ,")
				.arg(s.dbStorage_cloudy_fileData.totalcloudy)
				.arg(s.dbStorage_cloudy_fileData.lowcloudy);

			cols += QString(" v20001=%1 ,").arg(s.dbStorage_visibility_fileData.visibility);
			cols += QString(" v11002=%1 , v11042=%2 , v11212=%3 , v11041=%4 , v11043=%5 ,")
				.arg(s.dbStorage_wind_fileData.average_wind)
				.arg(s.dbStorage_wind_fileData.wind_max)
				.arg(s.dbStorage_wind_fileData.wind_max_direct)
				.arg(s.dbStorage_wind_fileData.wind_extreme)
				.arg(s.dbStorage_wind_fileData.wind_extreme_direct);

			cols += QString(" v13205=%1 , v12001_808=%2 , v12016=%3 , v12017=%4")
				.arg(s.dbStorage_nothing_fileData.daily_8to8_rain)
				.arg(s.dbStorage_nothing_fileData.daily_8to8_temperature)
				.arg(s.dbStorage_nothing_fileData.daily_8to8_maximum_temp)
				.arg(s.dbStorage_nothing_fileData.daily_8to8_minmimu_temp);

			cols += QString(", TS_YMD= str_to_date('%1','%Y%m%d')").arg(year*10000+month*100+day);
			where += QString("V01000=%1 AND  V04001=%2 AND v04002=%3 AND v04003=%4").arg(staid).arg(year).arg(month).arg(day);
			sql = QString("update t_dms_cd_surf_muday_ele_cn set %1  where %2").arg(cols).arg(where);
		}

		qry.exec(sql);

	}
	m_db.commit();

}

int FileAnalysisDll::Data2DB_A( QList<hour_data> t,QList<max_huge_wind_filedata> u)
{
	int cnt = 0;
	if (!m_db.isOpen() || !m_db.isValid())
	{
		return cnt;
	}

	QList<hour_data> hourdata = t;
	if(hourdata.size() == 0)
	{
		return cnt;
	}
	int year = hourdata.at(0).v04001_observe_year;
	int month = hourdata.at(0).v04002_observe_month;
	int day=1;
	int hour=1;
	if(year<1900 || month>12 || month<1 || day>31||day<1)
	{
		return cnt;
	}

	QSqlQuery qry(m_db);
	QSqlQuery qrySel(m_db);

	QString sql;
	QString sqlSel;

	QStringList rainDays;		//后面雨用的
	QList<int> days;
	QList<int> hours;
	int staid = hourdata.at(0).v01000_sta_Num.toInt();
	sqlSel = QString("SELECT  V04003 ,V04004 FROM T_DMS_RD_SURF_RSUAT_ELE WHERE V01000=%1 AND V04001=%2 AND V04002=%3").arg(staid).arg(year).arg(month);
	if(!qrySel.exec(sqlSel))
	{
		DBERROR(qrySel);
		return cnt;
	}
	days.clear();
	while(qrySel.next())
	{
		days.append(qrySel.value(0).toInt());
		hours.append(qrySel.value(1).toInt());
	}

	m_db.transaction();

	for(int i=0; i< hourdata.size(); i++)
	{
		day = hourdata.at(i).v04003_observe_day;
		hour = hourdata.at(i).v04004_observe_hour;
		if(days.indexOf(day) == -1 && hours.indexOf(hour) == -1) // insert
		{
			QString cols;
			QString vars;
			cols += QString("V01000, V04001, v04002, v04003, v04004, v05001, v06001, v07001, v07002, v02001");
			cols += QString(", v11001_002, v11002_002, v11202_010, v11042_010, v12001, v13019, v10004");

			vars += QString("%1, %2, %3, %4, %5, %6, %7, %8, %9, %10").arg(staid).arg(year).arg(month).arg(day).arg(hour).arg(hourdata.at(i).v05001_sta_Latitude).arg(hourdata.at(i).v06001_sta_Longitude).arg(hourdata.at(i).v07001_sta_high).arg(hourdata.at(i).v07002_sensor_high).arg(hourdata.at(i).v02001_observe_mode);
			vars += QString(", %1, %2, %3, %4, %5, %6, %7").arg(hourdata.at(i).v11001_002_2min_wind_direction).arg(hourdata.at(i).v11002_002_2min_wind_speed).arg(hourdata.at(i).v11202_010_10min_wind_direction).arg(hourdata.at(i).v11042_010_10min_wind_speed).arg(hourdata.at(i).v12001_temperature).arg(hourdata.at(i).v13019_1hour_Precipitation).arg(hourdata.at(i).v10004_pressure);

			sql = QString("INSERT INTO T_DMS_RD_SURF_RSUAT_ELE(%1) values(%2)").arg(cols).arg(vars);
		}
		else
		{
			QString cols;
			QString where;
			cols += QString(" V01000=%1 , V04001=%2 , v04002=%3 , V04003=%4 , v04004=%5 , v05001=%6 , v06001=%7 , v07001=%8 , v07002=%9 , v02001=%10").arg(staid).arg(year).arg(month).arg(day).arg(hour).arg(hourdata.at(i).v05001_sta_Latitude).arg(hourdata.at(i).v06001_sta_Longitude).arg(hourdata.at(i).v07001_sta_high).arg(hourdata.at(i).v07002_sensor_high).arg(hourdata.at(i).v02001_observe_mode);
			cols += QString(" , v11001_002=%1 , v11002_002=%2 , v11202_010=%3 , v11042_010=%4 , v12001=%5 , v13019=%6 , v10004=%7").arg(hourdata.at(i).v11001_002_2min_wind_direction).arg(hourdata.at(i).v11002_002_2min_wind_speed).arg(hourdata.at(i).v11202_010_10min_wind_direction).arg(hourdata.at(i).v11042_010_10min_wind_speed).arg(hourdata.at(i).v12001_temperature).arg(hourdata.at(i).v13019_1hour_Precipitation).arg(hourdata.at(i).v10004_pressure);
			where += QString("V01000=%1 AND  V04001=%2 AND v04002=%3 AND v04003=%4 AND v04004=%5").arg(staid).arg(year).arg(month).arg(day).arg(hour);
			sql = QString("update T_DMS_RD_SURF_RSUAT_ELE set %1  where %2").arg(cols).arg(where);
		}
		qry.exec(sql);
		//m_db.commit();
	}
	//////////////////////////////A文件中的日数据，其实就是最大风级大风，入muday/////////////////////////////
	QList<max_huge_wind_filedata> temp_wind_filedata = u;

	sqlSel = QString("SELECT  V04003 FROM t_dms_cd_surf_muday_ele_cn WHERE V01000=%1 AND V04001=%2 AND V04002=%3").arg(temp_wind_filedata.at(0).V01000).arg(temp_wind_filedata.at(0).V04001).arg(temp_wind_filedata.at(0).V04002);
	if(!qrySel.exec(sqlSel))
	{
		DBERROR(qrySel);
		return cnt;
	}
	//QList<int> days;
	days.clear();
	while(qrySel.next())
	{
		days.append(qrySel.value(0).toInt());
	}
	m_db.transaction();

	for (int i = 0;i<temp_wind_filedata.size();i++)
	{
		max_huge_wind_filedata tw_max_huge = temp_wind_filedata.at(i);
		int day = tw_max_huge.V04003;
		if (days.indexOf(day) == -1)
		{
			QString cols;
			QString vars;
			cols += QString("V01000, V04001, v04002, v04003, ");
			cols += QString("V11042, V11212, V11041, V11043");

			vars += QString("%1, %2, %3, %4, ").arg(tw_max_huge.V01000).arg(tw_max_huge.V04001).arg(tw_max_huge.V04002).arg(tw_max_huge.V04003);
			vars += QString("%1 ,%2, %3, %4").arg(tw_max_huge.v11042_1hour_10min_max_wind_speed).arg(tw_max_huge.v11202_1hour_10min_max_wind_direction)
				.arg(tw_max_huge.v11041_1hour_huge_wind_speed).arg(tw_max_huge.v11043_1hour_huge_wind_direction);

			sql = QString("INSERT INTO t_dms_cd_surf_muday_ele_cn(%1) values(%2)").arg(cols).arg(vars);
		}
		else
		{
			QString cols;
			QString where;
			cols += QString("V11042=%1, V11212=%2, V11041=%3, V11043=%4").arg(tw_max_huge.v11042_1hour_10min_max_wind_speed).arg(tw_max_huge.v11202_1hour_10min_max_wind_direction)
				.arg(tw_max_huge.v11041_1hour_huge_wind_speed).arg(tw_max_huge.v11043_1hour_huge_wind_direction);
			where += QString("V01000=%1 AND  V04001=%2 AND v04002=%3 AND v04003=%4").arg(tw_max_huge.V01000).arg(tw_max_huge.V04001).arg(tw_max_huge.V04002).arg(tw_max_huge.V04003);
			sql = QString("update t_dms_cd_surf_muday_ele_cn set %1  where %2").arg(cols).arg(where);
		}
		qry.exec(sql);
	}
	m_db.commit();
	//////////////////////////////A文件中的雨的日数据，入muday/////////////////////////////
	sqlSel = QString("SELECT  V04003 FROM T_DMS_RD_SURF_RSUAT_ELE WHERE V01000=%1 AND V04001=%2 AND V04002=%3").arg(staid).arg(year).arg(month);
	if(!qrySel.exec(sqlSel))
	{
		DBERROR(qrySel);
		return cnt;
	}
	while(qrySel.next())
	{
		rainDays.append(qrySel.value(0).toString()); //雨数据所用上面有更新过程，这里必须重新查询最新信息
	}
	m_db.transaction();

	for (int i = 0;i<rainDays.count();i++)
	{
		// 		if (days.indexOf(rainDays.at(i).toInt()) == -1)//其中days在上面的风数据的时候已经查询过最新表，故可以直接拿来用
		// 		{
		// 			sql = QString("INSERT into t_dms_cd_surf_muday_ele_cn (V01000,V04001,V04002,V04003,V13201,v10004) select v01000,v04001,v04002,v04003,SUM(v13019) as v13019 ,avg(v10004) as v10004 from t_dms_rd_surf_rsuat_ele WHERE v13019<1000 and V01000=%1 and v04001=%2 and v04002=%3 and v04003=%4 GROUP BY v01000,v04001,v04002,v04003")
		// 				.arg(staid).arg(year).arg(month).arg(rainDays.at(i));
		// 		}
		// 		else
		// 		{
		sql = QString("UPDATE t_dms_cd_surf_muday_ele_cn d,(select v01000,v04001,v04002,v04003,SUM(v13019) as v13019,avg(v10004) as v10004 from t_dms_rd_surf_rsuat_ele WHERE v13019<1000 and V01000=%1 and V04001=%2 and V04002=%3 and V04003=%4 GROUP BY v01000,v04001,v04002,v04003) h set d.V13201=h.v13019 ,d.v10004 = h.v10004 WHERE d.V01000=%5 and d.V04001=%6 and d.V04002=%7 and d.V04003=%8")
			.arg(staid).arg(year).arg(month).arg(rainDays.at(i)).arg(staid).arg(year).arg(month).arg(rainDays.at(i));
		//}
		qry.exec(sql);
	}
	m_db.commit();

	return cnt;
}

void FileAnalysisDll::Data2DB_AI( QList<observe_result> t)
{

	if (!m_db.isOpen() || !m_db.isValid())
	{
		return ;
	}

	{
		QList<observe_result> obList = t;

		QSqlQuery qry(m_db);
		QSqlQuery qrySel(m_db);

		QString sql;
		QString sqlSel;

		QList<int> stations;
		observe_result tempOB = obList.at(0);
		sqlSel = QString("SELECT V01000 FROM T_DMS_RD_SURF_RSUAT_ELE WHERE V04001=%1 AND V04002=%2 AND V04003=%3 AND V04004=%4").arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day).arg(tempOB.v04004_observe_hour);

		if(!qrySel.exec(sqlSel))
		{
			DBERROR(qrySel);
			return ;
		}
		stations.clear();
		while(qrySel.next())
		{
			stations.append(qrySel.value(0).toInt());
		}

		m_db.transaction();

		for (int i=0;i<obList.size();i++)
		{
			tempOB = obList.at(i);
			int sta = tempOB.v01000_sta_Num;
			/////////和T_DMS_MT_OTHE_SITED_GROUP关联起来//////////////////////
			{
				QString ttsqlSel = QString("select V01000 from T_DMS_MT_OTHE_SITED_GROUP where v01000 = %1").arg(sta);
				qrySel.exec(ttsqlSel);
				QList<int>  ts;
				ts.clear();
				while (qrySel.next());
				{
					ts.append(qrySel.value(0).toInt());
				}
				if (ts.indexOf(sta != -1))
				{
					QString cols,vars;
					cols += QString("v01000 ,v05001 ,v06001 ,V07001 ,V07033 ,V02001");
					vars += QString("%1 ,%2 ,%3 ,%4 ,%5 ,%6").arg(sta).arg(tempOB.v05001_sta_Latitude/10000.0).arg(tempOB.v06001_sta_Longitude/10000.0)
						.arg(tempOB.v07001_sta_high).arg(tempOB.v07002_sensor_high).arg(tempOB.v02001_observe_mode);
					ttsqlSel = QString("INSERT INTO T_DMS_MT_OTHE_SITED_GROUP(%1) values(%2)").arg(cols).arg(vars);
					qry.exec(ttsqlSel);
				}
			}

			//////////////////////////////////////////////////////////////////
			if (stations.indexOf(sta) == -1)
			{
				QString cols;
				QString vars;

				cols += QString("v01000,v04001,v04002,v04003,v04004,v04005,v04006,");

				cols += QString("v05001,v06001,v07001,v07002,v02001,");
				cols += QString("v11001_002,v11002_002,v11202_010,v11042_010,");
				cols += QString("v11202,v11042, v11042_752,v11001,v11002,");
				cols += QString("v11043,v11041,v11041_752,");

				cols += QString("v13019,");

				cols += QString("v12001,v12211,v12211_752,v12212,v12212_752,");

				cols += QString("v13003,v13007,v13007_752,");

				cols += QString("v13004,v12003,");

				cols += QString("v10004,v10201,v10201_752,v10202,v10202_752,");

				cols += QString("v12061_002,v12213_002,v12213_002_752,v12214_002,v12214_002_752,");
				cols += QString("v12061_001,v12213_001,v12213_001_752,v12214_001,v12214_001_752,");

				cols += QString("v12030_005,v12030_010,v12030_015,v12030_020,");
				cols += QString("v12030_040,v12030_080,v12030_160,v12030_320,");

				cols += QString("v13031,v10005,");

				cols += QString("v20001_052_001, v20001_006,v20001_006_752");

				vars += QString("%1, %2, %3, %4, %5, %6 ,%7 ,").arg(tempOB.v01000_sta_Num).arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day).arg(tempOB.v04004_observe_hour).arg(tempOB.v04005_observe_minute).arg(tempOB.v04006_observe_second);

				vars += QString("%1, %2, %3, %4, %5 ,").arg(tempOB.v05001_sta_Latitude).arg(tempOB.v06001_sta_Longitude).arg(tempOB.v07001_sta_high).arg(tempOB.v07002_sensor_high).arg(tempOB.v02001_observe_mode);
				vars += QString("%1, %2, %3, %4 ,").arg(tempOB.v11001_002_2min_wind_direction).arg(tempOB.v11002_002_2min_wind_speed).arg(tempOB.v11202_010_10min_wind_direction).arg(tempOB.v11042_010_10min_wind_speed);
				vars += QString("%1, %2, %3, %4, %5 ,").arg(tempOB.v10202_1hour_min_air_pressure).arg(tempOB.v11042_1hour_10min_max_wind_speed).arg(tempOB.v11041_752_1hour_huge_wind_time).arg(tempOB.v11001_moment_wind_direction).arg(tempOB.v11002_moment_wind_speed);
				vars += QString("%1, %2, %3 ,").arg(tempOB.v11043_1hour_huge_wind_direction).arg(tempOB.v11041_1hour_huge_wind_speed).arg(tempOB.v11041_752_1hour_huge_wind_time);

				vars += QString("%1 ,").arg(tempOB.v13019_1hour_Precipitation);

				vars += QString("%1, %2, %3, %4 ,%5 ,").arg(tempOB.v12001_temperature).arg(tempOB.v12211_1hour_max_temperature).arg(tempOB.v12211_752_1hour_max_temperature_time).arg(tempOB.v12212_1hour_min_temperature).arg(tempOB.v12212_752_1hour_min_temperature_time);
				vars += QString("%1, %2, %3 ,").arg(tempOB.v13003_relative_humidity).arg(tempOB.v13007_min_relative_humidity).arg(tempOB.v13007_752_min_relative_humidity_time);

				vars += QString("%1, %2 ,").arg(tempOB.v13004_water_pressure).arg(tempOB.v12003_point_temperature);

				vars += QString("%1, %2, %3,  %4, %5 ,").arg(tempOB.v10004_air_pressure).arg(tempOB.v10201_1hour_max_air_pressure).arg(tempOB.v10201_752_1hour_max_air_pressure_time).arg(tempOB.v10202_1hour_min_air_pressure).arg(tempOB.v10201_752_1hour_max_air_pressure_time);

				vars += QString("%1, %2, %3, %4, %5 ,").arg(tempOB.v12061_002_grass_temperature).arg(tempOB.v12213_002_max_grass_temperature).arg(tempOB.v12213_002_752_max_grass_temperature_time).arg(tempOB.v12214_002_min_grass_temperature).arg(tempOB.v12214_002_752_min_grass_temperature_time);
				vars += QString("%1, %2, %3, %4, %5 ,").arg(tempOB.v12061_001_ground_temperature).arg(tempOB.v12213_001_1hour_max_ground_temperature).arg(tempOB.v12213_001_752_1hour_max_ground_temperature_time).arg(tempOB.v12214_001_1hour_min_ground_temperature).arg(tempOB.v12214_001_752_1hour_min_ground_temperature_time);

				vars += QString("%1, %2, %3, %4 ,").arg(tempOB.v12030_005_5cm_ground_temperature).arg(tempOB.v12030_010_10cm_ground_temperature).arg(tempOB.v12030_015_15cm_ground_temperature).arg(tempOB.v12030_020_20cm_ground_temperature);
				vars += QString("%1, %2, %3, %4 ,").arg(tempOB.v12030_040_40cm_ground_temperature).arg(tempOB.v12030_080_80cm_ground_temperature).arg(tempOB.v12030_160_160cm_ground_temperature).arg(tempOB.v12030_320_320cm_ground_temperature);

				vars += QString("%1, %2 ,").arg(tempOB.v13031_1hour_evaporation).arg(tempOB.v10005_sea_pressure);

				vars += QString("%1, %2, %3").arg(tempOB.v20001_052_001_visibility).arg(tempOB.v20001_006_1hour_min_visibility).arg(tempOB.v20001_006_752_1hour_min_visibility_time);
				sql = QString("INSERT INTO t_dms_rd_surf_rsuat_ele(%1) values(%2)").arg(cols).arg(vars);
			}
			else
			{

				QString cols;
				QString where;

				cols += QString("v04005=%1,v04006=%2,").arg(tempOB.v04005_observe_minute).arg(tempOB.v04006_observe_second);
				cols += QString("v05001=%1,v06001=%2,v07001=%3,v07002=%4,v02001=%5,").arg(tempOB.v05001_sta_Latitude).arg(tempOB.v06001_sta_Longitude).arg(tempOB.v07001_sta_high).arg(tempOB.v07002_sensor_high).arg(tempOB.v02001_observe_mode);
				cols += QString("v11001_002=%1,v11002_002=%2,v11202_010=%3,v11042_010=%4,").arg(tempOB.v11001_002_2min_wind_direction).arg(tempOB.v11002_002_2min_wind_speed).arg(tempOB.v11202_010_10min_wind_direction).arg(tempOB.v11042_010_10min_wind_speed);
				cols += QString("v11202=%1,v11042=%2, v11042_752=%3,v11001=%4,v11002=%5,").arg(tempOB.v10202_1hour_min_air_pressure).arg(tempOB.v11042_1hour_10min_max_wind_speed).arg(tempOB.v11041_752_1hour_huge_wind_time).arg(tempOB.v11001_moment_wind_direction).arg(tempOB.v11002_moment_wind_speed);
				cols += QString("v11043=%1,v11041=%2,v11041_752=%3,").arg(tempOB.v11043_1hour_huge_wind_direction).arg(tempOB.v11041_1hour_huge_wind_speed).arg(tempOB.v11041_752_1hour_huge_wind_time);

				cols += QString("v13019=%1,").arg(tempOB.v13019_1hour_Precipitation);

				cols += QString("v12001=%1,v12211=%2,v12211_752=%3,v12212=%4,v12212_752=%5,").arg(tempOB.v12001_temperature).arg(tempOB.v12211_1hour_max_temperature).arg(tempOB.v12211_752_1hour_max_temperature_time).arg(tempOB.v12212_1hour_min_temperature).arg(tempOB.v12212_752_1hour_min_temperature_time);

				cols += QString("v13003=%1,v13007=%2,v13007_752=%3,").arg(tempOB.v13003_relative_humidity).arg(tempOB.v13007_min_relative_humidity).arg(tempOB.v13007_752_min_relative_humidity_time);

				cols += QString("v13004=%1,v12003=%2,").arg(tempOB.v13004_water_pressure).arg(tempOB.v12003_point_temperature);

				cols += QString("v10004=%1,v10201=%2,v10201_752=%3,v10202=%4,v10202_752=%5,").arg(tempOB.v10004_air_pressure).arg(tempOB.v10201_1hour_max_air_pressure).arg(tempOB.v10201_752_1hour_max_air_pressure_time).arg(tempOB.v10202_1hour_min_air_pressure).arg(tempOB.v10201_752_1hour_max_air_pressure_time);

				cols += QString("v12061_002=%1,v12213_002=%2,v12213_002_752=%3,v12214_002=%4,v12214_002_752=%5,").arg(tempOB.v12061_002_grass_temperature).arg(tempOB.v12213_002_max_grass_temperature).arg(tempOB.v12213_002_752_max_grass_temperature_time).arg(tempOB.v12214_002_min_grass_temperature).arg(tempOB.v12214_002_752_min_grass_temperature_time);
				cols += QString("v12061_001=%1,v12213_001=%2,v12213_001_752=%3,v12214_001=%4,v12214_001_752=%5,").arg(tempOB.v12061_001_ground_temperature).arg(tempOB.v12213_001_1hour_max_ground_temperature).arg(tempOB.v12213_001_752_1hour_max_ground_temperature_time).arg(tempOB.v12214_001_1hour_min_ground_temperature).arg(tempOB.v12214_001_752_1hour_min_ground_temperature_time);

				cols += QString("v12030_005=%1,v12030_010=%2,v12030_015=%3,v12030_020=%4,").arg(tempOB.v12030_005_5cm_ground_temperature).arg(tempOB.v12030_010_10cm_ground_temperature).arg(tempOB.v12030_015_15cm_ground_temperature).arg(tempOB.v12030_020_20cm_ground_temperature);
				cols += QString("v12030_040=%1,v12030_080=%2,v12030_160=%3,v12030_320=%4,").arg(tempOB.v12030_040_40cm_ground_temperature).arg(tempOB.v12030_080_80cm_ground_temperature).arg(tempOB.v12030_160_160cm_ground_temperature).arg(tempOB.v12030_320_320cm_ground_temperature);

				cols += QString("v13031=%1,v10005=%2,").arg(tempOB.v13031_1hour_evaporation).arg(tempOB.v10005_sea_pressure);

				cols += QString("v20001_052_001=%1, v20001_006=%2,v20001_006_752=%3").arg(tempOB.v20001_052_001_visibility).arg(tempOB.v20001_006_1hour_min_visibility).arg(tempOB.v20001_006_752_1hour_min_visibility_time);

				where += QString("V01000=%1 AND  V04001=%2 AND v04002=%3 AND v04003=%4 AND v04004=%5")
					.arg(tempOB.v01000_sta_Num).arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month)
					.arg(tempOB.v04003_observe_day).arg(tempOB.v04004_observe_hour);

				sql = QString("update t_dms_rd_surf_rsuat_ele set %1  where %2").arg(cols).arg(where);
			}
			qry.exec(sql);
		}
		////////////////////////////////////////日雨数据处理

		sqlSel = QString("SELECT  v01000 FROM t_dms_cd_surf_muday_ele_cn WHERE V04001=%1 AND V04002=%2 AND V04003=%3").arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day);
		if(!qrySel.exec(sqlSel))
		{
			DBERROR(qrySel);
		}
		QList<int> tmpStations;
		while(qrySel.next())
		{
			tmpStations.append(qrySel.value(0).toInt());//目前待处理的表中已有的雨的日数据站点列表
		}

		sqlSel = QString("SELECT V01000 FROM T_DMS_RD_SURF_RSUAT_ELE WHERE V04001=%1 AND V04002=%2 AND V04003=%3 AND V04004=%4").arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day).arg(tempOB.v04004_observe_hour);
		if(!qrySel.exec(sqlSel))
		{
			DBERROR(qrySel);
		}
		stations.clear();
		while(qrySel.next())
		{
			stations.append(qrySel.value(0).toInt()); //最新更新的雨数据站点列表
		}
		m_db.transaction();

		for (int i = 0;i<stations.size();i++)
		{

			if (tmpStations.contains(stations.at(i)))
			{
				//UpDate
				sql = QString("UPDATE t_dms_cd_surf_muday_ele_cn d,(select v01000,v04001,v04002,v04003,SUM(v13019) as v13019,min(v10004) as v10004 from t_dms_rd_surf_rsuat_ele WHERE v13019<1000 and V01000=%1 and V04001=%2 and V04002=%3 and V04003=%4 GROUP BY v01000,v04001,v04002,v04003) h set d.V13201=h.v13019 ,d.v10004 = h.v10004 WHERE d.V01000=%5 and d.V04001=%6 and d.V04002=%7 and d.V04003=%8")
					.arg(stations.at(i)).arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day).arg(stations.at(i)).arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day);
			}
			else
			{
				//InSert
				sql = QString("INSERT into t_dms_cd_surf_muday_ele_cn (V01000,V04001,V04002,V04003,V13201,v10004) select v01000,v04001,v04002,v04003,SUM(v13019) as v13019 ,min(v10004) as v10004 from t_dms_rd_surf_rsuat_ele WHERE v13019<1000 and V01000=%1 and v04001=%2 and v04002=%3 and v04003=%4 GROUP BY v01000,v04001,v04002,v04003")
					.arg(stations.at(i)).arg(tempOB.v04001_observe_year).arg(tempOB.v04002_observe_month).arg(tempOB.v04003_observe_day);
			}
			qry.exec(sql);
		}
		m_db.commit();
	}
}

void FileAnalysisDll::Data2DB_typhoon( QList<typhoon_forecast> t)
{
	if (!m_db.isOpen() || !m_db.isValid())
	{
		return ;
	}

	QList<typhoon_forecast> tyList = t;

	QSqlQuery qry(m_db);
	QSqlQuery qrySel(m_db);

	QString sql;
	QString sqlSel;

	QList<int> times;
	for (int i=0;i<tyList.size();i++)
	{
		typhoon_forecast tpTY = tyList.at(i);
		sqlSel = QString("SELECT V04400 FROM T_DMS_RD_OTHE_RFTYP_ELE_CN WHERE V04001='%1' AND V04002='%2' AND V04003='%3' AND V_OHM='%4' AND C_TYPHNAME='%5' AND C_CCCC='BABJ'").arg(tpTY.typhoon_forecast_live.Live_year).arg(tpTY.typhoon_forecast_live.Live_month).arg(tpTY.typhoon_forecast_live.Live_day)
			.arg(tpTY.typhoon_forecast_live.Live_hour).arg(tpTY.typhoon_forecast_live.typhoon_name);

		if(!qrySel.exec(sqlSel))
		{
			DBERROR(qrySel);
			return ;
		}
		times.clear();
		while(qrySel.next())
		{
			times.append(qrySel.value(0).toInt());
		}
		m_db.transaction();

		for (int j=0;j<tpTY.typhoon_forecast_point.size();j++)
		{
			int yy = tpTY.typhoon_forecast_live.Live_year;
			if (yy>50)
			{
				yy = 1900 + yy;
			}
			else
			{
				yy = 2000 + yy;
			}
			if (times.indexOf(tpTY.typhoon_forecast_point.at(j).forecast_time.mid(2,2).toInt()) == -1)
			{
				QString cols,vars;		
				cols += QString("C_CCCC ,C_TYPHNAME ,V04001 ,V04002 ,V04003 ,V_OHM ,V04400,");//主键大哥
				cols += QString("V01210 ,V01230 ,V01231 ,V31001,");
				cols += QString("V05001 ,V06001 ,V10004 ,V11041,");
				cols += QString("V11223_071 ,V11223_101,");
				cols += QString("V11224 ,V11225");


				vars += QString("'%1' ,'%2' ,%3 ,%4 ,%5 ,%6 ,%7 ,").arg(tpTY.typhoon_forecast_tital.foreact_tital).arg(tpTY.typhoon_forecast_live.typhoon_name)
					.arg(yy).arg(tpTY.typhoon_forecast_live.Live_month).arg(tpTY.typhoon_forecast_live.Live_day)
					.arg(tpTY.typhoon_forecast_live.Live_hour).arg(tpTY.typhoon_forecast_point.at(j).forecast_time.mid(2,2).toInt());
				vars += QString("%1 ,%2 ,%3 ,%4 ,").arg(tpTY.typhoon_forecast_live.ty_level).arg(tpTY.typhoon_forecast_live.typhoon_number).arg(tpTY.typhoon_forecast_live.typhoon_international_number)
					.arg(tpTY.typhoon_forecast_point.size());
				vars += QString("%1 ,%2 ,%3 ,%4 ,").arg(tpTY.typhoon_forecast_live.typhoon_Latitude).arg(tpTY.typhoon_forecast_live.typhoon_Longitude).arg(tpTY.typhoon_forecast_live.central_pressure).arg(tpTY.typhoon_forecast_live.central_Wind_velocity);
				vars += QString("%1 ,%2 ,").arg(tpTY.typhoon_forecast_live.typhoon_30kts).arg(tpTY.typhoon_forecast_live.typhoon_50kts);
				vars += QString("%1 ,%2").arg(tpTY.typhoon_forecast_part.ty_dircetion).arg((tpTY.typhoon_forecast_part.ty_speed));

				sql = QString("INSERT INTO T_DMS_RD_OTHE_RFTYP_ELE_CN(%1) values(%2)").arg(cols).arg(vars);
			}
			else
			{
				QString cols,where;

				cols += QString("V01210=%1 ,V01230=%2 ,V01231=%3 ,V31001=%4 ,").arg(tpTY.typhoon_forecast_live.ty_level).arg(tpTY.typhoon_forecast_live.typhoon_number).arg(tpTY.typhoon_forecast_live.typhoon_international_number)
					.arg(tpTY.typhoon_forecast_point.size());
				cols += QString("V05001=%1 ,V06001=%2 ,V10004=%3 ,V11041=%4 ,").arg(tpTY.typhoon_forecast_live.typhoon_Latitude).arg(tpTY.typhoon_forecast_live.typhoon_Longitude).arg(tpTY.typhoon_forecast_live.central_pressure).arg(tpTY.typhoon_forecast_live.central_Wind_velocity);
				cols += QString("V11223_071=%1 ,V11223_101=%2 ,").arg(tpTY.typhoon_forecast_live.typhoon_30kts).arg(tpTY.typhoon_forecast_live.typhoon_50kts);
				cols += QString("V11224=%1 ,V11225=%2").arg(tpTY.typhoon_forecast_part.ty_dircetion).arg((tpTY.typhoon_forecast_part.ty_speed));

				where += QString("C_CCCC='%1' and C_TYPHNAME='%2' and V04001=%3 and V04002=%4 and V04003=%5 and V_OHM=%6 and V04400=%8").arg(tpTY.typhoon_forecast_tital.foreact_tital).arg(tpTY.typhoon_forecast_live.typhoon_name)
					.arg(yy).arg(tpTY.typhoon_forecast_live.Live_month).arg(tpTY.typhoon_forecast_live.Live_day)
					.arg(tpTY.typhoon_forecast_live.Live_hour).arg(tpTY.typhoon_forecast_point.at(j).forecast_time.mid(2,2).toInt());

				sql = QString("update T_DMS_RD_OTHE_RFTYP_ELE_CN set %1  where %2").arg(cols).arg(where);
			}
			qry.exec(sql);
		}
	}	

	QList<int> chid;
	for (int k = 0;k<tyList.size();k++)
	{
		typhoon_forecast tpTY = tyList.at(k);
		int t_year = tpTY.typhoon_forecast_live.Live_year;
		if (t_year < 65)
		{
			t_year = 2000 + t_year;
		}
		else
		{
			t_year = 1900 + t_year;
		}
		int t_month = tpTY.typhoon_forecast_live.Live_month;
		int t_day = tpTY.typhoon_forecast_live.Live_day;
		int t_hour = tpTY.typhoon_forecast_live.Live_hour;
		int cpYDM = t_year * 1000000 + t_month * 10000 + t_day * 100 + t_hour;
		QDateTime t_dateTime = QDateTime::fromString(QString::number(cpYDM),"yyyyMMddhh");
		t_dateTime = t_dateTime.addSecs(28800);
		cpYDM = t_dateTime.toString("yyyyMMddhh").toInt();
		int m_chid = t_year*100 + QString::number(tpTY.typhoon_forecast_live.typhoon_number).right(2).toInt();
		int m_v05001 = tpTY.typhoon_forecast_live.typhoon_Latitude;
		int m_v06001 = tpTY.typhoon_forecast_live.typhoon_Longitude;
		int m_30kts = tpTY.typhoon_forecast_live.typhoon_30kts;
		int m_50kts = tpTY.typhoon_forecast_live.typhoon_50kts;
		int m_pressure = tpTY.typhoon_forecast_live.central_pressure;
		int m_velocity = tpTY.typhoon_forecast_live.central_Wind_velocity;
		int m_direction = tpTY.typhoon_forecast_part.ty_dircetion;
		int m_speed = tpTY.typhoon_forecast_part.ty_speed;
		int m_number = QString::number(tpTY.typhoon_forecast_live.typhoon_international_number).right(2).toInt();
		int tylvl = tpTY.typhoon_forecast_live.ty_level;
		int m_IntNumber = tpTY.typhoon_forecast_live.typhoon_international_number;
		QString m_namee = tpTY.typhoon_forecast_live.typhoon_name;
		//////////////////////////////////////////////////////////////////////////////////
		sqlSel = QString("select CH_ID from T_DMS_RD_OTHE_RRTYP_PAT_CN where C_PATH_YMD = %1").arg(cpYDM);
		int ch_id = m_chid;
		qrySel.exec(sqlSel);
		chid.clear();
		while(qrySel.next())
		{
			chid.append(qrySel.value(0).toInt());
		}
		if (chid.indexOf(ch_id) == -1)
		{
			QString cols,vars;

			cols += QString("CH_ID ,V_TYP_ALLCODE ,C_PATH_YMD,V05001 ,V06001 ,V10004 ,V11042 ,");
			cols += QString("V11223_071 ,V11223_101 ,V11224 ,V11225 ,C_TYP_NAME ,V_TYPE_FLAG ,V_FORRID");
			vars += QString("%1 ,%2 ,%3 ,%4, %5, %6, %7, ").arg(m_chid).arg(m_number).arg(cpYDM).arg(m_v05001).arg(m_v06001).arg(m_pressure).arg(m_velocity);
			vars += QString("%1 ,%2 ,%3 ,%4, '%5' ,%6 ,%7").arg(m_30kts).arg(m_50kts).arg(m_direction).arg(m_speed).arg(m_namee).arg(tylvl).arg(m_IntNumber);
			sql =  QString("INSERT INTO T_DMS_RD_OTHE_RRTYP_PAT_CN(%1) values(%2)").arg(cols).arg(vars);
		}
		else
		{
			QString cols,where;
			cols += QString("V_TYP_ALLCODE=%1,").arg(m_number);
			cols += QString("V05001=%1,V06001=%2,V10004=%3,V11042=%4,").arg(m_v05001).arg(m_v06001).arg(m_pressure).arg(m_velocity);
			cols += QString("V11223_071=%1 ,V11223_101=%2 ,V11224=%3 ,V11225=%4 ,C_TYP_NAME='%5' ,V_TYPE_FLAG=%6 ,V_FORRID=%7")
				.arg(m_30kts).arg(m_50kts).arg(m_direction).arg(m_speed).arg(m_namee).arg(tylvl).arg(m_IntNumber);
			where += QString("CH_ID=%1 and C_PATH_YMD=%2").arg(m_chid).arg(cpYDM);
			sql = QString("update T_DMS_RD_OTHE_RRTYP_PAT_CN set %1  where %2").arg(cols).arg(where);
		}
		qry.exec(sql);
	}
	m_db.commit();
}
