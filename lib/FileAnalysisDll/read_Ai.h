#pragma once
#include <QString>
#include <QDateTime>
#include <QStringList>
#include <QVector>
struct observe_result
{
	int v01000_sta_Num;
	int v04001_observe_year;
	int v04002_observe_month;
	int v04003_observe_day;
	int v04004_observe_hour;
	int v04005_observe_minute;
	int v04006_observe_second;
	QDateTime observe_time;
	int v05001_sta_Latitude;
	int v06001_sta_Longitude;
	int v07001_sta_high;//À©´ó10±¶¼ÇÂ¼
	int v07002_sensor_high;//À©´ó10±¶¼ÇÂ¼
	int v02001_observe_mode;

	int v11001_002_2min_wind_direction;
	int v11002_002_2min_wind_speed;
	int v11202_010_10min_wind_direction;
	int v11042_010_10min_wind_speed;
	int v11202_1hour_10min_max_wind_direction;
	int v11042_1hour_10min_max_wind_speed;
	int v11042_752_1hour_max_wind_time;
	int v11001_moment_wind_direction;
	int v11002_moment_wind_speed;
	int v11043_1hour_huge_wind_direction;
	int v11041_1hour_huge_wind_speed;
	int v11041_752_1hour_huge_wind_time;

	int v13019_1hour_Precipitation;

	int v12001_temperature;
	int v12211_1hour_max_temperature;
	int v12211_752_1hour_max_temperature_time;
	int v12212_1hour_min_temperature;
	int v12212_752_1hour_min_temperature_time;

	int v13003_relative_humidity;//À©´ó10±¶
	int v13007_min_relative_humidity;
	int v13007_752_min_relative_humidity_time;

	int v13004_water_pressure;

	int v12003_point_temperature;//À©´ó10±¶

	int v10004_air_pressure;//À©´ó10±¶
	int v10201_1hour_max_air_pressure;
	int v10201_752_1hour_max_air_pressure_time;
	int v10202_1hour_min_air_pressure;
	int v10202_752_1hour_min_air_pressure_time;

	int v12061_002_grass_temperature;
	int v12213_002_max_grass_temperature;
	int v12213_002_752_max_grass_temperature_time;
	int v12214_002_min_grass_temperature;
	int v12214_002_752_min_grass_temperature_time;

	int v12061_001_ground_temperature;
	int v12213_001_1hour_max_ground_temperature;
	int v12213_001_752_1hour_max_ground_temperature_time;
	int v12214_001_1hour_min_ground_temperature;
	int v12214_001_752_1hour_min_ground_temperature_time;

	int v12030_005_5cm_ground_temperature;
	int v12030_010_10cm_ground_temperature;
	int v12030_015_15cm_ground_temperature;
	int v12030_020_20cm_ground_temperature;
	int v12030_040_40cm_ground_temperature;
	int v12030_080_80cm_ground_temperature;
	int v12030_160_160cm_ground_temperature;
	int v12030_320_320cm_ground_temperature;

	int v13031_1hour_evaporation;
	int v10005_sea_pressure;

	int v20001_052_001_visibility;
	int v20001_006_1hour_min_visibility;
	int v20001_006_752_1hour_min_visibility_time;
};
class read_AI
{
public:
	read_AI(void);
	~read_AI(void);
	void start_AI(QString fileName);
	void analysis_AI(QStringList);
	QList<observe_result> Get_AI_Data(){return m_observe_result;}
private:
	QList<observe_result> m_observe_result;
	int symbol_process(QString);
};

