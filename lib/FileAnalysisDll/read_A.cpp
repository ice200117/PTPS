#include "read_A.h"
#include <QDebug>
#include <QtCore/QCoreApplication>

read_A::read_A(void)
{
}


read_A::~read_A(void)
{
}

int read_A::GetMon_Nums( int dataYear,int dataMonth)
{
	int monnum = 0;
	if (dataMonth == 1||dataMonth == 3||dataMonth == 5||dataMonth == 7||dataMonth == 8||dataMonth == 10||dataMonth == 12)
	{
		monnum = 31;
	}
	else if (dataMonth == 4||dataMonth == 6||dataMonth == 9||dataMonth == 11)
	{
		monnum = 30;
	}
	else
	{
		if ((dataYear%4==0&&dataYear%100!=0)||(dataYear%400==0))
		{
			monnum = 29;//闰年
		}
		else
		{
			monnum = 28;//不是闰年
		}
	}
	return monnum;
}

bool read_A::start_A(QString fileName)
{
	int element_nums = 0;//文件中的要素个数
	QStringList temp_element_data;//每个要素的数据
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return false;//打开失败
	}
	QTextStream in(&file);
	QString file_line = in.readLine();
	QStringList file_tital_split = file_line.split(" ");
	int size = file_tital_split.size();
	qDebug("file_tital_split.size() = %d\n",file_tital_split.size());
	if (file_tital_split.size()!= 12)
	{
		qDebug("file message error\n");
		return false;//头信息缺失
	}
	//获得基本头信息
	base_info.v01000_sta_Num = file_tital_split.at(0);
	QString latitude = file_tital_split.at(1);
	base_info.v05001_sta_Latitude = latitude.remove(4,5).toInt();
	QString longitude = file_tital_split.at(2);
	base_info.v06001_sta_Longitude = longitude.remove(5,6).toInt();
	base_info.v07001_sta_high = file_tital_split.at(3).toInt(); 
	base_info.v07002_sensor_high = file_tital_split.at(4).toInt();
	base_info.v02001_observe_mode = file_tital_split.at(7).toInt();
	base_info.v04001_observe_year = file_tital_split.at(10).toInt();
	base_info.v04002_observe_month = file_tital_split.at(11).toInt();
	Mon_Nums = GetMon_Nums(base_info.v04001_observe_year,base_info.v04002_observe_month);
	while (!file_line.isNull()) //数据装载至m_filedata
	{
		file_line = in.readLine();
		temp_element_data.append(file_line);
		if (file_line.contains("="))
		{
			element_nums++;
			m_filedata.append(temp_element_data);
			temp_element_data.clear();
		}
	}
	for(int element_num=0;element_num<m_filedata.size();element_num++)//风要素处理
	{
		QStringList oridata = m_filedata.at(element_num);//单个要素
		QString str = oridata.at(0);
		QByteArray ba = str.toLatin1(); 
		char* ch = ba.data();
		if(!str.compare("FE") || !str.compare("FH") || !str.compare("FK") || !str.compare("FN"))
		{
			int sec=element_num+1;
			int thi=sec+1;
			if(sec == m_filedata.size())
			{
				break;
			}	
			QStringList adddata1 = m_filedata.at(sec);
			QStringList adddata2 = m_filedata.at(thi);
			oridata.append(adddata1);
			oridata.append(adddata2);
			m_filedata.append(oridata);
			m_filedata.remove(element_num);
			m_filedata.remove(sec);
			m_filedata.remove(thi);
		}	
	}
	for(int element_num=0;element_num<m_filedata.size();element_num++)//降水要素处理
	{
		QStringList oridata = m_filedata.at(element_num);//单个要素
		QString str = oridata.at(0);
		QByteArray ba = str.toLatin1(); 
		char* ch = ba.data();
		if(!str.compare("R0"))
		{
			int sec=element_num+1;
			if(sec == m_filedata.size())
			{
				break;
			}	
			QStringList adddata1 = m_filedata.at(sec);
			oridata.append(adddata1);
			m_filedata.append(oridata);
			m_filedata.remove(element_num);
			m_filedata.remove(sec);
		}	
	}
	for(int element_num=0;element_num<m_filedata.size();element_num++)//降水要素处理
	{
		QStringList oridata = m_filedata.at(element_num);//单个要素
		QString str = oridata.at(0);
		QByteArray ba = str.toLatin1(); 
		char* ch = ba.data();
		if(!str.compare("R6"))
		{
			int sec=element_num+1;
			int thi=sec+1;
			if(sec == m_filedata.size())
			{
				break;
			}	
			QStringList adddata1 = m_filedata.at(sec);
			QStringList adddata2 = m_filedata.at(thi);
			oridata.append(adddata1);
			oridata.append(adddata2);
			m_filedata.append(oridata);
			m_filedata.remove(element_num);
			m_filedata.remove(sec);
			m_filedata.remove(thi);	
		}	
	}
	qDebug("after m_filedata = %d",m_filedata.size());
	file.close();
	analyzeelement();
	return true;
}

bool read_A::analyzeelement()
{
	int element_num = 0,element_line_num = 0;//要素个数，每个要素的行数
	for (element_num ;element_num<m_filedata.size();element_num++)//按要素循环
	{	
		QStringList tempdata = m_filedata.at(element_num);//单个要素
		QChar element_type = tempdata.at(0).at(0).toLatin1();
		QString str = tempdata.at(0);
		if (str.length() == 1)
		{
			continue;//59133 O99
		}
		if (str.left(1).toInt() >= 'A' && str.left(1).toInt() <= 'Z')
		{
			continue;
		}
		QByteArray ba = str.toLatin1(); 
		char* ch = ba.data();
		switch(ch[0])
		{
		case 'P':
			{
				analyze_pressure(tempdata,ch[1]);
			}
		case 'T'://温度
			{
				analyze_tempreature(tempdata,ch[1]);
				break;
			}	
		case 'R'://降水
			{
				analyze_rain(tempdata,ch[1]);
				break;
			}
		case 'S'://日照
			{
				analyze_sunshine(tempdata,ch[1]);
				break;
			}
		case 'F'://风
			{
				analyze_wind(tempdata,ch[1]);
			}
		}
	}
	hour_data hour_data_file;
	for (int i = 0;i<Mon_Nums;i++)
	{
		for(int j=0;j<24;j++)
		{
			hour_data_file.v01000_sta_Num = base_info.v01000_sta_Num;
			hour_data_file.v02001_observe_mode = base_info.v02001_observe_mode;
			hour_data_file.v04001_observe_year = base_info.v04001_observe_year;
			hour_data_file.v04002_observe_month = base_info.v04002_observe_month;
			hour_data_file.v05001_sta_Latitude = base_info.v05001_sta_Latitude;
			hour_data_file.v06001_sta_Longitude = base_info.v06001_sta_Longitude;
			hour_data_file.v07001_sta_high = base_info.v07001_sta_high;
			hour_data_file.v07002_sensor_high = base_info.v07002_sensor_high;
			hour_data_file.v04003_observe_day = i+1;
			hour_data_file.v04004_observe_hour = j+1;
			hour_data_file.v12001_temperature = m_hour_temperature.at(i).v12001_temperature[j];
			hour_data_file.hour_sunshine = m_hour_sunshine.at(i).hour_sunshine[j];
			hour_data_file.v11001_002_2min_wind_direction = m_2min_wind.at(i).v11001_002_2min_wind_direction[j];
			hour_data_file.v11002_002_2min_wind_speed = m_2min_wind.at(i).v11002_002_2min_wind_speed[j];
			hour_data_file.v11202_010_10min_wind_direction = m_10min_wind.at(i).v11202_010_10min_wind_direction[j];
			hour_data_file.v11042_010_10min_wind_speed = m_10min_wind.at(i).v11042_010_10min_wind_speed[j];
			hour_data_file.v13019_1hour_Precipitation = m_hour_rain.at(i).v13019_1hour_Precipitation[j];
			hour_data_file.v10004_pressure = m_hour_pressure.at(i).hour_pressure[j];
			m_hour_data.append(hour_data_file);
		}
	}
	return true;
}

void read_A::analyze_tempreature(QStringList tempreature_data,char tempreature_mode)
{
	QVector<QStringList> tempreature_data_block;
	QStringList chu_tempreature_data;
	for(int i=1;i<tempreature_data.size();i++)
	{
		tempreature_data.replaceInStrings("=",".");
		chu_tempreature_data.append(tempreature_data.at(i));
		if(tempreature_data.at(i).contains('.'))
		{ 
			chu_tempreature_data.replaceInStrings(".","");
			tempreature_data_block.append(chu_tempreature_data);
			chu_tempreature_data.clear();
		}
	}
	if(tempreature_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			hour_temperature_filedata temp_hour_temperature;
			maxmin_temperature_filedata temp_maxmin_temperature;
			for(int i=0;i<24;i++)//初始化
			{
				temp_hour_temperature.v12001_temperature[i]=999999.0;
			}
			temp_maxmin_temperature.V12052_max_temperature = 999999.0;
			temp_maxmin_temperature.V12053_min_temperature = 999999.0;
			temp_maxmin_temperature.V12052_001_max_temperature_time = 999999.0;
			temp_maxmin_temperature.V12053_001_min_temperature_time =999999.0;
			m_hour_temperature.append(temp_hour_temperature);
			m_maxmin_temperature.append(temp_maxmin_temperature);
		}
		return;
	}
	switch (tempreature_mode)//每天要记录的时次数，按方位式不同，共有4个
	{
	case '0':
		{
			for(int m=0;m<tempreature_data_block.size();m++)
			{
				hour_temperature_filedata temp_hour_temperature;
				maxmin_temperature_filedata temp_maxmin_temperature;
				QStringList every_tempreature_data = tempreature_data_block.at(m);
				QString line_tempreature_data = every_tempreature_data.at(0);
				QStringList everyone_split = line_tempreature_data.split(" ");
				for(int p=0;p<everyone_split.size()-2;p++)
				{
					temp_hour_temperature.v12001_temperature[p] = everyone_split.at(p).toInt();
				}
				temp_maxmin_temperature.V12052_max_temperature = everyone_split.at(4).toInt();
				temp_maxmin_temperature.V12053_min_temperature = everyone_split.at(5).toInt();
				 
				 
				line_tempreature_data.clear();
			}
			break;
		}
	case '9':
		{
			for(int m=0;m<tempreature_data_block.size();m++)
			{
				hour_temperature_filedata temp_hour_temperature;
				maxmin_temperature_filedata temp_maxmin_temperature;
				QStringList every_tempreature_data = tempreature_data_block.at(m);
				QString line_tempreature_data = every_tempreature_data.at(0);
				QStringList everyone_split = line_tempreature_data.split(" ");
				for(int p=0;p<everyone_split.size()-2;p++)
				{
					temp_hour_temperature.v12001_temperature[p] = everyone_split.at(p).toInt();
				}
				temp_maxmin_temperature.V12052_max_temperature = everyone_split.at(3).toInt();
				temp_maxmin_temperature.V12053_min_temperature = everyone_split.at(4).toInt();
				m_hour_temperature.append(temp_hour_temperature);
				m_maxmin_temperature.append(temp_maxmin_temperature);
				line_tempreature_data.clear();
			}
			break;
		}
	case 'A':
		{
			for(int m=0;m<tempreature_data_block.size();m++)
			{
				hour_temperature_filedata temp_hour_temperature;
				maxmin_temperature_filedata temp_maxmin_temperature;
				QStringList every_tempreature_data = tempreature_data_block.at(m);
				int p=0;
				for(int n=0;n<2;n++)
				{
					QString line_tempreature_data = every_tempreature_data.at(n);
					QStringList everyone_split = line_tempreature_data.split(" ");
					if(n==0)
					{
						for(p;p<everyone_split.size();p++)
						{
							temp_hour_temperature.v12001_temperature[p] = everyone_split.at(p).toInt();
						}
					}
					else if(n==1)
					{
						for(int q=0;p<everyone_split.size()-4;q++,p++)
						{
							temp_hour_temperature.v12001_temperature[p] = everyone_split.at(q).toInt();
						}
						temp_maxmin_temperature.V12052_max_temperature = everyone_split.at(12).toInt();
						temp_maxmin_temperature.V12052_001_max_temperature_time = 999999.0;
						temp_maxmin_temperature.V12053_min_temperature = everyone_split.at(13).toInt();
						temp_maxmin_temperature.V12053_001_min_temperature_time =999999.0;
					}
					line_tempreature_data.clear();
				}
				m_hour_temperature.append(temp_hour_temperature);
				m_maxmin_temperature.append(temp_maxmin_temperature);
			}
			break;
		}
	case 'B':
		{
			for(int m=0;m<tempreature_data_block.size();m++)
			{
				hour_temperature_filedata temp_hour_temperature;
				maxmin_temperature_filedata temp_maxmin_temperature;
				QStringList every_tempreature_data = tempreature_data_block.at(m);
				int p=0;
				for(int n=0;n<2;n++)
				{
					QString line_tempreature_data = every_tempreature_data.at(n);
					QStringList everyone_split = line_tempreature_data.split(" ");					
					if(n==0)
					{	
						for(p;p<everyone_split.size();p++)
						{
							temp_hour_temperature.v12001_temperature[p] = everyone_split.at(p).toInt();
						}
					}
					else if(n==1)
					{
						for(int q=0;q<everyone_split.size()-4;q++,p++)
						{
							temp_hour_temperature.v12001_temperature[p] = everyone_split.at(q).toInt();
						}
						temp_maxmin_temperature.V12052_max_temperature = everyone_split.at(12).toInt();
						temp_maxmin_temperature.V12052_001_max_temperature_time = everyone_split.at(13).toInt();
						temp_maxmin_temperature.V12053_min_temperature = everyone_split.at(14).toInt();
						temp_maxmin_temperature.V12053_001_min_temperature_time = everyone_split.at(15).toInt();
					}
					line_tempreature_data.clear();
				}
				m_hour_temperature.append(temp_hour_temperature);
				m_maxmin_temperature.append(temp_maxmin_temperature);
			}
			break;
		}
	}
}

void read_A::analyze_sunshine(QStringList sunshine_data,char sunshine_mode)
{
	if (sunshine_data.size() == 1)//文件没有数据，返回缺测数据
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			hour_sunshine_filedata temp_hour_sunshine;
			sunshine_filedata temp_sunshine;
			for(int j=0;j<24;j++)//初始化
			{
				temp_hour_sunshine.hour_sunshine[j] = 999999.0;
			}
			temp_sunshine.daily_sunshine_count = 999999.0;
			temp_sunshine.daily_sun_rise = 999999.0;
			temp_sunshine.daily_sun_set = 999999.0;
			m_sunshine.append(temp_sunshine);
			m_hour_sunshine.append(temp_hour_sunshine);
		}
		return;
	}
	switch (sunshine_mode)//每天要记录的时次数，按方位式不同，共有3个
	{
	case '0':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				sunshine_filedata temp_sunshine;
				sunshine_data.replaceInStrings("=","");
				temp_sunshine.daily_sunshine_count = sunshine_data.at(i).toInt();
				m_sunshine.append(temp_sunshine);
			}
			break;
		}
	case '2':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				hour_sunshine_filedata temp_hour_sunshine;
				sunshine_filedata temp_sunshine;
				sunshine_data.replaceInStrings("=","");
				QString line_sunshine = sunshine_data.at(i);
				QStringList everyone_split = line_sunshine.split(" ");
				for(int j=0;j<18;j++)
				{
					temp_hour_sunshine.hour_sunshine[j] = everyone_split.at(j).toInt();
				}
				temp_sunshine.daily_sunshine_count = everyone_split.at(18).toInt();
				m_sunshine.append(temp_sunshine);
				m_hour_sunshine.append(temp_hour_sunshine);
			}
			break;
		}
	case 'A':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				hour_sunshine_filedata temp_hour_sunshine;
				sunshine_filedata temp_sunshine;
				sunshine_data.replaceInStrings("=","");
				QString line_sunshine = sunshine_data.at(i);
				QStringList everyone_split = line_sunshine.split(" ");
				for(int j=0;j<24;j++)
				{
					temp_hour_sunshine.hour_sunshine[j] = everyone_split.at(j).toInt();
				}
				temp_sunshine.daily_sun_rise = everyone_split.at(24).toInt();
				temp_sunshine.daily_sun_set = everyone_split.at(25).toInt();
				temp_sunshine.daily_sunshine_count = everyone_split.at(26).toInt();
				m_sunshine.append(temp_sunshine);
				m_hour_sunshine.append(temp_hour_sunshine);
			}
			break;
		}
	}
}

void read_A::analyze_rain(QStringList rain_data,char rain_mode)
{
	if (rain_data.size() == 1)//文件没有数据，返回缺测数据
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			rain_filedata temp_rain;
			hour_rain_filedata temp_hour_rain;
			for(int j=0;j<24;j++)//初始化
			{
				temp_hour_rain.v13019_1hour_Precipitation[j] = 999999.0;
			}
			temp_rain.daily_20to20_Precipitation = 999999.0;
			temp_rain.daily_20to8_Precipitation = 999999.0;
			temp_rain.daily_8to20_Precipitation = 999999.0;
			m_rain.append(temp_rain);
			m_hour_rain.append(temp_hour_rain);
		}
		return;
	}
	switch (rain_mode)//每天要记录的时次数，按方位式不同，共有3个
	{
	case '2':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				rain_filedata temp_rain_fileData;
				temp_rain_fileData.daily_20to8_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(0));
				temp_rain_fileData.daily_8to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(1));
				temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(2));
				m_rain.append(temp_rain_fileData);
			}
			break;
		}
	case '0':
		{
			QStringList rain;
			QStringList hour_rain;
			int equal=1;
			for(int i=1;i<rain_data.size();i++)//拆分数据文件
			{
				if(equal==1)
				{
					rain.append(rain_data.at(i));
					if(rain_data.at(i).contains('='))
					{
						equal++;
					}
				}
				else if(equal==2)
				{
					hour_rain.append(rain_data.at(i));
					if(rain_data.at(i).contains('='))
					{
						equal++;
					}
				}
				else break;
			}
			for(int m=0;m<rain.size();m++)
			{
				rain_filedata temp_rain;
				QString line_rain = rain.at(m);
				line_rain.remove(".");
				line_rain.remove("=");
				QStringList everyone_split = line_rain.split(" ");
				temp_rain.daily_20to20_Precipitation = symbol_analyise(everyone_split.at(0));
				temp_rain.daily_20to8_Precipitation = symbol_analyise(everyone_split.at(1));
				temp_rain.daily_8to20_Precipitation = symbol_analyise(everyone_split.at(2));
				m_rain.append(temp_rain);
			}
			QStringList temp_hour_rain;
			QVector<QStringList> hour_rain_block;
			for(int j=0;j<hour_rain.size();j++)//处理降水要素小时数据
			{
				hour_rain.replaceInStrings("=",".");
				temp_hour_rain.append(hour_rain.at(j));
				if(hour_rain.at(j).contains('.'))
				{
					hour_rain_block.append(temp_hour_rain);
					temp_hour_rain.clear();
				}
			}
			for(int m=0;m<hour_rain_block.size();m++)
			{
				hour_rain_filedata temp_hour_rain_filedata;
				int p=0;
				QStringList every_hour_rain = hour_rain_block.at(m);
				for(int n=0;n<2;n++)
				{
					QString line_hour_rain = every_hour_rain.at(n);
					QStringList everyone_split = line_hour_rain.split(" ");
					everyone_split.replaceInStrings(".","");
					for(int q=0;q<everyone_split.size();q++,p++)
					{
						temp_hour_rain_filedata.v13019_1hour_Precipitation[p] = everyone_split.at(q).toInt();
					}
					line_hour_rain.clear();
				}
				m_hour_rain.append(temp_hour_rain_filedata);
			}
			break;
		}
	case '6':
		{
			QStringList rain;
			QStringList hour_rain;
			QStringList link_rain;
			int equal=1;
			for(int i=0;i<rain_data.size();i++)//拆分数据文件
			{
				if(equal==1)
				{
					rain.append(rain_data.at(i));
					if(rain_data.at(i).contains('='))
					{
						equal++;
					}
				}
				else if(equal==2)
				{
					hour_rain.append(rain_data.at(i));
					if(rain_data.at(i).contains('='))
					{
						equal++;
					}
				}
				else if(equal==3)
				{
					link_rain.append(rain_data.at(i));
					if(rain_data.at(i).contains('='))
					{
						equal++;
					}
				}
				else break;
			}
			rain.removeAt(0);
			for(int m=0;m<rain.size();m++)
			{
				rain_filedata temp_rain;
				QString line_rain = rain.at(m);
				line_rain.remove(".");
				line_rain.remove("=");
				QStringList everyone_split = line_rain.split(" ");
				temp_rain.daily_20to20_Precipitation = symbol_analyise(everyone_split.at(0));
				temp_rain.daily_20to8_Precipitation = symbol_analyise(everyone_split.at(1));
				temp_rain.daily_8to20_Precipitation = symbol_analyise(everyone_split.at(2));
				m_rain.append(temp_rain);
			}
			QStringList temp_hour_rain;
			QVector<QStringList> hour_rain_block;
			for(int j=0;j<hour_rain.size();j++)//处理降水要素小时数据
			{
				hour_rain.replaceInStrings("=",".");
				temp_hour_rain.append(hour_rain.at(j));
				if(hour_rain.at(j).contains('.'))
				{
					hour_rain_block.append(temp_hour_rain);
					temp_hour_rain.clear();
				}
			}
			for(int m=0;m<hour_rain_block.size();m++)
			{
				hour_rain_filedata temp_hour_rain_filedata;
				int p=0;
				QStringList every_hour_rain = hour_rain_block.at(m);
				for(int n=0;n<2;n++)
				{
					QString line_hour_rain = every_hour_rain.at(n);
					QStringList everyone_split = line_hour_rain.split(" ");
					everyone_split.replaceInStrings(".","");
					for(int q=0;q<everyone_split.size();q++,p++)
					{
						temp_hour_rain_filedata.v13019_1hour_Precipitation[p] = everyone_split.at(q).toInt();
					}
					line_hour_rain.clear();
				}
				m_hour_rain.append(temp_hour_rain_filedata);
			}
			link_rain_filedata temp_link_rain;
			QString line_link_rain = link_rain.at(0);
			line_link_rain.remove('=');
			QStringList every_link_rain = line_link_rain.split(" ");
			temp_link_rain.daily_20to8_t_Precipitation = every_link_rain.at(0).toInt();
			temp_link_rain.date = every_link_rain.at(1);
			temp_link_rain.month_rain = every_link_rain.at(2).toInt();
			m_link_rain.append(temp_link_rain);
			break;
		}
	}
}

void read_A::analyze_wind(QStringList wind_data,char wind_mode)
{
	QStringList wind_2min;
	QStringList wind_10min;
	QStringList wind_max;
	int equal=1;
	for(int i=0;i<wind_data.size();i++)//拆分2分钟10分钟最大极大数据文件
	{
		if(equal==1)
		{
			wind_2min.append(wind_data.at(i));
			if(wind_data.at(i).contains('='))
			{
				equal++;
			}
		}
		else if(equal==2)
		{
			wind_10min.append(wind_data.at(i));
			if(wind_data.at(i).contains('='))
			{
				equal++;
			}
		}
		else if(equal==3)
		{
			wind_max.append(wind_data.at(i));
			if(wind_data.at(i).contains('='))
			{
				equal++;
			}
		}
		else break;
	}
	if (wind_data.size() == 1)//文件没有数据，返回缺测数据
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			IImin_wind_filedata temp_2min_wind;
			VImin_wind_filedata temp_10min_wind;
			max_huge_wind_filedata temp_maxhuge_wind;
			for(int j=0;j<24;j++)//初始化
			{
				temp_2min_wind.v11001_002_2min_wind_direction[j] = 999999.0;
				temp_2min_wind.v11002_002_2min_wind_speed[j] = 999999.0;
				temp_10min_wind.v11042_010_10min_wind_speed[j] = 999999.0;
				temp_10min_wind.v11202_010_10min_wind_direction[j] = 999999.0;
			}
			temp_maxhuge_wind.v11043_1hour_huge_wind_direction = 999999.0;
			temp_maxhuge_wind.v11041_1hour_huge_wind_speed = 999999.0;
			temp_maxhuge_wind.v11041_752_1hour_huge_wind_time = 999999.0;
			temp_maxhuge_wind.v11042_1hour_10min_max_wind_speed = 999999.0;
			temp_maxhuge_wind.v11202_1hour_10min_max_wind_direction = 999999.0;
			temp_maxhuge_wind.v11042_752_1hour_max_wind_time = 999999.0;
			m_2min_wind.append(temp_2min_wind);
			m_10min_wind.append(temp_10min_wind);
			m_max_huge_wind.append(temp_maxhuge_wind);
		}
		return;
	}
	int mark = 0;//文件标记
	switch (wind_mode)//每天要记录的时次数，按方位式不同，共有4个
	{
	case 'E':
		{
			mark = 1;
			break;
		}
	case 'H':
		{
			mark = 1;
			break;
		}
	case 'K':
		{
			mark = 2;
			break;
		}
	case 'N':
		{
			mark = 2;
			break;
		}
	}
	QStringList temp_wind_2min;
	QVector<QStringList> wind_2min_block;
	QStringList temp_wind_10min;
	QVector<QStringList> wind_10min_block;
	wind_2min.removeAt(0);//删除FN行
	if(mark == 2)
	{
		for(int j=0;j<wind_2min.size();j++)//处理风要素2分钟风向风速数据
		{
			wind_2min.replaceInStrings("=",".");
			temp_wind_2min.append(wind_2min.at(j));
			if(wind_2min.at(j).contains('.'))
			{
				wind_2min_block.append(temp_wind_2min);
				temp_wind_2min.clear();
			}
		}
		for(int m=0;m<wind_2min_block.size();m++)//2分钟风赋值
		{
			IImin_wind_filedata temp_2min_wind;
			int p=0;
			QStringList every_wind_2min = wind_2min_block.at(m);
			for(int n=0;n<4;n++)
			{
				QString line_wind_2min = every_wind_2min.at(n);
				QStringList everyone_split = line_wind_2min.split(" ");
				for(int q=0;q<everyone_split.size();q++,p++)
				{
					QString pre = everyone_split.at(q).left(3);
					QString last = everyone_split.at(q).right(3);
					temp_2min_wind.v11001_002_2min_wind_direction[p] = symbol_wind(pre);
					temp_2min_wind.v11002_002_2min_wind_speed[p] = last.toInt();
				}
				line_wind_2min.clear();
			}
			m_2min_wind.append(temp_2min_wind);
		}
		for(int j=0;j<wind_10min.size();j++)//处理风要素10分钟风向风速数据
		{
			wind_10min.replaceInStrings("=",".");
			temp_wind_10min.append(wind_10min.at(j));
			if(wind_10min.at(j).contains('.'))
			{
				wind_10min_block.append(temp_wind_10min);
				temp_wind_10min.clear();
			}
		}
		for(int m=0;m<wind_10min_block.size();m++)//10分钟风赋值
		{
			VImin_wind_filedata temp_10min_wind;
			int p=0;
			QStringList every_wind_10min = wind_10min_block.at(m);
			for(int n=0;n<4;n++)
			{
				QString line_wind_10min = every_wind_10min.at(n);
				QStringList everyone_split = line_wind_10min.split(" ");
				for(int q=0;q<everyone_split.size();q++,p++)
				{
					QString pre = everyone_split.at(q).left(3);
					QString last = everyone_split.at(q).right(3);
					temp_10min_wind.v11202_010_10min_wind_direction[p] = symbol_wind(pre);
					temp_10min_wind.v11042_010_10min_wind_speed[p] = last.toInt();
				}
				line_wind_10min.clear();
			}
			m_10min_wind.append(temp_10min_wind);
		}
		for(int m=0;m<wind_max.size();m++)//最大极大赋值
		{
			max_huge_wind_filedata temp_maxhuge_wind;
			wind_max.replaceInStrings("="," ");
			QStringList line_wind_max = wind_max.at(m).split(" ");
			temp_maxhuge_wind.V01000 = base_info.v01000_sta_Num.toInt();
			temp_maxhuge_wind.V04001 = base_info.v04001_observe_year;
			temp_maxhuge_wind.V04002 = base_info.v04002_observe_month;
			temp_maxhuge_wind.V04003 = m+1;
			temp_maxhuge_wind.v11042_1hour_10min_max_wind_speed = line_wind_max.at(0).left(3).toInt();
			temp_maxhuge_wind.v11202_1hour_10min_max_wind_direction = symbol_wind(line_wind_max.at(0).right(3));
			temp_maxhuge_wind.v11042_752_1hour_max_wind_time = line_wind_max.at(1).toInt();
			temp_maxhuge_wind.v11041_1hour_huge_wind_speed = line_wind_max.at(2).left(3).toInt();
			temp_maxhuge_wind.v11043_1hour_huge_wind_direction = symbol_wind(line_wind_max.at(2).right(3));
			temp_maxhuge_wind.v11041_752_1hour_huge_wind_time = line_wind_max.at(3).toInt();
			m_max_huge_wind.append(temp_maxhuge_wind);
		}
	}
	else if(mark ==1)
	{
		for(int m=0;m<wind_2min.size();m++)
		{
			IImin_wind_filedata temp_2min_wind;
			QString line_wind_2min = wind_2min.at(m);
			line_wind_2min.remove(".");
			line_wind_2min.remove("=");
			QStringList everyone_split = line_wind_2min.split(" ");
			for(int p=0;p<everyone_split.size();p++)
			{
				QString pre = everyone_split.at(p).left(3);
				QString last = everyone_split.at(p).right(3);
				temp_2min_wind.v11001_002_2min_wind_direction[p] = symbol_wind(pre);
				temp_2min_wind.v11002_002_2min_wind_speed[p] = last.toInt();
			}
			m_2min_wind.append(temp_2min_wind);
		}
		
		for(int j=0;j<wind_10min.size();j++)//处理风要素10分钟风向风速数据
		{
			wind_10min.replaceInStrings("=",".");
			temp_wind_10min.append(wind_10min.at(j));
			if(wind_10min.at(j).contains('.'))
			{
				wind_10min_block.append(temp_wind_10min);
				temp_wind_10min.clear();
			}
		}
		for(int m=0;m<wind_10min_block.size();m++)//10分钟风赋值
		{
			VImin_wind_filedata temp_10min_wind;
			int p=0;
			QStringList every_wind_10min = wind_10min_block.at(m);
			for(int n=0;n<4;n++)
			{
				QString line_wind_10min = every_wind_10min.at(n);
				QStringList everyone_split = line_wind_10min.split(" ");
				for(int q=0;q<everyone_split.size();q++,p++)
				{
					QString pre = everyone_split.at(q).left(3);
					QString last = everyone_split.at(q).right(3);
					temp_10min_wind.v11202_010_10min_wind_direction[p] = symbol_wind(pre);
					temp_10min_wind.v11042_010_10min_wind_speed[p] = last.toInt();
				}
				line_wind_10min.clear();
			}
			m_10min_wind.append(temp_10min_wind);
		}
		for(int m=0;m<wind_max.size();m++)//最大极大赋值
		{
			max_huge_wind_filedata temp_maxhuge_wind;
			wind_max.replaceInStrings("="," ");
			QStringList line_wind_max = wind_max.at(m).split(" ");
			temp_maxhuge_wind.V01000 = base_info.v01000_sta_Num.toInt();
			temp_maxhuge_wind.V04001 = base_info.v04001_observe_year;
			temp_maxhuge_wind.V04002 = base_info.v04002_observe_month;
			temp_maxhuge_wind.V04003 = m+1;
			temp_maxhuge_wind.v11042_1hour_10min_max_wind_speed = line_wind_max.at(0).left(3).toInt();
			temp_maxhuge_wind.v11202_1hour_10min_max_wind_direction = symbol_wind(line_wind_max.at(0).right(3));
			temp_maxhuge_wind.v11042_752_1hour_max_wind_time = line_wind_max.at(1).toInt();
			temp_maxhuge_wind.v11041_1hour_huge_wind_speed = line_wind_max.at(2).left(3).toInt();
			temp_maxhuge_wind.v11043_1hour_huge_wind_direction = symbol_wind(line_wind_max.at(2).right(3));
			temp_maxhuge_wind.v11041_752_1hour_huge_wind_time = line_wind_max.at(3).toInt();
			m_max_huge_wind.append(temp_maxhuge_wind);
		}
	}
	/*for(int m=0;m<m_element.size();m++)
	{
		qDebug("m_element.at(%d).v11041_752_1hour_huge_wind_time = %d\n",m,m_element.at(m).v11041_752_1hour_huge_wind_time);
	}*/
	//qDebug("wind_10min_block = %d\n",wind_10min_block.size());	
}

float read_A::symbol_analyise( QString str)
{
	str.remove('=');
	if (str.contains(";"))//特殊符号替换
	{
		str.replace(QString(";"),QString("1"));
	}
	else if (str.contains(":"))//特殊符号替换
	{
		str.replace(QString(":"),QString("2"));
	}
	else if (str.contains(",,,,"))//微量降水按0算
	{
		str = QString("0000");
	}
	return str.toFloat()/*/10.0*/;
}

int read_A::symbol_wind( QString str)
{
	str.remove('P');
	str.remove('A');

	if (!str.compare("N"))//特殊符号替换
	{
		return 0;
	}
	else if (!str.compare("NNE"))//特殊符号替换
	{
		return 23;
	}
	else if (!str.compare("NE"))//特殊符号替换
	{
		return 45;
	}
	else if (!str.compare("ENE"))//特殊符号替换
	{
		return 68;
	}
	else if (!str.compare("E"))//特殊符号替换
	{
		return 90;
	}
	else if (!str.compare("ESE"))//特殊符号替换
	{
		return 113;
	}
	else if (!str.compare("SE"))//特殊符号替换
	{
		return 135;
	}
	else if (!str.compare("SSE"))//特殊符号替换
	{
		return 158;
	}
	else if (!str.compare("S"))//特殊符号替换
	{
		return 180;
	}
	else if (!str.compare("SSW"))//特殊符号替换
	{
		return 203;
	}
	else if (!str.compare("SW"))//特殊符号替换
	{
		return 225;
	}
	else if (!str.compare("WSW"))//特殊符号替换
	{
		return 248;
	}
	else if (!str.compare("W"))//特殊符号替换
	{
		return 270;
	}
	else if (!str.compare("WNW"))//特殊符号替换
	{
		return 293;
	}
	else if (!str.compare("NW"))//特殊符号替换
	{
		return 315;
	}
	else if (!str.compare("NNW"))//特殊符号替换
	{
		return 338;
	}
	else if (!str.compare("C"))//特殊符号替换
	{
		return 0;
	}
	else return str.toInt();
}

void read_A::analyze_pressure( QStringList pressure_data,char pressure_mode)
{
	pressure_data.replaceInStrings("=","");
	
	if (pressure_data.size() == 1)//文件没有数据，返回缺测数据
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			hour_pressure_filedata temp_hour_pressure;
			for(int j=0;j<24;j++)//初始化
			{
				temp_hour_pressure.hour_pressure[j] = 999999.0;
			}
		}
		return;
	}
	QStringList pre_day_data;
	switch(pressure_mode)
	{
	case 'C':
		{
			for (int i = 1;i<pressure_data.size();i++)
			{
				QString tmp_str;
				tmp_str += pressure_data.at(i);
				tmp_str += " ";
				tmp_str += pressure_data.at(i+1);
				i++;
				pre_day_data.append(tmp_str);
			}
			for (int j=0;j<pre_day_data.size();j++)
			{
				hour_pressure_filedata temp_pre_filedata;
				QStringList tmp_strList = pre_day_data.at(j).split(" ");
				for (int k = 0;k<24;k++)
				{
					int dd = tmp_strList.at(k).toInt();
					if (dd < 999)
					{
						dd = 10000+dd;
					}
					temp_pre_filedata.hour_pressure[k] = dd;
				}
				m_hour_pressure.append(temp_pre_filedata);
			}
		}
	}
}
