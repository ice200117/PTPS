/*****************************************************
 *
 *
 *Version 4.0
 *
 *
 * *************************************************/

#include "ddp_ascii_common.h"
//#include "mmd_ascii.h"

/*
const CLOUD_SHAPE cloudshape[30]={
    {"CUU",31},{"FCB",48},{"CUO",32},{"CBV",33},
    {"CBP",39},{"SCR",40},{"SCP",41},{"SCU",34},
    {"SCA",42},{"SCT",43},{"STB",32},{"FSB",37},
    {"NSB",5 },{"FNB",44},{"ASR",45},{"ASP",46},
    {"ACR",21},{"ACP",22},{"ACE",24},{"ACU",26},
    {"ACL",28},{"ACA",49},{"CII",11},{"CIE",12},
    {"CIO",47},{"CIN",14},{"CSI",32},{"CSE",15},
    {"CCB",1}, {"///", DEFAULT_VALUE}
};
*/
const CLOUD_SHAPE cloudshape[30]={
    {"CUU",31},{"FCB",48},{"CUO",32},{"CBV",33},
    {"CBP",39},{"SCR",50},{"SCP",51},{"SCU",34},
    {"SCA",52},{"SCT",43},{"STB",7},{"FSB",37},
    {"NSB",5 },{"FNB",44},{"ASR",45},{"ASP",46},
    {"ACR",21},{"ACP",22},{"ACE",24},{"ACU",26},
    {"ACL",28},{"ACA",49},{"CII",11},{"CIE",12},
    {"CIO",47},{"CIN",14},{"CSI",16},{"CSE",15},
    {"CCB",1}, {"///", DEFAULT_VALUE}
};

#define     WIND_DIRECT_GROUP   (28)

const WIND_DIRECT winddirect[WIND_DIRECT_GROUP]={
    {"N", 360.}, {"PPN", 360.}, {"NNE", 22.5},{"NE", 45.}, {"PNE", 45.}, {"ENE", 67.5},
    {"E", 90.}, {"PPE", 90.}, {"ESE", 112.5}, {"SE", 135.}, {"PSE", 135}, {"SSE", 157.5},
    {"S", 180.}, {"PPS", 180.}, {"SSW", 202.5}, {"SW", 225.}, {"PSW", 225}, {"WSW", 247.5},
    {"W", 270.}, {"PPW", 270.}, {"WNW", 292.5}, {"NW", 315}, {"PNW", 315}, {"NNW", 337.5},
    {"C", 0}, {"PPC", 0}, {"///", DEFAULT_VALUE}, {"...", DEFAULT_VALUE}
};

const   int     weatherphenomenon[34]={
    1,    /*露	      */
    2,    /*霜	      */
    3,    /*结冰	      */
    4,    /*烟幕	      */
    5,    /*霾	      */
    6,    /*浮尘	      */
    7,    /*扬沙	      */
    8,    /*尘卷风	  */
    10,   /*轻雾	      */
    13,   /*闪电	      */
    14,   /*极光	      */
    15,   /*大风	      */
    16,   /*积雪	      */
    17,   /*雷暴	      */
    18,   /*飑	      */
    19,   /*龙卷	      */
    31,   /*沙尘暴	  */
    38,   /*吹雪	      */
    39,   /*雪暴	      */
    42,   /*雾	      */
    48,   /*雾凇	      */
    50,   /*毛毛雨	  */
    56,   /*雨凇	      */
    60,   /*雨	      */
    68,   /*雨夹雪	  */
    70,   /*雪	      */
    76,   /*冰针	      */
    77,   /*米雪	      */
    79,   /*冰粒	      */
    80,   /*阵雨	      */
    83,   /*阵性雨夹雪  */
    85,   /*阵雪	      */
    87,   /*霰	      */
    89    /*冰雹	      */
};


#define FILE_NAME_SEPARATOR 		'_'

#define TIME_POSITION_IN_FILE_NAME	5
#define CCCC_POSITION_IN_FILE_NAME  4
#define C_POSITION_IN_FILE_NAME		3
/**
函数名：	handle_file_name
函数功能：   	处理文件名信息 	
@param		pszFileName		文件名指针			输入参数
@param		pszAdd			新增结构体指针			输入输出参数

@return 	无
*/
void handle_file_name(const char *pszFileName,new_add_struct *pszAdd)
{
    char acTmp[MAX_FILE_NAME] = {0};		/*临时存储*/	
    const char *pszTmp = NULL;				/*临时存储*/
    const char *pszTmpFileName = NULL;		/*文件名指针*/
    int iGroupCount = 1;				/*计数变量*/
	int iFlag_CCCC = 0;

	//printf("pszFileName=%s\n",pszFileName);
	if(strchr(pszFileName,'/') != NULL)
	{
		pszTmpFileName = strrchr(pszFileName,'/');
	}
	else
		pszTmpFileName = pszFileName;

	//printf("pszTmpFileName=%s\n",pszTmpFileName);
    /*以下划线分割文件名*/
    while((pszTmp = strchr(pszTmpFileName,FILE_NAME_SEPARATOR)) != NULL)	
    {
        strncpy(acTmp,pszTmpFileName,strlen(pszTmpFileName) - strlen(pszTmp));	
        if( TIME_POSITION_IN_FILE_NAME == iGroupCount)
        {
            strncpy(pszAdd->acWriteYearMonthDay,acTmp,8);	
            strncpy(pszAdd->acWriteHourMinSec,acTmp+8,6);
        }
		if( C_POSITION_IN_FILE_NAME == iGroupCount)
		{
			if(acTmp[0] == 'C')
				iFlag_CCCC = 1;
		}
		if( CCCC_POSITION_IN_FILE_NAME == iGroupCount && iFlag_CCCC == 1)
		{
			strncpy(pszAdd->acCCCC,acTmp,4);
		}

        pszTmpFileName = pszTmp + 1;
        memset(acTmp,0,sizeof(acTmp));
        iGroupCount ++;
    }
    /*检查订正标志*/
    if((pszTmp = strstr(pszTmpFileName,"-CC")) != NULL)	
        strncpy(pszAdd->acFlag,pszTmp+1,3);
}

char    *rtrimex(char *s)
{
    int len;
    char    *cp;

    len = strlen(s);
    cp = s + len - 1;
    while ( (len >= 1) && (*cp < ' '))
    {
        *cp = '\0';
        len--, cp--;
    }
    return s;
}

char    *ltrim(char *s)
{
    int i, len;
    char    *cp;

    len = strlen(s);
    cp = s ;

    for ( i=0; i<=len-1; i++)
    {
        if ( *cp == ' '|| *cp =='\t' || *cp=='\n' || *cp == '\r')
            *cp++;
        else
            break;
    }

    if (s != cp)
        strcpy ( s , cp ) ;
    //return cp;
    return s;
}

char    *rtrim(char *s)
{
    int len;
    char    *cp;

    len = strlen(s);
    cp = s + len - 1;
    while ( len >= 1 && (*cp == ' '|| *cp == '\n' || *cp == '\t' || *cp =='\r' ))
    {
        *cp = '\0';
        len--, cp--;
    }
    return s;
}
char    *rtrim_new(char *s)
{
    int len;
    char    *cp;

    len = strlen(s);
    cp = s + len - 1;
    //while ( len >= 1 && (*cp == ' '|| *cp == '\n' || *cp == '\t' || *cp =='\r' ))
    while ( len >= 1 && (*cp == ' '|| *cp == '\t' ))
    {
        *cp = '\0';
        len--, cp--;
    }
    return s;
}
char    *trim_new(char *s)
{
    char    *cp;

    cp = ltrim(rtrim_new(s));
    /* if ( *cp == ' ' || *cp == '\0')  return NULL; */
    return cp;
}
char    *trim(char *s)
{
    char    *cp;

    cp = ltrim(rtrim(s));
    /* if ( *cp == ' ' || *cp == '\0')  return NULL; */
    return cp;
}

const char * GetStringStart(const char * pszStr)
{
    const /*unsigned*/ char * p = (const /*unsigned*/ char *)pszStr;
    while((*p <= ' ' || *p == ',')  && *p != 0) 
    {
        p++;
    }
    return p;
}

const char * GetStringStart2(const char * pszStr)
{
    const unsigned char* p = (const unsigned char *)pszStr;
    while(*p <= ' ' && *p != 0) 
    {
        p++;
    }
    return p;
}

int GetOneReport_ZCZC(FILE *fp, char *report, int *report_len)
{
    char str[2048];
    char temp_rep[MAX_AUTOREPORT_LEN] = {0};
    int  flag = 0;
    int  i = 0;

    while( fgets(str,2048,fp) != NULL )
    {
        i++;
        ltrim(str);
        if( i == 1 )
        {
            if ( strstr(str, "ZCZC") != NULL )
                continue;
            else
                return ERROR_START_OF_FILE;
        }        
        /*if ( strstr(str, AWS_FILE_END_ID) != NULL )
        return ERROR_END_OF_FILE;

        if ( strlen(temp_rep)+strlen(str) > MAX_AUTOREPORT_LEN )
        {
        return ERROR_REPORT_TOO_LONG;
        }*/
        if ( strstr(str, AWS_FILE_END_ID) != NULL )
        {
            if ( flag == 0 )
                return ERROR_REPORT_TOO_SHORT;
            /*rtrim(str);
            strcat(temp_rep,str);*/
            strcpy(report,temp_rep);
            return SUCCESS_OP;
        }
        else
        {
            flag = 1;
            rtrim_new(str);
            strcat(temp_rep,str);
            strcat(temp_rep, " ");
        }
    }
    return ERROR_END_OF_FILE;
}

int GetOneReport(FILE *fp, char *report, int *report_len)
{
    char str[2048];
    char temp_rep[MAX_AUTOREPORT_LEN] = {0};
    int  flag = 0;

    while( fgets(str,2048,fp) != NULL )
    {
        ltrim(str);
        if ( strstr(str, AWS_FILE_END_ID) != NULL )
            return ERROR_END_OF_FILE;

        if ( strlen(temp_rep)+strlen(str) > MAX_AUTOREPORT_LEN )
        {
            return ERROR_REPORT_TOO_LONG;
        }
        if ( strchr(str, AWS_REPORT_END_ID) != NULL )
        {
            if ( flag == 0 )
                return ERROR_REPORT_TOO_SHORT;
            rtrim_new(str);
            strcat(temp_rep,str);
            strcpy(report,temp_rep);
            return SUCCESS_OP;
        }
        else
        {
            flag = 1;
            rtrim_new(str);
            strcat(temp_rep,str);
            strcat(temp_rep, " ");
        }
    }
    return ERROR_END_OF_FILE;
}
int GetAutoReport(FILE *fp, char *report, int *report_len)
{
    char str[2048];
    char temp_rep[MAX_AUTOREPORT_LEN] = {0};
    int  flag = 0;
    while( fgets(str,2048,fp) != NULL )
    {
        ltrim(str);
        if ( strstr(str, AWS_FILE_END_ID) != NULL )
            return ERROR_END_OF_FILE;

        if ( strlen(temp_rep)+strlen(str) > MAX_AUTOREPORT_LEN )
        {
            return ERROR_REPORT_TOO_LONG;
        }
        if ( strchr(str, AWS_REPORT_END_ID) != NULL )
        {
            if ( flag == 0 )
                return ERROR_REPORT_TOO_SHORT;
            rtrim(str);
            strcat(temp_rep,str);
            strcpy(report,temp_rep);
            return SUCCESS_OP;
        }
        else
        {
            flag = 1;
            rtrim(str);
            strcat(temp_rep,str);
            strcat(temp_rep, " ");
        }
    }
    return ERROR_END_OF_FILE;
}

int  GetCloudType(const char * pszCloud)
{
    int     k;
    if ((pszCloud == NULL) || (*pszCloud == 0))
        return DEFAULT_VALUE;

    for (k = 0; k < 30; k ++)
    {
        if (strncmp(cloudshape[k].szClodShape, pszCloud, 3) == 0)
        {
            return cloudshape[k].nShape;
        }
    }
    return -1;
}

double  GetWindDirect(const char * pszWindDirect)
{
    int k;
    int nError = 0;
    if ((pszWindDirect == NULL)|| (*pszWindDirect == 0))
        return DEFAULT_VALUE;
    for (k = 0; k < WIND_DIRECT_GROUP; k++)
    {
        if (strcmp(pszWindDirect, winddirect[k].szWindDirect) == 0)
        {
            return winddirect[k].dDirect;
        }
    }
    return GetDoubleValue(pszWindDirect, '/', 0, &nError);
}

int  GetAWSPrecipitation6or12(char * pszPrecipitaion, double * pdPreciptation, int * pnTimeFlag, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strlen(pszPrecipitaion) != 5)
        if (pszPrecipitaion[0] != '6')
        {
            *pnError = ERROR_PRECIPITATION_PREFIX;
            return 1;
        }
        else if ((pszPrecipitaion[4] != '1') && (pszPrecipitaion[4] != '2'))
        {
            *pnError = ERROR_PRECIPITATION_SUFFIX;
            return 1;
        }
        if (pszPrecipitaion[4] == '1')
        {
            *pnTimeFlag = 1;
        }
        else if(pszPrecipitaion[4] == '2')
        {
            *pnTimeFlag = 2;
        }
        strncpy(szValue, pszPrecipitaion + 1, 3);
        szValue[3] = 0;
        if (strncmp(szValue, "///",3) == 0)
        {
            *pdPreciptation = DEFAULT_VALUE;
            return 0;
        }
        for (i = 0; i < 3; i ++)
        {
            if (!isdigit(szValue[i]))
            {
                *pnError = ERROR_INVALID_CHARACTER;
                return 1;
            }
        }
        nValue = strtol(szValue, NULL, 10);
        if (nValue >= 991)
        {
            dValue = (1.0 * (nValue - 990)) / 10;
        }
        else if (nValue == 990)
        {
            dValue = 999990;
        }
        else
        {
            dValue = nValue;
        }
        *pdPreciptation = dValue;
        return 0;
}

int     GetAWS24PressureTemperatureChange(const char * pszPT, double * pdPC, double * pdTC, int * pnError)
{
    char szP[3] = {0};
    char szT[3] = {0};
    int  i;
    int  nValue;
    double dValue;
    *pnError = 0;
    if (pszPT[0] != '0')
    {
        *pnError = ERROR_INVALID_CHARACTER;
        return 1;
    }
    strncpy(szP, pszPT + 1, 2);
    strncpy(szT, pszPT + 3, 2);
    if (strncmp(szP, "//", 2) == 0)
    {
        *pdPC = DEFAULT_VALUE;
    }
    else
    {
        for (i = 0; i < 2; i ++)
        {
            if (!isdigit(szP[i]))
            {
                break;
            }
        }
        if (i != 2)
        {
            *pnError = ERROR_INVALID_CHARACTER;
            *pdPC = DEFAULT_VALUE;
        }
        else
        {
            nValue = strtol(szP, NULL, 10);
            if (nValue >= 50)
            {
                dValue = -1.0 * (nValue - 50);
            }
            else
            {
                dValue = nValue;
            }
            *pdPC = dValue;
        }
    }

    if (strncmp(szT, "//", 2) == 0)
    {
        *pdTC = DEFAULT_VALUE;
        return 0;
    }
    else
    {
        for (i = 0; i < 2; i ++)
        {
            if (!isdigit(szT[i]))
            {
                break;
            }
        }
        if (i != 2)
        {
            *pnError = ERROR_INVALID_CHARACTER;
            *pdTC = DEFAULT_VALUE;
        }
        else
        {
            nValue = strtol(szT, NULL, 10);
            if (nValue >= 50)
            {
                dValue = -1.0 * (nValue - 50);
            }
            else
            {
                dValue = nValue;
            }
            *pdTC = dValue;
        }
    }
    if (*pnError != 0)
        return 1;
    return 0;
}

int     GetAWS24Rain(const char * pszRain, double * pdRain, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[5] = {0};
    *pnError = 0;
    strncpy(szValue, pszRain + 1, 4);
    if (strncmp(szValue, "////", 4) == 0)
    {
        *pdRain = DEFAULT_VALUE;
        return 0;
    }
    else if (strncmp(pszRain, "79999", 5) == 0)
    {
        *pdRain = 999900;
        return 0;
    }
    nValue = strtol(szValue, NULL, 10);
    dValue = 0.1 * nValue;
    *pdRain = dValue;
    return 0;
}

int     GetAWS24MaxTemperature(const char * pszTempertature, double * pdMaxTemperature, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszTempertature+1, "////", 4) == 0)
    {
        *pdMaxTemperature = DEFAULT_VALUE;
        return 0;
    }
    if ((pszTempertature[1] != '0') && (pszTempertature[1] != '1'))
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pdMaxTemperature = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszTempertature + 2, 3);
   // for (i = 0; i < 3; i ++)
   // {
   //     if (szValue[i] != 0)
   //     {
   //         *pnError = ERROR_INVALID_CHARACTER;
   //         *pdMaxTemperature = DEFAULT_VALUE;
   //         return 1;
   //     }
   // }
    nValue = strtol(szValue, NULL, 10);
    if (pszTempertature[1] == '0')
    {
        dValue = 1.0 * nValue / 10;
    }
    else
    {
        dValue = -1.0 * nValue/ 10;
    }
    *pdMaxTemperature = dValue;
    return 0;
}

int     GetAWS24MinTemperature(const char * pszTempertature, double * pdMinTemperature, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszTempertature+1, "////", 4) == 0)
    {
        *pdMinTemperature = DEFAULT_VALUE;
        return 0;
    }
    if ((pszTempertature[1] != '0') && (pszTempertature[1] != '1'))
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pdMinTemperature = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszTempertature + 2, 3);
    nValue = strtol(szValue, NULL, 10);
    if (pszTempertature[1] == '0')
    {
        dValue = 1.0 * nValue / 10.;
    }
    else
    {
        dValue = -1.0 * nValue/ 10.;
    }
    *pdMinTemperature = dValue;
    return 0;
}

int     GetAWS12AverTemperature(const char * pszTempertature, double * pdTemperature, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszTempertature+1, "////", 4) == 0)
    {
        *pdTemperature = DEFAULT_VALUE;
        return 0;
    }
    if ((pszTempertature[1] != '0') && (pszTempertature[1] != '1'))
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pdTemperature = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszTempertature + 2, 3);
    nValue = strtol(szValue, NULL, 10);
    if (pszTempertature[1] == '0')
    {
        dValue = 1.0 * nValue / 10.;
    }
    else
    {
        dValue = -1.0 * nValue/ 10.;
    }
    *pdTemperature = dValue;
    return 0;
}

int     GetAWSMaxWindSpeed(const char * pszWind, double * pdWindSpeed, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszWind, "911", 3) != 0)
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pdWindSpeed = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszWind + 3, 2);
    if (strncmp(szValue, "//", 2) == 0)
    {
        *pdWindSpeed = DEFAULT_VALUE;
        return 0;
    }
    for (i = 0; i < 2; i ++)
    {
        if (!isdigit(szValue[i]))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            *pdWindSpeed = DEFAULT_VALUE;
            return 1;
        }
    }
    nValue = strtod(szValue, NULL);
    dValue = nValue;
    *pdWindSpeed = dValue;
    return 0;
}

int     GetAWSMaxWindDirect(const char * pszWind, double * pdWindDirect, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszWind, "915", 3) != 0)
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pdWindDirect = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszWind + 3, 2);
    if (strncmp(szValue, "//", 2) == 0)
    {
        *pdWindDirect = DEFAULT_VALUE;
        return 0;
    }
    for (i = 0; i < 2; i ++)
    {
        if (!isdigit(szValue[i]))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            *pdWindDirect = DEFAULT_VALUE;
            return 1;
        }
    }
    nValue = strtod(szValue, NULL);
    dValue = nValue * 10;
    *pdWindDirect = dValue;
    return 0;
}

int     GetAWSWeatherWhirl(const char * pszWhirl, int * pnWhirl, int * pnWhirlDirect, int * pnError)
{
    int     i;
    char    szW;
    char    szWD;

    *pnError = 0;
    if (strncmp(pszWhirl, "919", 3) != 0)
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pnWhirl = DEFAULT_VALUE;
        *pnWhirlDirect = DEFAULT_VALUE;
        return 1;
    }
    szW = pszWhirl[3];
    szWD = pszWhirl[4];
    if (szW == '/')
    {
        *pnWhirl = DEFAULT_VALUE;
    }
    else if ((szW < '0') || (szW > '9'))
    {
        *pnWhirl = DEFAULT_VALUE;
        *pnError = ERROR_INVALID_CHARACTER;
    }
    else
    {
        *pnWhirl = szW - 48;
    }
    if (szWD == '/')
    {
        *pnWhirlDirect = DEFAULT_VALUE;
    }
    else if ((szWD < '0') || (szWD > '9'))
    {
        *pnWhirlDirect = DEFAULT_VALUE;
        *pnError = ERROR_INVALID_CHARACTER;
    }
    else
    {
        *pnWhirlDirect = szWD - 48;
    }
    if (*pnError != 0)
        return 1;
    return 0;
}

int     GetAWSGlaze(const char * pszGlaze, int * pnGlaze, int * pnError)
{
    int     nValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszGlaze, "934", 3) != 0)
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pnGlaze = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszGlaze + 3, 2);
    if (strncmp(szValue, "//", 2) == 0)
    {
        *pnGlaze = DEFAULT_VALUE;
        return 0;
    }
    for (i = 0; i < 2; i ++)
    {
        if (!isdigit(szValue[i]))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            *pnGlaze = DEFAULT_VALUE;
            return 1;
        }
    }
    nValue = strtod(szValue, NULL);
	/*
	if(nValue >= 56 && nValue <= 90)
		nValue = (nValue - 50)*10;
	else if(nValue >= 91 && nValue <= 96)
		nValue = (nValue - 90)*10;
	else if(nValue == 97)
		nValue = 999990;
	else if(nValue == 98)
		nValue = 400;
	else if(nValue == 99)
		nValue = 999999;
	*/
	if((nValue >= 0 && nValue <= 26) || (nValue >90 && nValue <= 97) || nValue == 99)
		//nValue = INTEGER_DEFAULT_EMPTY;
		nValue = nValue;
	else if(nValue == 27)
		nValue = 999900;
	else if(nValue >=28 && nValue <= 55)
		nValue = nValue;
	else if(nValue >= 56 && nValue <= 90)
		nValue = (nValue - 50)*10;
	else if(nValue == 98)
		nValue = 400;


    *pnGlaze = nValue;
    return 0;
}

int     GetAWSHaliDiameter(const char * pszHali, double * pdDiameter, int * pnError)
{
    int     nValue;
    double  dValue;
    int     i;
    char    szValue[4] = {0};
    *pnError = 0;
    if (strncmp(pszHali, "939", 3) != 0)
    {
        *pnError = ERROR_INVALID_CHARACTER;
        *pdDiameter = DEFAULT_VALUE;
        return 1;
    }
    strncpy(szValue, pszHali + 3, 2);
    if (strncmp(szValue, "//", 2) == 0)
    {
        *pdDiameter = DEFAULT_VALUE;
        return 0;
    }
    for (i = 0; i < 2; i ++)
    {
        if (!isdigit(szValue[i]))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            *pdDiameter = DEFAULT_VALUE;
            return 1;
        }
    }
    nValue = strtod(szValue, NULL);
    dValue = nValue ;
    *pdDiameter = dValue;
    return 0;
}

int     GetStationNo(const char * pszStationNo, int * pnError)
{
    int k, nValue, i;
    *pnError = 0;
    if ((pszStationNo[0] >= 'A') && (pszStationNo[0] < 'Z'))
    {
        k = pszStationNo[0];
    }
    else if ((pszStationNo[0] >= '0') && (pszStationNo[0] <= '9'))
    {
        k = pszStationNo[0] - 48;
    }
    else
    {
        *pnError = ERROR_INVALID_CHARACTER;
        return DEFAULT_VALUE;
    }
    for (i = 1; i < 5; i ++)
    {
        if (!isdigit(pszStationNo[i]))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            return DEFAULT_VALUE;
        }
    }
    nValue = strtol(pszStationNo+1, NULL, 10);
    nValue += 10000 * k;
    return nValue;
}

int     GetIntegerValue(const char * pszValue, char cDefault, int nScale, int * pnError)
{
    int     nValue;
    int     len = strlen(pszValue);
    int     i, iBegin, iEnd;
    char    szDefault[17] = {0};	
    memset(szDefault, cDefault, 16);
    *pnError = 0;
    if (strncmp(pszValue, szDefault, len) == 0)
    {
        return DEFAULT_VALUE;
    }
    for (i = 0; i < len; i ++)
    {
        if ((!isdigit(pszValue[i])) && (pszValue[i] != '-'))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            return DEFAULT_VALUE;
        }
    }
    nValue = strtol(pszValue, NULL, 10);
    if (nScale < 0)
    {
        iBegin = nScale;
        iEnd = 0;
        for (i = iBegin; i < iEnd; i ++)
        {
            nValue *= 10;
        }
    }
    else
    {
        iBegin = 0;
        iEnd = nScale;
        for (i = iBegin; i < iEnd; i ++)
        {
            nValue /= 10;
        }
    }
    return  nValue;
}

double  GetDoubleValue(const char * pszValue, char cDefault, int nScale, int * pnError)
{
    double  dValue;
    int     nValue;
    int     len = strlen(pszValue);
    int     i, iBegin, iEnd;
    char    szDefault[17] = {0};
    memset(szDefault, cDefault, 16);
    *pnError = 0;
    if (strncmp(pszValue, szDefault, len) == 0)
    {
        return DEFAULT_VALUE;
    }
    for (i = 0; i < len; i ++)
    {
        if ((!isdigit(pszValue[i])) && (pszValue[i] != '-') && (pszValue[i] != '.') && 
            (pszValue[i] != '+') && (pszValue[i] != 'E') && (pszValue[i] != 'e'))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            return DEFAULT_VALUE;
        }
    }
    //nValue = strtol(pszValue, NULL, 10);
    //dValue = nValue;
    dValue = strtod(pszValue, NULL);
    if (nScale < 0)
    {
        iBegin = nScale;
        iEnd = 0;
        for (i = iBegin; i < iEnd; i ++)
        {
            dValue *= 10;
        }
    }
    else
    {
        iBegin = 0;
        iEnd = nScale;
        for (i = iBegin; i < iEnd; i ++)
        {
            dValue /= 10;
        }
    }
    return  dValue;
}

/*double  GetDoubleValue(const char * pszValue, char cDefault, int nScale, int * pnError)
{
double  dValue;
int     nValue;
int     len = strlen(pszValue);
int     i, iBegin, iEnd;
char    szDefault[17] = {0};
memset(szDefault, cDefault, 16);
*pnError = 0;
if (strncmp(pszValue, szDefault, len) == 0)
{
return DEFAULT_VALUE;
}
for (i = 0; i < len; i ++)
{
if ((!isdigit(pszValue[i])) && (pszValue[i] != '-') && (pszValue[i] != '.'))
{
*pnError = ERROR_INVALID_CHARACTER;
return DEFAULT_VALUE;
}
}
//nValue = strtol(pszValue, NULL, 10);
//dValue = nValue;
dValue = strtod(pszValue, NULL);
if (nScale < 0)
{
iBegin = nScale;
iEnd = 0;
for (i = iBegin; i < iEnd; i ++)
{
dValue *= 10;
}
}
else
{
iBegin = 0;
iEnd = nScale;
for (i = iBegin; i < iEnd; i ++)
{
dValue /= 10;
}
}
return  dValue;
}*/

double  GetDoubleValue_1(const char * pszValue, char * pszDefault, int nScale, int * pnError)
{
    double  dValue;
    int     nValue;
    int     len = strlen(pszValue);
    int     i, iBegin, iEnd;
    //char    szDefault[17] = {0};
    //memset(szDefault, cDefault, 16);
    *pnError = 0;
    if (strncmp(pszValue, pszDefault, len) == 0)
    {
        return DEFAULT_VALUE;
    }
    for (i = 0; i < len; i ++)
    {
        if ((!isdigit(pszValue[i])) && (pszValue[i] != '-') && (pszValue[i] != '.'))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            return DEFAULT_VALUE;
        }
    }
    //nValue = strtol(pszValue, NULL, 10);
    //dValue = nValue;
    dValue = strtod(pszValue, NULL);
    if (nScale < 0)
    {
        iBegin = nScale;
        iEnd = 0;
        for (i = iBegin; i < iEnd; i ++)
        {
            dValue *= 10;
        }
    }
    else
    {
        iBegin = 0;
        iEnd = nScale;
        for (i = iBegin; i < iEnd; i ++)
        {
            dValue /= 10;
        }
    }
    return  dValue;
}

double     GetLatitudeLongitude(const char * pszValue, int nType, int nScale, int *pnError)
{
    char szValue[10] = {0};
    char szN = 0;
    double dScale;
    int     nValue;
    double  dValue;
    int     i, iBegin, iEnd;
    int  len = strlen(pszValue);
    strncpy(szValue, pszValue, len-1);
    szN = pszValue[len-1];
    //dScale = pow(10., nScale);
    *pnError = 0;
    if (strncmp(szValue, "////////////", len-1) == 0)
    {
        return DEFAULT_VALUE;
    }
    for (i = 0; i < len-1; i ++)
    {
        //commet by nathan
        //        printf("szValue[i]=%c\n",szValue[i]);
        if (!isdigit(szValue[i]))
        {
            *pnError = ERROR_INVALID_CHARACTER;
            printf("33333333333333\n");
            return DEFAULT_VALUE;
        }
    }
    if ((nType == 1) && ((szN != 'N') && (szN != 'S')))
    {
        *pnError = ERROR_INVALID_CHARACTER;
        printf("444444444444\n");
        return DEFAULT_VALUE;
    }
    if ((nType == 2) && ((szN != 'E') && (szN != 'W')))
    {
        *pnError = ERROR_INVALID_CHARACTER;
        printf("5555555555\n");
        return DEFAULT_VALUE;
    }
    nValue = strtol(szValue, NULL, 10);
    dValue = nValue;
    if (nScale < 0)
    {
        iBegin = nScale;
        iEnd = 0;
        for (i = iBegin; i < iEnd; i ++)
        {
            dValue *= 10;
        }
    }
    else
    {
        iBegin = 0;
        iEnd = nScale;
        for (i = iBegin; i < iEnd; i ++)
        {
            dValue /= 10;
        }
    }
    if ((szN == 'W') || (szN == 'S'))
    {
        dValue = -1.0 * dValue;
    }
    return dValue;
}

double  GetWindSpeed(const char * pszValue, int nScale, char cDefault, int * pnError)
{
    const char * pszItem;
    *pnError = 0;
    if ((pszItem = strchr(pszValue, '>')) != NULL)
    {
        return GetDoubleValue(pszItem+1, cDefault, 0, pnError);
    }
    return GetDoubleValue(pszValue, cDefault, nScale, pnError);
}

double  GetDepthTemperature(const char * pszValue, int nScale, char cDefault, int * pnError)
{
    const char * pszItem;
    char    szValue[32]={0};
    *pnError = 0;
    if ((pszItem = strchr(pszValue, '.')) != NULL)
    {
        return GetDoubleValue(pszItem + 1, cDefault, nScale, pnError);
    }
    if ((pszItem = strchr(pszValue, '+')) != NULL)
    {
        strcpy(szValue, "-");
        strcat(szValue, pszItem + 1);
        return GetDoubleValue(szValue, cDefault, nScale, pnError);
    }
    return GetDoubleValue(pszValue, cDefault, nScale, pnError);
}

/*转化字符为空格*/
int  ConvertBuffer(char *pInput)
{
    char *pszContent = pInput;
    while(*pszContent != '\0')
    {
        if( *pszContent < ' ')
            if( *pszContent != '\n' )
            {
                *pszContent = ' ';
            }
            pszContent++;
    }
    return 0;
}

int  GetOneReport_ZCZC_1(FILE *fpReport,char *report,int *report_len)
{
    int fsize = 0;
    char *start,*end;
    fseek(fpReport,0L,SEEK_END);
    fsize=ftell(fpReport);
    fseek(fpReport,0L,SEEK_SET);
    fread(report,1,fsize,fpReport);
    report[fsize] = 0;
    //printf("fsize = %d \n",fsize);
    //printf("report  = %s \n",report);
    //fclose(fpReport);
    *report_len = fsize;
    if ( (start = strstr(report, "ZCZC")) == NULL )
        return ERROR_START_OF_FILE;
    if( (end = strstr(report,AWS_FILE_END_ID)) == NULL )
        return ERROR_END_OF_FILE;
    if (  end < start )
    {
        return ERROR_FILE_FORMAT;
    }
    return SUCCESS_OP;
}
int iSubStringByComma_r(unsigned char *pszBuf, unsigned char *pszString, int *iGroup_Ret)
{

	int iRet = 0;
	if ('\0' == *pszString )
	{
		return -1;
	}
	
	
	while (',' != *pszString)
	{
		if ('\0' == *pszString ) 
		{
			goto Ending;
		}
		else
		{
            *pszBuf++ = *pszString++;
            iRet++;
            *iGroup_Ret=(*iGroup_Ret+1);
		}
	}

	if(',' == *pszString )
	{
		*pszBuf = '\0';
		iRet++;
	}
Ending: 
  
	*pszBuf = '\0';
	return iRet;

	
}

