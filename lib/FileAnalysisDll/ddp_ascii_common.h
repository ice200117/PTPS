 /******************************************************/
 //Copyrigth (C),2010-2011,ITC. Co.,Ltd.
 //FileName:   ddp_ascii_common.h
 //Author:     王娟  朱孟坤
 //Data:     2011-4-13
 //Description：ascii格式解码公共头文件
 //Version： V4.1.1
 //Latest Time: 2011-11-23
 //Tester:    王娟
 //Modified:2012-11-23:修改解码中的返回值：
 //                    #define ERROR_FILE_NAME                 (15)//文件名错误
 //                    #define ERROR_FILE_NOT_EXIT              (16)//文件不存在或找不到
 //                    #define ERROR_NOT_ENOUGH_STRUCT_BUFFER      (13) //返回的结构体个数不足
 //                    #define ERROR_NOT_ENOUGH_ERRORMSG_BUFFER    (11)//错误消息缓冲区长度不够
 //                    #define ERROR_NOT_ENOUGH_REPORT_BUFFER      (14)//返回的报告缓冲区长度不足
 //                    #define DECODE_ PARTAIL_SUCCESS            (1)//解码部分正确部分错误
 //                    #define ERROR_DECODE_FAILURE               (2)//解码全部失败
 //                    #define ERROR_NOT_ENOUGH_MSG_BUFFER         (12)//消息缓冲区长度不够
 /*********************************************************/
#ifndef __DDP_ASCII_COMMON_H__
#define __DDP_ASCII_COMMON_H__

#define MAX_AUTOREPORT_LEN              (8192)
#define SUCCESS_OP                      (0)
#define SUCCESS_OP_HEADER                 (102)
#define ERROR_FILE_NAME_IS_NULL         (100)
#define ERROR_ACCESS_FILE               (101)
#define ERROR_END_OF_FILE               (1000)
#define ERROR_REPORT_TOO_LONG           (1001)
#define ERROR_REPORT_TOO_SHORT          (1002)

#define ERROR_NOT_ENOUGH_GROUP          (1003)
#define ERROR_INVALID_CHARACTER         (1004)
#define FILE_END_ERROR                  (1005)
#define ERROR_END_OF_RECORD             (1006)
#define ERROR_START_OF_FILE             (1007)
#define ERROR_FILE_FORMAT               (1011)
#define ERROR_SECTION_TOO_SHORT         (1012)
#define ERROR_INTEGER_VAR               (1013)
#define ERROR_DOUBLE_VAR                (1014)
//#define ERROR_FILE_NAME                 (1023)
#define ERROR_FILE_NAME                 (15)//文件名错误
#define ERROR_FILE_NOT_EXIT              (16)//文件不存在或找不到

#define ERROR_NOT_ENOUGH_STRUCT_BUFFER		(13) //返回的结构体个数不足
#define ERROR_NOT_ENOUGH_ERRORMSG_BUFFER	(11)//错误消息缓冲区长度不够
#define ERROR_NOT_ENOUGH_REPORT_BUFFER		(14)//返回的报告缓冲区长度不足

//2012-11-23新增错误返回号
#define DECODE_PARTAIL_SUCCESS            (1)//解码部分正确部分错误
#define ERROR_DECODE_FAILURE               (2)//解码全部失败
#define ERROR_NOT_ENOUGH_MSG_BUFFER         (12)//消息缓冲区长度不够

#define	D_VALUE                                 (0.01)
#define	DD_VALUE                                (0.1)

#define DECODE_STRCAT(ErrMsg,ErrMsgLen,TmpErrMsg) do{		  \
    if(strlen((ErrMsg)) + strlen((TmpErrMsg)) >= (ErrMsgLen)) \
    return ERROR_NOT_ENOUGH_ERRORMSG_BUFFER;          \
     else 							  \
     strcat((ErrMsg), (TmpErrMsg)); 			  \
}while(0)

#define FILE_NAME_SEPARATOR 		'_'
#define MAX_FILE_NAME			128
#define MAX_TYPE_LEN 128
#define TIME_POSITION_IN_FILE_NAME	5
/*写入报告*/
#define REPORT_STRCAT(reportbuffer,reportbuflen,report) do{				\
    if(strlen((reportbuffer)) + strlen((report)) >= (reportbuflen))			\
    return ERROR_NOT_ENOUGH_REPORT_BUFFER; 					\
    else										\
    strcat((reportbuffer), (report));					\
}while(0)
/*新增加结构体*/
typedef struct _new_add_struct{
    char acWriteYearMonthDay[10];	/*编报年月日*/
    char acWriteHourMinSec[10];		/*编报时分秒*/
	char acCCCC[5];					/*编报中心*/
    char acFlag[5];					/*订正标志*/
}new_add_struct;


#define ERROR_PRECIPITATION_PREFIX      (2001)
#define ERROR_PRECIPITATION_SUFFIX      (2002)

#define AWS_REPORT_END_ID               '='
#define AWS_FILE_END_ID                 "NNNN"

#define DEFAULT_VALUE                   (999999)

#ifdef __cplusplus
extern "C" {
#endif
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <ctype.h>
	enum    DATATYPE
	{
		DT_INTEGER = 0,
		DT_STRING  = 1,
		DT_DOUBLE  = 2
	};

	typedef struct _tagFIELD_DEFINE
	{
		int     nType;
		int     nFieldLength;
		int     nScale;
	}ASCII_FIELD_DEFINE;

	typedef struct _tagAFileElementMode 
	{
		char    szTag[3];
		char    iItem;
		int     nMode;
	}A_FILE_ELEMENT_MODE;

	typedef struct _tagCloudShape
	{
		char    szClodShape[4];
		int     nShape;
	}CLOUD_SHAPE;

	typedef struct _tagWindDirect
	{
		char    szWindDirect[4];
		double  dDirect;
	}WIND_DIRECT;

	void    handle_file_name(const char *pszFileName,new_add_struct *pszAdd);
	char *  trim(char * pszStr);
	char *  trim_new(char * pszStr);
	char *  ltrim(char * pszStr);
	char *  rtrim(char * pszStr);
	char *  rtrim_new(char *s);
	char *  rtrimex(char * pszStr);
	const char * GetStringStart(const char * pszStr);
	const char * GetStringStart2(const char * pszStr);
	int     GetOneReport_ZCZC(FILE *fp, char *report, int *report_len);
	int     GetOneReport(FILE *fp, char *report, int *report_len);
	int     GetAutoReport(FILE *fp, char *report, int *report_len);
	int     GetCloudType(const char * pszCloud);
	double  GetWindDirect(const char * pszWindDirect);
	int     GetAWSPrecipitation6or12(char * pszPrecipitaion, double * pdPreciptation, int * pnTimeFlag, int * pnError);
	int     GetAWS24PressureTemperatureChange(const char * pszPT, double * pdPC, double * pdTC, int * pnError);
	int     GetAWS24Rain(const char * pszRain, double * pdRain, int * pnError);
	int     GetAWS24MaxTemperature(const char * pszTempertature, double * pdMaxTemperature, int * pnError);
	int     GetAWS24MinTemperature(const char * pszTempertature, double * pdMinTemperature, int * pnError);
	int     GetAWS12AverTemperature(const char * pszTempertature, double * pdTemperature, int * pnError);
	int     GetAWSMaxWindSpeed(const char * pszWind, double * pdWindSpeed, int * pnError);
	int     GetAWSMaxWindDirect(const char * pszWind, double * pdWindDirect, int * pnError);
	int     GetAWSWeatherWhirl(const char * pszWhirl, int * pnWhirl, int * pnWhirlDirect, int * pnError);
	int     GetAWSGlaze(const char * pszGlaze, int * pnGlaze, int * pnError);
	int     GetAWSHaliDiameter(const char * pszHali, double * pdDiameter, int * pnError);
	int     GetStationNo(const char * pszStationNo, int * pnError);
	int     GetIntegerValue(const char * pszValue, char cDefault, int nScale, int * pnError);
	double  GetDoubleValue(const char * pszValue, char cDefault, int nScale, int * pnError);
	double  GetDoubleValue_1(const char * pszValue, char * pszDefault, int nScale, int * pnError);
	double  GetLatitudeLongitude(const char * pszValue, int nType, int nScale, int *pnError);
	double  GetWindSpeed(const char * pszValue, int nScale, char cDefault, int * pnError);
	double  GetDepthTemperature(const char * pszValue, int nScale, char cDefault, int * pnError);
	int     ConvertBuffer(char *pInput);
	int     GetOneReport_ZCZC_1(FILE *fpReport,char *report,int *report_len);
	int     iSubStringByComma_r(unsigned char *pszBuf, unsigned char *pszString, int *iGroup_Ret);

#ifdef __cplusplus
};
#endif
#endif
