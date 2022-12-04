/******************************************
* FILE: ca.cpp
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
*
*******************************************/

#include "ca.h"

#include <cmath>
#include <utility>
#include <vector>
#include <sstream>
#include <iostream>
#include "probability.h"


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

void CA::moveCellToCenter(int x, int y)
{
    int center = X/2;

    if (x <= center && y <= center)
    {
        moveCell(x, y, x + probability(0.7), y + probability(0.7));
    }
    else if (x <= center && y >= center)
    {
        moveCell(x, y, x + probability(0.7), y - probability(0.7));
    }
    else if (x >= center && y >= center)
    {
        moveCell(x, y, x - probability(0.7), y - probability(0.7));
    }
    else if (x >= center && y <= center)
    {
        moveCell(x, y, x - probability(0.7), y + probability(0.7));
    }
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

void CA::spawn_rate_calc()
{
    spawn_rate = (1.0 * (nVic - nDef) * nPC) / (nT);
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

bool CA::setCellAgeThreshold(int threshold)
{
    if (threshold <= 0)
    {
        return false;
    }
    age_threshold = threshold;
    return true;
}

bool CA::setNDead(int ndead)
{
    if (ndead <= 0)
    {
        return false;
    }
    n_dead = ndead;
    return true;
}

bool CA::setTherapyDivisionProbability(int doses)
{
    if (doses <= 0)
    {
        return false;
    }
    p_0 = (bp_0 * gamma_PC) / pow(doses, 1.0 / n_dead);
    return true;
}

bool CA::setTherapyTumorCarryingCapacity(int capacity)
{
    if (capacity < 0 || capacity > R_max / 2.0)
    {
        return false;
    }
    K_c = capacity - R_max / 2.0;
    return true;
}

bool CA::setTherapyResistancePC(double res)
{
    if (res < 0.0 || res > 0.95)
    {
        return false;
    }
    gamma_PC = res;
    return true;
}

bool CA::setTherapyResistanceQC(double res)
{
    if (res < 0.0 || res > 0.4)
    {
        return false;
    }
    gamma_PC = res;
    return true;
}

bool CA::setTherapyResistanceIC(double res)
{
    if (res < 0.0 || res > 0.7)
    {
        return false;
    }
    gamma_PC = res;
    return true;
}

bool CA::setTherapyCellDeath(int time)
{
    if (time <= 0)
    {
        return false;
    }
    treatment_TRIVIAL_IMPLEMENTATION = true;
    killtime = time;
    return true;
}

void CA::setLog(std::string filename)
{
    log.open(filename);
}

void CA::writeLog()
{
    std::stringstream msg{};

    msg << "časový krok: " << time_step << "\n"
        << "\tpočet buňek nádoru:\t\t" << nT << "\n"
        << "\tpočet P buněk:\t\t\t" << nPC << "\n"
        << "\tpočet I buněk:\t\t\t" << nIC << "\n"
        << "\tpoloměr tumoru:\t\t\t" << R_t << "\n"
        << "\ttloušťka tkáně P buněk:\t\t" << W_p << "\n"
        << "\ttloušťka nekrotické tkáně:\t" << R_n << "\n"
        << "\ttempo přírůstku I buněk:\t" << spawn_rate << "\n"
        << std::endl;
    ;

    if (log.is_open())
    {
        log << msg.str();
    }
    else
    {
        std::cout << msg.str();
    }
}

void CA::init()
{
    initCell(X/2, X/2, Cell::PC);
    ++nPC;
    ++nT;

    for (int y = 1; y < X-1; ++y)
    {
        for (int x = 1; x < X-1; ++x)
        {
            if (probability(0.001))
            {
                initCell(x, y, Cell::IC);
                ++nIC;
            }
        }
    }

    for (int y = X-35; y > X-55; y -= 2)
    {
        for (int x = X-35; x > X-55; x -= 2)
        {
            initCell(x, y, Cell::IC);
            get(x, y).age = -1;
            ++nIC;
        }
    }
    writeLog();
}

void CA::step()
{
    ++time_step;
    R_t_calc();
    W_p_calc();
    R_n_calc();
    spawn_rate_calc();

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
            
            case Cell::US:
                ruleUS(x, y);
                break;

            case Cell::DC:
                ruleDC(x, y);
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
    nIC += nIC_diff;
    nIC_diff = 0;

    writeLog();
}

double CA::simpleDeathProb(Cell::Type type)
{
    double probab{};
    switch (type)
    {
    case Cell::PC:
        probab = 4 / (random01() * gamma_PC);
        break;

    case Cell::QC:
        probab = 8 / (random01() * gamma_QC);
        break;

    case Cell::IC:
        probab = 6 / (random01() * gamma_IC);
        break;
    
    default:
        probab = 0;
        break;
    }

    return probab / (200.0*(time_step - killtime));
}

void CA::rulePC(int x, int y)
{
    if (treatment_TRIVIAL_IMPLEMENTATION
            && killtime < time_step
            && probability(simpleDeathProb(Cell::PC)))
    {
        setCell(x, y, Cell::US);
        --nPC_diff;
        --nT_diff;
        return;
    }

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
    if (treatment_TRIVIAL_IMPLEMENTATION
            && killtime < time_step
            && probability(simpleDeathProb(Cell::QC)))
    {
        setCell(x, y, Cell::US);
        --nT_diff;
        return;
    }

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
    if (treatment_TRIVIAL_IMPLEMENTATION
            && killtime < time_step
            && probability(simpleDeathProb(Cell::IC)))
    {
        setCell(x, y, Cell::US);
        --nIC_diff;
        return;
    }

    std::vector<std::pair<int, int>> indicesPC{};
    std::vector<std::pair<int, int>> indicesES{};
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
            indicesPC.push_back(std::make_pair(x+xo, y+yo));
        }
        if (neighborhood[i].type == Cell::ES)
        {
            indicesES.push_back(std::make_pair(x+xo, y+yo));
        }
    }

    if (!indicesPC.empty())
    {
        std::pair<int, int> idx = random_choice(indicesPC);
        if (probability(p_dT))
        {
            setCell(idx.first, idx.second, Cell::US);
            setCell(x, y, Cell::ES);
            --nPC_diff;
            --nT_diff;
            --nIC_diff;
            ++nVic;
        }
        else if (probability(p_dI))
        {
            setCell(x, y, Cell::ES);
            --nIC_diff;
            ++nDef;
        }
    }
    else if (r(x, y) > R_t && get(x, y).age == -1)
    {
        moveCellToCenter(x, y);
    }
    else if (!indicesES.empty())
    {
        std::pair<int, int> idx = random_choice(indicesES);
        if (get(idx.first, idx.second).type == Cell::ES)
        {
            moveCell(x, y, idx.first, idx.second);
        }

        indicesES.push_back(std::make_pair(x, y));
        idx = random_choice(indicesES);
        if (get(idx.first, idx.second).type == Cell::ES)
        {
            if (probability((spawn_rate * R_t) / (nIC * r(x, y))))
            {
                setCell(idx.first, idx.second, Cell::IC);
                ++nIC_diff;
            }
        }
    }
}

void CA::ruleUS(int x, int y)
{
    if (++get(x, y).age > n_dead)
    {
        setCell(x, y, Cell::DC);
    }
}

void CA::ruleDC(int x, int y)
{
    int cnt = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (neighborhood[i].type == Cell::ES)
        {
            ++cnt;
        }
    }

    if (cnt > 5)
    {
        setCell(x, y, Cell::ES);
    }
}

/******************************************
* END OF FILE: ca.cpp
*******************************************/

