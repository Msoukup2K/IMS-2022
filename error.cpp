/**************************************************
 * FILE: error.cpp
 * 
 * IMS 2022/23 -- 11. Model pomocí celulárního automatu
 *
 * author:   Vojtech Kucera (xkucer0h)
 * date:     2022-12-04
 * 
 * based on my error module from the IJC course
 * 
 *************************************************/

#include "error.h"

#include <cstdio>
#include <cstdarg>
#include <cstdlib>

void warning_msg(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Varování: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
}

void error_exit(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Chyba: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);

    exit(EXIT_FAILURE);
}

/*************************************************
 * END OF FILE: error.cpp
 ************************************************/

