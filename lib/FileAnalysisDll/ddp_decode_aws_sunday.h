#ifndef _DDP_DECODE_AWS_SUNDAY_H
#define _DDP_DECODE_AWS_SUNDAY_H_

//#include "mmd_ascii.h"
#include "ddp_ascii_common.h"
//#pragma options align=packed
#pragma pack(push, 1)//   �����Ժ����structrue����1�ֽڶ���  
//�����Զ�վ���������ļ�
typedef  struct _GroundAutoStationSunlightDataRP
{
    char acStationNo[5+1];              /*��վ��*/   //V01000
    double dbLatitude;                  /*γ��*/
    double dbLongitude;                 /*����*/
    int iSunlightMode;                  /*����ʱ�Ʒ�ʽ*/
    int iObservYear;                    /*���Ϲ۲���*/ //V04001
    int iObservMonth;                   /*���Ϲ۲���*/ //V04002
    int iObservDay;                     /*���Ϲ۲���*/ //V04003
    int iObservHour;                    /*���Ϲ۲�ʱ*/
    int iObservMinute;                  /*���Ϲ۲��*/
    int iObservSecond;					/*���Ϲ۲���*/
    double dSunlightTime0_1;               /*0-1ʱ����ʱ��*/
    double dSunlightTime1_2;               /*1-2ʱ����ʱ��*/
    double dSunlightTime2_3;               /*2-3ʱ����ʱ��*/
    double dSunlightTime3_4;               /*3-4ʱ����ʱ��*/
    double dSunlightTime4_5;               /*4-5ʱ����ʱ��*/
    double dSunlightTime5_6;               /*5-6ʱ����ʱ��*/
    double dSunlightTime6_7;               /*6-7ʱ����ʱ��*/
    double dSunlightTime7_8;               /*7-8ʱ����ʱ��*/
    double dSunlightTime8_9;               /*8-9ʱ����ʱ��*/
    double dSunlightTime9_10;          /*9-10ʱ����ʱ��*/
    double dSunlightTime10_11;         /*10-11ʱ����ʱ��*/
    double dSunlightTime11_12;         /*11-12ʱ����ʱ��*/
    double dSunlightTime12_13;         /*12-13ʱ����ʱ��*/
    double dSunlightTime13_14;         /*13-14ʱ����ʱ��*/
    double dSunlightTime14_15;         /*14-15ʱ����ʱ��*/
    double dSunlightTime15_16;         /*15-16ʱ����ʱ��*/
    double dSunlightTime16_17;         /*16-17ʱ����ʱ��*/
    double dSunlightTime17_18;         /*17-18ʱ����ʱ��*/
    double dSunlightTime18_19;         /*18-19ʱ����ʱ��*/
    double dSunlightTime19_20;         /*19-20ʱ����ʱ��*/
    double dSunlightTime20_21;         /*20-21ʱ����ʱ��*/
    double dSunlightTime21_22;         /*21-22ʱ����ʱ��*/
    double dSunlightTime22_23;         /*22-23ʱ����ʱ��*/
    double dSunlightTime23_24;         /*23-24ʱ����ʱ��*/
    double dSunlightTotal;                 /*�պϼ�����ʱ��*/ //v14032

    /*�����ṹ���Ա*/
    char acWriteReportCenter[6];               /*�౨����*/
    int  acWriteYear;               /*�౨��*/
    int  acWriteMonth;               /*�౨��*/
    int  acWriteDay;               /*�౨��*/
    int  acWriteHour;             /*�౨ʱ*/
    int  acWriteMin;             /*�౨��*/
    int  acWriteSec;             /*�౨��*/
    char acFlag[5];                         /*������־*/
    char acFileName[MAX_FILE_NAME];     /*�ļ���*/
    int iReportLen;                         /*���泤��*/
    char acType[MAX_TYPE_LEN];              /*�������*/
	char acRType[4+1];			/*�������*/
	char acAA[2+1];				/*�������*/
    char acNO[10];				/*�������*/
	char acObservationMode;
}
GroundAutoStationSunlightDataRP;
#pragma pack(pop)   //   ��������ջ���Ķ���ֵ(1�ֽ�),����Ϊ�Ժ����structrue���ֽڶ���ֵ 
/*���ļ������ĺ�������*/
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

