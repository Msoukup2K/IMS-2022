/**************************************************
 * FILE: error.h
 * 
 * IMS 2022/23 -- 11. Model pomocí celulárního automatu
 *
 * author:   Vojtech Kucera (xkucer0h)
 * date:     2022-12-04
 * 
 * based on my error module from the IJC course
 * 
 *************************************************/

#ifndef ERROR_H_
#define ERROR_H_

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif // ERROR_H_

/*************************************************
 * END OF FILE: error.h
 ************************************************/

