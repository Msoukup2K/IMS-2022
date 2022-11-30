/******************************************
* FILE: animation.h
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-29
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

    void setModel(CA *ca) { ANIMATION_MODEL = ca; }
    void setFreq(int sp) { ANIMATION_FREQUENCY = sp; }

    Animation(int argc, char **argv, const char *title);
};

#endif // ANIMATION_H_

/******************************************
* END OF FILE: animation.h
*******************************************/

