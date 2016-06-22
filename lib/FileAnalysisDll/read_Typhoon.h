#pragma once
#include <QString>
#include <QStringList>
#include <QList>
enum typhoon_level
{
	TD = 1,//热带低压
	TS,//热带风暴
	STS,//强热带风暴
	TY,//台风
	STY,//强台风
	SPUER_TY,//超强台风
};
enum typhoon_objective_forecast_symbol
{
	TMBJ_1 = 1,//国家气象中心，国家气象中心台风数值预报模式
	SHTM,//上海台风研究所，上海台风数值预报模式
	WIPS,//上海台风研究所，西北太平洋台风强度统计预报
	STC,//上海台风研究所，西北太平洋台风路径客观集成预报
	GRAPES_TCM,//上海台风研究所，GRAPES_TCM（SGTM）台风数值预报
	TCSP,//上海台风研究所，西北太平洋台风强度气候持续性预报
	PLSC,//上海台风研究所，西北太平洋台风强度偏最小二乘气候持续预报
	JSPC,//江苏省气象台，概率园法台风路径决策预报
	GZTM,//广州热带海洋气象研究所，中国南海台风模式
	ANNGA,//广西区气象局，南海区域台风路径（强度）遗传神经网络预报
	LNTCM,//沈阳大气环境研究所，辽宁台风数值预报模式
};
struct typhoon_tital //报头
{
	QString foreact_tital;//预报形式
	int broadcast_time;//预报时间
};

struct typhoon_live //台风中心位置和强度实况
{
	typhoon_level ty_level;
	QString typhoon_name;//台风名称
	int typhoon_number;//国家气象中心台风编号
	int typhoon_international_number;//台风国际编号
	int Live_year;//台风实况日期
	int Live_month;
	int Live_day;
	int Live_hour;
	int Live_minute;
	//00HR
	int typhoon_Latitude;//台风纬度
	int typhoon_Longitude;//台风经度
	int central_pressure;//中心气压，单位hPa
	int central_Wind_velocity;//中心最大风速,单位m/s
	//50kts
	int typhoon_50kts;//50海里/小时大风圈半径
	//30kts
	int typhoon_30kts;//30海里/小时大风圈半径
};

struct typhoon_part//预报时间段
{
	QString forecast_time;//预报时间
	int ty_dircetion;//台风方向
	int ty_speed;//台风速度
};

struct typhoon_point//预报时间点
{
	QString forecast_time;//预报的时间，如P-12HR,P+12HP,P+24HR
	int forecast_Latitude;//这个时间下的纬度
	int forecast_Longitude;//这个时间下的经度
	int forecast_pressure;//这个时间下的气压
	int forecast_speed;//这个时间下的速度
};

struct typhoon_landed
{
	QString landed_location;//登陆地点
	int typhoon_landed_time;//登陆时间
	int typhoon_landed_speed;//登陆速度
};

struct typhoon_forecast
{
	typhoon_tital typhoon_forecast_tital;
	typhoon_live typhoon_forecast_live;
	typhoon_part typhoon_forecast_part;
	QList<typhoon_point> typhoon_forecast_point;
};
class read_typhoon
{
public:
	read_typhoon(void);
	~read_typhoon(void);

	void start_typhoon(QString fileName);
	QList<typhoon_forecast> Get_typhoon_Data(){return Vec_typhoon_forecast;}

private:
	int livemonth;
	typhoon_forecast m_typhoon_forecast;

	typhoon_tital m_typhoon_tital;
	typhoon_live m_typhoon_live;
	QList<typhoon_point> Vec_typhoon_forecast_point;
	QList<typhoon_forecast> Vec_typhoon_forecast;
	bool read_first_paragraph(QStringList analyes_message);
	bool read_second_paragraph(QStringList analyes_message);
	//bool read_third_paragraph(QStringList analyes_message);
	//bool read_fourth_paragraph(QStringList analyes_message);
	//bool read_fivth_paragraph(QStringList analyes_message);
	bool read_sixth_paragraph(QStringList analyes_message);
	//bool read_seventh_paragraph(QStringList analyes_message);
	int symbol_replace(QString str);

	bool typhoonLevelComfirm(QString tylvl,int &nlocation);
};

