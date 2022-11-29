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


int main(int argc, char *argv[])
{
    Animation animation{argc, argv, "IMS 2022/23 -- simulace"};

    animation.run();

	return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

