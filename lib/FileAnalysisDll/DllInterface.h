#ifndef DLLINTERFACE_H
#define DLLINTERFACE_H

//#include<windows.h>*/

#include <string.h> //c

#include  <QtCore/qglobal.h>

#ifdef COMMON_LIB
# define COMMON_EXPORT Q_DECL_EXPORT
#else
# define COMMON_EXPORT Q_DECL_IMPORT
#endif

using namespace std;

extern "C" {

//bool __declspec(dllexport) execArge( char * iniFileName, char * readADataPath );
//bool COMMON_EXPORT execArge( char * iniFileName, char * readADataPath );
//char* COMMON_EXPORT execArge( char * iniFileName, char * readADataPath );
int COMMON_EXPORT execArge( char * iniFileName, char * readADataPath );

};

#endif
