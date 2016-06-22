 /******************************************************/
 //Copyrigth (C),2010-2011,ITC. Co.,Ltd.
 //FileName:   ddp_aws_decode_sundata.c
 //Author:      吴楠
 //Data:     2011-08-22
 //Description：ascii格式解码地面日照数据文件
 //Version： V4.1.1
 //Latest Time: 2012-11-29
 //Tester:    王娟
 //modified:朱孟坤 2012-11-29 1.修改文件名截取规则
 //                           2.修改错误信息输出格式规则，及错误返回值
 /*********************************************************/



#include "ddp_decode_aws_sunday.h"

#define     AWS_GROUPS_SUN  (35)



/*********************日照数据****************************/
ASCII_FIELD_DEFINE  awsfField[AWS_GROUPS_SUN]={
	{1, 5, 0},    {2, 6, 4},    {2, 7, 4}, 
	{0, 1, 0},    {0, 4, 0},    {0, 2, 0},
	{0, 2, 0},    {0, 2, 0},    {0, 2, 0},
	{0, 2, 0},    {2, 2, 1},    {2, 2, 1},/*1~2小时*/
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 2, 1},    {2, 2, 1},
	{2, 2, 1},    {2, 3, 1}
};

//处理文件名
//函数名: processFileName()
//函数功能:处理文件名,填充相应的结构体信息
//out: pszFileName
//return:成功返回0 失败为1
void processFileName(GroundAutoStationSunlightDataRP *pRpt,char *pszFileName)
{
	char psztime[20]={0};
	char tmp[20]={0};
	char acTmp[MAX_FILE_NAME] = {0};		/*临时存储*/	
	char *pszTmp = NULL;				/*临时存储*/
	char *pszTmpFileName = pszFileName;		/*文件名指针*/
	int iGroupCount = 0;					/*计数变量*/
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
			if(strncmp(tmp,"C",1) == 0)//多站文件
			{
				flag = 1;//多站文件 
			}
		}
		if((flag == 1) && (iGroupCount == 3) )
		{
			flag = 0;
			strncpy(pRpt->acWriteReportCenter,acTmp,4);
		}
		if(iGroupCount == 4)//取时间
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
  函数名：	ProcessOneReport
  函数功能：   	处理单个报告，填充相应的结构体信息 	
  @param		pszReport		指向报告的指针			输入参数
  @param		pRpt			指向对应结构体数组的指针	输出参数
  @param		pszErrorMsg		返回错误信息的头指针		输出参数
  @param		iErrorMsgLen		错误信息的长度			输入参数

  @return 	如果成功返回0，失败返回非0
  */
int ProcessOneReport(const char * pszReport, GroundAutoStationSunlightDataRP * pRpt, char * pszErrorMsg,int iErrorMsgLen,int iRpt)
{
	int     nDefault = DEFAULT_VALUE;		/*缺测值*/
	double  dDefault = DEFAULT_VALUE;		/*缺测值*/
	int     k;					/*循环变量*/
	int     i;					/*循环变量*/
	double     nValue;					/*临时赋值变量*/
	double  dValue;					/*临时赋值变量*/
	double  dScale;					/*临时赋值变量*/
	char    szItem[256] = {0};			/*临时信息存放数组*/
	char    szErrMsg[256] = {0};			/*临时出错信息存放数组*/
	const char * pszContent = pszReport;		/*指向报告的指针*/
	unsigned char * puRpt = (unsigned char *)pRpt;	/*指向结构体的指针*/
	int     nError;					/*错误代码变量*/
	int     nTimeFlag;				/*标志*/
	double  dPC, dTC;				/*变量*/
	int     nMw, nDa;				/*变量*/
	double  dD,dM,dS;				/*度，分，秒*/
	char 	szTmp[10] = {0};		/*临时存储*/
    int  iErr=0;                  //判断是否是第一次出粗
	
    iRpt=iRpt+1;
    /*处理报告的每组*/
	for (i = 0; i < AWS_GROUPS_SUN; i ++)
	{
		if (*pszContent == 0)/*报告尾*/
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
			/*获取组*/
			pszContent = GetStringStart(pszContent);
			
			strncpy(szItem, pszContent, awsfField[i].nFieldLength);
			szItem[awsfField[i].nFieldLength] = 0;
			trim(szItem);
			if (strlen(szItem) != awsfField[i].nFieldLength)
			{
               if(iErr==0)
               {
			    	sprintf(szErrMsg, ",%d(组%s不足%d位",iRpt, szItem, awsfField[i].nFieldLength);
                    iErr=1;
               }
               else
               {
			    	sprintf(szErrMsg, "，组%s不足%d位",szItem, awsfField[i].nFieldLength);
               }
				DECODE_STRCAT(pszErrorMsg, iErrorMsgLen,szErrMsg);
			}
			pszContent += awsfField[i].nFieldLength;
			/*区站号*/
			if(i == 0)
			{
				memcpy(puRpt, szItem, sizeof(char)*5);
				puRpt += sizeof(char)*6;
			}

			/*整型*/
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
						    sprintf(szErrMsg, ",%d(组%s转换错误",iRpt, szItem);
                            iErr=1;
                        }
                        else
                        {
						    sprintf(szErrMsg, "，组%s转换错误",szItem);
                        
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
			/*实型*/
			else if (awsfField[i].nType == DT_DOUBLE)
			{
				if (strncmp(szItem, "////////////////", awsfField[i].nFieldLength) == 0)
				{
					memcpy(puRpt, &dDefault, sizeof(double));
					puRpt += sizeof(double);
				}
				else
				{
					/*纬度*/
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
					/*经度*/
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
							    sprintf(szErrMsg, ",%d(组%s转换错误",iRpt, szItem);
                                iErr=1;
                            }
                            else
                            {
							    sprintf(szErrMsg, "，组 %s转换错误", szItem);
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
  函数名：	ProcessGroundAutoStationSunlightDataRP
  函数功能：	从输入的地面自动站逐小时数据文件解析报告内容，保存到对应的结构体数组中，
  并且输出报告内容，报告个数，错误信息
  @param		pszReportFileName	地面自动站逐小时文件指针	输入参数
  @param		pszReportBuffer		返回报告信息的头刚?	输出参数
  @param		iReportBufferLen	返回报告信息的长度		输入输出参数
  @param		pRpt			指向对应结构体数组的指针	输出参数
  @param		piReportCount		报告的个数			输入输出参数
  @param		pszErrorMsg		返回错误信息的头指针		输出参数
  @param		iErrorMsgLen		错误信息的长度			输入参数

  @return 	如果成功返回0，失败返回非0
  */
int ProcessGroundAutoStationSunlightDataRP(const char * pszReportFileName,char *pszReportBuffer,int *iReportBufferLen, GroundAutoStationSunlightDataRP * pRpt, int *piReportCount, char * pszErrorMsg,int iErrorMsgLen)
{
	FILE *fpReport;				/*打开文件的指针*/
	char errmsg[300];			/*临时错误信息存储数组*/
	char report[MAX_AUTOREPORT_LEN] = {0};	/*临时报告信息存储数组*/
	int  report_len = 0;			/*报告长度*/
	int  ret;				/*调用函数返回值*/
	int  iRpt = 0;				/*报告个数*/
	new_add_struct newAdd;			/*新增信息结构体*/
	char FileName[MAX_FILE_NAME]={0};
    time_t tdata;
    struct tm tmdata;
    int YCount=0;
    int NCount=0;
	/*检查输入文件指针是否为空,文件内容是否为空,为空则写入错误信息中*/
	if (pszReportFileName == NULL || strlen(pszReportFileName) == 0)
	{
		sprintf(errmsg, "文件名为空\n");
		DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
		return ERROR_FILE_NAME_IS_NULL;
	}
	/*打开文件,失败则写入错误信息*/

	fpReport = fopen(pszReportFileName,"r");
	if(fpReport == NULL)
	{
		sprintf(errmsg,"文件%s打不开\n",pszReportFileName);
		DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
		return ERROR_ACCESS_FILE;
	}

	/*从文件名得到信息*/
	//memset(&newAdd,0,sizeof(newAdd));
	//	handle_file_name(pszReportFileName,&newAdd);
	/*处理文件*/
	while(!feof(fpReport))
	{
		if(iRpt >= *piReportCount)
		{
			fclose(fpReport);
			sprintf(errmsg,"没有足够的结构体!\n");
			DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
			return ERROR_NOT_ENOUGH_STRUCT_BUFFER;
		}
		/*从文件读取报告*/
		memset(report,0,sizeof(report));
		ret = GetAutoReport(fpReport,report,&report_len);

		/*读到文件末尾*/
		if ( ret == ERROR_END_OF_FILE ) 
			break;

		/*不成功返回*/
		if (ERROR_REPORT_TOO_SHORT == ret)
		{
			sprintf(errmsg,"报告太短\n");
			DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);

			continue;
		}
		else if (ERROR_REPORT_TOO_LONG == ret)
		{
			sprintf(errmsg, "报告太长\n");
			DECODE_STRCAT(pszErrorMsg,iErrorMsgLen, errmsg);
			continue;
		}
		/*成功返回，处理报告*/
		if (pRpt != NULL)
		{
			/*处理报告*/
			ret = ProcessOneReport(report, &pRpt[iRpt], pszErrorMsg,iErrorMsgLen,iRpt);
			/*处理报告不成功*/
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
            /*调整资料观测时间日-1*/
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
		/*新增返回信息*/
		/*返回报告信息*/
		REPORT_STRCAT(pszReportBuffer,*iReportBufferLen,report);	
		/*报告信息的写入对应的结构体*/
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
		/*报告个数增加*/
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
