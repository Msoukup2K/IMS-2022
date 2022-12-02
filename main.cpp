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

    MODEL = new CA{100};
#if 1
    int st = 0;
    for (int j = 0; j < 100; j += 3)
        for (int i = 0; i < 100; ++i)
        {
            if (st == 0)
            {
                MODEL->setCell(i, j, Cell::PC);
                MODEL->setCell(i, j+1, Cell::PC);
                MODEL->setCell(i, j+2, Cell::PC);
                if (i == 99)
                    st = 1;
            }
            else if (st == 1)
            {
                MODEL->setCell(i, j, Cell::QC);
                MODEL->setCell(i, j+1, Cell::QC);
                MODEL->setCell(i, j+2, Cell::QC);
                if (i == 99)
                    st = 2;
            }
            else if (st == 2)
            {
                MODEL->setCell(i, j, Cell::NC);
                MODEL->setCell(i, j+1, Cell::NC);
                MODEL->setCell(i, j+2, Cell::NC);
                if (i == 99)
                    st = 3;
            }
            else if (st == 3)
            {
                MODEL->setCell(i, j, Cell::IC);
                MODEL->setCell(i, j+1, Cell::IC);
                MODEL->setCell(i, j+2, Cell::IC);
                if (i == 99)
                    st = 0;
            }
        }
#endif
    Animation animation{argc, argv, "IMS 2022/23 -- simulace", MODEL};

    animation.setFreq(50);
    animation.run();

    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

