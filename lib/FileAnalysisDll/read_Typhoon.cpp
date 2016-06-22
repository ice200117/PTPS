#include "read_Typhoon.h"
#include <QFileInfo>
#include <QDebug>
read_typhoon::read_typhoon(void)
{
	m_typhoon_live.central_pressure = 0;
	m_typhoon_live.central_Wind_velocity = 0;
	m_typhoon_live.Live_day = 0;
	m_typhoon_live.Live_hour = 0;
	m_typhoon_live.Live_minute = 0;
	m_typhoon_live.Live_month = 0;
	m_typhoon_live.Live_year = 0;
	m_typhoon_live.ty_level = TD;
	m_typhoon_live.typhoon_30kts = 0;
	m_typhoon_live.typhoon_50kts = 0;
	m_typhoon_live.typhoon_international_number = 0;
	m_typhoon_live.typhoon_Latitude = 0;
	m_typhoon_live.typhoon_Longitude = 0;
	m_typhoon_live.typhoon_name = QString("");
	m_typhoon_live.typhoon_number = 0;

	m_typhoon_tital.broadcast_time = 0;
	m_typhoon_tital.foreact_tital = QString("");
}

read_typhoon::~read_typhoon(void)
{
}

void read_typhoon::start_typhoon( QString fileName )
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	QFileInfo fi(file);
	QString qline;
	int elementnum = 0;
	qline = fi.fileName();
	livemonth = qline.mid(2,2).toInt();
	QVector<QStringList> m_Foreact;
	QStringList Foreactlist,qlinesplit;
	while (!file.atEnd()) 
	{
		qline = file.readLine();
		// 		if (qline.contains("WOCI41 BCSH"))
		// 		{
		// 			qDebug()<<fileName;
		// 		}
		if (qline.contains("WTPQ20 BABJ") || qline.contains("WTPQ20 RJTD") || qline.contains("WOCI41 BCSH"))
			//if (qline.contains("WTPQ20 BABJ") || qline.contains("WTPQ20 RJTD") || qline.contains("WTPQ20 VHHH") || qline.contains("WOCI41 BCGZ") || qline.contains("WOCI41 BCSH") || qline.contains("WTPN31 PGTW"))
		{
			//中央 日本 香港 广州 上海 关岛
			Foreactlist.append(qline);
			while(!file.atEnd())
			{
				qline = file.readLine();

				Foreactlist.append(qline);
				if (qline.contains("NNNN"))
				{
					elementnum++;
					m_Foreact.append(Foreactlist);
					Foreactlist.clear();
					break;
				}
			}
		}
		//if (qline.contains("WTPQ20 BABJ"))
		//{
		//	//qline = file.readLine();
		//	m_typhoon_tital.foreact_tital = "WTPQ20 BABJ";
		//	m_typhoon_tital.broadcast_time = qline.remove(QString("WTPQ20 BABJ")).toInt();

		//	qline = file.readLine();

		//	if (qline.contains("SUBJECTIVE FORECAST"))
		//	{
		//		qline = file.readLine();
		//		qline.remove("UTC").remove("INITIAL TIME");
		//		qlinesplit = qline.split(" ");
		//		m_typhoon_live.typhoon_name = qlinesplit.at(1);
		//		m_typhoon_live.typhoon_number = qlinesplit.at(2).toInt();
		//		qline = qlinesplit.at(3);
		//		m_typhoon_live.typhoon_international_number = qline.remove("(").remove(")").toInt();
		//		m_typhoon_live.Live_Time = qlinesplit.at(4).toInt();

		//		qline = file.readLine();
		//		qline = qlinesplit.at(1);
		//		m_typhoon_live.typhoon_Latitude = qline.remove("N").toFloat()*10;
		//		qline = qlinesplit.at(2);
		//		m_typhoon_live.typhoon_Longitude = qline.remove("E").toFloat()*10;
		//		qline = qlinesplit.at(3);
		//		m_typhoon_live.central_pressure = qline.remove("hPa").toInt();
		//		qline = qlinesplit.at(4);
		//		m_typhoon_live.central_Wind_velocity = qline.remove("m/s").toInt();
		//	}
		//}
	}
	file.close();

	for (int i = 0;i<elementnum;i++)
	{
		Vec_typhoon_forecast_point.clear();

		QStringList forl = m_Foreact.at(i);
		read_first_paragraph(forl);
		forl.removeAt(0);//读第一段，然后去掉第一段
		//read_second_paragraph(forl);

		read_sixth_paragraph(forl);
		Vec_typhoon_forecast.append(m_typhoon_forecast);
	}
}

bool read_typhoon::read_first_paragraph(QStringList analyes_message)
{
	QString temp_tital = analyes_message.at(0);
	if (temp_tital.contains("WTPQ20 BABJ"))
	{
		m_typhoon_tital.broadcast_time = temp_tital.remove(QString("WTPQ20 BABJ")).toInt();
		temp_tital = QString("BABJ");
		//temp_tital += "中央";
		m_typhoon_tital.foreact_tital = temp_tital;
		m_typhoon_forecast.typhoon_forecast_tital = m_typhoon_tital;
		return true;
	}
	else if (temp_tital.contains("WTPQ20 RJTD"))
	{
		m_typhoon_tital.broadcast_time = temp_tital.remove(QString("WTPQ20 RJTD")).toInt();
		temp_tital = QString("RJTD");
		//temp_tital += "日本";
		m_typhoon_tital.foreact_tital = temp_tital;
		m_typhoon_forecast.typhoon_forecast_tital = m_typhoon_tital;
		return true;
	}
	else if (temp_tital.contains("WTPQ20 VHHH"))
	{
		m_typhoon_tital.broadcast_time = temp_tital.remove(QString("WTPQ20 VHHH")).toInt();
		temp_tital = "WTPQ20 VHHH";
		temp_tital +="香港";
		m_typhoon_tital.foreact_tital = temp_tital;
		m_typhoon_forecast.typhoon_forecast_tital = m_typhoon_tital;
		return true;
	}
	else if (temp_tital.contains("WOCI41 BCGZ"))
	{
		m_typhoon_tital.broadcast_time = temp_tital.remove(QString("WOCI41 BCGZ")).toInt();
		temp_tital = "WOCI41 BCGZ";
		temp_tital += "广州";
		m_typhoon_tital.foreact_tital = temp_tital;
		m_typhoon_forecast.typhoon_forecast_tital = m_typhoon_tital;
		return true;
	}
	else if (temp_tital.contains("WOCI41 BCSH"))
	{
		m_typhoon_tital.broadcast_time = temp_tital.remove(QString("WOCI41 BCSH")).toInt();
		temp_tital = QString("BCSH");
		//temp_tital += "上海";
		m_typhoon_tital.foreact_tital = temp_tital;
		m_typhoon_forecast.typhoon_forecast_tital = m_typhoon_tital;
		return true;
	}
	else if (temp_tital.contains("WTPN31 PGTW"))
	{
		m_typhoon_tital.broadcast_time = temp_tital.remove(QString("WTPN31 PGTW")).toInt();
		temp_tital = "WTPN31 PGTW";
		temp_tital +="关岛";
		m_typhoon_tital.foreact_tital = temp_tital;
		m_typhoon_forecast.typhoon_forecast_tital = m_typhoon_tital;
		return true;
	}
	else
	{
		return false;
	}
}

bool read_typhoon::read_second_paragraph( QStringList analyes_message )
{
	QString temp_str = analyes_message.at(0);
	temp_str.remove("UTC").remove("INITIAL TIME");
	QStringList temp_strList = temp_str.split(" ",QString::SkipEmptyParts);
	QString tylvl = temp_strList.at(0);
	if (tylvl == "STPER TY" )
	{
		m_typhoon_live.ty_level = SPUER_TY;
	}
	else if (tylvl == "STY")
	{
		m_typhoon_live.ty_level = STY;
	}
	else if (tylvl == "TY")
	{
		m_typhoon_live.ty_level = TY;
	}
	else if (tylvl == "STS")
	{
		m_typhoon_live.ty_level = STS;
	}
	else if (tylvl == "TS")
	{
		m_typhoon_live.ty_level = TS;
	}
	else if (tylvl == "TD")
	{
		m_typhoon_live.ty_level = TD;
	}
	else
	{
		return false;
	}

	m_typhoon_live.typhoon_name = temp_strList.at(1);

	if (temp_strList.size()>= 3)
	{
		m_typhoon_live.typhoon_number = temp_strList.at(2).toInt();
		tylvl = temp_strList.at(2);
		m_typhoon_live.Live_year = tylvl.left(2).toInt();
	}

	if (temp_strList.size() >= 4)
	{
		tylvl = temp_strList.at(3);
		m_typhoon_live.typhoon_international_number = tylvl.remove("(").remove(")").toInt();
	}

	m_typhoon_live.Live_month = livemonth;
	if (temp_strList.size() >= 5)
	{
		tylvl = temp_strList.at(4);
		m_typhoon_live.Live_day = tylvl.left(2).toInt();
		m_typhoon_live.Live_hour = tylvl.mid(2,2).toInt();
		m_typhoon_live.Live_minute = tylvl.right(2).toInt();
	}

	temp_str = analyes_message.at(1);
	temp_strList = temp_str.split(" ",QString::SkipEmptyParts);
	tylvl = temp_strList.at(1);
	if (tylvl.contains(QString(".")))
	{
		m_typhoon_live.typhoon_Latitude = tylvl.remove("N").remove(".").toInt();
	}
	else
	{
		m_typhoon_live.typhoon_Latitude = tylvl.remove("N").toInt() * 10;
	}
	tylvl = temp_strList.at(2);
	if (tylvl.contains(QString(".")))
	{
		m_typhoon_live.typhoon_Longitude = tylvl.remove("E").remove(".").toInt();
	}
	else
	{
		m_typhoon_live.typhoon_Longitude = tylvl.remove("E").toInt() * 10;
	}
	tylvl = temp_strList.at(3);
	m_typhoon_live.central_pressure = tylvl.remove("hPa",Qt::CaseInsensitive).toInt();
	tylvl = temp_strList.at(4);
	m_typhoon_live.central_Wind_velocity = tylvl.remove("m/s",Qt::CaseInsensitive).toInt();

	return true;
}

bool read_typhoon::read_sixth_paragraph( QStringList analyes_message )
{
	QString temp_sixth_string = analyes_message.at(0);
	QStringList temp_sixth_list;
	if (temp_sixth_string.contains("SUBJECTIVE FORECAST"))//中国报文
	{
		if (m_typhoon_tital.foreact_tital == QString("BABJ"))//大北京
		{
			analyes_message.removeAt(0);
			if (read_second_paragraph(analyes_message))
			{
				analyes_message.removeAt(0);
				analyes_message.removeAt(0);
			}
			if (analyes_message.at(0).contains("30KTS"))
			{
				QString kts = analyes_message.at(0);
				m_typhoon_live.typhoon_30kts = kts.remove("30KTS").remove("KM").toInt();
				analyes_message.removeAt(0);
			}
			else
			{
				m_typhoon_live.typhoon_30kts = 0;
			}
			if (analyes_message.at(0).contains("50KTS"))
			{
				QString kts = analyes_message.at(0);
				m_typhoon_live.typhoon_50kts = kts.remove("50KTS").remove("KM").toInt();
				analyes_message.removeAt(0);
			}
			else
			{
				m_typhoon_live.typhoon_50kts = 0;
			}
			m_typhoon_forecast.typhoon_forecast_live = m_typhoon_live;
			{
				typhoon_point temp_typhoon_forecast_point;
				temp_typhoon_forecast_point.forecast_Latitude = m_typhoon_live.typhoon_Latitude;
				temp_typhoon_forecast_point.forecast_Longitude = m_typhoon_live.typhoon_Longitude;
				temp_typhoon_forecast_point.forecast_pressure = m_typhoon_live.central_pressure;
				temp_typhoon_forecast_point.forecast_speed = m_typhoon_live.central_Wind_velocity;
				temp_typhoon_forecast_point.forecast_time = "P+00HR";
				Vec_typhoon_forecast_point.append(temp_typhoon_forecast_point);
			}
			for (int i = 0;i<analyes_message.size();i++)
			{
				temp_sixth_string = analyes_message.at(i);
				temp_sixth_list = temp_sixth_string.split(" ");

				if (temp_sixth_list.at(0).contains("+") || temp_sixth_list.at(0).contains("-"))
				{
					typhoon_point temp_typhoon_forecast_point;

					temp_typhoon_forecast_point.forecast_time = temp_sixth_list.at(0);
					temp_sixth_string = temp_sixth_list.at(1);
					if (temp_sixth_string.contains(QString(".")))
					{
						temp_typhoon_forecast_point.forecast_Latitude = temp_sixth_string.remove("N").remove(".").toInt();
					}
					else
					{
						temp_typhoon_forecast_point.forecast_Latitude = temp_sixth_string.remove("N").toInt() * 10;
					}
					temp_sixth_string = temp_sixth_list.at(2);
					if (temp_sixth_string.contains(QString(".")))
					{
						temp_typhoon_forecast_point.forecast_Longitude = temp_sixth_string.remove("E").remove(".").toInt();
					}
					else
					{
						temp_typhoon_forecast_point.forecast_Longitude = temp_sixth_string.remove("E").toInt() * 10;
					}
					temp_sixth_string = temp_sixth_list.at(3);
					temp_typhoon_forecast_point.forecast_pressure = temp_sixth_string.remove("hPa",Qt::CaseInsensitive).toInt();
					temp_sixth_string = temp_sixth_list.at(4);
					temp_typhoon_forecast_point.forecast_speed = temp_sixth_string.remove("m/s",Qt::CaseInsensitive).remove("=").toInt();
					Vec_typhoon_forecast_point.append(temp_typhoon_forecast_point);

					//m_typhoon_forecast.typhoon_forecast_point = Vec_typhoon_forecast_point;
				}
				else if (temp_sixth_list.last().contains("km/h",Qt::CaseInsensitive))
				{
					typhoon_part temp_typhoon_forecast_part;
					temp_typhoon_forecast_part.forecast_time = QString("");
					temp_typhoon_forecast_part.ty_dircetion = 0;
					temp_typhoon_forecast_part.ty_speed = 0;

					temp_typhoon_forecast_part.forecast_time = temp_sixth_list.at(0);
					temp_typhoon_forecast_part.ty_dircetion = symbol_replace(temp_sixth_list.at(1));
					temp_sixth_string = temp_sixth_list.at(2);
					temp_typhoon_forecast_part.ty_speed = temp_sixth_string.remove("km/h",Qt::CaseInsensitive).remove("=").toInt();
					//Vec_typhoon_forecast_part.append(temp_typhoon_forecast_part);

					m_typhoon_forecast.typhoon_forecast_part = temp_typhoon_forecast_part;
				}
				m_typhoon_forecast.typhoon_forecast_point = Vec_typhoon_forecast_point;
			}
		}
		else if (m_typhoon_tital.foreact_tital == QString("BCSH"))//上海
		{
			QString stttt = analyes_message.at(1);
			stttt = stttt.remove("=");
			QStringList temp_strList = stttt.split(" ",QString::SkipEmptyParts);
			QString tylvl = temp_strList.at(0);
			if (tylvl == "STPER TY" )
			{
				m_typhoon_live.ty_level = SPUER_TY;
			}
			else if (tylvl == "STY")
			{
				m_typhoon_live.ty_level = STY;
			}
			else if (tylvl == "TY")
			{
				m_typhoon_live.ty_level = TY;
			}
			else if (tylvl == "STS")
			{
				m_typhoon_live.ty_level = STS;
			}
			else if (tylvl == "TS")
			{
				m_typhoon_live.ty_level = TS;
			}
			else if (tylvl == "TD")
			{
				m_typhoon_live.ty_level = TD;
			}
			//台风编号
			if (temp_strList.size()>=2)
			{
				tylvl = temp_strList.at(1);

				m_typhoon_live.typhoon_number = tylvl.toInt();
				m_typhoon_live.typhoon_international_number = tylvl.toInt();
				m_typhoon_live.Live_year = tylvl.left(2).toInt();
			}
			m_typhoon_live.typhoon_name = QString("");
			m_typhoon_live.Live_month = livemonth;

			if (temp_strList.size() >= 3)//日时分
			{
				tylvl = temp_strList.at(2);
				tylvl.remove("UTC");
				m_typhoon_live.Live_day = tylvl.left(2).toInt();
				m_typhoon_live.Live_hour = tylvl.mid(2,2).toInt();
				m_typhoon_live.Live_minute = tylvl.right(2).toInt();
			}
			//没有台风名称
			for (int j=2;j<analyes_message.size();j++)
			{
				stttt = analyes_message.at(j);
				stttt = stttt.remove("=");
				temp_strList = stttt.split(" ",QString::SkipEmptyParts);
				tylvl = temp_strList.at(0);
				if (tylvl == QString("00HR"))
				{
					tylvl = temp_strList.at(1);
					if (tylvl.contains(QString(".")))
					{
						m_typhoon_live.typhoon_Latitude = tylvl.remove("N").remove(".").toInt();
					}
					else
					{
						m_typhoon_live.typhoon_Latitude = tylvl.remove("N").toInt() * 10;
					}
					tylvl = temp_strList.at(2);
					if (tylvl.contains(QString(".")))
					{
						m_typhoon_live.typhoon_Longitude = tylvl.remove("E").remove(".").toInt();
					}
					else
					{
						m_typhoon_live.typhoon_Longitude = tylvl.remove("E").toInt() * 10;
					}

					m_typhoon_live.central_pressure = 0;
					m_typhoon_live.central_Wind_velocity = 0;
					m_typhoon_live.typhoon_30kts = 0;
					m_typhoon_live.typhoon_50kts = 0;

					m_typhoon_forecast.typhoon_forecast_live = m_typhoon_live;
					{
						typhoon_point temp_typhoon_forecast_point;
						temp_typhoon_forecast_point.forecast_Latitude = m_typhoon_live.typhoon_Latitude;
						temp_typhoon_forecast_point.forecast_Longitude = m_typhoon_live.typhoon_Longitude;
						temp_typhoon_forecast_point.forecast_pressure = m_typhoon_live.central_pressure;
						temp_typhoon_forecast_point.forecast_speed = m_typhoon_live.central_Wind_velocity;
						temp_typhoon_forecast_point.forecast_time = "P+00HR";
						Vec_typhoon_forecast_point.append(temp_typhoon_forecast_point);
					}
					//读下一行移动方向移动速度
					j++;
					stttt = analyes_message.at(j);
					stttt = stttt.remove("=");
					temp_strList = stttt.split(" ",QString::SkipEmptyParts);
					tylvl = temp_strList.at(0);

					typhoon_part temp_typhoon_forecast_part;
					temp_typhoon_forecast_part.forecast_time = QString("");
					temp_typhoon_forecast_part.ty_dircetion = 0;
					temp_typhoon_forecast_part.ty_speed = 0;

					temp_typhoon_forecast_part.forecast_time = temp_strList.at(0);
					tylvl = temp_strList.at(1);
					temp_typhoon_forecast_part.ty_dircetion = tylvl.left(3).toInt();
					tylvl = tylvl.right(3);
					temp_typhoon_forecast_part.ty_speed = tylvl.toInt();
					//Vec_typhoon_forecast_part.append(temp_typhoon_forecast_part);

					m_typhoon_forecast.typhoon_forecast_part = temp_typhoon_forecast_part;
				}
				if (tylvl == QString("P24HR") || tylvl == QString("P48HR") || tylvl == QString("P72HR") || tylvl == QString("P96HR"))
				{
					typhoon_point temp_typhoon_forecast_point;

					temp_typhoon_forecast_point.forecast_time = QString("%1+%2").arg(tylvl.left(1)).arg(tylvl.right(4));
					temp_sixth_string = temp_strList.at(1);
					if (temp_sixth_string.contains(QString(".")))
					{
						temp_typhoon_forecast_point.forecast_Latitude = temp_sixth_string.remove("N").remove(".").toInt();
					}
					else
					{
						temp_typhoon_forecast_point.forecast_Latitude = temp_sixth_string.remove("N").toInt() * 10;
					}
					temp_sixth_string = temp_strList.at(2);
					if (temp_sixth_string.contains(QString(".")))
					{
						temp_typhoon_forecast_point.forecast_Longitude = temp_sixth_string.remove("E").remove(".").toInt();
					}
					else
					{
						temp_typhoon_forecast_point.forecast_Longitude = temp_sixth_string.remove("E").toInt() * 10;
					}
					//没有速度和压力
					temp_typhoon_forecast_point.forecast_pressure = 0;
					temp_typhoon_forecast_point.forecast_speed = 0;
					Vec_typhoon_forecast_point.append(temp_typhoon_forecast_point);
				}
				m_typhoon_forecast.typhoon_forecast_point = Vec_typhoon_forecast_point;
			}
		}
	}
	else if (temp_sixth_string.contains("RSMC TROPICAL CYCLONE ADVISORY"))//日本报文，从我找到的报文中，日本的报文好像都以这个开头
	{
		for (int j=1;j<analyes_message.size();j++)
		{
			QString stttt = analyes_message.at(j);

			if (stttt.left(4) == "NAME")
			{
				QStringList temp_strList = stttt.split(" ",QString::SkipEmptyParts);
				int temp_strList_location = 1;
				int is_n_plus = 0;
				QString tylvl;
				for (temp_strList_location;temp_strList_location<temp_strList.size();temp_strList_location++)
				{
					tylvl = temp_strList.at(temp_strList_location);
					if (typhoonLevelComfirm(tylvl,is_n_plus))
					{
						break;
					}
				}
				temp_strList_location = temp_strList_location + is_n_plus;
				//台风编号
				//if (temp_strList.size()>=3)
				if (temp_strList.size() >= temp_strList_location + 1)
				{
					//m_typhoon_live.typhoon_number = temp_strList.at(2).toInt();
					//tylvl = temp_strList.at(2);
					//m_typhoon_live.Live_year = tylvl.left(2).toInt();
					tylvl = temp_strList.at(temp_strList_location);

					m_typhoon_live.typhoon_number = tylvl.toInt();
					m_typhoon_live.Live_year = tylvl.left(2).toInt();
					temp_strList_location++;
				}
				//台风名称
				//if (temp_strList.size() >= 4)
				if (temp_strList.size() >= temp_strList_location + 1)
				{
					//m_typhoon_live.typhoon_name = temp_strList.at(3);
					m_typhoon_live.typhoon_name = temp_strList.at(temp_strList_location);
					temp_strList_location++;
				}
				//台风国际编号
				//if (temp_strList.size() >= 5)
				if (temp_strList.size() >= temp_strList_location + 1)
				{
					//tylvl = temp_strList.at(4);
					tylvl = temp_strList.at(temp_strList_location);
					m_typhoon_live.typhoon_international_number = tylvl.remove("(").remove(")").toInt();
				}
			}
			m_typhoon_live.Live_month = livemonth;
			if (stttt.contains("ANALYSIS"))
			{
				stttt = analyes_message.at(++j);
				if (stttt.left(4) == "PSTN")//present 现在时
				{
					QString tylvl;
					QStringList temp_strList = stttt.split(" ",QString::SkipEmptyParts);

					if (temp_strList.size() >= 2)//日时分
					{
						tylvl = temp_strList.at(1);
						tylvl.remove("UTC");
						m_typhoon_live.Live_day = tylvl.left(2).toInt();
						m_typhoon_live.Live_hour = tylvl.mid(2,2).toInt();
						m_typhoon_live.Live_minute = tylvl.right(2).toInt();
					}

					if (temp_strList.size() >= 3)//纬度
					{
						tylvl = temp_strList.at(2);
						if (tylvl.contains(QString(".")))
						{
							m_typhoon_live.typhoon_Latitude = tylvl.remove("N").remove(".").toInt();
						}
						else
						{
							m_typhoon_live.typhoon_Latitude = tylvl.remove("N").toInt() * 10;
						}
					}

					if (temp_strList.size() >= 4)//经度
					{
						tylvl = temp_strList.at(3);
						if (tylvl.contains(QString(".")))
						{
							m_typhoon_live.typhoon_Longitude = tylvl.remove("E").remove(".").toInt();
						}
						else
						{
							m_typhoon_live.typhoon_Longitude = tylvl.remove("E").toInt() * 10;
						}
					}
				}
				j++;
				while(j<analyes_message.size())
				{
					stttt = analyes_message.at(j);
					QStringList temp_strList = stttt.split(" ",QString::SkipEmptyParts);
					QString temp_strList0 = temp_strList.at(0);
					QString temp_staList1;
					if (temp_strList0 == "MOVE")
					{
						temp_staList1 = temp_strList.at(1);

						typhoon_part temp_typhoon_forecast_part;
						temp_typhoon_forecast_part.forecast_time = QString("");
						temp_typhoon_forecast_part.ty_dircetion = 0;
						temp_typhoon_forecast_part.ty_speed = 0;

						temp_typhoon_forecast_part.forecast_time = QString("P12HR");
						temp_typhoon_forecast_part.ty_dircetion = symbol_replace(temp_staList1);
						temp_staList1 = temp_strList.at(2);
						if (temp_staList1.contains(QString("SLOWLY")))
						{
							temp_typhoon_forecast_part.ty_speed = 0;
						}
						else
						{
							temp_typhoon_forecast_part.ty_speed = temp_staList1.remove("KT",Qt::CaseInsensitive).remove("=").toInt();
						}
						m_typhoon_forecast.typhoon_forecast_part = temp_typhoon_forecast_part;
					}
					else if (temp_strList0 == "PRES")
					{
						temp_staList1 = temp_strList.at(1);
						m_typhoon_live.central_pressure = temp_staList1.remove("HPA",Qt::CaseInsensitive).toInt();
					}
					else if (temp_strList0 == "MXWD")
					{
						temp_staList1 = temp_strList.at(1);
						m_typhoon_live.central_Wind_velocity = temp_staList1.remove("KT",Qt::CaseInsensitive).toInt();
					}
					else if (temp_strList0 == "GUST")
					{
					}
					else if (temp_strList0 == "30KT")
					{
						temp_staList1 = temp_strList.at(1);
						m_typhoon_live.typhoon_30kts = temp_staList1.remove("NM").remove("KM").toInt();
					}
					else if (temp_strList0 == "50KT")
					{
						temp_staList1 = temp_strList.at(1);
						m_typhoon_live.typhoon_50kts = temp_staList1.remove("NM").remove("KM").toInt();
					}
					else if (temp_strList0.contains("FORECAST"))
					{
						break;
					}
					j++;
				}
			}
			m_typhoon_forecast.typhoon_forecast_live = m_typhoon_live;
			if (stttt.contains("FORECAST"))
			{
				j++;
				Vec_typhoon_forecast_point.clear();
				{
					typhoon_point temp_typhoon_forecast_point;
					temp_typhoon_forecast_point.forecast_Latitude = m_typhoon_live.typhoon_Latitude;
					temp_typhoon_forecast_point.forecast_Longitude = m_typhoon_live.typhoon_Longitude;
					temp_typhoon_forecast_point.forecast_pressure = m_typhoon_live.central_pressure;
					temp_typhoon_forecast_point.forecast_speed = m_typhoon_live.central_Wind_velocity;
					temp_typhoon_forecast_point.forecast_time = "P+00HR";
					Vec_typhoon_forecast_point.append(temp_typhoon_forecast_point);
				}
				int hfList = analyes_message.size()-j;
				int hfListcount = hfList/5;//除以5是因为每个预报块都是5行，这样就知道有几次预报了
				for (int hfi = 0;hfi<hfListcount;hfi++)
				{
					typhoon_point temp_typhoon_forecast_point;


					QString tylvl = analyes_message.at(j + hfi*5);
					QStringList tyList = tylvl.split(" ",QString::SkipEmptyParts);
					tylvl = tyList.at(0);
					temp_typhoon_forecast_point.forecast_time = QString("P+%1HR").arg(tylvl.remove("HF",Qt::CaseInsensitive));
					tylvl = tyList.at(2);
					if (tylvl.contains(QString(".")))
					{
						temp_typhoon_forecast_point.forecast_Latitude = tylvl.remove("N").remove(".").toInt();
					}
					else
					{
						temp_typhoon_forecast_point.forecast_Latitude = tylvl.remove("N").toInt() * 10;
					}
					tylvl = tyList.at(3);
					if (tylvl.contains(QString(".")))
					{
						temp_typhoon_forecast_point.forecast_Longitude = tylvl.remove("E").remove(".").toInt();
					}
					else
					{
						temp_typhoon_forecast_point.forecast_Longitude = tylvl.remove("E").toInt() * 10;
					}

					tylvl = analyes_message.at(j + hfi*5 + 2);
					tyList = tylvl.split(" ",QString::SkipEmptyParts);
					tylvl = tyList.at(1);
					temp_typhoon_forecast_point.forecast_pressure = tylvl.remove("HPA",Qt::CaseInsensitive).toInt();

					tylvl = analyes_message.at(j + hfi*5 + 3);
					tyList = tylvl.split(" ",QString::SkipEmptyParts);
					tylvl = tyList.at(1);
					temp_typhoon_forecast_point.forecast_speed = tylvl.remove("KT",Qt::CaseInsensitive).toInt();

					Vec_typhoon_forecast_point.append(temp_typhoon_forecast_point);
				}
				m_typhoon_forecast.typhoon_forecast_point = Vec_typhoon_forecast_point;
				//return true;
			}
		}
	}
	return true;
}

int read_typhoon::symbol_replace( QString str )
{
	str.remove('P');
	str.remove('A');
	int dir = 0;
	if (!str.compare("N"))//特殊符号替换
	{
		dir = 0;
	}
	else if (!str.compare("NNE"))//特殊符号替换
	{
		dir = 23;
	}
	else if (!str.compare("NE"))//特殊符号替换
	{
		dir = 45;
	}
	else if (!str.compare("ENE"))//特殊符号替换
	{
		dir = 68;
	}
	else if (!str.compare("E"))//特殊符号替换
	{
		dir = 90;
	}
	else if (!str.compare("ESE"))//特殊符号替换
	{
		dir = 113;
	}
	else if (!str.compare("SE"))//特殊符号替换
	{
		dir = 135;
	}
	else if (!str.compare("SSE"))//特殊符号替换
	{
		dir = 158;
	}
	else if (!str.compare("S"))//特殊符号替换
	{
		dir = 180;
	}
	else if (!str.compare("SSW"))//特殊符号替换
	{
		dir = 203;
	}
	else if (!str.compare("SW"))//特殊符号替换
	{
		dir = 225;
	}
	else if (!str.compare("WSW"))//特殊符号替换
	{
		dir = 248;
	}
	else if (!str.compare("W"))//特殊符号替换
	{
		dir = 270;
	}
	else if (!str.compare("WWN"))//特殊符号替换
	{
		dir = 293;
	}
	else if (!str.compare("NW"))//特殊符号替换
	{
		dir = 315;
	}
	else if (!str.compare("NNW"))//特殊符号替换
	{
		dir = 338;
	}
	else if (!str.compare("C"))//特殊符号替换
	{
		dir = 0;
	}
	else 
	{
		dir = str.toInt();
	}
	return dir;
}

bool read_typhoon::typhoonLevelComfirm( QString tylvl ,int &nlocation)
{
	nlocation = 1;
	//if (tylvl == "STPER TY" )
	/**@brief 按空格分隔，不可能传进来stper ty的，只检查stper，然后n加2*/
	if (tylvl == QString("STPER"))
	{
		m_typhoon_live.ty_level = SPUER_TY;
		nlocation = 2;
		return true;
	}
	else if (tylvl == QString("STY"))
	{
		m_typhoon_live.ty_level = STY;
		return true;
	}
	else if (tylvl == QString("TY"))
	{
		m_typhoon_live.ty_level = TY;
		return true;
	}
	else if (tylvl == QString("STS"))
	{
		m_typhoon_live.ty_level = STS;
		return true;
	}
	else if (tylvl == QString("TS"))
	{
		m_typhoon_live.ty_level = TS;
		return true;
	}
	else if (tylvl == QString("TD"))
	{
		m_typhoon_live.ty_level = TD;
		return true;
	}
	else
	{
		return false;
	}
}
