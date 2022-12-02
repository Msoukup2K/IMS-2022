/******************************************
* FILE: probability.cpp
*
* [ProjectName]
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-12-02
*
*******************************************/

#include "probability.h"

#include <random>
#include <ctime>

void probability_init()
{
    std::srand(std::time(nullptr));
}

bool probability(double prob)
{
    return ((1.0f * std::rand()) / RAND_MAX) <= prob;
}

/******************************************
* END OF FILE: probability.cpp
*******************************************/

