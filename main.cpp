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
    MODEL->init();

#if 0
    bool sw = true;
    for (int i = 0; i < MODEL->size(); ++i)
    {
        for (int j = 0; j < MODEL->size(); ++j)
        {
            MODEL->initCell(j, i, sw ? Cell::IC : Cell::DC);
            sw = !sw;
        }
    }
#endif
#if 0
    int st = 0;
    for (int j = 0; j < MODEL->size(); j += 3)
        for (int i = 0; i < MODEL->size(); ++i)
        {
            if (st == 0)
            {
                MODEL->initCell(i, j, Cell::PC);
                MODEL->initCell(i, j+1, Cell::PC);
                MODEL->initCell(i, j+2, Cell::PC);
                if (i == 99)
                    st = 1;
            }
            else if (st == 1)
            {
                MODEL->initCell(i, j, Cell::QC);
                MODEL->initCell(i, j+1, Cell::QC);
                MODEL->initCell(i, j+2, Cell::QC);
                if (i == 99)
                    st = 2;
            }
            else if (st == 2)
            {
                MODEL->initCell(i, j, Cell::NeC);
                MODEL->initCell(i, j+1, Cell::NeC);
                MODEL->initCell(i, j+2, Cell::NeC);
                if (i == 99)
                    st = 3;
            }
            else if (st == 3)
            {
                MODEL->initCell(i, j, Cell::IC);
                MODEL->initCell(i, j+1, Cell::IC);
                MODEL->initCell(i, j+2, Cell::IC);
                if (i == MODEL->size()-1)
                    st = 0;
            }
        }
#endif
    Animation animation{argc, argv, "IMS 2022/23 -- simulace", MODEL};
    animation.setFreq(2000);

    animation.run();

    return EXIT_SUCCESS;
}

/******************************************
* END OF FILE: main.cpp
*******************************************/

