#ifndef DATATYPE_H_
#define DATATYPE_H_

#pragma pack(1)


//��վ������Ϣ
struct BaseInfo{
    char stationID[6];
    char dateTime[15]; //����ʱ yyyyMMddhhmmss
    char latitude[7]; //�ȷ���
    char longitude[8]; //�ȷ���
    float elevation; //�۲ⳡ�κ��߶� m
    float APSElev; //��ѹ�������κ��߶� m
    char ObWay[2]; //�۲ⷽʽ
    char QCI[4]; //�������Ʊ�ʶ
    char FCI[4]; //�ļ�������ʶ
};

//��ѹ����
struct PP{
    float locAP; //��ǰʱ�̵ı�վ��ѹ hPa
    float SSAP; //����ʱ�̵ĺ�ƽ����ѹ
    float threeHourDiffAP; //3Сʱ��ѹ
    float twentyFourHourDiffAP; //24Сʱ��ѹ
    float maxAP; //ÿ1Сʱ�ڵ���߱�վ��ѹֵ
    char  maxAPTime[5];
    float minAP; //ÿ1Сʱ�ڵ���ͱ�վ��ѹֵ
    char  minAPTime[5];
};

//�¶Ⱥ�ʪ������
struct TH{
    float AT; //����ʱ�̵Ŀ����¶� ��
    float maxAT; //ÿ1Сʱ�ڵ��������
    char  maxATTime[5]; //ÿ1Сʱ��������³���ʱ��
    float minAT; //ÿ1Сʱ�ڵ��������
    char  minATTime[5]; //ÿ1Сʱ��������³���ʱ��
    float TwentyFourDiffAT; //24Сʱ����
    float TFMaxAT; //��ȥ24Сʱ�������
    float TFMinAT; //��ȥ24Сʱ�������
    float dewT; //¶���¶�
    int   HU;   //���ʪ��
    int   minHU; //ÿ1Сʱ�ڵ���С���ʪ��
    char  minHUTime[5]; //ÿ1Сʱ����С���ʪ�ȳ���ʱ��
    float vaporPressure; //ˮ��ѹ hPa
};

//�ۼƽ�ˮ������������ mm,΢��������Ϊ��������΢������ֵΪ888888
struct RE{
    float oneHourRain; //ÿ1Сʱ�ڵĽ�ˮ���ۻ��� mm
    float threeHourRain; //��ȥ3Сʱ��ˮ��
    float sixHourRain; //��ȥ6Сʱ��ˮ��
    float twelveHourRain; //��ȥ12Сʱ��ˮ��
    float twentyFourHourRain; //��ȥ24Сʱ��ˮ��
    char RJMT[3]; //�˹����ܹ۲⽵ˮ������ʱ������
    float RJMRain; //�˹����ܹ۲⽵ˮ��
    float oneHourEvaporation; //Сʱ������ mm
};

struct WI{ //��۲�����
    int   twoMiniteWD; //��ǰʱ�̵�2����ƽ������ 1��
    float twoMiniteWS; //2����ƽ������ m/s
    int   tenMiniteWD;
    float tenMiniteWS;
    int   maxWD;
    float maxWS;
    char  maxWST[5]; //ÿ1Сʱ��10���������ٳ���ʱ�䣬ʱ�ָ���λ
    int   instantaneousWD; //��ǰʱ�̵�˲ʱ����
    float instantaneousWS;
    int extremeWD; //ÿһСʱ�ڼ���˲ʱ���ٶ�Ӧ�ķ���
    float extremeWS; //ÿһСʱ�ڼ���˲ʱ����
    char extremeWST[5]; //ÿһСʱ�ڼ���˲ʱ���ٳ���ʱ��
    float sixHourExtremeWS; //��ȥ6Сʱ�ڼ���˲ʱ����
    int sixHourExtremeWD; //��ȥ6Сʱ�ڼ���˲ʱ���ٶ�Ӧ�ķ���
    float twelveHourExtremeWS; //��ȥ12Сʱ�ڼ���˲ʱ����
    int twelveHourExtremeWD; //��ȥ12Сʱ�ڼ���˲ʱ���ٶ�Ӧ�ķ���
};

struct DT{ //��������
    float DST; //��ǰʱ�̵ĵ����¶� ��
    float maxDST; //ÿ1Сʱ�ڵĵ�������¶�
    char  maxDSTTime[5];
    float minDST; //ÿ1Сʱ�ڵĵ�������¶�
    char  minDSTTime[5];
    float twelveminDST;
    float fivecmDST; //5���׵���
    float tencmDST;
    float fifteencmDST;
    float twentycmDST;
    float fortycmDST;
    float eightycmDST;
    float oneHundredSixtycmDST;
    float threeHundredtwentycmDST;
    float grassLandT; //��ǰʱ�̲����¶�
    float maxGrassLandT; //ÿ1Сʱ�ڲ�������¶�
    char maxGrassLandTTime[5]; //ÿ1Сʱ�ڲ�������¶ȳ���ʱ��
    float minGrassLandT; //ÿ1Сʱ�ڲ�������¶�
    char minGrassLandTTime[5]; //ÿ1Сʱ�ڲ�������¶ȳ���ʱ��
};

struct VV{ //�Զ��۲��ܼ������� m
    float oneMiniteHV; //��ǰʱ�̵�1����ƽ��ˮƽ�ܼ���
    float tenMiniteHV;
    float minHV; //ÿ1Сʱ�ڵ���С�ܼ���
    char  minHVTime[5];
};

struct CW{ //�˹��۲��ܼ��ȡ��ơ�������
    float RHV; //�����ܼ��ȣ����˹����� km
    char  TCloudage[4]; //������
    char  LCloudage[4]; //������
    char  reportCloudage[4]; //�౨����
    int   cloudHeight; //�Ƹ� m,����ĵͣ��У���״�Ƹߣ����˹����룬Ϊ�౨iRiXhVV�е�h������Nh����ʱ�������Ƹ�ֵ����д��2500
    char  cloudForm[25]; //��״
    char  choudCode[4]; //��״���루���룩
    char  currentWeather[3]; //���������������
    char  pastWeatherT[3]; //��ȥ��������ʱ������,����������Ϊ06������������Ϊ03��������������00ʱΪ12���������������ܣ���ʱ��Ϊ06���Ƿ�����(����)��ʱ�Σ��̶��ࡰ//��
    char  pastW1[2]; //��ȥ����1
    char  pastW2[2];
    char  stateOfGround[3];
};

struct SP{ //������Ҫ��������
    float  snowDepth; //��ѩ��� cm,΢��������Ϊ��������΢������ֵΪ888888
    float  snowPressure; //ѩѹ g/(cm*cm)
    int  frozenSoilDepth1Upper; //������ȵ�1������ֵ cm
    int  frozenSoilDepth1Lower; //������ȵ�1������ֵ cm
    int  frozenSoilDepth2Upper; //������ȵ�2������ֵ cm
    int  frozenSoilDepth2Lower; //������ȵ�2������ֵ cm
    char  TornadoDisCode[2]; //�����������վ�������
    char  TornadoDirCode[2]; //�����������վ��λ����
    int  glazeDiameter; //���߻�������ڡ��ֱ��
    int  maxHailDia; //������ֱ��
};

struct QCCode{ //��������������,��9��
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

struct QC{ //���������������װ
    struct QCCode Q1; //̨վ��
    struct QCCode Q2; //ʡ��
    struct QCCode Q3; //���Ҽ�
};

//��������Ҫ�����ݽṹ��
struct AWSData{
    struct BaseInfo baseInfo; //��վ������Ϣ
    struct PP pp; //��ѹ���� hPa
    struct TH th; //�¶Ⱥ�ʪ������ ��
    struct RE re; //�ۼƽ�ˮ������������ mm
    struct WI wi; //��۲����� 1�� m/s
    struct DT dt; //�������� ��
    struct VV vv; //�Զ��۲��ܼ������� m
    struct CW cw; //�˹��۲��ܼ��ȡ��ơ�������
    struct SP sp; //������Ҫ��������
    float  miniteRain[60]; //Сʱ��ÿ���ӽ�ˮ������
    char   MW[256]; //�˹��۲�������������
    struct QC qc; //��������������
};


#pragma pack()
#endif /* DATATYPE_H_ */
