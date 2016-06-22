 /******************************************************/
 //Copyrigth (C),2010-2011,ITC. Co.,Ltd.
 //FileName:   ddp_aws_decode_sundata.c
 //Author:      ���
 //Data:     2011-08-22
 //Description��ascii��ʽ����������������ļ�
 //Version�� V4.1.1
 //Latest Time: 2012-11-29
 //Tester:    ����
 //modified:������ 2012-11-29 1.�޸��ļ�����ȡ����
 //                           2.�޸Ĵ�����Ϣ�����ʽ���򣬼����󷵻�ֵ
 /*********************************************************/



#include "ddp_decode_aws_sunday.h"

#define     AWS_GROUPS_SUN  (35)



/*********************��������****************************/
ASCII_FIELD_DEFINE  awsfField[AWS_GROUPS_SUN]={
	{1, 5, 0},    {2, 6, 4},    {2, 7, 4}, 
	{0, 1, 0},    {0, 4, 0},    {0, 2, 0},
	{0, 2, 0},    {0, 2, 0},    {0, 2, 0},
	{0, 2, 0},    {2, 2, 1},    {2, 2, 1},/*1~2Сʱ*/
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 3, 1}
};

//�����ļ���
//������: processFileName()
//��������:�����ļ���,�����Ӧ�Ľṹ����Ϣ
//out: pszFileName
//return:�ɹ�����0 ʧ��Ϊ1
void processFileName(GroundAutoStationSunlightDataRP *pRpt,char *pszFileName)
{
	char psztime[20]={0};
	char tmp[20]={0};
	char acTmp[MAX_FILE_NAME] = {0};		/*��ʱ�洢*/	
	char *pszTmp = NULL;				/*��ʱ�洢*/
	char *pszTmpFileName = pszFileName;		/*�ļ���ָ��*/
	int iGroupCount = 0;					/*��������*/
	int flag = 0;
	/*if(strchr(pszFileName,'/') != NULL)
	{
		pszTmpFileName = strrchr(pszFileName,'/');
	}*/

    if(strchr(pszFileName,'/') != NULL)
    {
        pszTmpFileName = strrchr(pszFileName,'/');
    }
    else
	{
        pszTmpFileName = pszFileName;
	}
	
	memset(pRpt->acWriteReportCenter,0,6);
	pRpt->acWriteYear = 999998;
	pRpt->acWriteMonth = 999998;
	pRpt->acWriteDay  = 999998;
	pRpt->acWriteHour = 999998;
	pRpt->acWriteMin  = 999998;
	pRpt->acWriteSec  = 999998;
	memset(pRpt->acFlag,0,5);
	memset(pRpt->acNO,0,10);
	memset(pRpt->acType,0,MAX_TYPE_LEN);
	pRpt->acObservationMode = '0';
	strncpy(acTmp,pszTmpFileName,MAX_FILE_NAME);

	while((pszTmp = strchr(pszTmpFileName,'_')) != NULL)	
	{
		strncpy(acTmp,pszTmpFileName,strlen(pszTmpFileName) - strlen(pszTmp));
		if(iGroupCount == 2)
		{
			strncpy(tmp,acTmp,1);
			if(strncmp(tmp,"C",1) == 0)//��վ�ļ�
			{
				flag = 1;//��վ�ļ� 
			}
		}
		if((flag == 1) && (iGroupCount == 3) )
		{
			flag = 0;
			strncpy(pRpt->acWriteReportCenter,acTmp,4);
		}
		if(iGroupCount == 4)//ȡʱ��
		{
			strncpy(tmp,acTmp,14);
			strncpy(psztime,tmp,4);
			pRpt->acWriteYear = atoi(psztime);
			memset(psztime,0,20);
			strncpy(psztime,(tmp+4),2);
			pRpt->acWriteMonth = atoi(psztime);
			memset(psztime,0,20);
			strncpy(psztime,(tmp+6),2);
			pRpt->acWriteDay = atoi(psztime);
			memset(psztime,0,20);
			strncpy(psztime,(tmp+8),2);
			pRpt->acWriteHour = atoi(psztime);
			memset(psztime,0,20);
			strncpy(psztime,(tmp+10),2);
			pRpt->acWriteMin = atoi(psztime);
			memset(psztime,0,20);
			strncpy(psztime,(tmp+12),2);
			pRpt->acWriteSec = atoi(psztime);
		}
		pszTmpFileName = pszTmp + 1;
		memset(acTmp,0,sizeof(acTmp));
		iGroupCount ++;
	}
	pszTmp =  strstr(pszTmpFileName,"-CC");
	if(pszTmp != NULL)
	{
		strncpy(pRpt->acFlag,pszTmp+1,3);
	}
	if(strlen(pRpt->acWriteReportCenter) == 0)
		strncpy(pRpt->acWriteReportCenter,"*",1);
	strncpy(pRpt->acType,"AWSS", 4);
	strncpy(pRpt->acNO,"999998",6);
	strncpy(pRpt->acRType,"AWSS",4);
	strncpy(pRpt->acAA,"CI",2);
}




/**
  ��������	ProcessOneReport
  �������ܣ�   	���������棬�����Ӧ�Ľṹ����Ϣ 	
  @param		pszReport		ָ�򱨸��ָ��			�������
  @param		pRpt			ָ���Ӧ�ṹ�������ָ��	�������
  @param		pszErrorMsg		���ش�����Ϣ��ͷָ��		�������
  @param		iErrorMsgLen		������Ϣ�ĳ���			�������

  @return 	����ɹ�����0��ʧ�ܷ��ط�0
  */
int ProcessOneReport(const char * pszReport, GroundAutoStationSunlightDataRP * pRpt, char * pszErrorMsg,int iErrorMsgLen,int iRpt)
{
	int     nDefault = DEFAULT_VALUE;		/*ȱ��ֵ*/
	double  dDefault = DEFAULT_VALUE;		/*ȱ��ֵ*/
	int     k;					/*ѭ������*/
	int     i;					/*ѭ������*/
	double     nValue;					/*��ʱ��ֵ����*/
	double  dValue;					/*��ʱ��ֵ����*/
	double  dScale;					/*��ʱ��ֵ����*/
	char    szItem[256] = {0};			/*��ʱ��Ϣ�������*/
	char    szErrMsg[256] = {0};			/*��ʱ������Ϣ�������*/
	const char * pszContent = pszReport;		/*ָ�򱨸��ָ��*/
	unsigned char * puRpt = (unsigned char *)pRpt;	/*ָ��ṹ���ָ��*/
	int     nError;					/*����������*/
	int     nTimeFlag;				/*��־*/
	double  dPC, dTC;				/*����*/
	int     nMw, nDa;				/*����*/
	double  dD,dM,dS;				/*�ȣ��֣���*/
	char 	szTmp[10] = {0};		/*��ʱ�洢*/
    int  iErr=0;                  //�ж��Ƿ��ǵ�һ�γ���
	
    iRpt=iRpt+1;
    /*�������ÿ��*/
	for (i = 0; i < AWS_GROUPS_SUN; i ++)
	{
		if (*pszContent == 0)/*����β*/
		{
			if (awsfField[i].nType == DT_INTEGER)
			{
				memcpy(puRpt, &nDefault, sizeof(int));
				puRpt += sizeof(int);
			}
			else if (awsfField[i].nType == DT_DOUBLE)
			{
				memcpy(puRpt, &dDefault, sizeof(double));
				puRpt += sizeof(double);
			}
		}
		else
		{
			/*��ȡ��*/
			pszContent = GetStringStart(pszContent);
			
			strncpy(szItem, pszContent, awsfField[i].nFieldLength);
			szItem[awsfField[i].nFieldLength] = 0;
			trim(szItem);
			if (strlen(szItem) != awsfField[i].nFieldLength)
			{
               if(iErr==0)
               {
			    	sprintf(szErrMsg, ",%d(��%s����%dλ",iRpt, szItem, awsfField[i].nFieldLength);
                    iErr=1;
               }
               else
               {
			    	sprintf(szErrMsg, "����%s����%dλ",szItem, awsfField[i].nFieldLength);
               }
				DECODE_STRCAT(pszErrorMsg, iErrorMsgLen,szErrMsg);
			}
			pszContent += awsfField[i].nFieldLength;
			/*��վ��*/
			if(i == 0)
			{
				memcpy(puRpt, szItem, sizeof(char)*5);
				puRpt += sizeof(char)*6;
			}

			/*����*/
			if (awsfField[i].nType == DT_INTEGER)
			{
				if (strncmp(szItem, "////////////////", awsfField[i].nFieldLength) == 0)
				{
					memcpy(puRpt, &nDefault, sizeof(int));
					puRpt += sizeof(int);
				}
				else
				{
					errno = 0;
					nValue = (int)strtol(szItem, (char**)NULL, 10);
					if (errno != 0)
					{
                        if(iErr==0)
                        {
						    sprintf(szErrMsg, ",%d(��%sת������",iRpt, szItem);
                            iErr=1;
                        }
                        else
                        {
						    sprintf(szErrMsg, "����%sת������",szItem);
                        
                        }
						DECODE_STRCAT(pszErrorMsg, iErrorMsgLen,szErrMsg);
					}
					else
					{
						memcpy(puRpt, &nValue, sizeof(int));
						puRpt += sizeof(int);
					}
				}
			}
			/*ʵ��*/
			else if (awsfField[i].nType == DT_DOUBLE)
			{
				if (strncmp(szItem, "////////////////", awsfField[i].nFieldLength) == 0)
				{
					memcpy(puRpt, &dDefault, sizeof(double));
					puRpt += sizeof(double);
				}
				else
				{
					/*γ��*/
					if(i == 1)
					{
						strncpy(szTmp,szItem,2);
						szTmp[2] = '\0';
						dD = strtod(szTmp,NULL);
						strncpy(szTmp,szItem+2,2);
						szTmp[2] = '\0';
						dM = strtod(szTmp,NULL);
						strncpy(szTmp,szItem+4,2);
						szTmp[2] = '\0';
						dS = strtod(szTmp,NULL);

						dValue = dD + (dS/60 + dM)/60;
						memcpy(puRpt, &dValue, sizeof(double));
						puRpt += sizeof(double);
					}
					/*����*/
					else if(i == 2)
					{
						strncpy(szTmp,szItem,3);
						szTmp[3] = '\0';
						dD = strtod(szTmp,NULL);
						strncpy(szTmp,szItem+3,2);
						szTmp[2] = '\0';
						dM = strtod(szTmp,NULL);
						strncpy(szTmp,szItem+5,2);
						szTmp[2] = '\0';
						dS = strtod(szTmp,NULL);

						dValue = dD + (dS/60 + dM)/60;
						memcpy(puRpt, &dValue, sizeof(double));
						puRpt += sizeof(double);
					}
					else 
					{
						dScale = pow(10, awsfField[i].nScale);
						errno = 0;
						nValue = (int)strtol(szItem, (char**)NULL, 10);
						
						dValue = 1.0 * nValue / dScale;
						//printf("errno = %d, nValue = %d!\n", errno, nValue);
						if (errno != 0)
						{
							perror("err:");
                            if(iErr==0)
                            {
							    sprintf(szErrMsg, ",%d(��%sת������",iRpt, szItem);
                                iErr=1;
                            }
                            else
                            {
							    sprintf(szErrMsg, "���� %sת������", szItem);
                            }
                            DECODE_STRCAT(pszErrorMsg, iErrorMsgLen,szErrMsg);
						}
						else
						{
							memcpy(puRpt, &dValue, sizeof(double));
							puRpt += sizeof(double);
						}
					}
				}
			}
		}
	}
     
    if(iErr==1)
    {
        sprintf(szErrMsg, ")");
        DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, szErrMsg);
        
        return 1;
		//return 0; //Lice 2012/12/26
    }


	return 0;
}

/**
  ��������	ProcessGroundAutoStationSunlightDataRP
  �������ܣ�	������ĵ����Զ�վ��Сʱ�����ļ������������ݣ����浽��Ӧ�Ľṹ�������У�
  ��������������ݣ����������������Ϣ
  @param		pszReportFileName	�����Զ�վ��Сʱ�ļ�ָ��	�������
  @param		pszReportBuffer		���ر�����Ϣ��ͷ��?	�������
  @param		iReportBufferLen	���ر�����Ϣ�ĳ���		�����������
  @param		pRpt			ָ���Ӧ�ṹ�������ָ��	�������
  @param		piReportCount		����ĸ���			�����������
  @param		pszErrorMsg		���ش�����Ϣ��ͷָ��		�������
  @param		iErrorMsgLen		������Ϣ�ĳ���			�������

  @return 	����ɹ�����0��ʧ�ܷ��ط�0
  */
int ProcessGroundAutoStationSunlightDataRP(const char * pszReportFileName,char *pszReportBuffer,int *iReportBufferLen, GroundAutoStationSunlightDataRP * pRpt, int *piReportCount, char * pszErrorMsg,int iErrorMsgLen)
{
	FILE *fpReport;				/*���ļ���ָ��*/
	char errmsg[300];			/*��ʱ������Ϣ�洢����*/
	char report[MAX_AUTOREPORT_LEN] = {0};	/*��ʱ������Ϣ�洢����*/
	int  report_len = 0;			/*���泤��*/
	int  ret;				/*���ú�������ֵ*/
	int  iRpt = 0;				/*�������*/
	new_add_struct newAdd;			/*������Ϣ�ṹ��*/
	char FileName[MAX_FILE_NAME]={0};
    time_t tdata;
    struct tm tmdata;
    int YCount=0;
    int NCount=0;
	/*��������ļ�ָ���Ƿ�Ϊ��,�ļ������Ƿ�Ϊ��,Ϊ����д�������Ϣ��*/
	if (pszReportFileName == NULL || strlen(pszReportFileName) == 0)
	{
		sprintf(errmsg, "�ļ���Ϊ��\n");
		DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
		return ERROR_FILE_NAME_IS_NULL;
	}
	/*���ļ�,ʧ����д�������Ϣ*/

	fpReport = fopen(pszReportFileName,"r");
	if(fpReport == NULL)
	{
		sprintf(errmsg,"�ļ�%s�򲻿�\n",pszReportFileName);
		DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
		return ERROR_ACCESS_FILE;
	}

	/*���ļ����õ���Ϣ*/
	//memset(&newAdd,0,sizeof(newAdd));
	//	handle_file_name(pszReportFileName,&newAdd);
	/*�����ļ�*/
	while(!feof(fpReport))
	{
		if(iRpt >= *piReportCount)
		{
			fclose(fpReport);
			sprintf(errmsg,"û���㹻�Ľṹ��!\n");
			DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
			return ERROR_NOT_ENOUGH_STRUCT_BUFFER;
		}
		/*���ļ���ȡ����*/
		memset(report,0,sizeof(report));
		ret = GetAutoReport(fpReport,report,&report_len);

		/*�����ļ�ĩβ*/
		if ( ret == ERROR_END_OF_FILE ) 
			break;

		/*���ɹ�����*/
		if (ERROR_REPORT_TOO_SHORT == ret)
		{
			sprintf(errmsg,"����̫��\n");
			DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);

			continue;
		}
		else if (ERROR_REPORT_TOO_LONG == ret)
		{
			sprintf(errmsg, "����̫��\n");
			DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
			continue;
		}
		/*�ɹ����أ�������*/
		if (pRpt != NULL)
		{
			/*������*/
			ret = ProcessOneReport(report, &pRpt[iRpt], pszErrorMsg,iErrorMsgLen,iRpt);
			/*�����治�ɹ�*/
	        /*if(ret != 0)
			{
				fclose(fpReport);
				*piReportCount = iRpt;
				return ret;
			}*/
            if(ret!=0)
            {
                NCount++;
            }
            else
            {
                YCount++;
            }
#if 0
            /*�������Ϲ۲�ʱ����-1*/
            memset(&tmdata, 0, sizeof(tmdata));
            if ((pRpt[iRpt].iObservYear < 9999) && (pRpt[iRpt].iObservMonth < 99) &&  (pRpt[iRpt].iObservDay < 99))
            {
                tmdata.tm_year = pRpt[iRpt].iObservYear - 1900;
                tmdata.tm_mon = pRpt[iRpt].iObservMonth - 1;
                tmdata.tm_mday = pRpt[iRpt].iObservDay-1;
                tdata = mktime(&tmdata);
                memset(&tmdata, 0, sizeof(tmdata));
                localtime_r(&tdata, &tmdata);
                pRpt[iRpt].iObservYear = tmdata.tm_year + 1900;
                pRpt[iRpt].iObservMonth = tmdata.tm_mon + 1;
                pRpt[iRpt].iObservDay = tmdata.tm_mday;
            }
#endif

		}
		/*����������Ϣ*/
		/*���ر�����Ϣ*/
		REPORT_STRCAT(pszReportBuffer,*iReportBufferLen,report);	
		/*������Ϣ��д���Ӧ�Ľṹ��*/
		strncpy(FileName,pszReportFileName,MAX_FILE_NAME);
		processFileName(&pRpt[iRpt],FileName);
		pRpt[iRpt].iReportLen = strlen(report);
		/*
		   strncpy(pRpt[iRpt].acWriteYearMonthDay,newAdd.acWriteYearMonthDay,sizeof(pRpt[iRpt].acWriteYearMonthDay));
		   strncpy(pRpt[iRpt].acWriteHourMinSec,newAdd.acWriteHourMinSec,sizeof(pRpt[iRpt].acWriteHourMinSec));
		   strncpy(pRpt[iRpt].acFlag,newAdd.acFlag,sizeof(pRpt[iRpt].acFlag));
		   strncpy(pRpt[iRpt].acFileName,pszReportFileName,sizeof(pRpt[iRpt].acFileName));
		   strncpy(pRpt[iRpt].acType,"AWS",sizeof(pRpt[iRpt].acType));
		   */	
		/*�����������*/
		iRpt ++;
	}
	fclose(fpReport);
	*piReportCount = iRpt;
	*iReportBufferLen = strlen(pszReportBuffer);
    
    if(NCount==0)
    {
        return SUCCESS_OP;
    }
    if(NCount!=0 && YCount!=0)
    {
        sprintf(errmsg, "%d", NCount);
        strcat(errmsg,pszErrorMsg);
        strcpy(pszErrorMsg,errmsg);
        
        return DECODE_PARTAIL_SUCCESS;
    }

    if(NCount!=0 && YCount==0)
    {
        sprintf(errmsg, "%d", NCount);
        strcat(errmsg,pszErrorMsg);
        strcpy(pszErrorMsg,errmsg);
        
        return ERROR_DECODE_FAILURE;
    }
        
    return SUCCESS_OP;
}
