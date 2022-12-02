/******************************************
* FILE: ca.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-29
*
*******************************************/

#include "ca.h"

#include "probability.h"


CA::CA(unsigned int size) : X{size}
{
    board = new Cell *[X]{};
    board_old = new Cell *[X]{};

    for (unsigned int i = 0; i < X; ++i)
    {
        board[i] = new Cell[X]{Cell::ES};
        board_old[i] = new Cell[X]{Cell::ES};
    }
}

CA::~CA()
{
    for (unsigned int i = 0; i < X; ++i)
    {
        delete[] board[i];
        delete[] board_old[i];
    }

    delete[] board;
    delete[] board_old;
}

void CA::neighbors(unsigned int x, unsigned int y)
{
    neighborhood[0] = board_old[x-1][y-1];
    neighborhood[1] = board_old[x][y-1];
    neighborhood[2] = board_old[x+1][y-1];
    neighborhood[3] = board_old[x+1][y];
    neighborhood[4] = board_old[x+1][y+1];
    neighborhood[5] = board_old[x][y+1];
    neighborhood[6] = board_old[x-1][y+1];
    neighborhood[7] = board_old[x-1][y];
}

void CA::step()
{
    for (unsigned int y = 1; y < X-1; ++y)
    {
        for (unsigned int x = 1; x < X-1; ++x)
        {
            neighbors(x, y);
            switch (get(x, y))
            {
            case Cell::PC:
                rulePC();
                break;

            case Cell::QC:
                ruleQC();
                break;

            case Cell::NeC:
                ruleNeC();
                break;

            case Cell::IC:
                ruleIC();
                break;
            
            default:
                break;
            }
        }
    }

    for (unsigned int y = 1; y < X-1; ++y)
    {
        for (unsigned int x = 1; x < X-1; ++x)
        {
            board_old[x][y] = board[x][y];
        }
    }

    ++time_step;
}

void CA::rulePC()
{
}

void CA::ruleQC()
{
}

void CA::ruleNeC()
{
}

void CA::ruleIC()
{
}

/******************************************
* END OF FILE: ca.cpp
*******************************************/

