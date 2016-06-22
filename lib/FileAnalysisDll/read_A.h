#pragma once
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QDateTime>

//struct observe_result
//{
//	QString v01000_sta_Num;
//	int v04001_observe_year;
//	int v04002_observe_month;
//	int v04003_observe_day;
//	int v04004_observe_hour;
//	int v04005_observe_minute;
//	int v04006_observe_second;
//	QDateTime observe_time;
//	int v05001_sta_Latitude;
//	int v06001_sta_Longitude;
//	int v07001_sta_high;//����10����¼
//	int v07002_sensor_high;//����10����¼
//	int v02001_observe_mode;
//
//	int v11001_002_2min_wind_direction[24];
//	int v11002_002_2min_wind_speed[24];
//	int v11202_010_10min_wind_direction[24];
//	int v11042_010_10min_wind_speed[24];
//	int v11202_1hour_10min_max_wind_direction;
//	int v11042_1hour_10min_max_wind_speed;
//	int v11042_752_1hour_max_wind_time;
//	int v11001_moment_wind_direction;
//	int v11002_moment_wind_speed;
//	int v11043_1hour_huge_wind_direction;
//	int v11041_1hour_huge_wind_speed;
//	int v11041_752_1hour_huge_wind_time;
//
//	int v13019_1hour_Precipitation;
//
//	int v12001_temperature[24];
//	int v12211_1hour_max_temperature;
//	int v12211_752_1hour_max_temperature_time;
//	int v12212_1hour_min_temperature;
//	int v12212_752_1hour_min_temperature_time;
//	int V12016_24hour_max_temperature;
//	int V12017_24hour_min_temperayure;
//
//	int v13003_relative_humidity;//����10��
//	int v13007_min_relative_humidity;
//	int v13007_752_min_relative_humidity_time;
//
//	int v13004_water_pressure;
//
//	int v12003_point_temperature;//����10��
//
//	int v10004_air_pressure;//����10��
//	int v10201_1hour_max_air_pressure;
//	int v10201_752_1hour_max_air_pressure_time;
//	int v10202_1hour_min_air_pressure;
//	int v10202_752_1hour_min_air_pressure_time;
//
//	int v12061_002_grass_temperature;
//	int v12213_002_max_grass_temperature;
//	int v12213_002_752_max_grass_temperature_time;
//	int v12214_002_min_grass_temperature;
//	int v12214_002_752_min_grass_temperature_time;
//
//	int v12061_001_ground_temperature;
//	int v12213_001_1hour_max_ground_temperature;
//	int v12213_001_752_1hour_max_ground_temperature_time;
//	int v12214_001_1hour_min_ground_temperature;
//	int v12214_001_752_1hour_min_ground_temperature_time;
//
//	int v12030_005_5cm_ground_temperature;
//	int v12030_010_10cm_ground_temperature;
//	int v12030_015_15cm_ground_temperature;
//	int v12030_020_20cm_ground_temperature;
//	int v12030_040_40cm_ground_temperature;
//	int v12030_080_80cm_ground_temperature;
//	int v12030_160_160cm_ground_temperature;
//	int v12030_320_320cm_ground_temperature;
//
//	int v13031_1hour_evaporation;
//	int v10005_sea_pressure;
//
//	int v20001_052_001_visibility;
//	int v20001_006_1hour_min_visibility;
//	int v20001_006_752_1hour_min_visibility_time;
//};

struct base_info_filedata
{
	QString v01000_sta_Num;
	int v04001_observe_year;
	int v04002_observe_month;
	int v05001_sta_Latitude;
	int v06001_sta_Longitude;
	int v07001_sta_high;//����10����¼
	int v07002_sensor_high;//����10����¼
	int v02001_observe_mode;
};

struct IImin_wind_filedata
{
	int v11001_002_2min_wind_direction[24];
	int v11002_002_2min_wind_speed[24];
};

struct VImin_wind_filedata
{
	int v11202_010_10min_wind_direction[24];
	int v11042_010_10min_wind_speed[24];
};

struct max_huge_wind_filedata
{
	int V01000;// '��վ��
	int	V04001;// '��
	int	V04002;// '��
	int	V04003;// '��      
	int v11202_1hour_10min_max_wind_direction;
	int v11042_1hour_10min_max_wind_speed;
	int v11042_752_1hour_max_wind_time;
	int v11043_1hour_huge_wind_direction;
	int v11041_1hour_huge_wind_speed;
	int v11041_752_1hour_huge_wind_time;
};

struct hour_temperature_filedata
{
	int v12001_temperature[24];
};

struct maxmin_temperature_filedata
{
	int V12052_max_temperature;               //���������                     
	int V12052_001_max_temperature_time;      //��������³���ʱ��             
	int V12053_min_temperature;               //���������                     
	int V12053_001_min_temperature_time;      //��������³���ʱ��   
};

struct hour_rain_filedata
{
	int v13019_1hour_Precipitation[24];
};

struct rain_filedata
{
	float daily_20to8_Precipitation;//20��8ʱ��ˮ��  v13203
	float daily_8to20_Precipitation;//8��20ʱ��ˮ��  v13204
	float daily_20to20_Precipitation;//20��20ʱ��ˮ��  v13201
};

struct link_rain_filedata
{
	int daily_20to8_t_Precipitation;
	QString date;
	int month_rain;
};

struct hour_sunshine_filedata
{
	int hour_sunshine[24];
};
struct hour_pressure_filedata
{
	int hour_pressure[24];
};
struct sunshine_filedata
{
	float daily_sunshine_count;//����ʱ��  v14032
	float daily_sun_rise;//�ճ�ʱ��  v04211
	float daily_sun_set;//����ʱ��  v04212
};

struct hour_data
{
	QString v01000_sta_Num;
	int v04001_observe_year;
	int v04002_observe_month;
	int v04003_observe_day;
	int v04004_observe_hour;
	int v05001_sta_Latitude;
	int v06001_sta_Longitude;
	int v07001_sta_high;//����10����¼
	int v07002_sensor_high;//����10����¼
	int v02001_observe_mode;
	int v11001_002_2min_wind_direction;
	int v11002_002_2min_wind_speed;
	int v11202_010_10min_wind_direction;
	int v11042_010_10min_wind_speed;
	int v12001_temperature;
	int v13019_1hour_Precipitation;
	int hour_sunshine;
	int v10004_pressure;
};

class read_A
{
public:
	read_A(void);
	~read_A(void);
	bool analyzeelement();
	bool start_A(QString);

	QList<hour_data>Get_A_Data(){return m_hour_data;}
	QList<max_huge_wind_filedata>Get_A_wind_Data(){return m_max_huge_wind;}
	//QList<dbStorage> GetdbStorage(){return m_dbStorage;}
private:
	//QList<dbStorage> m_dbStorage;//�����õ�����
	int GetMon_Nums(int ,int);//ÿ�µ�������31��30��29��28��
	float symbol_analyise(QString);//��ˮ����������滻
	int symbol_wind(QString);//������������滻
	void analyze_tempreature(QStringList ,char);//�����¶ȣ����з�λʽ����ÿʱ���¶Ⱥ������С����ͺ�Ǳ��¼
	void analyze_rain(QStringList ,char);//������ˮ
	void analyze_sunshine(QStringList ,char);//�������գ����з�λʽ���һλ���������գ�����ֻ�����һ��
	void analyze_wind(QStringList ,char);//������
	void analyze_pressure(QStringList ,char);//������ѹ
	QVector<QStringList> m_filedata;//���ļ��������İ�Ҫ�طֵ����ݣ�һ��Ҫ��һ��LIST

	base_info_filedata base_info;//A �ļ�������Ϣ

	QList<hour_temperature_filedata> m_hour_temperature;//Сʱ�¶�
	QList<maxmin_temperature_filedata> m_maxmin_temperature;//�������¶�

	QList<IImin_wind_filedata> m_2min_wind;//2���ӷ��ٷ���
	QList<VImin_wind_filedata> m_10min_wind;//10���ӷ��ٷ���
	QList<max_huge_wind_filedata> m_max_huge_wind;//��󼫴�缰����ʱ��

	QList<rain_filedata> m_rain;//��ʱ��ˮ��20-8 8-20 20-20
	QList<hour_rain_filedata> m_hour_rain;//�Լ�Сʱ��ˮ��
	QList<link_rain_filedata> m_link_rain;//��ˮ��������ֵ
	QList<hour_pressure_filedata> m_hour_pressure;//Сʱ��ѹ
	QList<hour_sunshine_filedata> m_hour_sunshine;//����ʱ��
	QList<sunshine_filedata> m_sunshine;//������ʱ�����ճ�ʱ�䡢����ʱ��
	QList<hour_data> m_hour_data;//Сʱ����
	int Mon_Nums;//��������A�ļ�������
};

