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
	ca->initCell(30, 20);ca->initCell(31, 20);ca->initCell(30, 21); \
	ca->initCell(31, 21);ca->initCell(40, 20);ca->initCell(40, 21); \
	ca->initCell(40, 22);ca->initCell(41, 19);ca->initCell(41, 23); \
	ca->initCell(42, 18);ca->initCell(42, 24);ca->initCell(43, 18); \
	ca->initCell(43, 24);ca->initCell(44, 21);ca->initCell(45, 19); \
	ca->initCell(45, 23);ca->initCell(46, 20);ca->initCell(46, 21); \
	ca->initCell(46, 22);ca->initCell(47, 21);ca->initCell(50, 20); \
	ca->initCell(50, 19);ca->initCell(50, 18);ca->initCell(51, 20); \
	ca->initCell(51, 19);ca->initCell(51, 18);ca->initCell(52, 17); \
	ca->initCell(52, 21);ca->initCell(54, 17);ca->initCell(54, 16); \
	ca->initCell(54, 21);ca->initCell(54, 22);ca->initCell(64, 19); \
	ca->initCell(64, 18);ca->initCell(65, 18);ca->initCell(65, 19); \
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

