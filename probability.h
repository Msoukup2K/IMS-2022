/******************************************
* FILE: probability.h
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#ifndef PROBABILITY_H_
#define PROBABILITY_H_

#include <vector>

void probability_init();

double random01();

bool probability(double prob);

std::pair<int, int> random_choice(std::vector<std::pair<int, int>> indices);

#endif // PROBABILITY_H_

/******************************************
* END OF FILE: probability.h
*******************************************/

