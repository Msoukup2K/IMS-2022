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

#include <iostream>

CA::CA(unsigned int width, unsigned int height) :
    X{width}, Y{height}
{
    board = new Cell *[X];
    board_old = new Cell *[X];

    for (unsigned int i = 0; i < X; ++i)
    {
        board[i] = new Cell[Y]{};
        board_old[i] = new Cell[Y]{};
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

unsigned int CA::neighbors(unsigned int x, unsigned int y)
{
    return board_old[x-1][y-1] + board_old[x][y-1] + board_old[x+1][y-1]
        +  board_old[x-1][y]   +                     board_old[x+1][y]
        +  board_old[x-1][y+1] + board_old[x][y+1] + board_old[x+1][y+1];
}

void CA::step()
{
    for (unsigned int y = 1; y < Y-1; ++y)
    {
        for (unsigned int x = 1; x < X-1; ++x)
        {
            int neighbour = neighbors(x, y);
            if (board[x][y] && (neighbour == 2 || neighbour == 3))
            {
            }
            else if (!board[x][y] && neighbour == 3)
            {
                board[x][y] = 1;
            }
            else
            {
                board[x][y] = 0;
            }
        }
    }

    for (unsigned int y = 1; y < Y-1; ++y)
    {
        for (unsigned int x = 1; x < X-1; ++x)
        {
            board_old[x][y] = board[x][y];
        }
    }
}

void CA::print()
{
    for (unsigned int y = 1; y < Y-1; ++y)
    {
        for (unsigned int x = 1; x < X-1; ++x)
        {
            std::cout << (board[x][y] ? '$' : '.');
        }
        std::cout << std::endl;
    }
}


/******************************************
* END OF FILE: ca.cpp
*******************************************/

