#include "decode.h"
#include <QDebug>
decode::decode()
{

}

decode::decode(QString fileName, enum FUJIAN_DATATYPE dataType){
	setFileName(fileName);
	setDateType(dataType);
}

decode::~decode()
{

}

int decode::decode_file(){

	if(m_dataType == AWS){
		struct AWSData* readAWSData = NULL;
		int report_num = 0;
		report_num = readAWS(m_fileName.toStdString().c_str(), &readAWSData);

		if(report_num>0){
			m_AWSDataList.clear();
			for(int i=0;i<report_num;i++){
				m_AWSDataList.append(readAWSData[i]);
			}

		}

		free(readAWSData);
		return report_num;
	}else if(m_dataType == ASS){
		GroundAutoStationSunlightDataRP* readASSData = NULL;
		int ret = -1;
		int buf_len = 10*1024*1024;
		char* rptBuffer = NULL;
		int rptCount = 50000;
		int err_len = 10*1024*1024;
		char* err_msg = NULL;

		rptBuffer = (char*)calloc(buf_len, sizeof(char));
		readASSData = (GroundAutoStationSunlightDataRP*)calloc(rptCount, sizeof(GroundAutoStationSunlightDataRP));
		err_msg = (char*)calloc(err_len, sizeof(char));

		
		ret = ProcessGroundAutoStationSunlightDataRP(m_fileName.toStdString().c_str(), rptBuffer, &buf_len, readASSData, &rptCount,
															err_msg, err_len);
		if(ret == 0){
			m_ASSDataList.clear();
			for(int i=0;i<rptCount;i++){

				m_ASSDataList.append(readASSData[i]);
			}
			free(rptBuffer);
			free(err_msg);
			free(readASSData);
			return rptCount;
		}else{
			free(rptBuffer);
			free(err_msg);
			free(readASSData);
			return 0;
		}
	}
	//else if(m_dataType == A0){

	//	int report_num = 0;
	//	read_a0 *m_read_a0 = new read_a0;
	//	m_read_a0->openfile(m_fileName);
	//	m_read_a0->analyzeelement();
	//	m_A0DataList = m_read_a0->GetdbStorage();

	//	report_num = m_A0DataList.size();

	//	delete m_read_a0;

	//	return report_num;
	//}

	return 0;
}

int decode::decode_file(QString fileName, enum FUJIAN_DATATYPE dataType){
	qDebug() << fileName << endl;
	setFileName(fileName);
	setDateType(dataType);
	return decode_file();
}

int decode::decode_file(QString fileName, QList<struct AWSData>& AWSDataList){
	int report_num = decode_file(fileName, AWS);
	AWSDataList = getAWSDataList();
	return report_num;
}

int decode::decode_file(QString fileName, QList<GroundAutoStationSunlightDataRP>& ASSDataList){
	int report_num = decode_file(fileName, ASS);
	ASSDataList = getASSDataList();
	return report_num;
}
int decode::decode_file(QString fileName, QList<dbStorage>& A0DataList){
	int report_num = decode_file(fileName, A0);
	A0DataList = getA0DataList();
	return report_num;
}