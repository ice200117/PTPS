#ifndef _DDP_DECODE_AWS_SUNDAY_H
#define _DDP_DECODE_AWS_SUNDAY_H_

//#include "mmd_ascii.h"
#include "ddp_ascii_common.h"
//#pragma options align=packed
#pragma pack(push, 1)//   这里以后定义的structrue将以1字节对齐  
//地面自动站日照数据文件
typedef  struct _GroundAutoStationSunlightDataRP
{
    char acStationNo[5+1];              /*区站号*/   //V01000
    double dbLatitude;                  /*纬度*/
    double dbLongitude;                 /*经度*/
    int iSunlightMode;                  /*日照时制方式*/
    int iObservYear;                    /*资料观测年*/ //V04001
    int iObservMonth;                   /*资料观测月*/ //V04002
    int iObservDay;                     /*资料观测日*/ //V04003
    int iObservHour;                    /*资料观测时*/
    int iObservMinute;                  /*资料观测分*/
    int iObservSecond;					/*资料观测秒*/
    double dSunlightTime0_1;               /*0-1时日照时间*/
    double dSunlightTime1_2;               /*1-2时日照时间*/
    double dSunlightTime2_3;               /*2-3时日照时间*/
    double dSunlightTime3_4;               /*3-4时日照时间*/
    double dSunlightTime4_5;               /*4-5时日照时间*/
    double dSunlightTime5_6;               /*5-6时日照时间*/
    double dSunlightTime6_7;               /*6-7时日照时间*/
    double dSunlightTime7_8;               /*7-8时日照时间*/
    double dSunlightTime8_9;               /*8-9时日照时间*/
    double dSunlightTime9_10;          /*9-10时日照时间*/
    double dSunlightTime10_11;         /*10-11时日照时间*/
    double dSunlightTime11_12;         /*11-12时日照时间*/
    double dSunlightTime12_13;         /*12-13时日照时间*/
    double dSunlightTime13_14;         /*13-14时日照时间*/
    double dSunlightTime14_15;         /*14-15时日照时间*/
    double dSunlightTime15_16;         /*15-16时日照时间*/
    double dSunlightTime16_17;         /*16-17时日照时间*/
    double dSunlightTime17_18;         /*17-18时日照时间*/
    double dSunlightTime18_19;         /*18-19时日照时间*/
    double dSunlightTime19_20;         /*19-20时日照时间*/
    double dSunlightTime20_21;         /*20-21时日照时间*/
    double dSunlightTime21_22;         /*21-22时日照时间*/
    double dSunlightTime22_23;         /*22-23时日照时间*/
    double dSunlightTime23_24;         /*23-24时日照时间*/
    double dSunlightTotal;                 /*日合计日照时数*/ //v14032

    /*新增结构体成员*/
    char acWriteReportCenter[6];               /*编报中心*/
    int  acWriteYear;               /*编报年*/
    int  acWriteMonth;               /*编报月*/
    int  acWriteDay;               /*编报日*/
    int  acWriteHour;             /*编报时*/
    int  acWriteMin;             /*编报分*/
    int  acWriteSec;             /*编报秒*/
    char acFlag[5];                         /*订正标志*/
    char acFileName[MAX_FILE_NAME];     /*文件名*/
    int iReportLen;                         /*报告长度*/
    char acType[MAX_TYPE_LEN];              /*资料类别*/
	char acRType[4+1];			/*报告类别*/
	char acAA[2+1];				/*地理编码*/
    char acNO[10];				/*公报编号*/
	char acObservationMode;
}
GroundAutoStationSunlightDataRP;
#pragma pack(pop)   //   弹出编译栈顶的对齐值(1字节),并作为以后定义的structrue的字节对齐值 
/*本文件包含的函数声明*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
	int ProcessOneReport(const char * pszReport, GroundAutoStationSunlightDataRP * pRpt, char * pszErrorMsg,int iErrorMsgLen,int iRpt);
	int ProcessGroundAutoStationSunlightDataRP(const char * pszReportFileName,char *pszReportBuffer,int *iReportBufferLen, GroundAutoStationSunlightDataRP * pRpt, int *piReportCount, char * pszErrorMsg,int iErrorMsgLen);
#ifdef __cplusplus
};
#endif

//#pragma options align=power

#endif

