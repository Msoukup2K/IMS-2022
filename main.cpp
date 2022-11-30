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


int main(int argc, char *argv[])
{
//    Animation animation{argc, argv, "IMS 2022/23 -- simulace"};

//    animation.run();

	CA *ca = new CA{100, 50};
	GLIDER_GUN_INIT(ca);

	for (int i = 0; i < 100; ++i)
	{
		system("clear");
		ca->print();
		ca->step();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	delete ca;
    
    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

