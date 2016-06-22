#pragma once
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QDateTime>
//气压(P)
const unsigned short P0 = 6;
const unsigned short P9 = 5;
const unsigned short PA = 26;
const unsigned short PB = 28;
//气温(T)
const unsigned short T0 = 6;
const unsigned short T9 = 5;
const unsigned short TA = 64;
const unsigned short TB = 28;
//湿球温度（I）、露点温度（Td）
const unsigned short I2 = 4;
const unsigned short I7 = 4;
const unsigned short I8 = 3;
const unsigned short IB = 24;
//水汽压（E）
const unsigned short E0 = 4;
const unsigned short E9 = 3;
const unsigned short EA = 3;
//相对湿度（U）
const unsigned short U0 = 5;
const unsigned short U2 = 4;
const unsigned short U7 = 4;
const unsigned short U9 = 3;
const unsigned short UA = 25;
const unsigned short UB = 26;
//云量（N）
const unsigned short N0 = 4;
const unsigned short N9 = 3;
const unsigned short NA = 24;
//云高（H）
const unsigned short H0 = 4;
const unsigned short H9 = 3;
const unsigned short HB = 24;
//云状（C）
const unsigned short C0 = 4;
const unsigned short C9 = 3;
const unsigned short CA = 4;
//能见度（V）
const unsigned short V0 = 4;
const unsigned short V7 = 3;
const unsigned short V8 = 4;
const unsigned short V9 = 3;
const unsigned short VA = 24;
//降水量（R）
const unsigned short R0 = 3;
const unsigned short R2 = 3;
const unsigned short R6 = 3;

//....

typedef enum _Evaluation_elements
{
	atmospheric_pressure = 0,               //气压(P)
	air_temperature,						//气温(T)
	Wet_bulb_temperature,					//湿球温度（I）、露点温度（Td）
	Water_Pressure,							//水汽压（E）
	Relative_humidity,						//相对湿度（U） 
	Cloudiness,								//云量（N）
	Cloud_height,							//云高（H）
	Cloud,									//云状（C）
	Visibility,								//能见度（V）
	Precipitation,							//降水量（R）
	Weather_phenomena,						//天气现象（W）
	Evaporation,							//蒸发量（L）
	accumulated_snow,						//积雪（Z）
	Wire_icing,								//电线积冰（G）
	wind,									//风（F）
	Shallow_geothermal,						//浅层地温（D）
	Ground_Temperature,						//深层地温（K）
	Sunshine,								//日照（S）
	Grass_surface_temperature,				//草面（雪面）温度（B）
} Evaluation_ele;

struct BaseInfo_A0
{
	QString stationID;//站点编号          v01000
	QString latlonitude; //经纬度 
	QString observation; //观测场拔海高度 m
	QString senson; //气压传感器拔海高度 m
	QString year; //年
	QString month; //月
	//A文件结构体
	//QString latitude;//纬度
	//QString longitude;//经度
	//QString windheight;//风速感应器距地（平台）高度
	//QString groundheight;//观测平台距地高度
	//QString method;//观测方式和测站类别
	//QString identification;//观测项目标识
	//QString qc;//质量控制指示码
};

/*struct BaseInfo_A
{
	QString stationID;//区站号 
	QString latitude;//纬度
	QString longitude;//经度
	QString observation;//观测场拔海高度
	QString senson;//气压感应器拔海高度
	QString windheight;//风速感应器距地（平台）高度
	QString groundheight;//观测平台距地高度
	QString method;//观测方式和测站类别
	QString identification;//观测项目标识
	QString qc;//质量控制指示码
	QString year; //年
	QString month; //月
};*/

struct temperature_fileData
{
	float daily_average;//平均值           v12001
	float daily_maximum;//最大值，没有或缺测记999         v12052
	float daily_maximum_time;//最大值出现时间，没有记999  v12052_001
	float daily_minimum;//最小值，没有或缺测记999    v12053
	float daily_minimum_time;//最小值出现时间，没有记999  v12053_001
	/*Add by zhaoxx in 20130305*/
	float daily_wet_temperature;//湿球温度,没有记999 V12002
	float daily_bulb_temperature;//露点温度,没有记999 V12003
};
struct rain_fileData
{
	float daily_20to8_Precipitation;//20至8时降水量  v13203
	float daily_8to20_Precipitation;//8至20时降水量  v13204
	float daily_20to20_Precipitation;//20至20时降水量  v13201
};
struct sunshine_fileData
{
	float daily_sunshine_count;//日照时数  v14032
	float daily_sun_rise;//日出时间  v04211
	float daily_sun_set;//日落时间  v04212
};

struct vaporPressure_fileData
{
	float vaporPressure;//水汽压 V13004
};

struct relativhumidity_fileData
{
	float relativhumidity;//平均相对湿度 V13003
	float relativhumidity_minnum;//最小相对湿度 V13007
	float relativhumidity_minnum_time;//最小相对湿度出现时间 V13007_001
};

struct cloudy_fileData
{
	float totalcloudy;//总云量 V20010
	float lowcloudy;//低云量 V20051
};

struct visibility_fileData
{
	float visibility;//能见度 V20001
};

struct wind_fileData
{
	float average_wind;//平均风速 V11002
	float wind_max;//最大风速 V11042
	int wind_max_direct;//最大风速风向 V11212
	float wind_extreme;//极大风速 V11041
	int wind_extreme_direct;//极大风速风向 V11043
};

struct nothing_fileData
{
	float daily_8to8_rain;//8-8降水量  v13205
	float daily_8to8_temperature;//8-8平均温度   v12001_808
	float daily_8to8_maximum_temp;//8-8最大温度   v12016
	float daily_8to8_minmimu_temp;//8-8最小温度   v12017
};

struct dbStorage
{
	QDateTime dbStorage_dataTime;
	BaseInfo_A0 dbStorage_baseInfo;
	temperature_fileData dbStorage_temperature_fileData;
	rain_fileData dbStorage_rain_fileData;
	sunshine_fileData dbStorage_sunshine_fileData;
	relativhumidity_fileData dbStorage_relativhumidity_fileData;
	vaporPressure_fileData dbStorage_vaporPressure_fileData;
	cloudy_fileData dbStorage_cloudy_fileData;
	visibility_fileData dbStorage_visibility_fileData;
	wind_fileData dbStorage_wind_fileData;
	nothing_fileData dbStorage_nothing_fileData;
};


class read_a0
{
public:
	read_a0(void);
	~read_a0(void);
	bool analyzeelement();
	bool start_A0(QString);
	QList<dbStorage> Get_A0_Data(){return m_dbStorage;};
private:
	QList<dbStorage> m_dbStorage;//解析好的数据
	int GetMon_Nums(int ,int);//每月的天数，31，30，29，28天
	float symbol_analyise(QString);//降水量特殊符号替换
	void analyze_tempreature(QStringList ,char);//解析温度，所有方位式都有每时次温度和最大最小，求和后非别记录
	void analyze_rain(QStringList ,char);//解析降水
	void analyze_sunshine(QStringList ,char);//解析日照，所有方位式最后一位都是总日照，所以只记随后一个
	void analyze_vaporPressure(QStringList ,char);//解析水汽压 求平均水汽压
	void analyze_relativhumidity(QStringList ,char);//解析相对湿度 求平均相对湿度
	void analyze_cloudy(QStringList ,char);//解析云量 求平均总云量、平均低云量
	void analyze_visibility(QStringList ,char);//解析能见度 求平均能见度
	void analyze_wind(QStringList ,char);//解析风
	int symbol_wind(QString);//风向特殊符号替换
	QVector<QStringList> m_filedata;//从文件读出来的按要素分的数据，一个要素一个LIST
	BaseInfo_A0 m_bashinfo;//文件头，只有一个
	int Mon_Nums;//解析的月A0文件的天数
	QList<temperature_fileData> m_temperature_fileData;
	QList<rain_fileData> m_rain_fileData;
	QList<sunshine_fileData> m_sunshine_fileData;
	QList<vaporPressure_fileData> m_vaporPressure_fileData;
	QList<relativhumidity_fileData> m_relativhumidity_fileData;
	QList<cloudy_fileData> m_cloudy_fileData;
	QList<visibility_fileData> m_visibility_fileData;
	QList<wind_fileData> m_wind_fileData;
};

