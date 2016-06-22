#ifndef ALGPACK_H_
#define ALGPACK_H_


#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>

//#include "logSys.h"
#include "ERROR.h"
#include "dataType.h"
#include "UseFunc.h"
#include <ctype.h>
	int readAWS(const char* fileName, struct AWSData** readAWSData);
#ifdef __cplusplus
};
#endif
#endif /* ALGPACK_H_ */
