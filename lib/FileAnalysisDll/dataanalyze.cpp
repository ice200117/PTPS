#include "dataanalyze.h"
// #include "SolarDate.h"   
// #include "ChineseDate.h"
DataAnalyze::DataAnalyze()
{

}

DataAnalyze::~DataAnalyze()
{

}

void DataAnalyze::decode_AI( QString Ai_fileName )
{
	read_AI temp_read_AI;
	temp_read_AI.start_AI(Ai_fileName);
	r = temp_read_AI.Get_AI_Data();
}

void DataAnalyze::decode_typhoon( QString typhoon_fileName )
{
	read_typhoon temp_read_typhoon;
	temp_read_typhoon.start_typhoon(typhoon_fileName);
	s = temp_read_typhoon.Get_typhoon_Data();
}

void DataAnalyze::decode_A0( QString A0_fileName )
{
	read_a0 temp_read_A0;
	temp_read_A0.start_A0(A0_fileName);
	t = temp_read_A0.Get_A0_Data();
}

void DataAnalyze::decode_A( QString A_fileName )
{
	read_A temp_read_A;
	temp_read_A.start_A(A_fileName);
	u = temp_read_A.Get_A_Data();
	w = temp_read_A.Get_A_wind_Data();
}

// void DataAnalyze::decode_tracksh( QString tracksh_fileName )
// {
// 	read_tracksh *temp_read_tracksh = new read_tracksh();
// 	temp_read_tracksh->start_tracksh(tracksh_fileName);
// 	v = temp_read_tracksh->Get_tracksh();
// }

// QDate DataAnalyze::ChineseDate2SolarDate( QDate d)
// {
// 	ChineseDate today(d.year(), d.month(), d.day()); 
// 	SolarDate tmp;
// 	tmp = today.ToSolarDate();
// 	QString s = QString("%1%2%3").arg(tmp.GetYear()).arg(tmp.GetMonth()).arg(tmp.GetDay());
// 
// 	QDate tempsolardate = QDate::fromString(s,"yyyyMd");
// 	return tempsolardate;
// }

// QDate DataAnalyze::SolarDate2ChineseDate( QDate d)
// {
// 	SolarDate today(d.year(),d.month(), d.day());
// 	ChineseDate tmp; 
// 	today.ToChineseDate(tmp);
// 	QString s = QString("%1%2%3").arg(tmp.GetYear()).arg(tmp.GetMonth()).arg(tmp.GetDay());
// 	QDate tempd = QDate::fromString(s,"yyyyMd");
// 	return tempd;
// }

// int DataAnalyze::Get_Ch_mod( QDate begin_Date,QDate end_Date)
// {
// 	int ch_mod = 0,modulus = 0;
// 	QList<QDate> datelist;
// 	QString dfdg;
// 	while(begin_Date != end_Date)
// 	{
// 		datelist.append(begin_Date);
// 		begin_Date = begin_Date.addDays(1);
// 	}
// 	datelist.append(begin_Date);
// 	for (int i = 0;i<datelist.size();i++)
// 	{
// 		int year = datelist.at(i).year();
// 		int month = datelist.at(i).month();
// 		int day = datelist.at(i).day();
// 		QDate solarD = QDate::fromString(QString("%1%2%3").arg(year).arg(month).arg(day),"yyyyMd");
// 		QDate chD = SolarDate2ChineseDate(solarD);
// 		int chday = chD.day();
// 		if (chday>=1 && chday<=5)
// 			ch_mod = 2;
// 		else if (chday >=6 && chday <=7)
// 			ch_mod = 1;
// 		else if (chday >=8 && chday <=12)
// 			ch_mod = 0;
// 		else if (chday >=13 && chday <=14)
// 			ch_mod = 1;
// 		else if (chday >=15 && chday <=19)
// 			ch_mod = 2;
// 		else if (chday >=20 && chday <=22)
// 			ch_mod = 1;
// 		else if (chday >=23 && chday <=26)
// 			ch_mod = 0;
// 		else if (chday >=27 && chday <=29)
// 			ch_mod = 1;
// 		else if (chday == 30)
// 			ch_mod = 2;
// 
// 		if (ch_mod>modulus)
// 		{
// 			modulus = ch_mod;
// 		}
// 	}
// 	return modulus;
// }

