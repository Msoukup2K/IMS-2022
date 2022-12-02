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
    const int X; // the board is of size X*X
    Cell **board;
    Cell **board_old;
    Cell neighborhood[8]; // the neighborhood of the current cell
    /*
        indexing of neighborhood (C = current):
        6  5  4
        7  C  3
        0  1  2

        from bottom left corner -- corresponding to visualization in the animation
    */

    // parameters:
    int time_step = 0;
    double p_0 = 0.7; // base probability of division of PC
    double a_p = 0.42; // base necrotic thickness
    double b_n = 0.53; // base living tumor thickness
    double R_max = 37.5; // maximum tumor extent
    double p_dT = 0.5; // tumor death constant
    double p_dI = 0.2; // immune death constant
    double K_c = 0.0 - R_max / 2.0; // chemotherapy effect on the division

    double r(int x, int y); // distance from center
    double br(int x, int y); // probability of diviion of PC
    double R_t(); // average radius of the tumor
    double W_p(); // thickness of proliferating cancerous cells

    // rules:
    void rulePC(int x, int y);
    void ruleQC(int x, int y);
    void ruleNeC(int x, int y);
    void ruleIC(int x, int y);

    // set neighborhood to the neighbors of the cell at (x, y)
    void neighbors(int x, int y);

public:
    int size();
    
    Cell get(int x, int y);
    Cell getOld(int x, int y);
    float getColor(int x, int y);

    void initCell(int x, int y, Cell cell);
    void setCell(int x, int y, Cell cell);

    void init();
    void step();

    explicit CA(int width);
    ~CA();
};

inline int CA::size()
{
    return X;
}

inline Cell CA::get(int x, int y)
{
    return board[x][y];
}

inline Cell CA::getOld(int x, int y)
{
    return board_old[x][y];
}

inline float CA::getColor(int x, int y)
{
    return get(x, y) / 255.0f;
}

inline void CA::initCell(int x, int y, Cell cell)
{
    board[x][y] = board_old[x][y] = cell;
}

inline void CA::setCell(int x, int y, Cell cell)
{
    board[x][y] = cell;
}

#endif // CA_H_

/******************************************
* END OF FILE: ca.h
*******************************************/

