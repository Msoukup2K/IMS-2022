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

#include <cmath>
#include <utility>
#include <vector>
#include "probability.h"

#include <iostream>

CA::CA(int size) : X{size % 2 == 0 ? size+1 : size}
{
    board = new Cell *[X]{};
    board_old = new Cell *[X]{};

    for (int i = 0; i < X; ++i)
    {
        board[i] = new Cell[X]{};
        board_old[i] = new Cell[X]{};
    }
}

CA::~CA()
{
    for (int i = 0; i < X; ++i)
    {
        delete[] board[i];
        delete[] board_old[i];
    }

    delete[] board;
    delete[] board_old;
}

double CA::r(int x, int y)
{
    int center = X/2;
    return sqrt(pow(x-center, 2) + pow(y-center, 2));
}

double CA::br(int x, int y)
{
    return p_0 * ( 1.0 - r(x, y) / (R_max - K_c) );
}

void CA::R_t_calc()
{
    double sum = 0;
    long point_count = 0;
    for (int y = 0; y < X; ++y)
    {
        int x = 0;
        for (; getOld(x, y).type != Cell::PC && x < X/2; ++x)
            ;
        if (getOld(x, y).type == Cell::PC)
        {
            sum += r(x, y);
            ++point_count;

            x = X - 1;
            for (; getOld(x, y).type != Cell::PC && x > X/2; --x)
                ;
            if (getOld(x, y).type == Cell::PC)
            {
                sum += r(x, y);
                ++point_count;
            }
        }
    }
    for (int x = 0; x < X; ++x)
    {
        int y = 0;
        for (; getOld(x, y).type != Cell::PC && y < X/2; ++y)
            ;
        if (getOld(x, y).type == Cell::PC)
        {
            sum += r(x, y);
            ++point_count;
            y = X - 1;
            for (; getOld(x, y).type != Cell::PC && y > X/2; --y)
                ;
            if (getOld(x, y).type == Cell::PC)
            {
                sum += r(x, y);
                ++point_count;
            }
        }
    }

    R_t =  sum / point_count;
}

void CA::W_p_calc()
{
    W_p = a_p * pow(R_t, 2.0/3.0);
}

void CA::R_n_calc()
{
    R_n = R_t - b_n * pow(R_t, 2.0/3.0) - W_p;
}


void CA::neighbors(int x, int y)
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

void CA::init()
{
    initCell(X/2, X/2, Cell::PC);
    ++nPC;
}

void CA::step()
{
    /*
    if (time_step >= 25)
    {
        return;
    }
    */
    ++time_step;
    R_t_calc();
    W_p_calc();
    R_n_calc();

    for (int y = 1; y < X-1; ++y)
    {
        for (int x = 1; x < X-1; ++x)
        {
            neighbors(x, y);
            switch (getOld(x, y).type)
            {
            case Cell::PC:
                rulePC(x, y);
                break;

            case Cell::QC:
                ruleQC(x, y);
                break;

            // ignore necrotic cells, they stay the same

            case Cell::IC:
                ruleIC(x, y);
                break;
            
            default:
                break;
            }
        }
    }

    for (int y = 0; y < X; ++y)
    {
        for (int x = 0; x < X; ++x)
        {
            board_old[x][y] = board[x][y];
        }
    }
    nT += nT_diff;
    nT_diff = 0;
    nPC += nPC_diff;
    nPC_diff = 0;
}

void CA::rulePC(int x, int y)
{
    std::vector<std::pair<int, int>> indices{};
    int xo{};
    int yo{};
    for (int i = 0; i < 8; ++i)
    {
        switch (i)
        {
        case 0:
            xo = -1;
            yo = -1;
            break;
        case 1:
            xo = 0;
            yo = -1;
            break;
        case 2:
            xo = +1;
            yo = -1;
            break;
        case 3:
            xo = +1;
            yo = 0;
            break;
        case 4:
            xo = +1;
            yo = +1;
            break;
        case 5:
            xo = 0;
            yo = +1;
            break;
        case 6:
            xo = -1;
            yo = +1;
            break;
        case 7:
            xo = -1;
            yo = 0;
            break;
        
        default:
            break;
        }

        if (neighborhood[i].type == Cell::ES)
        {
            indices.push_back(std::make_pair(x+xo, y+yo));
        }
    }

    if (!indices.empty() && probability(br(x, y)))
    {
        std::pair<int, int> idx = random_choice(indices);
        setCell(x, y, Cell::PC);
        setCell(idx.first, idx.second, Cell::PC);
        ++nT_diff;
        ++nPC_diff;
    }

    if (++get(x, y).age >= age_threshold && r(x, y) < R_t - W_p)
    {
        setCell(x, y, Cell::QC);
        --nPC_diff;
    }
}

void CA::ruleQC(int x, int y)
{
    double dist = r(x, y);
    if (dist < R_n)
    {
        setCell(x, y, Cell::NeC);
    }
    else if (dist > R_t - W_p)
    {
        setCell(x, y, Cell::PC);
        ++nPC_diff;
    }
}

void CA::ruleIC(int x, int y)
{
    std::vector<std::pair<int, int>> indices{};
    int xo{};
    int yo{};
    for (int i = 0; i < 8; ++i)
    {
        switch (i)
        {
        case 0:
            xo = -1;
            yo = -1;
            break;
        case 1:
            xo = 0;
            yo = -1;
            break;
        case 2:
            xo = +1;
            yo = -1;
            break;
        case 3:
            xo = +1;
            yo = 0;
            break;
        case 4:
            xo = +1;
            yo = +1;
            break;
        case 5:
            xo = 0;
            yo = +1;
            break;
        case 6:
            xo = -1;
            yo = +1;
            break;
        case 7:
            xo = -1;
            yo = 0;
            break;
        
        default:
            break;
        }

        if (neighborhood[i].type == Cell::PC)
        {
            indices.push_back(std::make_pair(x+xo, y+yo));
        }
    }
}

/******************************************
* END OF FILE: ca.cpp
*******************************************/

