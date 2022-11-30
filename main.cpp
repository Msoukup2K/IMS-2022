/******************************************
* FILE: main.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-16
*
*******************************************/

#include <thread>
#include <iostream>

#include "animation.h"
#include "ca.h"


static CA *ca = new CA{1000, 500};

void cleanup()
{
    delete ca;
}

int main(int argc, char *argv[])
{
    atexit(cleanup);
    GLIDER_GUN_INIT(ca);

    Animation animation{argc, argv, "IMS 2022/23 -- simulace"};
    animation.setModel(ca);
    animation.setFreq(300);
    animation.run();
    
    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

