#include "read_A0.h"
#include <QDebug>
#include <QtCore/QCoreApplication>

read_a0::read_a0(void)
{
}


read_a0::~read_a0(void)
{
}

int read_a0::GetMon_Nums( int dataYear,int dataMonth)
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

bool read_a0::start_A0(QString fileName)
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
	if (file_tital_split.size()!= 6)
	{
		qDebug("file message error\n");
		return false;//头信息缺失
	}
	//获得基本头信息

	if(file_tital_split.size() == 6)
	{
		m_bashinfo.stationID = file_tital_split.at(0);
		m_bashinfo.latlonitude = file_tital_split.at(1);
		m_bashinfo.observation = file_tital_split.at(2);
		m_bashinfo.senson = file_tital_split.at(3);
		m_bashinfo.year = file_tital_split.at(4);
		m_bashinfo.month = file_tital_split.at(5);
// 		m_bashinfo.groundheight = 999999.0;
// 		m_bashinfo.identification = 999999.0;
// 		m_bashinfo.latitude = 999999.0;
// 		m_bashinfo.longitude = 999999.0;
// 		m_bashinfo.method = 999999.0;
// 		m_bashinfo.month = 999999.0;
// 		m_bashinfo.observation = 999999.0;
// 		m_bashinfo.qc = 999999.0;
// 		m_bashinfo.windheight = 999999.0;
		Mon_Nums = GetMon_Nums(m_bashinfo.year.toInt(),m_bashinfo.month.toInt());
		qDebug("m_bashinfo.stationID = \n",m_bashinfo.stationID.toAscii().constData());
	}
	//else if(file_tital_split.size() == 12)
	//{
	//	m_bashinfo.stationID = file_tital_split.at(0);
	//	m_bashinfo.latitude = file_tital_split.at(1);
	//	m_bashinfo.longitude = file_tital_split.at(2);
	//	m_bashinfo.observation = file_tital_split.at(3);
	//	m_bashinfo.senson = file_tital_split.at(4);
	//	m_bashinfo.windheight = file_tital_split.at(5);
	//	m_bashinfo.groundheight = file_tital_split.at(6);
	//	m_bashinfo.method = file_tital_split.at(7);
	//	m_bashinfo.identification = file_tital_split.at(8);
	//	m_bashinfo.qc = file_tital_split.at(9);
	//	m_bashinfo.year = file_tital_split.at(10);
	//	m_bashinfo.month = file_tital_split.at(11);
	//	m_bashinfo.latlonitude = 999999.0;
	//	Mon_Nums = GetMon_Nums(m_bashinfo.year.toInt(),m_bashinfo.month.toInt());
	//	qDebug("4444444444444444444444444444444444444\n");
	//	qDebug(m_bashinfo.stationID.toAscii().constData());

	//}
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
	qDebug("original m_filedata = %d",m_filedata.size());
	for(int element_num=0;element_num<m_filedata.size();element_num++)//A0文件云量处理
	{
		QStringList oridata = m_filedata.at(element_num);//单个要素
		QString str = oridata.at(0);
		QByteArray ba = str.toLatin1(); 
		char* ch = ba.data();
		int end;
		if(!str.compare("N9") || !str.compare("N0") || !str.compare("NA"))
		{
			int del=element_num+1;
			if(del == m_filedata.size())
			{
				break;
			}			
			QStringList adddata = m_filedata.at(del);
			oridata.append(adddata);
			m_filedata.append(oridata);
			m_filedata.remove(element_num);
			m_filedata.remove(del);
			oridata.clear();
		}	
	}
	for(int element_num=0;element_num<m_filedata.size();element_num++)//A0文件风处理
	{
		QStringList oridata = m_filedata.at(element_num);//单个要素
		QString str = oridata.at(0);
		QByteArray ba = str.toLatin1(); 
		char* ch = ba.data();
		int end;
		if(!str.compare("F0") || !str.compare("F4") || !str.compare("F5") || !str.compare("F6") || !str.compare("F7") || !str.compare("F8"))
		{
			int del=element_num+1;
			if(del == m_filedata.size())
			{
				break;
			}	
			QString add(ch);
			QStringList adddata = m_filedata.at(del);
			adddata.prepend(add);
			m_filedata.append(adddata);
			m_filedata.remove(element_num);
			m_filedata.remove(del);
			oridata.clear();
			adddata.clear();
		}	
	}
	qDebug("after m_filedata = %d",m_filedata.size());
	file.close();
	analyzeelement();
	return true;
}

bool read_a0::analyzeelement()
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
		case 'E'://水汽压
			{
				analyze_vaporPressure(tempdata,ch[1]);
				break;
			}
		case 'U'://相对湿度
			{
				analyze_relativhumidity(tempdata,ch[1]);
				break;
			}
		case 'N'://云量
			{
				analyze_cloudy(tempdata,ch[1]);
				break;
			}
		case 'V'://能见度
			{
				analyze_visibility(tempdata,ch[1]);
				break;
			}
		case 'F'://风
			{
				analyze_wind(tempdata,ch[1]);
				break;
			}
		}
	}
	nothing_fileData temp_nothing_fileData;
	temp_nothing_fileData.daily_8to8_rain = 999999.0;
	temp_nothing_fileData.daily_8to8_temperature = 999999.0;
	temp_nothing_fileData.daily_8to8_maximum_temp = 999999.0;
	temp_nothing_fileData.daily_8to8_minmimu_temp = 999999.0;
	if (m_temperature_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			temperature_fileData temp_temperature_fileData;
			temp_temperature_fileData.daily_maximum = 999999.0;
			temp_temperature_fileData.daily_maximum_time = 999999.0;
			temp_temperature_fileData.daily_minimum = 999999.0;
			temp_temperature_fileData.daily_minimum_time = 999999.0;
			temp_temperature_fileData.daily_average = 999999.0;
			m_temperature_fileData.append(temp_temperature_fileData);
		}
	}
	if (m_rain_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			rain_fileData temp_rain_fileData;
			temp_rain_fileData.daily_20to8_Precipitation = 999999.0;
			temp_rain_fileData.daily_8to20_Precipitation = 999999.0;
			temp_rain_fileData.daily_20to20_Precipitation = 999999.0;
			m_rain_fileData.append(temp_rain_fileData);
		}
	}
	if (m_sunshine_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			sunshine_fileData temp_sunshine_fileData;
			temp_sunshine_fileData.daily_sunshine_count = 99999.0;
			temp_sunshine_fileData.daily_sun_rise = 999999.0;
			temp_sunshine_fileData.daily_sun_set = 999999.0;
			m_sunshine_fileData.append(temp_sunshine_fileData);
		}
	}
	if (m_relativhumidity_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			relativhumidity_fileData temp_relativhumidity_fileData;
			temp_relativhumidity_fileData.relativhumidity = 999999.0;
			temp_relativhumidity_fileData.relativhumidity_minnum = 999999.0;
			temp_relativhumidity_fileData.relativhumidity_minnum_time = 999999.0;
			m_relativhumidity_fileData.append(temp_relativhumidity_fileData);
		}
	}
	if (m_vaporPressure_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			vaporPressure_fileData temp_vaporPressure_fileData;
			temp_vaporPressure_fileData.vaporPressure = 999999.0;
			m_vaporPressure_fileData.append(temp_vaporPressure_fileData);
		}
	}
	if (m_cloudy_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			cloudy_fileData temp_cloudy_fileData;
			temp_cloudy_fileData.totalcloudy = 999999.0;
			temp_cloudy_fileData.lowcloudy = 999999.0;
			m_cloudy_fileData.append(temp_cloudy_fileData);
		}
	}
	if (m_visibility_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			visibility_fileData temp_visibility_fileData;
			temp_visibility_fileData.visibility = 999999.0;
			m_visibility_fileData.append(temp_visibility_fileData);
		}
	}
	if (m_wind_fileData.size() == 0)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			wind_fileData temp_wind_fileData;
			temp_wind_fileData.average_wind = 999999.0;
			temp_wind_fileData.wind_max = 999999.0;
			temp_wind_fileData.wind_max_direct = 99999.0;
			temp_wind_fileData.wind_extreme = 999999.0;
			temp_wind_fileData.wind_extreme_direct = 999999.0;
			m_wind_fileData.append(temp_wind_fileData);
		}
	}
	for(int i=1;i<Mon_Nums+1;i++)
	{
		QString temp_datatime;
		if (i<10)
		{
			temp_datatime = m_bashinfo.year;
			temp_datatime =temp_datatime+m_bashinfo.month;
			int eeee = 0;
			temp_datatime =temp_datatime+QString::number(eeee);
			temp_datatime =temp_datatime+QString::number(i);
		}
		else
		{
			temp_datatime = m_bashinfo.year+m_bashinfo.month+QString::number(i);
		}
		dbStorage temp_dbStorage;
		temp_dbStorage.dbStorage_dataTime = QDateTime::fromString(temp_datatime,"yyyyMMdd");
		temp_dbStorage.dbStorage_baseInfo = m_bashinfo;
		temp_dbStorage.dbStorage_temperature_fileData = m_temperature_fileData.at(i-1);
		temp_dbStorage.dbStorage_rain_fileData = m_rain_fileData.at(i-1);
		temp_dbStorage.dbStorage_sunshine_fileData = m_sunshine_fileData.at(i-1);
		temp_dbStorage.dbStorage_vaporPressure_fileData = m_vaporPressure_fileData.at(i-1);
		temp_dbStorage.dbStorage_relativhumidity_fileData = m_relativhumidity_fileData.at(i-1);
		temp_dbStorage.dbStorage_cloudy_fileData = m_cloudy_fileData.at(i-1);
		temp_dbStorage.dbStorage_visibility_fileData = m_visibility_fileData.at(i-1);
		temp_dbStorage.dbStorage_wind_fileData = m_wind_fileData.at(i-1);
		temp_dbStorage.dbStorage_nothing_fileData = temp_nothing_fileData;
		m_dbStorage.append(temp_dbStorage);
	}
	return true;
}

void read_a0::analyze_wind(QStringList wind_data,char wind_mode)
{
	qDebug("1-1\n");
	if (wind_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			wind_fileData temp_wind_fileData;
			temp_wind_fileData.average_wind = 999999.0;
			temp_wind_fileData.wind_max = 999999.0;
			temp_wind_fileData.wind_max_direct = 99999.0;
			temp_wind_fileData.wind_extreme = 999999.0;
			temp_wind_fileData.wind_extreme_direct = 999999.0;
			m_wind_fileData.append(temp_wind_fileData);
		}
		return;
	}
	int data_times = 0,data_numerical = 0;//每天记录的时次，记录值累加
	switch (wind_mode)//每天要记录的时次数，按方位式不同，共有12个
	{
	case '0':
		{
			for (int i = 1;i<Mon_Nums+1;i++)
			{
				wind_fileData temp_wind_fileData;
				QString daily_value = wind_data.at(i);
				daily_value.remove('=');
				QStringList tempdata = daily_value.split(' ');
				QString winddata1_1 = tempdata.at(0);
				QString winddata1_2 = tempdata.at(0);
				QString winddata2_1 = tempdata.at(1);
				QString winddata2_2 = tempdata.at(1);
				QString previous1_1 = winddata1_1.remove(3,6);
				QString previous1_2 = winddata1_2.remove(0,3);
				QString last2_1 = winddata2_1.remove(3,6);
				QString last2_2 = winddata2_2.remove(0,3);
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_extreme = previous1_1.toFloat();
				temp_wind_fileData.wind_extreme_direct = symbol_wind(previous1_2.remove('P'));
				temp_wind_fileData.wind_max = last2_1.toFloat();
				temp_wind_fileData.wind_max_direct = symbol_wind(last2_2.remove('P'));
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '2':
		{
			for (int i = 0;i<Mon_Nums;i++)
			{
				wind_fileData temp_wind_fileData;
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_max = 999999.0;
				temp_wind_fileData.wind_max_direct = 99999.0;
				temp_wind_fileData.wind_extreme = 999999.0;
				temp_wind_fileData.wind_extreme_direct = 999999.0;
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '4':
		{
			for (int i = 1;i<Mon_Nums+1;i++)
			{
				wind_fileData temp_wind_fileData;
				QString daily_value = wind_data.at(i);
				daily_value.remove('=');
				QStringList tempdata = daily_value.split(' ');
				QString winddata1 = tempdata.at(0);
				QString winddata2 = tempdata.at(0);
				QString previous = winddata1.remove(3,6);
				QString last = winddata2.remove(0,3);
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_extreme = 999999.0;
				temp_wind_fileData.wind_extreme_direct = 999999.0;
				temp_wind_fileData.wind_max = previous.toFloat();
				temp_wind_fileData.wind_max_direct = symbol_wind(last.remove('P'));
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '5':
		{
			for (int i = 1;i<Mon_Nums+1;i++)
			{
				wind_fileData temp_wind_fileData;
				QString daily_value = wind_data.at(i);
				daily_value.remove('=');
				QStringList tempdata = daily_value.split(' ');
				QString winddata1 = tempdata.at(0);
				QString winddata2 = tempdata.at(0);
				QString previous = winddata1.remove(3,6);
				QString last = winddata2.remove(0,3);
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_extreme = previous.toFloat();
				temp_wind_fileData.wind_extreme_direct = symbol_wind(last.remove('P'));
				temp_wind_fileData.wind_max = 999999.0;
				temp_wind_fileData.wind_max_direct = 999999.0;
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '6':
		{
			for (int i = 1;i<Mon_Nums+1;i++)
			{
				wind_fileData temp_wind_fileData;
				QString daily_value = wind_data.at(i);
				daily_value.remove('=');
				QStringList tempdata = daily_value.split(' ');
				QString winddata1 = tempdata.at(0);
				QString winddata2 = tempdata.at(0);
				QString previous = winddata1.remove(3,6);
				QString last = winddata2.remove(0,3);
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_extreme = 999999.0;
				temp_wind_fileData.wind_extreme_direct = 999999.0;
				temp_wind_fileData.wind_max = previous.toFloat();
				temp_wind_fileData.wind_max_direct = symbol_wind(last.remove('P'));
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '7':
		{
			for (int i = 1;i<Mon_Nums+1;i++)
			{
				wind_fileData temp_wind_fileData;
				QString daily_value = wind_data.at(i);
				daily_value.remove('=');
				QStringList tempdata = daily_value.split(' ');
				QString winddata1_1 = tempdata.at(0);
				QString winddata1_2 = tempdata.at(0);
				QString winddata2_1 = tempdata.at(1);
				QString winddata2_2 = tempdata.at(1);
				QString previous1_1 = winddata1_1.remove(3,6);
				QString previous1_2 = winddata1_1.remove(0,3);
				QString last2_1 = winddata2_1.remove(3,6);
				QString last2_2 = winddata2_2.remove(0,3);
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_extreme = previous1_1.toFloat();
				temp_wind_fileData.wind_extreme_direct = symbol_wind(previous1_2.remove('P'));
				temp_wind_fileData.wind_max = last2_1.toFloat();
				temp_wind_fileData.wind_max_direct = symbol_wind(last2_2.remove('P'));
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '8':
		{
			for (int i = 1;i<Mon_Nums+1;i++)
			{
				wind_fileData temp_wind_fileData;
				QString daily_value = wind_data.at(i);
				daily_value.remove('=');
				QStringList tempdata = daily_value.split(' ');
				QString winddata1 = tempdata.at(0);
				QString winddata2 = tempdata.at(0);
				QString previous = winddata1.remove(3,6);
				QString last = winddata2.remove(0,3);
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_extreme = previous.toFloat();
				temp_wind_fileData.wind_extreme_direct = symbol_wind(last.remove('P'));
				temp_wind_fileData.wind_max = 999999.0;
				temp_wind_fileData.wind_max_direct = 999999.0;
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	case '9':
		{
			for (int i = 0;i<Mon_Nums;i++)
			{
				wind_fileData temp_wind_fileData;
				temp_wind_fileData.average_wind = 999999.0;
				temp_wind_fileData.wind_max = 999999.0;
				temp_wind_fileData.wind_max_direct = 99999.0;
				temp_wind_fileData.wind_extreme = 999999.0;
				temp_wind_fileData.wind_extreme_direct = 999999.0;
				m_wind_fileData.append(temp_wind_fileData);
			}
			break;
		}
	}
	qDebug("1-2\n");
}

void read_a0::analyze_visibility(QStringList visibility_data,char visibility_mode)
{
	qDebug("2-1\n");
	if (visibility_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			visibility_fileData temp_visibility_fileData;
			temp_visibility_fileData.visibility = 999999.0;
			m_visibility_fileData.append(temp_visibility_fileData);
		}
		return;
	}
	int data_times = 0,data_numerical = 0;//每天记录的时次，记录值累加
	switch (visibility_mode)//每天要记录的时次数，按方位式不同，共有5个
	{
	case '0':
		{
			data_times = 4;
			break;
		}
	case '7':
		{
			data_times = 3;
			break;
		}
	case '8':
		{
			data_times = 4;
			break;
		}
	case '9':
		{
			data_times = 3;
			break;
		}
	case 'A':
		{
			data_times = 24;
			break;
		}
	}
	for (int i=1;i<Mon_Nums+1;i++)//一个月的数据拆成天，每一天的数据存放到各自对象中，最后放到m_dbStorage中
	{
		visibility_fileData temp_visibility_fileData;
		QString daily_value = visibility_data.at(i);
		daily_value.remove('=');
		QStringList tempdata = daily_value.split(' ');//一天的数据拆成时次，累加
		for (int j=0;j<data_times;j++)
		{
			data_numerical += tempdata.at(j).toInt();
		}
		//qDebug("data_numerical = %d\n",data_numerical);
		temp_visibility_fileData.visibility = data_numerical/data_times/*/10.0*/;
		//qDebug("visibility = %f\n",temp_visibility_fileData.visibility);
		data_numerical = 0;
		m_visibility_fileData.append(temp_visibility_fileData);
	}
	qDebug("2-2\n");
}

void read_a0::analyze_cloudy(QStringList cloudy_data,char cloudy_mode)
{
	qDebug("3-1\n");
	if (cloudy_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			cloudy_fileData temp_cloudy_fileData;
			temp_cloudy_fileData.totalcloudy = 999999.0;
			temp_cloudy_fileData.lowcloudy = 999999.0;
			m_cloudy_fileData.append(temp_cloudy_fileData);
		}
		return;
	}
	int data_times = 0,data_numerical = 0;//每天记录的时次，记录值累加
	switch (cloudy_mode)//每天要记录的时次数，按方位式不同，共有3个
	{
	case '0':
		{
			data_times = 4;
			break;
		}
	case '9':
		{
			data_times = 3;
			break;
		}
	case 'A':
		{
			data_times = 24;
			break;
		}
	}

	for (int i=1;i<Mon_Nums+1;i++)//一个月的数据拆成天，每一天的数据存放到各自对象中，最后放到m_dbStorage中
	{
		cloudy_fileData temp_cloudy_fileData;
		QString daily_value = cloudy_data.at(i);
		daily_value.remove('=');
		QStringList tempdata = daily_value.split(' ');//一天的数据拆成时次，累加
		for (int j=0;j<data_times;j++)
		{
			data_numerical += tempdata.at(j).toInt();
		}
		temp_cloudy_fileData.totalcloudy = data_numerical/data_times/*/10.0*/;
		//qDebug("\totalcloudy = %f\n",temp_cloudy_fileData.totalcloudy);
		data_numerical = 0;
		m_cloudy_fileData.append(temp_cloudy_fileData);
	}
	for(int i=Mon_Nums+1;i<(2*Mon_Nums)+1;i++)
	{
		cloudy_fileData temp_cloudy_fileData;
		QString daily_value = cloudy_data.at(i);
		daily_value.remove('=');
		QStringList tempdata = daily_value.split(' ');//一天的数据拆成时次，累加
		for (int j=0;j<data_times;j++)
		{
			data_numerical += tempdata.at(j).toInt();
		}
		temp_cloudy_fileData.lowcloudy= data_numerical/data_times;//10.0
		//qDebug("lowcloudy = %f\n",temp_cloudy_fileData.lowcloudy);
		data_numerical = 0;
		m_cloudy_fileData.append(temp_cloudy_fileData);
	}
	qDebug("3-2\n");
}

void read_a0::analyze_relativhumidity( QStringList relativhumidity_data,char relativhumidity_mode)
{
	qDebug("4-1\n");
	if (relativhumidity_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			relativhumidity_fileData temp_relativhumidity_fileData;
			temp_relativhumidity_fileData.relativhumidity = 999999.0;
			temp_relativhumidity_fileData.relativhumidity_minnum = 999999.0;
			temp_relativhumidity_fileData.relativhumidity_minnum_time = 999999.0;
			m_relativhumidity_fileData.append(temp_relativhumidity_fileData);
		}
		return;
	}
	int data_times = 0,data_numerical = 0;//每天记录的时次，记录值累加
	switch (relativhumidity_mode)//每天要记录的时次数，按方位式不同，共有6个
	{
	case '0':
		{
			data_times = 4;
			break;
		}
	case '2':
		{
			data_times = 4;
			break;
		}
	case '7':
		{
			data_times = 3;
			break;
		}
	case '9':
		{
			data_times = 3;
			break;
		}
	case 'A':
		{
			data_times = 24;
			break;
		}
	case 'B':
		{
			data_times = 24;
			break;
		}
	}
	for (int i=1;i<Mon_Nums+1;i++)//一个月的数据拆成天，每一天的数据存放到各自对象中，最后放到m_dbStorage中
	{
		relativhumidity_fileData temp_relativhumidity_fileData;
		QString daily_value = relativhumidity_data.at(i);
		daily_value.remove('=');
		QStringList tempdata = daily_value.split(' ');//一天的数据拆成时次，累加
		for (int j=0;j<data_times;j++)
		{
			data_numerical += tempdata.at(j).toInt();
		}
		//qDebug("data_numerical = %d\n",data_numerical);
		temp_relativhumidity_fileData.relativhumidity = data_numerical/data_times/*/10.0*/;
		//qDebug("relativhumidity = %f\n",temp_relativhumidity_fileData.relativhumidity);
		data_numerical = 0;
		if (relativhumidity_mode == 'B')
		{
			temp_relativhumidity_fileData.relativhumidity_minnum = tempdata.at(tempdata.size()-2).toFloat()/*/10*/;
			temp_relativhumidity_fileData.relativhumidity_minnum_time = tempdata.at(tempdata.size()-1).toFloat();
		}
		else if (relativhumidity_mode == 'A' || relativhumidity_mode == '0' || relativhumidity_mode == '7')
		{
			temp_relativhumidity_fileData.relativhumidity_minnum = tempdata.at(tempdata.size()-1).toFloat();
			temp_relativhumidity_fileData.relativhumidity_minnum_time = 999999.0;
		}
		else
		{
			temp_relativhumidity_fileData.relativhumidity_minnum = 999999.0;
			temp_relativhumidity_fileData.relativhumidity_minnum_time = 999999.0;
		}
		//qDebug("temp_relativhumidity_fileData.relativhumidity_minnum = %f\n",temp_relativhumidity_fileData.relativhumidity_minnum);
		//qDebug("temp_relativhumidity_fileData.relativhumidity_minnum_time = %f\n",temp_relativhumidity_fileData.relativhumidity_minnum_time);
		m_relativhumidity_fileData.append(temp_relativhumidity_fileData);
	}
	qDebug("4-2\n");
}

void read_a0::analyze_vaporPressure( QStringList vaporPressure_data,char vaporPressure_mode)
{
	qDebug("5-1\n");
	if (vaporPressure_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			vaporPressure_fileData temp_vaporPressure_fileData;
			temp_vaporPressure_fileData.vaporPressure = 999999.0;
			m_vaporPressure_fileData.append(temp_vaporPressure_fileData);
		}
		return;
	}
	int data_times = 0,data_numerical = 0;//每天记录的时次，记录值累加
	switch (vaporPressure_mode)//每天要记录的时次数，按方位式不同，共有3个
	{
	case '0':
		{
			data_times = 4;
			break;
		}
	case '9':
		{
			data_times = 3;
			break;
		}
	case 'A':
		{
			data_times = 24;
			break;
		}
	}
	for (int i=1;i<Mon_Nums+1;i++)//一个月的数据拆成天，每一天的数据存放到各自对象中，最后放到m_dbStorage中
	{
		vaporPressure_fileData temp_vaporPressure_fileData;
		QString daily_value = vaporPressure_data.at(i);
		daily_value.remove('=');
		QStringList tempdata = daily_value.split(' ');//一天的数据拆成时次，累加
		for (int j=0;j<data_times;j++)
		{
			data_numerical += tempdata.at(j).toInt();
		}
		//qDebug("data_numerical = %d\n",data_numerical);
		temp_vaporPressure_fileData.vaporPressure = data_numerical/data_times/*/10.0*/;
		//qDebug("vaporPressure = %f\n",temp_vaporPressure_fileData.vaporPressure);
		data_numerical = 0;

		m_vaporPressure_fileData.append(temp_vaporPressure_fileData);
	}
	qDebug("5-2\n");
}

void read_a0::analyze_tempreature( QStringList tempreature_data,char tempreatrue_mode)
{
	qDebug("6-1\n");
	if (tempreature_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			temperature_fileData temp_temperature_fileData;
			temp_temperature_fileData.daily_maximum = 999999.0;
			temp_temperature_fileData.daily_maximum_time = 999999.0;
			temp_temperature_fileData.daily_minimum = 999999.0;
			temp_temperature_fileData.daily_minimum_time = 999999.0;
			temp_temperature_fileData.daily_average = 999999.0;
			m_temperature_fileData.append(temp_temperature_fileData);
		}
		return;
	}
	int data_times = 0,data_numerical = 0;//每天记录的时次，记录值累加
	qDebug("tempreatrue_mode = %c\n",tempreatrue_mode);
	switch (tempreatrue_mode)//每天要记录的时次数，按方位式不同，共有四个
	{
	case '0':
		{
			data_times = 4;
			break;
		}
	case '9':
		{
			data_times = 3;
			break;
		}
	case 'A':
		{
			data_times = 24;
			break;
		}
	case 'B':
		{
			data_times = 24;
			break;
		}
	}
	for (int i=1;i<Mon_Nums+1;i++)//一个月的数据拆成天，每一天的数据存放到各自对象中，最后放到m_dbStorage中
	{
		qDebug("i = %d\n",i);

		temperature_fileData temp_temperature_fileData;
		QString daily_value = tempreature_data.at(i);
		//qDebug("###################################\n");
		//qDebug(daily_value.toAscii().constData());
		daily_value.remove('=');
		QStringList tempdata = daily_value.split(' ');//一天的数据拆成时次，累加
		for (int j=0;j<data_times;j++)
		{
			data_numerical += tempdata.at(j).toInt();
			//qDebug("data_numerical = %d\n",data_numerical);
		}
		temp_temperature_fileData.daily_average = data_numerical/data_times/*/10.0*/;
		data_numerical = 0;
		if (tempreatrue_mode == 'B')
		{
			qDebug("mode=B\n");
			temp_temperature_fileData.daily_maximum = tempdata.at(tempdata.size()-4).toFloat()/*/10*/;
			//qDebug("temp_temperature_fileData.daily_maximum = %f\n",temp_temperature_fileData.daily_maximum);
			temp_temperature_fileData.daily_maximum_time = tempdata.at(tempdata.size()-3).toFloat();
			temp_temperature_fileData.daily_minimum = tempdata.at(tempdata.size()-2).toFloat()/*/10*/;
			temp_temperature_fileData.daily_minimum_time = tempdata.at(tempdata.size()-1).toFloat();
		}
		else
		{
			temp_temperature_fileData.daily_maximum = tempdata.at(tempdata.size()-2).toFloat()/*/10.0*/;
			//qDebug("tempreatrue_mode = %c\n",tempreatrue_mode);
			//qDebug("temp_temperature_fileData.daily_maximum = %f\n",temp_temperature_fileData.daily_maximum);
			temp_temperature_fileData.daily_maximum_time = 999999.0;
			temp_temperature_fileData.daily_minimum = tempdata.at(tempdata.size()-1).toFloat()/*/10.0*/;
			temp_temperature_fileData.daily_minimum_time = 999999.0;
		}
		m_temperature_fileData.append(temp_temperature_fileData);
	}
	qDebug("6-2\n");
}

void read_a0::analyze_rain( QStringList rain_data,char rain_mode)
{
	qDebug("7-1\n");
	if (rain_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			rain_fileData temp_rain_fileData;
			temp_rain_fileData.daily_20to8_Precipitation = 999999.0;
			temp_rain_fileData.daily_8to20_Precipitation = 999999.0;
			temp_rain_fileData.daily_20to20_Precipitation = 999999.0;
			m_rain_fileData.append(temp_rain_fileData);
		}
		return;
	}
	switch (rain_mode)//每天要记录的时次数，按方位式不同，共有四个
	{
	case '0':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				rain_fileData temp_rain_fileData;
				temp_rain_fileData.daily_20to8_Precipitation = 999999.0;
				temp_rain_fileData.daily_8to20_Precipitation = 999999.0;
				temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(0));
				m_rain_fileData.append(temp_rain_fileData);
			}
			break;
		}
	case '1':
		{
			int imon = 0;
			for(int i=1;i<rain_data.size();i++)
			{
				imon++;
				QString ds = rain_data.at(i).split(' ').at(0);
				if (ds.toInt() != imon)
				{
					rain_fileData temp_rain_fileData;
					temp_rain_fileData.daily_20to8_Precipitation = 0.0;
					temp_rain_fileData.daily_8to20_Precipitation = 0.0;
					temp_rain_fileData.daily_20to20_Precipitation = 0.0;
					m_rain_fileData.append(temp_rain_fileData);
					i--;
					continue;
				}
				else
				{
					rain_fileData temp_rain_fileData;
					temp_rain_fileData.daily_20to8_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(1));
					temp_rain_fileData.daily_8to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(2));
					temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(3));
					m_rain_fileData.append(temp_rain_fileData);
				}
			}
			if (m_rain_fileData.size() != m_temperature_fileData.size())
			{
				int qnmd = m_rain_fileData.size();
				for (int ii = 0;ii<m_temperature_fileData.size() - qnmd;ii++)
				{
					rain_fileData temp_rain_fileData;
					temp_rain_fileData.daily_20to8_Precipitation = 0.0;
					temp_rain_fileData.daily_8to20_Precipitation = 0.0;
					temp_rain_fileData.daily_20to20_Precipitation = 0.0;
					m_rain_fileData.append(temp_rain_fileData);
				}
			}
			break;
		}
	case '2':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				rain_fileData temp_rain_fileData;
				temp_rain_fileData.daily_20to8_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(0));
				temp_rain_fileData.daily_8to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(1));
				temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(2));
				m_rain_fileData.append(temp_rain_fileData);
			}
			break;
		}
	case '3':
		{
			int imon = 0;
			for(int i=1;i<rain_data.size();i++)
			{
				imon++;
				QString ds = rain_data.at(i).split(' ').at(0);
				if (ds.toInt() != imon)
				{
					rain_fileData temp_rain_fileData;
					temp_rain_fileData.daily_20to8_Precipitation = 0.0;
					temp_rain_fileData.daily_8to20_Precipitation = 0.0;
					temp_rain_fileData.daily_20to20_Precipitation = 0.0;
					m_rain_fileData.append(temp_rain_fileData);
					i--;
					continue;
				}
				else
				{
					rain_fileData temp_rain_fileData;
					temp_rain_fileData.daily_20to8_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(1));
					temp_rain_fileData.daily_8to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(2));
					temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(3));
					m_rain_fileData.append(temp_rain_fileData);
				}
			}
			if (m_rain_fileData.size() != m_temperature_fileData.size())
			{
				int qnmd = m_rain_fileData.size();
				for (int ii = 0;ii<m_temperature_fileData.size() - qnmd;ii++)
				{
					rain_fileData temp_rain_fileData;
					temp_rain_fileData.daily_20to8_Precipitation = 0.0;
					temp_rain_fileData.daily_8to20_Precipitation = 0.0;
					temp_rain_fileData.daily_20to20_Precipitation = 0.0;
					m_rain_fileData.append(temp_rain_fileData);
				}
			}
			break;
		}
	case '5':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				rain_fileData temp_rain_fileData;
				temp_rain_fileData.daily_20to8_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(0));
				temp_rain_fileData.daily_8to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(1));
				temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(2));
				m_rain_fileData.append(temp_rain_fileData);
			}
			break;
		}
	case '6':
		{
			for(int i=1;i<Mon_Nums+1;i++)
			{
				rain_fileData temp_rain_fileData;
				temp_rain_fileData.daily_20to8_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(0));
				temp_rain_fileData.daily_8to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(1));
				temp_rain_fileData.daily_20to20_Precipitation = symbol_analyise(rain_data.at(i).split(' ').at(2));
				m_rain_fileData.append(temp_rain_fileData);
			}
			break;
		}
	}
	qDebug("7-2\n");
}

void read_a0::analyze_sunshine( QStringList sunshine_data,char sunshine_mode)
{
	qDebug("8-1\n");
	if (sunshine_data.size() == 1)
	{
		for (int i = 0;i<Mon_Nums;i++)
		{
			sunshine_fileData temp_sunshine_fileData;
			temp_sunshine_fileData.daily_sunshine_count = 99999.0;
			temp_sunshine_fileData.daily_sun_rise = 999999.0;
			temp_sunshine_fileData.daily_sun_set = 999999.0;
			m_sunshine_fileData.append(temp_sunshine_fileData);
		}
		return;
	}
	int data_times = 0;
	switch (sunshine_mode)
	{
	case '0':
		{
			data_times = 0;
			break;
		}
	case '2':
		{
			data_times = 18;
			break;
		}
	case 'A':
		{
			data_times = 26;
			break;
		}
	case '=':
		{
			for (int i=0;i<Mon_Nums;i++)
			{
				sunshine_fileData temp_sunshine_fileData;
				temp_sunshine_fileData.daily_sunshine_count = 99999.0;
				temp_sunshine_fileData.daily_sun_rise = 999999.0;
				temp_sunshine_fileData.daily_sun_set = 999999.0;
				m_sunshine_fileData.append(temp_sunshine_fileData);
			}
			return;
			break;
		}
	}
	for(int i=1;i<Mon_Nums+1;i++)
	{
		QString ds = sunshine_data.at(i);
		ds.remove('=');
		QString tempdata = ds.split(' ').at(data_times);//一天的数据拆成时次
		sunshine_fileData temp_sunshine_fileData;
		temp_sunshine_fileData.daily_sunshine_count = tempdata.toFloat()/*/10.0*/;
		if (sunshine_mode == 'A')
		{
			temp_sunshine_fileData.daily_sun_rise = ds.split(' ').at(data_times-2).toFloat();
			temp_sunshine_fileData.daily_sun_set = ds.split(' ').at(data_times-1).toFloat();
		}
		else
		{
			temp_sunshine_fileData.daily_sun_rise = 999999.0;
			temp_sunshine_fileData.daily_sun_set = 999999.0;
		}
		m_sunshine_fileData.append(temp_sunshine_fileData);
	}
	qDebug("8-2\n");
}

float read_a0::symbol_analyise( QString str)
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

int read_a0::symbol_wind( QString str)
{
	str.remove('P');
	str.remove('A');

	if (!str.compare("N") || !str.compare("00,"))//特殊符号替换
	{
		return 0;
	}
	else if (!str.compare("NNE") || !str.compare(",,3"))//特殊符号替换
	{
		return 23;
	}
	else if (!str.compare("NE") || !str.compare("0,3"))//特殊符号替换
	{
		return 45;
	}
	else if (!str.compare("ENE") || !str.compare("3,3"))//特殊符号替换
	{
		return 68;
	}
	else if (!str.compare("E") || !str.compare("003"))//特殊符号替换
	{
		return 90;
	}
	else if (!str.compare("ESE") || !str.compare("3'3"))//特殊符号替换
	{
		return 113;
	}
	else if (!str.compare("SE") || !str.compare("0'3"))//特殊符号替换
	{
		return 135;
	}
	else if (!str.compare("SSE") || !str.compare("''3"))//特殊符号替换
	{
		return 158;
	}
	else if (!str.compare("S") || !str.compare("00'"))//特殊符号替换
	{
		return 180;
	}
	else if (!str.compare("SSW") || !str.compare("''2"))//特殊符号替换
	{
		return 203;
	}
	else if (!str.compare("SW") || !str.compare("0'2"))//特殊符号替换
	{
		return 225;
	}
	else if (!str.compare("WSW") || !str.compare("2'2"))//特殊符号替换
	{
		return 248;
	}
	else if (!str.compare("W") || !str.compare("002"))//特殊符号替换
	{
		return 270;
	}
	else if (!str.compare("WNW") || !str.compare("2,2"))//特殊符号替换
	{
		return 293;
	}
	else if (!str.compare("NW") || !str.compare("0,2"))//特殊符号替换
	{
		return 315;
	}
	else if (!str.compare("NNW") || !str.compare(",,2"))//特殊符号替换
	{
		return 338;
	}
	else if (!str.compare("C") || !str.compare("00:"))//特殊符号替换
	{
		return 0;
	}
	else if (!str.compare("///"))
	{
		return 0;
	}
	else 
		return str.toInt();
}
