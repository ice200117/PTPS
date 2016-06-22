#pragma once
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QDateTime>
//��ѹ(P)
const unsigned short P0 = 6;
const unsigned short P9 = 5;
const unsigned short PA = 26;
const unsigned short PB = 28;
//����(T)
const unsigned short T0 = 6;
const unsigned short T9 = 5;
const unsigned short TA = 64;
const unsigned short TB = 28;
//ʪ���¶ȣ�I����¶���¶ȣ�Td��
const unsigned short I2 = 4;
const unsigned short I7 = 4;
const unsigned short I8 = 3;
const unsigned short IB = 24;
//ˮ��ѹ��E��
const unsigned short E0 = 4;
const unsigned short E9 = 3;
const unsigned short EA = 3;
//���ʪ�ȣ�U��
const unsigned short U0 = 5;
const unsigned short U2 = 4;
const unsigned short U7 = 4;
const unsigned short U9 = 3;
const unsigned short UA = 25;
const unsigned short UB = 26;
//������N��
const unsigned short N0 = 4;
const unsigned short N9 = 3;
const unsigned short NA = 24;
//�Ƹߣ�H��
const unsigned short H0 = 4;
const unsigned short H9 = 3;
const unsigned short HB = 24;
//��״��C��
const unsigned short C0 = 4;
const unsigned short C9 = 3;
const unsigned short CA = 4;
//�ܼ��ȣ�V��
const unsigned short V0 = 4;
const unsigned short V7 = 3;
const unsigned short V8 = 4;
const unsigned short V9 = 3;
const unsigned short VA = 24;
//��ˮ����R��
const unsigned short R0 = 3;
const unsigned short R2 = 3;
const unsigned short R6 = 3;

//....

typedef enum _Evaluation_elements
{
	atmospheric_pressure = 0,               //��ѹ(P)
	air_temperature,						//����(T)
	Wet_bulb_temperature,					//ʪ���¶ȣ�I����¶���¶ȣ�Td��
	Water_Pressure,							//ˮ��ѹ��E��
	Relative_humidity,						//���ʪ�ȣ�U�� 
	Cloudiness,								//������N��
	Cloud_height,							//�Ƹߣ�H��
	Cloud,									//��״��C��
	Visibility,								//�ܼ��ȣ�V��
	Precipitation,							//��ˮ����R��
	Weather_phenomena,						//��������W��
	Evaporation,							//��������L��
	accumulated_snow,						//��ѩ��Z��
	Wire_icing,								//���߻�����G��
	wind,									//�磨F��
	Shallow_geothermal,						//ǳ����£�D��
	Ground_Temperature,						//�����£�K��
	Sunshine,								//���գ�S��
	Grass_surface_temperature,				//���棨ѩ�棩�¶ȣ�B��
} Evaluation_ele;

struct BaseInfo_A0
{
	QString stationID;//վ����          v01000
	QString latlonitude; //��γ�� 
	QString observation; //�۲ⳡ�κ��߶� m
	QString senson; //��ѹ�������κ��߶� m
	QString year; //��
	QString month; //��
	//A�ļ��ṹ��
	//QString latitude;//γ��
	//QString longitude;//����
	//QString windheight;//���ٸ�Ӧ����أ�ƽ̨���߶�
	//QString groundheight;//�۲�ƽ̨��ظ߶�
	//QString method;//�۲ⷽʽ�Ͳ�վ���
	//QString identification;//�۲���Ŀ��ʶ
	//QString qc;//��������ָʾ��
};

/*struct BaseInfo_A
{
	QString stationID;//��վ�� 
	QString latitude;//γ��
	QString longitude;//����
	QString observation;//�۲ⳡ�κ��߶�
	QString senson;//��ѹ��Ӧ���κ��߶�
	QString windheight;//���ٸ�Ӧ����أ�ƽ̨���߶�
	QString groundheight;//�۲�ƽ̨��ظ߶�
	QString method;//�۲ⷽʽ�Ͳ�վ���
	QString identification;//�۲���Ŀ��ʶ
	QString qc;//��������ָʾ��
	QString year; //��
	QString month; //��
};*/

struct temperature_fileData
{
	float daily_average;//ƽ��ֵ           v12001
	float daily_maximum;//���ֵ��û�л�ȱ���999         v12052
	float daily_maximum_time;//���ֵ����ʱ�䣬û�м�999  v12052_001
	float daily_minimum;//��Сֵ��û�л�ȱ���999    v12053
	float daily_minimum_time;//��Сֵ����ʱ�䣬û�м�999  v12053_001
	/*Add by zhaoxx in 20130305*/
	float daily_wet_temperature;//ʪ���¶�,û�м�999 V12002
	float daily_bulb_temperature;//¶���¶�,û�м�999 V12003
};
struct rain_fileData
{
	float daily_20to8_Precipitation;//20��8ʱ��ˮ��  v13203
	float daily_8to20_Precipitation;//8��20ʱ��ˮ��  v13204
	float daily_20to20_Precipitation;//20��20ʱ��ˮ��  v13201
};
struct sunshine_fileData
{
	float daily_sunshine_count;//����ʱ��  v14032
	float daily_sun_rise;//�ճ�ʱ��  v04211
	float daily_sun_set;//����ʱ��  v04212
};

struct vaporPressure_fileData
{
	float vaporPressure;//ˮ��ѹ V13004
};

struct relativhumidity_fileData
{
	float relativhumidity;//ƽ�����ʪ�� V13003
	float relativhumidity_minnum;//��С���ʪ�� V13007
	float relativhumidity_minnum_time;//��С���ʪ�ȳ���ʱ�� V13007_001
};

struct cloudy_fileData
{
	float totalcloudy;//������ V20010
	float lowcloudy;//������ V20051
};

struct visibility_fileData
{
	float visibility;//�ܼ��� V20001
};

struct wind_fileData
{
	float average_wind;//ƽ������ V11002
	float wind_max;//������ V11042
	int wind_max_direct;//�����ٷ��� V11212
	float wind_extreme;//������� V11041
	int wind_extreme_direct;//������ٷ��� V11043
};

struct nothing_fileData
{
	float daily_8to8_rain;//8-8��ˮ��  v13205
	float daily_8to8_temperature;//8-8ƽ���¶�   v12001_808
	float daily_8to8_maximum_temp;//8-8����¶�   v12016
	float daily_8to8_minmimu_temp;//8-8��С�¶�   v12017
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
	QList<dbStorage> m_dbStorage;//�����õ�����
	int GetMon_Nums(int ,int);//ÿ�µ�������31��30��29��28��
	float symbol_analyise(QString);//��ˮ����������滻
	void analyze_tempreature(QStringList ,char);//�����¶ȣ����з�λʽ����ÿʱ���¶Ⱥ������С����ͺ�Ǳ��¼
	void analyze_rain(QStringList ,char);//������ˮ
	void analyze_sunshine(QStringList ,char);//�������գ����з�λʽ���һλ���������գ�����ֻ�����һ��
	void analyze_vaporPressure(QStringList ,char);//����ˮ��ѹ ��ƽ��ˮ��ѹ
	void analyze_relativhumidity(QStringList ,char);//�������ʪ�� ��ƽ�����ʪ��
	void analyze_cloudy(QStringList ,char);//�������� ��ƽ����������ƽ��������
	void analyze_visibility(QStringList ,char);//�����ܼ��� ��ƽ���ܼ���
	void analyze_wind(QStringList ,char);//������
	int symbol_wind(QString);//������������滻
	QVector<QStringList> m_filedata;//���ļ��������İ�Ҫ�طֵ����ݣ�һ��Ҫ��һ��LIST
	BaseInfo_A0 m_bashinfo;//�ļ�ͷ��ֻ��һ��
	int Mon_Nums;//��������A0�ļ�������
	QList<temperature_fileData> m_temperature_fileData;
	QList<rain_fileData> m_rain_fileData;
	QList<sunshine_fileData> m_sunshine_fileData;
	QList<vaporPressure_fileData> m_vaporPressure_fileData;
	QList<relativhumidity_fileData> m_relativhumidity_fileData;
	QList<cloudy_fileData> m_cloudy_fileData;
	QList<visibility_fileData> m_visibility_fileData;
	QList<wind_fileData> m_wind_fileData;
};

