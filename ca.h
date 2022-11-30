/******************************************
* FILE: ca.h
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* author:   Vojtech Kucera (xkucer0h)
* date:     2022-11-29
*
*******************************************/

#ifndef CA_H_
#define CA_H_

#include <ostream>

#define GLIDER_GUN_INIT(ca) do { \
    ca->initCell(30, 50);ca->initCell(31, 50);ca->initCell(30, 51); \
    ca->initCell(31, 51);ca->initCell(40, 50);ca->initCell(40, 51); \
    ca->initCell(40, 52);ca->initCell(41, 49);ca->initCell(41, 53); \
    ca->initCell(42, 48);ca->initCell(42, 54);ca->initCell(43, 48); \
    ca->initCell(43, 54);ca->initCell(44, 51);ca->initCell(45, 49); \
    ca->initCell(45, 53);ca->initCell(46, 50);ca->initCell(46, 51); \
    ca->initCell(46, 52);ca->initCell(47, 51);ca->initCell(50, 50); \
    ca->initCell(50, 49);ca->initCell(50, 48);ca->initCell(51, 50); \
    ca->initCell(51, 49);ca->initCell(51, 48);ca->initCell(52, 47); \
    ca->initCell(52, 51);ca->initCell(54, 47);ca->initCell(54, 46); \
    ca->initCell(54, 51);ca->initCell(54, 52);ca->initCell(64, 49); \
    ca->initCell(64, 48);ca->initCell(65, 48);ca->initCell(65, 49); \
} while (0)

using Cell = unsigned int;

class CA
{
private:
    const unsigned int X; // width of the board
    const unsigned int Y; // height of the board
    Cell **board;
    Cell **board_old;

public:
    unsigned int width() { return X; }
    unsigned int height() { return Y; }
    Cell get(unsigned int x, unsigned int y) { return board[x][y]; }
    
    void initCell(unsigned int x, unsigned int y);
    unsigned int neighbors(unsigned int x, unsigned int y);
    void step();
    void print();

    CA(unsigned int width, unsigned int height);
    ~CA();
};

inline void CA::initCell(unsigned int x, unsigned int y)
{
    board[x][y] = board_old[x][y] = 1;
}

#endif // CA_H_

/******************************************
* END OF FILE: ca.h
*******************************************/

