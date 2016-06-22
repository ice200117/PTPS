#ifndef USEFUNC_H_
#define USEFUNC_H_



#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>
#include <stdio.h>

//从字符串数组中截取指定位置pos，指定长度Len的字符串，如果Len为0，则表示截取到最后
char* subS(char* s , int pos , int Len);

//从带路径到文件名中提取出不带路径到文件名
char* getFileName(char* pathFile);
#ifdef __cplusplus
};
#endif
#endif /* USEFUNC_H_ */
