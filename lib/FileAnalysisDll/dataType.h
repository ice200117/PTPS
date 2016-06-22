#ifndef DATATYPE_H_
#define DATATYPE_H_

#pragma pack(1)


//测站基本信息
struct BaseInfo{
    char stationID[6];
    char dateTime[15]; //国际时 yyyyMMddhhmmss
    char latitude[7]; //度分秒
    char longitude[8]; //度分秒
    float elevation; //观测场拔海高度 m
    float APSElev; //气压传感器拔海高度 m
    char ObWay[2]; //观测方式
    char QCI[4]; //质量控制标识
    char FCI[4]; //文件更正标识
};

//气压数据
struct PP{
    float locAP; //当前时刻的本站气压 hPa
    float SSAP; //当期时刻的海平面气压
    float threeHourDiffAP; //3小时变压
    float twentyFourHourDiffAP; //24小时变压
    float maxAP; //每1小时内的最高本站气压值
    char  maxAPTime[5];
    float minAP; //每1小时内的最低本站气压值
    char  minAPTime[5];
};

//温度和湿度数据
struct TH{
    float AT; //当期时刻的空气温度 ℃
    float maxAT; //每1小时内的最高气温
    char  maxATTime[5]; //每1小时内最高气温出现时间
    float minAT; //每1小时内的最低气温
    char  minATTime[5]; //每1小时内最低气温出现时间
    float TwentyFourDiffAT; //24小时变温
    float TFMaxAT; //过去24小时最高气温
    float TFMinAT; //过去24小时最低气温
    float dewT; //露点温度
    int   HU;   //相对湿度
    int   minHU; //每1小时内的最小相对湿度
    char  minHUTime[5]; //每1小时内最小相对湿度出现时间
    float vaporPressure; //水汽压 hPa
};

//累计降水和蒸发量数据 mm,微量保文中为“，”。微量存数值为888888
struct RE{
    float oneHourRain; //每1小时内的降水量累积量 mm
    float threeHourRain; //过去3小时降水量
    float sixHourRain; //过去6小时降水量
    float twelveHourRain; //过去12小时降水量
    float twentyFourHourRain; //过去24小时降水量
    char RJMT[3]; //人工加密观测降水量描述时间周期
    float RJMRain; //人工加密观测降水量
    float oneHourEvaporation; //小时蒸发量 mm
};

struct WI{ //风观测数据
    int   twoMiniteWD; //当前时刻的2分钟平均风向 1°
    float twoMiniteWS; //2分钟平均风速 m/s
    int   tenMiniteWD;
    float tenMiniteWS;
    int   maxWD;
    float maxWS;
    char  maxWST[5]; //每1小时内10分钟最大风速出现时间，时分各两位
    int   instantaneousWD; //当前时刻的瞬时风向
    float instantaneousWS;
    int extremeWD; //每一小时内极大瞬时风速对应的风向
    float extremeWS; //每一小时内极大瞬时风速
    char extremeWST[5]; //每一小时内极大瞬时风速出现时间
    float sixHourExtremeWS; //过去6小时内极大瞬时风速
    int sixHourExtremeWD; //过去6小时内极大瞬时风速对应的风向
    float twelveHourExtremeWS; //过去12小时内极大瞬时风速
    int twelveHourExtremeWD; //过去12小时内极大瞬时风速对应的风向
};

struct DT{ //地温数据
    float DST; //当前时刻的地面温度 ℃
    float maxDST; //每1小时内的地面最高温度
    char  maxDSTTime[5];
    float minDST; //每1小时内的地面最低温度
    char  minDSTTime[5];
    float twelveminDST;
    float fivecmDST; //5厘米地温
    float tencmDST;
    float fifteencmDST;
    float twentycmDST;
    float fortycmDST;
    float eightycmDST;
    float oneHundredSixtycmDST;
    float threeHundredtwentycmDST;
    float grassLandT; //当前时刻草面温度
    float maxGrassLandT; //每1小时内草面最高温度
    char maxGrassLandTTime[5]; //每1小时内草面最高温度出现时间
    float minGrassLandT; //每1小时内草面最高温度
    char minGrassLandTTime[5]; //每1小时内草面最高温度出现时间
};

struct VV{ //自动观测能见度数据 m
    float oneMiniteHV; //当前时刻的1分钟平均水平能见度
    float tenMiniteHV;
    float minHV; //每1小时内的最小能见度
    char  minHVTime[5];
};

struct CW{ //人工观测能见度、云、天数据
    float RHV; //正点能见度，由人工输入 km
    char  TCloudage[4]; //总云量
    char  LCloudage[4]; //低云量
    char  reportCloudage[4]; //编报云量
    int   cloudHeight; //云高 m,正点的低（中）云状云高，由人工输入，为编报iRiXhVV中的h；当无Nh的云时，若无云高值，均写入2500
    char  cloudForm[25]; //云状
    char  choudCode[4]; //云状编码（云码）
    char  currentWeather[3]; //现在天气现象编码
    char  pastWeatherT[3]; //过去天气描述时间周期,对于天气报为06，补充天气报为03，加密天气报的00时为12，其他天气（加密）报时次为06，非发天气(加密)报时次，固定编“//”
    char  pastW1[2]; //过去天气1
    char  pastW2[2];
    char  stateOfGround[3];
};

struct SP{ //其他重要天气数据
    float  snowDepth; //积雪深度 cm,微量保文中为“，”。微量存数值为888888
    float  snowPressure; //雪压 g/(cm*cm)
    int  frozenSoilDepth1Upper; //冻土深度第1栏上限值 cm
    int  frozenSoilDepth1Lower; //冻土深度第1栏下限值 cm
    int  frozenSoilDepth2Upper; //冻土深度第2栏上限值 cm
    int  frozenSoilDepth2Lower; //冻土深度第2栏下限值 cm
    char  TornadoDisCode[2]; //龙卷、尘卷风距测站距离编码
    char  TornadoDirCode[2]; //龙卷、尘卷风距测站方位编码
    int  glazeDiameter; //电线积冰（雨凇）直径
    int  maxHailDia; //最大冰雹直径
};

struct QCCode{ //数据质量控制码,共9组
    char code1[9];
    char code2[14];
    char code3[9];
    char code4[17];
    char code5[20];
    char code6[5];
    char code7[13];
    char code8[11];
    char code9[61];
};

struct QC{ //数据质量控制码封装
    struct QCCode Q1; //台站级
    struct QCCode Q2; //省级
    struct QCCode Q3; //国家级
};

//地面气象要素数据结构体
struct AWSData{
    struct BaseInfo baseInfo; //测站基本信息
    struct PP pp; //气压数据 hPa
    struct TH th; //温度和湿度数据 ℃
    struct RE re; //累计降水和蒸发量数据 mm
    struct WI wi; //风观测数据 1° m/s
    struct DT dt; //地温数据 ℃
    struct VV vv; //自动观测能见度数据 m
    struct CW cw; //人工观测能见度、云、天数据
    struct SP sp; //其他重要天气数据
    float  miniteRain[60]; //小时内每分钟降水量数据
    char   MW[256]; //人工观测连续天气现象
    struct QC qc; //数据质量控制码
};


#pragma pack()
#endif /* DATATYPE_H_ */
