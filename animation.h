/******************************************
* FILE: animation.h
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <GL/glut.h>

#include "ca.h"

extern CA *ANIMATION_MODEL;
extern int ANIMATION_FREQUENCY;

class Animation
{
private:
    
public:
    void setDisplayFunc(void (*f)(void));
    void setReshapeFunc(void (*f)(int, int));
    void setIdleFunc(void (*f)(void));
    void run();

    void setFreq(int freq);

    Animation(int argc, char **argv, const char *title, CA *model);
};

inline void Animation::setFreq(int freq)
{
    ANIMATION_FREQUENCY = freq;
}

#endif // ANIMATION_H_

/******************************************
* END OF FILE: animation.h
*******************************************/

