#ifndef USEFUNC_H_
#define USEFUNC_H_



#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>
#include <stdio.h>

//���ַ��������н�ȡָ��λ��pos��ָ������Len���ַ��������LenΪ0�����ʾ��ȡ�����
char* subS(char* s , int pos , int Len);

//�Ӵ�·�����ļ�������ȡ������·�����ļ���
char* getFileName(char* pathFile);
#ifdef __cplusplus
};
#endif
#endif /* USEFUNC_H_ */
