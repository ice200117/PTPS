/**
 *          @file:  global_def.hpp
 *         @brief:  
 *        @author:  liu bin , ice200117@126.com
 *          @date:  2014年04月14日 10时38分11秒
 *       @version:  none
 *          @note:  
 */
#ifndef  GLOBAL_DEF_HPP
#define  GLOBAL_DEF_HPP

#include  <stdio.h>

inline void debug_printf(const char* file,
        int line, 
        const char* function, 
        const char* fmt,
        ...)
{
    
    va_list ap;
    va_start(ap, fmt);
    char buf[1024*8] = {};
    vsnprintf(buf, 1024*8, fmt, ap);
  
    va_end(ap);
    fprintf(stderr, "[%s][%s +%d] %s\n", function, file, line, buf);
    fflush(stderr);
}

#define idebug(fmt, ...)            \
    debug_printf(__FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__);
    //fprintf(stderr, fmt, __VA_ARGS__);

#endif   /* ----- #ifndef GLOBAL_DEF_HPP  ----- */

