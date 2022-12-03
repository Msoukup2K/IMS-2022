/******************************************
* FILE: main.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#include <iostream>

#include "animation.h"
#include "ca.h"
#include "probability.h"

static CA *MODEL = nullptr;

void cleanup()
{
    delete MODEL;
}

int main(int argc, char *argv[])
{
    atexit(cleanup);
    probability_init();

    MODEL = new CA{180};
    MODEL->init();

    Animation animation{argc, argv, "IMS 2022/23 -- simulace", MODEL};
    animation.setFreq(100);

    animation.run();

    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

