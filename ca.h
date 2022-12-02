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

enum Cell {
    ES = 0, // empty space
    NoC = 0, // normal cell
    PC = 112, // proliferative tumor cell
    QC = 211, // quiscent cell
    NeC = 90, // necrotic cell
    US = 0, // unstable state
    IC = 255, // immune cell
    DC = 0, // dead cell as a result of immune system or therapy
};

class CA
{
private:
    const unsigned int X; // the board is of size X*X
    Cell **board;
    Cell **board_old;
    Cell neighborhood[8]; // the neighborhood of the current cell
    /*
        indexing of neighborhood (C = current):
        0  1  2
        7  C  3
        6  5  4
    */

    // parameters:
    unsigned int time_step = 0;
    double p_0 = 0.7;
    double a_p = 0.42;
    double b_n = 0.53;
    double R_max = 37.5;
    double p_dT = 0.5;
    double p_dI = 0.2;

    // private methods:
    void neighbors(unsigned int x, unsigned int y);

    void rulePC();
    void ruleQC();
    void ruleNeC();
    void ruleIC();

public:
    unsigned int size();
    
    Cell get(unsigned int x, unsigned int y);
    float getColor(unsigned int x, unsigned int y);
    void initCell(unsigned int x, unsigned int y, Cell cell);
    void setCell(unsigned int x, unsigned int y, Cell cell);

    void step();

    explicit CA(unsigned int width);
    ~CA();
};

inline unsigned int CA::size()
{
    return X;
}

inline Cell CA::get(unsigned int x, unsigned int y)
{
    return board[x][y];
}

inline float CA::getColor(unsigned int x, unsigned int y)
{
    return get(x, y) / 255.0f;
}

inline void CA::initCell(unsigned int x, unsigned int y, Cell cell)
{
    board[x][y] = board_old[x][y] = cell;
}

inline void CA::setCell(unsigned int x, unsigned int y, Cell cell)
{
    board[x][y] = cell;
}

#endif // CA_H_

/******************************************
* END OF FILE: ca.h
*******************************************/

