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
extern double ANIMATION_PERIOD1000;

class Animation
{
private:
    
public:
    void run();
    void setFreq(double freq);

    Animation(int argc, char **argv, const char *title, CA *model);
};

inline void Animation::run()
{
    glutMainLoop();
}

inline void Animation::setFreq(double freq)
{
    ANIMATION_PERIOD1000 = 1000.0 / freq;
}

#endif // ANIMATION_H_

/******************************************
* END OF FILE: animation.h
*******************************************/

