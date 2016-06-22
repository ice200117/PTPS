#ifndef DECODE_H
#define DECODE_H

//#include "tceas_decode_global.h"

#include <QString>
#include <QList>
#include "read_A0.h"

// extern "C" {
#include "dataType.h"
#include "algPack.h"
#include "ddp_decode_aws_sunday.h"
// };

enum FUJIAN_DATATYPE{
	AWS,
	ASS,
	A0
};


class decode
{
public:
	decode();
	decode(QString fileName, enum FUJIAN_DATATYPE dataType);
	~decode();

	void setFileName(QString fileName){m_fileName = fileName;};
	void setDateType(enum FUJIAN_DATATYPE dataType){m_dataType = dataType;};

	QList<struct AWSData> getAWSDataList(){return m_AWSDataList;}
	QList<GroundAutoStationSunlightDataRP> getASSDataList(){return m_ASSDataList;}
	QList<dbStorage> getA0DataList(){return m_A0DataList;}

	int decode_file();
	int decode_file(QString fileName, enum FUJIAN_DATATYPE dataType);

	int decode_file(QString fileName, QList<struct AWSData>&);
	int decode_file(QString fileName, QList<GroundAutoStationSunlightDataRP>&);
	int decode_file(QString fileName, QList<dbStorage>&);



private:
	QString m_fileName;
	enum FUJIAN_DATATYPE m_dataType;

	QList<struct AWSData> m_AWSDataList;
	QList<GroundAutoStationSunlightDataRP> m_ASSDataList;
	QList<dbStorage> m_A0DataList;

	
};

#endif // DECODE_H
