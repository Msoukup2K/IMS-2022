/******************************************
* FILE: main.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-16
*
*******************************************/

#include <iostream>

#include "animation.h"
#include "ca.h"


static CA *MODEL = nullptr;

void cleanup()
{
    delete MODEL;
}

int main(int argc, char *argv[])
{
    atexit(cleanup);

    MODEL = new CA{150};
    Animation animation{argc, argv, "IMS 2022/23 -- simulace", MODEL};
    GLIDER_GUN_INIT(MODEL);

    animation.setFreq(200);
    animation.run();
    
    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

