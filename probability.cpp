/******************************************
* FILE: probability.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#include "probability.h"

#include <random>
#include <ctime>

void probability_init()
{
    std::srand(std::time(nullptr));
}

double random01()
{
    return (1.0f * std::rand()) / RAND_MAX;
}

bool probability(double prob)
{
    if (prob <= 0.0f)
    {
        return false;
    }
    return random01() <= prob;
}

std::pair<int, int> random_choice(std::vector<std::pair<int, int>> indices)
{
    return indices.at(std::rand() % indices.size());
}

/******************************************
* END OF FILE: probability.cpp
*******************************************/

