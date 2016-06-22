#pragma once
#include <QString>
#include <QStringList>
#include <QList>
enum typhoon_level
{
	TD = 1,//�ȴ���ѹ
	TS,//�ȴ��籩
	STS,//ǿ�ȴ��籩
	TY,//̨��
	STY,//ǿ̨��
	SPUER_TY,//��ǿ̨��
};
enum typhoon_objective_forecast_symbol
{
	TMBJ_1 = 1,//�����������ģ�������������̨����ֵԤ��ģʽ
	SHTM,//�Ϻ�̨���о������Ϻ�̨����ֵԤ��ģʽ
	WIPS,//�Ϻ�̨���о���������̫ƽ��̨��ǿ��ͳ��Ԥ��
	STC,//�Ϻ�̨���о���������̫ƽ��̨��·���͹ۼ���Ԥ��
	GRAPES_TCM,//�Ϻ�̨���о�����GRAPES_TCM��SGTM��̨����ֵԤ��
	TCSP,//�Ϻ�̨���о���������̫ƽ��̨��ǿ�����������Ԥ��
	PLSC,//�Ϻ�̨���о���������̫ƽ��̨��ǿ��ƫ��С�����������Ԥ��
	JSPC,//����ʡ����̨������԰��̨��·������Ԥ��
	GZTM,//�����ȴ����������о������й��Ϻ�̨��ģʽ
	ANNGA,//����������֣��Ϻ�����̨��·����ǿ�ȣ��Ŵ�������Ԥ��
	LNTCM,//�������������о���������̨����ֵԤ��ģʽ
};
struct typhoon_tital //��ͷ
{
	QString foreact_tital;//Ԥ����ʽ
	int broadcast_time;//Ԥ��ʱ��
};

struct typhoon_live //̨������λ�ú�ǿ��ʵ��
{
	typhoon_level ty_level;
	QString typhoon_name;//̨������
	int typhoon_number;//������������̨����
	int typhoon_international_number;//̨����ʱ��
	int Live_year;//̨��ʵ������
	int Live_month;
	int Live_day;
	int Live_hour;
	int Live_minute;
	//00HR
	int typhoon_Latitude;//̨��γ��
	int typhoon_Longitude;//̨�羭��
	int central_pressure;//������ѹ����λhPa
	int central_Wind_velocity;//����������,��λm/s
	//50kts
	int typhoon_50kts;//50����/Сʱ���Ȧ�뾶
	//30kts
	int typhoon_30kts;//30����/Сʱ���Ȧ�뾶
};

struct typhoon_part//Ԥ��ʱ���
{
	QString forecast_time;//Ԥ��ʱ��
	int ty_dircetion;//̨�緽��
	int ty_speed;//̨���ٶ�
};

struct typhoon_point//Ԥ��ʱ���
{
	QString forecast_time;//Ԥ����ʱ�䣬��P-12HR,P+12HP,P+24HR
	int forecast_Latitude;//���ʱ���µ�γ��
	int forecast_Longitude;//���ʱ���µľ���
	int forecast_pressure;//���ʱ���µ���ѹ
	int forecast_speed;//���ʱ���µ��ٶ�
};

struct typhoon_landed
{
	QString landed_location;//��½�ص�
	int typhoon_landed_time;//��½ʱ��
	int typhoon_landed_speed;//��½�ٶ�
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

