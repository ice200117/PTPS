#include "UseFunc.h"

char* subS(char* s, int pos, int Len) {
    static char sp[100] = "";
    int i, j = 0;
    int end = 0;
    strcpy(sp, s);

    if (Len == 0) {
        end = strlen(sp);
    } else {
        end = pos + Len;
    }
    for (i = pos; i < end; i++) {
        sp[j++] = s[i];
    }
    sp[j] = 0;
    return sp;
}

char* getFileName(char* pathFile) {
    int i = 0;
    int flag = 0;
    int len = strlen(pathFile);

    for(i = len; i>0; i--){
        if((pathFile[i-1] == '/') || (pathFile[i-1] == '\\')){
            flag = i;
            break;
        }
    }
    return subS(pathFile, flag, 0);
}
