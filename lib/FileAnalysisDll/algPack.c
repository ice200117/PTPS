#include "algPack.h"

int initAWSData(struct AWSData* readAWSData){
	return 0;
}

int countChar(char* str, char c,int filelen)
{	
	int count = 0;   
	char tmp = *str;   
	int i = 0;   
	int fl = 0;

	for(fl = 0;fl<filelen;fl++)    
	{          
		if(tmp == c)count ++;         
		i ++;          
		tmp = *(str + i);    
	}   

	return count;
}

int parseAWSData(char* pAWSData, struct AWSData* readAWSData){
    char* pCode;
    char delim[5]={0};
    int count=0;
    int fd;
    FILE *fp;
    char line[256]={0};
    int i,j;
    int tmpd=0;
    float tmpf=0.0;
    int sign=1;
    char *tmps=NULL;

    
    //sscanf(pAWSData, "%5c\n", line);
    while(pAWSData[0]<0 || pAWSData[0]>255 || !isalnum(pAWSData[0]))pAWSData++;//rmHeadNum++;
    //printf("pASW len = %d\n", strlen(pAWSData));//+rmHeadNum));
    if(strlen(pAWSData)<50)return 0;

	initAWSData(readAWSData);

    //fp = fopen("tmp", "w+");
    while(!(fp=fopen("tmp", "wb"))){
        //printf("%s--file:%s  line:%d\n", WTEMP_ERROR, __FILE__, __LINE__);
        //return 0;
    }
    fwrite(pAWSData, strlen(pAWSData), 1, fp);
    fflush(fp);
    fclose(fp);
    //rewind(fp);
    //fp = fopen("tmp", "r");
    //if(fp==NULL){
	while(!(fp=fopen("tmp", "r"))){
        //printf("%s--file:%s  line:%d\n", RTEMP_ERROR, __FILE__, __LINE__);
        //return 0;
    }
	errno = 0;
    strcpy(delim, " \r\n");
    for(i=0;i<15 && !feof(fp);i++){
        memset(line, 0, 256);
        fgets(line, sizeof(line), fp);
        //printf("%d\n",strlen(line));
        //printf("%d\n", subS(line,0,1)[0]);
        //printf("%d\n", subS(line,1,1)[0]);
        switch(i){
            case 0:
                pCode= strtok(line, delim);
                //printf("0****%s\n", pCode);
                strncpy(readAWSData->baseInfo.stationID, pCode, 5); //区站号
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
							//QString dT = pCode;
							//dT = QDateTime::fromString(dT,"yyyyMMddhhssmm").addSecs(28800).toString("yyyyMMddhhssmm");

							//std::string str = dT.toStdString();
							//const char *ch = str.c_str();

                            strncpy(readAWSData->baseInfo.dateTime, pCode, 14); //日期时间
                            break;
                        case 2:
                            strncpy(readAWSData->baseInfo.latitude, pCode, 6); //纬度
                            break;
                        case 3:
                            strncpy(readAWSData->baseInfo.longitude, pCode, 7); //经度
                            break;
                        case 4:

                            if(isdigit(subS(pCode,1,1)[0]) && isdigit(subS(pCode,2,1)[0]) &&
                                isdigit(subS(pCode,3,1)[0]) && isdigit(subS(pCode,4,1)[0])){
                                if(strcmp(subS(pCode,0,1),"-")==0){ 
                                    sign=-1;
                                    sscanf(subS(pCode,1,4),"%f",&tmpf);
                                    readAWSData->baseInfo.elevation = (float)sign * tmpf * 0.1; //观测场海拔，m
                                }else if(isdigit(subS(pCode,0,1)[0])){
                                    sscanf(subS(pCode,0,5),"%f",&tmpf);
                                    readAWSData->baseInfo.elevation = tmpf * 0.1; //观测场海拔，m
                                }
                            }
                            break;
                        case 5:
                            if(isdigit(subS(pCode,1,1)[0]) && isdigit(subS(pCode,2,1)[0]) &&
                                    isdigit(subS(pCode,3,1)[0]) && isdigit(subS(pCode,4,1)[0])){
                                if(strcmp(subS(pCode,0,1),"-")==0){
                                    sign=-1;
                                    sscanf(subS(pCode,1,4),"%f",&tmpf);
                                    readAWSData->baseInfo.APSElev = (float)sign * tmpf * 0.1; //气压传感器海拔，m
                                }else if(isdigit(subS(pCode,0,1)[0])){
                                    sscanf(subS(pCode,0,5),"%f",&tmpf);
                                    readAWSData->baseInfo.APSElev = tmpf * 0.1; //观测场海拔，m
                                }
                            }
                            break;
                        case 6:
                            strncpy(readAWSData->baseInfo.ObWay, pCode, 1); //观测方式
                            break;
                        case 7:
                            strncpy(readAWSData->baseInfo.QCI, pCode, 3); //质量控制标识
                            break;
                        case 8:
                            strncpy(readAWSData->baseInfo.FCI, pCode, 3); //文件更正标识
                            break;
                    }
                    count++;
                }
                break;
            case 1:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "PP")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,1,1)[0]) && isdigit(subS(pCode,2,1)[0]) && 
                               isdigit(subS(pCode,3,1)[0]) && isdigit(subS(pCode,4,1)[0])&& 
                                    isdigit(subS(pCode,0,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->pp.locAP = tmpf * 0.1; //本站气压 hPa
                            }
                            break;
                        case 2:
                            if(isdigit(subS(pCode,1,1)[0]) && isdigit(subS(pCode,2,1)[0]) && 
                                isdigit(subS(pCode,3,1)[0]) && isdigit(subS(pCode,4,1)[0])&& 
                                    isdigit(subS(pCode,0,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->pp.SSAP = tmpf * 0.1; //海平面气压 hPa
                            }
                            break;
                        case 3:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->pp.threeHourDiffAP = (1000.0 - tmpf) * 0.1; //3小时变压 hPa
                            }
                            break;
                        case 4:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->pp.twentyFourHourDiffAP = (1000.0 - tmpf) * 0.1; //24小时变压 hPa
                            }
                            break;
                        case 5:
                            if(isdigit(subS(pCode,1,1)[0]) && isdigit(subS(pCode,2,1)[0]) && 
                                isdigit(subS(pCode,3,1)[0]) && isdigit(subS(pCode,4,1)[0])&& 
                                    isdigit(subS(pCode,0,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->pp.maxAP = tmpf * 0.1; //每1小时内的最高本站气压值
                            }
                            break;
                        case 6:
                            strncpy(readAWSData->pp.maxAPTime, pCode, 4); //
                            break;
                        case 7:
                            if(isdigit(subS(pCode,1,1)[0]) && isdigit(subS(pCode,2,1)[0]) && 
                                isdigit(subS(pCode,3,1)[0]) && isdigit(subS(pCode,4,1)[0])&& 
                                    isdigit(subS(pCode,0,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->pp.minAP = tmpf * 0.1; //每1小时内的最低本站气压值
                            }
                            break;
                        case 8:
                            strncpy(readAWSData->pp.minAPTime, pCode, 4); //
                            break;
                    }
                    count++;
                }
                break;
            case 2:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "TH")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.AT = (1000.0 - tmpf) * 0.1; //气温
                            }
                            break;
                        case 2:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.maxAT = (1000.0 - tmpf) * 0.1; //每1小时内的最高气温
                            }
                            break;
                        case 3:
                            strncpy(readAWSData->th.maxATTime, pCode, 4); //
                            break;
                        case 4:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.minAT = (1000.0 - tmpf) * 0.1; //每1小时内的最低气温
                            }
                            break;
                        case 5:
                            strncpy(readAWSData->th.minATTime, pCode, 4); //
                            break;
                        case 6:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.TwentyFourDiffAT = (1000.0 - tmpf) * 0.1; //24小时变温
                            }
                            break;
                        case 7:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.TFMaxAT = (1000.0 - tmpf) * 0.1; //过去24小时最高气温
                            }
                            break;
                        case 8:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.TFMinAT = (1000.0 - tmpf) * 0.1; //过去24小时内的最低气温
                            }
                            break;
                        case 9:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->th.dewT = (1000.0 - tmpf) * 0.1; //露点温度
                            }
                            break;
                        case 10:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->th.HU = tmpd; //相对湿度
                            }
                            break;
                        case 11:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->th.minHU = tmpd; //每1小时内最小相对湿度
                            }
                            break;
                        case 12:
                            strncpy(readAWSData->th.minHUTime, pCode, 4); //
                            break;
                        case 13:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->th.vaporPressure = tmpf * 0.1; //水汽压
                            }
                            break;
                    }
                    count++;
                }
                break;
            case 3:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "RE")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->re.oneHourRain = tmpf * 0.1; //每1小时降水量,mm
                            }else if(strcmp(pCode,",,,,")==0){
                                readAWSData->re.oneHourRain = 0000.0; //微量时存入888888
                            }
                            break;
                        case 2:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0]) &&
                                isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->re.threeHourRain = tmpf * 0.1; //过去3小时降水量
                            }else if(strcmp(pCode,",,,,,")==0){
                                readAWSData->re.threeHourRain = 0000.0; //微量时存入888888
                            }
                            break;
                        case 3:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0]) &&
                                isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->re.sixHourRain = tmpf * 0.1; //过去6小时降水量
                            }else if(strcmp(pCode,",,,,,")==0){
                                readAWSData->re.sixHourRain = 0000.0; //微量时存入888888
                            }
                            break;
                        case 4:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0]) &&
                                isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->re.twelveHourRain = tmpf * 0.1; //过去12小时降水量
                            }else if(strcmp(pCode,",,,,,")==0){
                                readAWSData->re.twelveHourRain = 0000.0; //微量时存入888888
                            }
                            break;
                        case 5:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0]) &&
                                isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->re.twentyFourHourRain = tmpf * 0.1; //过去24小时降水量
                            }else if(strcmp(pCode,",,,,,")==0){
                                readAWSData->re.twentyFourHourRain = 0000.0; //微量时存入888888
                            }
                            break;
                        case 6:
                            strncpy(readAWSData->re.RJMT, pCode, 2); //人工加密观测降水量描述时间周期
                            break;
                        case 7:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0]) &&
                                isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->re.RJMRain = tmpf * 0.1; //人工加密观测降水量
                            }else if(strcmp(pCode,",,,,,")==0){
                                readAWSData->re.RJMRain = 888888.0; //微量时存入888888
                            }
                            break;
                        case 8:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->re.oneHourEvaporation = tmpf * 0.1; //小时蒸发量,mm
                            }else if(strcmp(pCode,",,,,")==0){
                                readAWSData->re.oneHourEvaporation = 888888.0; //微量时存入888888
                            }
                            break;
                    }
                    count++;
                }
                break;
            case 4:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "WI")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.twoMiniteWD = tmpd ; //当前时刻的2分钟平均风向 1°
                            }
                            break;
                        case 2:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.twoMiniteWS = tmpf * 0.1; //2分钟平均风速 m/s
                            }
                            break;
                        case 3:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.tenMiniteWD = tmpd ; //当前时刻的10分钟平均风向 1°
                            }
                            break;
                        case 4:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.tenMiniteWS = tmpf * 0.1; //10分钟平均风速 m/s
                            }
                            break;
                        case 5:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.maxWD = tmpd ; //
                            }
                            break;
                        case 6:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                    isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.maxWS = tmpf * 0.1; //
                            }
                            break;
                        case 7:
                            strncpy(readAWSData->wi.maxWST, pCode, 4); //每1小时内10分钟最大风速出现时间，时分各两位
                            break;
                        case 8:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.instantaneousWD = tmpd ; //
                            }
                            break;
                        case 9:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                    isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.instantaneousWS = tmpf * 0.1; //
                            }
                            break;
                        case 10:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.extremeWD = tmpd ; //
                            }
                            break;
                        case 11:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                    isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.extremeWS = tmpf * 0.1; //
                            }
                            break;
                        case 12:
                            strncpy(readAWSData->wi.extremeWST, pCode, 4); //每一小时内极大瞬时风速出现时间
                            break;
                        case 13:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                    isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.sixHourExtremeWS = tmpf * 0.1; //
                            }
                            break;
                        case 14:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.sixHourExtremeWD = tmpd ; //
                            }
                            break;
                        case 15:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                    isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->wi.twelveHourExtremeWS = tmpf * 0.1; //
                            }
                            break;
                        case 16:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0])){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->wi.twelveHourExtremeWD = tmpd ; //
                            }
                            break;
                    }
                    count++;
                }
                break;
            case 5:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "DT")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.DST = (1000.0 - tmpf) * 0.1; //当前时刻的地面温度 ℃
                            }
                            break;
                        case 2:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.maxDST = (1000.0 - tmpf) * 0.1; //每1小时内的地面最高温度
                            }
                            break;
                        case 3:
                            strncpy(readAWSData->dt.maxDSTTime, pCode, 4); //
                            break;
                        case 4:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.minDST = (1000.0 - tmpf) * 0.1; //每1小时内的地面最低温度
                            }
                            break;
                        case 5:
                            strncpy(readAWSData->dt.minDSTTime, pCode, 4); //
                            break; 
                        case 6:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.twelveminDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 7:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.fivecmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 8:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.tencmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 9:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.fifteencmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 10:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.twentycmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 11:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.fortycmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 12:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.eightycmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 13:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.oneHundredSixtycmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 14:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.threeHundredtwentycmDST = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 15:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.grassLandT = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 16:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.maxGrassLandT = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 17:
                            strncpy(readAWSData->dt.maxGrassLandTTime, pCode, 4); //
                            break; 
                        case 18:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->dt.minGrassLandT = (1000.0 - tmpf) * 0.1; //
                            }
                            break;
                        case 19:
                            strncpy(readAWSData->dt.minGrassLandTTime, pCode, 4); //
                            break; 
                    }
                    count++;
                }
                break;
            case 6:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "VV")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])
                                && isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->vv.oneMiniteHV = tmpf; //当前时刻的1分钟平均水平能见度
                            }
                            break;
                        case 2:
                         if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])
                                && isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->vv.tenMiniteHV = tmpf; //
                            }
                            break;
                        case 3:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])
                                && isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->vv.minHV = tmpf; //每1小时内的最小能见度
                            }
                            break;
                        case 4:
                            strncpy(readAWSData->vv.minHVTime, pCode, 4); //
                            break;
                    }
                    count++;
                }
                break;
            case 7:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "CW")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,5),"%f",&tmpf);
                                readAWSData->cw.RHV = tmpf * 0.1; //正点能见度，由人工输入 km
                            }
                            break;
                        case 2:
                            strncpy(readAWSData->cw.TCloudage, pCode, 3); //
                            break;
                        case 3:
                            strncpy(readAWSData->cw.LCloudage, pCode, 3); //
                            break;
                        case 4:
                            strncpy(readAWSData->cw.reportCloudage, pCode, 3); //
                            break;
                        case 5:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])
                                && isdigit(subS(pCode,4,1)[0])){
                                sscanf(subS(pCode,0,5),"%d",&tmpd);
                                readAWSData->cw.cloudHeight = tmpd; //云高 m,正点的低（中）云状云高，由人工输入，为编报iRiXhVV中的h；当无Nh的云时，若无云高值，均写入2500
                            }
                            break;
                        case 6:
                            strncpy(readAWSData->cw.cloudForm, pCode, 24); //
                            break;
                        case 7:
                            strncpy(readAWSData->cw.choudCode, pCode, 3); //
                            break;
                        case 8:
                            strncpy(readAWSData->cw.currentWeather, pCode, 2); //
                            break;
                        case 9:
                            strncpy(readAWSData->cw.pastWeatherT, pCode, 2); //
                            break;
                        case 10:
                            strncpy(readAWSData->cw.pastW1, pCode, 1); //
                            break;
                        case 11:
                            strncpy(readAWSData->cw.pastW2, pCode, 1); //
                            break;
                        case 12:
                            strncpy(readAWSData->cw.stateOfGround, pCode, 2); //
                            break;
                    }
                    count++;
                }
                break;
            case 8:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "SP")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) && isdigit(subS(pCode,3,1)[0])){
                                sscanf(subS(pCode,0,4),"%f",&tmpf);
                                readAWSData->sp.snowDepth = tmpf * 0.1; //积雪深度 cm
                            }else if(strcmp(pCode,",,,,")==0){
                                readAWSData->sp.snowDepth = 888888.0; //微量时存入888888
                            } 
                            break;
                        case 2:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%f",&tmpf);
                                readAWSData->sp.snowPressure = tmpf * 0.1; //雪压 g/(cm*cm)
                            }
                            break;
                        case 3:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->sp.frozenSoilDepth1Upper = tmpd; //冻土深度第1栏上限值 cm
                            }else if(strcmp(pCode,",,,")==0){
                                readAWSData->sp.frozenSoilDepth1Upper = 888888; //微量时存入888888
                            }
                            break;
                        case 4:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->sp.frozenSoilDepth1Lower = tmpd; //冻土深度第1栏下限值 cm
                            }else if(strcmp(pCode,",,,")==0){
                                readAWSData->sp.frozenSoilDepth1Lower = 888888; //微量时存入888888
                            }
                            break;
                        case 5:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->sp.frozenSoilDepth2Upper = tmpd; //
                            }else if(strcmp(pCode,",,,")==0){
                                readAWSData->sp.frozenSoilDepth2Upper = 888888; //微量时存入888888
                            }
                            break;
                        case 6:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->sp.frozenSoilDepth2Lower = tmpd; //
                            }else if(strcmp(pCode,",,,")==0){
                                readAWSData->sp.frozenSoilDepth2Lower = 888888; //微量时存入888888
                            }
                            break;
                        case 7:
                            strncpy(readAWSData->sp.TornadoDisCode, pCode, 1); //龙卷、尘卷风距测站距离编码
                            break;
                        case 8:
                            strncpy(readAWSData->sp.TornadoDirCode, pCode, 1); //龙卷、尘卷风距测站方位编码
                            break;
                        case 9:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->sp.glazeDiameter = tmpd; //电线积冰（雨凇）直径
                            }
                            break;
                        case 10:
                            if(isdigit(subS(pCode,0,1)[0]) && isdigit(subS(pCode,1,1)[0]) && 
                                isdigit(subS(pCode,2,1)[0]) ){
                                sscanf(subS(pCode,0,3),"%d",&tmpd);
                                readAWSData->sp.maxHailDia = tmpd; //最大冰雹直径
                            }
                            break;
                    }
                    count++;
                }
                break;
            case 9:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "MR")!=0)break;
                if(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    if(strlen(pCode)==120){
                        for(j=0;j<60;j++){
                            tmps = strdup(subS(pCode,j*2,2));
                            if(strcmp(tmps,",,")==0){
                                readAWSData->miniteRain[j] = 888888.0; //小时内每分钟降水量数据
                            }else if(isdigit(subS(tmps,0,1)[0]) && isdigit(subS(tmps,1,1)[0])){
                                sscanf(tmps ,"%f", &tmpf);
                                readAWSData->miniteRain[j] = tmpf * 0.1; //小时内每分钟降水量数据
                            }
                            free(tmps);
                        }
                    }
                }
                break;
            case 10:
                pCode= strtok(line, "\r\n");
                //printf("1****%s\n", pCode);
                if(strcmp(subS(pCode,0,2), "MW")==0){
                    strcpy(readAWSData->MW, subS(pCode, 3, 0));
                }
                break;
            case 11:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                break;
            case 12:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "Q1")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            strncpy(readAWSData->qc.Q1.code1, pCode, 8);
                            break;
                        case 2:
                            strncpy(readAWSData->qc.Q1.code2, pCode, 14);
                            break;
                        case 3:
                            strncpy(readAWSData->qc.Q1.code3, pCode, 8);
                            break;
                        case 4:
                            strncpy(readAWSData->qc.Q1.code4, pCode, 16);
                            break;
                        case 5:
                            strncpy(readAWSData->qc.Q1.code5, pCode, 19);
                            break;
                        case 6:
                            strncpy(readAWSData->qc.Q1.code6, pCode, 4);
                            break;
                        case 7:
                            strncpy(readAWSData->qc.Q1.code7, pCode, 12);
                            break;
                        case 8:
                            strncpy(readAWSData->qc.Q1.code8, pCode, 10);
                            break;
                        case 9:
                            strncpy(readAWSData->qc.Q1.code9, pCode, 60);
                            break;
                    }
                    count++;
                }
                break;
            case 13:
                pCode= strtok(line, delim);
                //printf("1****%s\n", pCode);
                if(strcmp(pCode, "Q2")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            strncpy(readAWSData->qc.Q2.code1, pCode, 8);
                            break;
                        case 2:
                            strncpy(readAWSData->qc.Q2.code2, pCode, 14);
                            break;
                        case 3:
                            strncpy(readAWSData->qc.Q2.code3, pCode, 8);
                            break;
                        case 4:
                            strncpy(readAWSData->qc.Q2.code4, pCode, 16);
                            break;
                        case 5:
                            strncpy(readAWSData->qc.Q2.code5, pCode, 19);
                            break;
                        case 6:
                            strncpy(readAWSData->qc.Q2.code6, pCode, 4);
                            break;
                        case 7:
                            strncpy(readAWSData->qc.Q2.code7, pCode, 12);
                            break;
                        case 8:
                            strncpy(readAWSData->qc.Q2.code8, pCode, 10);
                            break;
                        case 9:
                            strncpy(readAWSData->qc.Q2.code9, pCode, 60);
                            break;
                    }
                    count++;
                }
                break;
            case 14:
                pCode= strtok(line, delim);
                //printf("14****%s\n", pCode);
                if(strcmp(pCode, "Q3")!=0)break; 
                count=1;
                while(pCode=strtok(NULL, delim)){
                    //printf("*****%s\n", pCode);
                    switch(count){
                        case 1:
                            strncpy(readAWSData->qc.Q3.code1, pCode, 8);
                            break;
                        case 2:
                            strncpy(readAWSData->qc.Q3.code2, pCode, 14);
                            break;
                        case 3:
                            strncpy(readAWSData->qc.Q3.code3, pCode, 8);
                            break;
                        case 4:
                            strncpy(readAWSData->qc.Q3.code4, pCode, 16);
                            break;
                        case 5:
                            strncpy(readAWSData->qc.Q3.code5, pCode, 19);
                            break;
                        case 6:
                            strncpy(readAWSData->qc.Q3.code6, pCode, 4);
                            break;
                        case 7:
                            strncpy(readAWSData->qc.Q3.code7, pCode, 12);
                            break;
                        case 8:
                            strncpy(readAWSData->qc.Q3.code8, pCode, 10);
                            break;
                        case 9:
                            strncpy(readAWSData->qc.Q3.code9, pCode, 60);
                            break;
                    }
                    count++;
                }
                break;
        }
    }

    fclose(fp);
    remove("tmp");
    return 1;
}

/* 读AWS数据报 */
int readAWS(const char* fileName, struct AWSData** readAWSData){
    int state =0;
    FILE* fpFile=NULL;
    int nFileLength=0;
    char* pBuffer;
    char** pAWSData;
    char delim[5];
    int nAWSData=0;
    int i=0;
    char* tmpS;
	int ret_len=0;

    /*打开文件*/
    fpFile = fopen(fileName, "rb");
    if(fpFile == NULL) {
        printf("%s--file:%s  line:%d\n", READAWS_ERROR, __FILE__, __LINE__);
        return -1;
    }       

    fseek(fpFile, 0, SEEK_END);
    nFileLength = ftell(fpFile);
    /*申请内存*/
    pBuffer = (char*)calloc(nFileLength+1,sizeof(char));
    if ( NULL == pBuffer )
    {   
        printf("%s--file:%s  line:%d\n", MALLOC_ERROR, __FILE__, __LINE__);
        return -1; 

    }
    fseek(fpFile, 0, SEEK_SET);

    /*文件拷贝到内存里*/

    //memset(pBuffer, 0, nFileLength+1);
	ret_len = fread(pBuffer, 1, nFileLength, fpFile);
	printf("ret_len = %d!\n", ret_len);
	if(ret_len < nFileLength)memset(pBuffer+ret_len, 0, nFileLength-ret_len);
	printf("strlen(pBuffer) = %d!\n", strlen(pBuffer));



    fclose(fpFile);

    /* 获取数据文件中有多少个单站数据 */
    printf("%d\n",nFileLength);

	nAWSData = countChar(pBuffer,'=',nFileLength); //这句要放在strtok前面

    strcpy(delim, "=");
    //pAWSData[i] = strtok(pBuffer, delim);
    tmpS = strtok(pBuffer, delim);

    //printf("len = %d\n",strlen(pAWSData[i]));
    //nAWSData = nFileLength/strlen(pAWSData[i]);
    printf("len = %d\n",strlen(tmpS));
    //nAWSData = nFileLength/(strlen(tmpS)-10);
	
    printf("n = %d\n", nAWSData);
	if(nAWSData <=0)return 0;
    /* 为存放数据的字符串和结构体分配空间,并保存到数据到字符串数组里 */
    *readAWSData = (struct AWSData*)calloc(nAWSData, sizeof(struct AWSData));
    pAWSData = (char**)calloc(nAWSData, sizeof(char*));
    //strcpy(pAWSData[i],tmpS);
    pAWSData[0] = tmpS;

    for(i=1;i<nAWSData;i++){
        pAWSData[i]=strtok(NULL, delim);
    }

    /* 解析每个单站数据 */
	for(i=0;i<nAWSData;i++){
		if(pAWSData[i]!=NULL){
//			printf("i = %d\n", i);
            state += parseAWSData(pAWSData[i], (*readAWSData) + i); //处理成功1个，则返回值加1
        }
    }
	free(pBuffer);
    free(pAWSData);

    //return nAWSData;
    return state;
}

