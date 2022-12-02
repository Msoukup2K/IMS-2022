/******************************************
* FILE: probability.h
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-12-02
*
*******************************************/

#ifndef PROBABILITY_H_
#define PROBABILITY_H_

#include <vector>

void probability_init();

bool probability(double prob);

std::pair<int, int> random_choice(std::vector<std::pair<int, int>> indices);

#endif // PROBABILITY_H_

/******************************************
* END OF FILE: probability.h
*******************************************/

