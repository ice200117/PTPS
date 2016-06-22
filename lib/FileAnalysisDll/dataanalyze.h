#ifndef DATAANALYZE_H
#define DATAANALYZE_H

//#include "dataanalyze_global.h"

#include "read_Ai.h"
#include "read_Typhoon.h"
#include "read_A0.h"
#include "read_A.h"
//#include "read_tracksh.h"
class DataAnalyze
{
public:
	DataAnalyze();
	~DataAnalyze();
	
	void decode_AI(QString Ai_fileName);
	QList<observe_result> Get_AI_Data(){return r;}

	void decode_typhoon(QString typhoon_fileName);
	QList<typhoon_forecast> Get_typhoon(){return s;}

	void decode_A0(QString A0_fileName);
	QList<dbStorage> Get_A0_Data(){return t;}

	void decode_A(QString A_fileName);
	QList<hour_data> Get_A_Data(){return u;}
	QList<max_huge_wind_filedata> Get_A_wind_Data(){return w;}

// 	void decode_tracksh(QString tracksh_fileName);
// 	QList<tracksh_list> Get_tracksh_Data(){return v;}

// 	QDate ChineseDate2SolarDate(QDate);
// 	QDate SolarDate2ChineseDate(QDate);
// 	int Get_Ch_mod(QDate,QDate);
private:
	QList<observe_result> r;
	QList<typhoon_forecast> s;
	QList<dbStorage> t;
	QList<hour_data> u;
	//QList<tracksh_list> v;
	QList<max_huge_wind_filedata> w;
};

#endif // DATAANALYZE_H
