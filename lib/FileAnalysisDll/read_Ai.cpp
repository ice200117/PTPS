#include "read_Ai.h"
#include <QFile>
#define missing_data 999999
read_AI::read_AI(void)
{

}


read_AI::~read_AI(void)
{
}


void read_AI::start_AI(QString fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QString qline = NULL,qtemp = NULL;
	QStringList observeList;
	int linenum = 0;
	while (!file.atEnd()) 
	{
		qtemp = file.readLine();
		if (!qtemp.isEmpty() && !qtemp.isNull())
		{
			qline += qtemp;
			qline += " ";
			linenum++;
			if (linenum == 3)
			{
				observeList.append(qline);
				qline.clear();
				linenum = 0;
			}
		}

	}
	file.close();
	analysis_AI(observeList);
}

void read_AI::analysis_AI(QStringList tl)
{
	QStringList observeList = tl;
	observe_result temp_observe_result;
	for (int i = 0;i<observeList.size();i++)
	{
		QStringList tempList = observeList.at(i).split(" ", QString::SkipEmptyParts);
		if (tempList.size() != 59)
		{
			return ;
		}
		QString staNum = tempList.at(0);
		QChar ss = staNum.at(0);
		int asciif = ss.toAscii();
		QString tsn;
		if (asciif >= 48 && asciif <= 57)
		{
			tsn = staNum;
		}
		else
		{
			tsn = QString("%1").arg(asciif);
			staNum.remove(0,1);
			tsn += staNum;
		}
		

		temp_observe_result.v01000_sta_Num = tsn.toInt();
		temp_observe_result.v05001_sta_Latitude = tempList.at(1).toInt();
		temp_observe_result.v06001_sta_Longitude = tempList.at(2).toInt();
		temp_observe_result.v07001_sta_high = tempList.at(3).toInt();
		temp_observe_result.v07002_sensor_high = tempList.at(4).toInt();
		temp_observe_result.v02001_observe_mode = tempList.at(5).toInt();

		QDateTime datetime = QDateTime::fromString(tempList.at(6),"yyyyMMddhhmmss");
		int year = datetime.toString("yyyy").toInt();
		int month = datetime.toString("MM").toInt();
		int day = datetime.toString("dd").toInt();
		int hour = datetime.toString("hh").toInt();
		int minute = datetime.toString("mm").toInt();
		int second = datetime.toString("ss").toInt();

		temp_observe_result.v04001_observe_year = year;
		temp_observe_result.v04002_observe_month = month;
		temp_observe_result.v04003_observe_day = day;
		temp_observe_result.v04004_observe_hour = hour;
		temp_observe_result.v04005_observe_minute = minute;
		temp_observe_result.v04006_observe_second = second;
		temp_observe_result.observe_time = datetime;

		temp_observe_result.v11001_002_2min_wind_direction = symbol_process(tempList.at(7));
		temp_observe_result.v11002_002_2min_wind_speed = symbol_process(tempList.at(8));
		temp_observe_result.v11202_010_10min_wind_direction = symbol_process(tempList.at(9));
		temp_observe_result.v11042_010_10min_wind_speed = symbol_process(tempList.at(10));

		temp_observe_result.v11202_1hour_10min_max_wind_direction = symbol_process(tempList.at(11));
		temp_observe_result.v11042_1hour_10min_max_wind_speed = symbol_process(tempList.at(12));
		temp_observe_result.v11042_752_1hour_max_wind_time = symbol_process(tempList.at(13));

		temp_observe_result.v11001_moment_wind_direction = symbol_process(tempList.at(14));
		temp_observe_result.v11002_moment_wind_speed = symbol_process(tempList.at(15));

		temp_observe_result.v11043_1hour_huge_wind_direction = symbol_process(tempList.at(16));
		temp_observe_result.v11041_1hour_huge_wind_speed = symbol_process(tempList.at(17));
		temp_observe_result.v11041_752_1hour_huge_wind_time = symbol_process(tempList.at(18));

		temp_observe_result.v13019_1hour_Precipitation = symbol_process(tempList.at(19));

		temp_observe_result.v12001_temperature = symbol_process(tempList.at(20));
		temp_observe_result.v12211_1hour_max_temperature = symbol_process(tempList.at(21));
		temp_observe_result.v12211_752_1hour_max_temperature_time = symbol_process(tempList.at(22));
		temp_observe_result.v12212_1hour_min_temperature = symbol_process(tempList.at(23));
		temp_observe_result.v12212_752_1hour_min_temperature_time = symbol_process(tempList.at(24));

		temp_observe_result.v13003_relative_humidity = symbol_process(tempList.at(25));
		temp_observe_result.v13007_min_relative_humidity = symbol_process(tempList.at(26));
		temp_observe_result.v13007_752_min_relative_humidity_time = symbol_process(tempList.at(27));

		temp_observe_result.v13004_water_pressure = symbol_process(tempList.at(28));

		temp_observe_result.v12003_point_temperature = symbol_process(tempList.at(29));
		temp_observe_result.v10004_air_pressure = symbol_process(tempList.at(30));
		temp_observe_result.v10201_1hour_max_air_pressure = symbol_process(tempList.at(31));
		temp_observe_result.v10201_752_1hour_max_air_pressure_time = symbol_process(tempList.at(32));
		temp_observe_result.v10202_1hour_min_air_pressure = symbol_process(tempList.at(33));
		temp_observe_result.v10202_752_1hour_min_air_pressure_time = symbol_process(tempList.at(34));

		temp_observe_result.v12061_002_grass_temperature = symbol_process(tempList.at(35));
		temp_observe_result.v12213_002_max_grass_temperature = symbol_process(tempList.at(36));
		temp_observe_result.v12213_002_752_max_grass_temperature_time = symbol_process(tempList.at(37));
		temp_observe_result.v12214_002_min_grass_temperature = symbol_process(tempList.at(38));
		temp_observe_result.v12214_002_752_min_grass_temperature_time = symbol_process(tempList.at(39));

		temp_observe_result.v12061_001_ground_temperature = symbol_process(tempList.at(40));
		temp_observe_result.v12213_001_1hour_max_ground_temperature = symbol_process(tempList.at(41));
		temp_observe_result.v12213_001_752_1hour_max_ground_temperature_time = symbol_process(tempList.at(42));
		temp_observe_result.v12214_001_1hour_min_ground_temperature = symbol_process(tempList.at(43));
		temp_observe_result.v12214_001_752_1hour_min_ground_temperature_time = symbol_process(tempList.at(44));

		temp_observe_result.v12030_005_5cm_ground_temperature = symbol_process(tempList.at(45));
		temp_observe_result.v12030_010_10cm_ground_temperature = symbol_process(tempList.at(46));
		temp_observe_result.v12030_015_15cm_ground_temperature = symbol_process(tempList.at(47));
		temp_observe_result.v12030_020_20cm_ground_temperature = symbol_process(tempList.at(48));
		temp_observe_result.v12030_040_40cm_ground_temperature = symbol_process(tempList.at(49));
		temp_observe_result.v12030_080_80cm_ground_temperature = symbol_process(tempList.at(50));
		temp_observe_result.v12030_160_160cm_ground_temperature = symbol_process(tempList.at(51));
		temp_observe_result.v12030_320_320cm_ground_temperature = symbol_process(tempList.at(52));

		temp_observe_result.v13031_1hour_evaporation = symbol_process(tempList.at(53));
		temp_observe_result.v10005_sea_pressure = symbol_process(tempList.at(54));
		temp_observe_result.v20001_052_001_visibility = symbol_process(tempList.at(55));
		temp_observe_result.v20001_006_1hour_min_visibility = symbol_process(tempList.at(56));
		temp_observe_result.v20001_006_752_1hour_min_visibility_time = symbol_process(tempList.at(57));

		m_observe_result.append(temp_observe_result);
	}
}

int read_AI::symbol_process( QString str)
{
	if (str.contains("\/"))
	{
		return missing_data;
	}
	else
	{
		return str.toInt();
	}
}
