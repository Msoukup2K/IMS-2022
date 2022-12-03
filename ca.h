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

struct Cell {
    enum Type {
        ES = 0, // empty space or normal cell
        PC = 1, // proliferative tumor cell
        QC = 2, // quiscent cell
        NeC = 3, // necrotic cell
        US = 0, // unstable state
        IC = 4, // immune cell
        DC = 0, // dead cell as a result of immune system or therapy
    };

    int age = 0;
    Type type = ES;
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
    
    // cell counts
    int nT_diff = 0;
    int nPC_diff = 0;

    int nT = 0;
    int nPC = 0;
    int nIC = 0;

    // parameters:
    int time_step = 0;
    int age_threshold = 15;
    double p_0 = 0.7; // base probability of division of PC
    double a_p = 0.22; // base living tumor thickness
    double b_n = 0.53; // base necrotic thickness
    double R_max = 37.5; // maximum tumor extent
    double p_dT = 0.5; // tumor death constant
    double p_dI = 0.2; // immune death constant
    double K_c = 0.0 - R_max / 2.0; // chemotherapy effect on the division
    double R_t; // average radius of the tumor, rough approximation (error around 1)
    double W_p; // thickness of proliferating cancerous cells
    double R_n; // thickness of necrotic cells

    double r(int x, int y); // distance from center
    double br(int x, int y); // probability of diviion of PC
    void R_t_calc(); // calculate R_t for the current step
    void W_p_calc(); // calculate W_p for the current step
    void R_n_calc(); // calculate R_n for the current step

    // rules:
    void rulePC(int x, int y);
    void ruleQC(int x, int y);
    void ruleIC(int x, int y);

    // set neighborhood to the neighbors of the cell at (x, y)
    void neighbors(int x, int y);

public:
    int size();
    
    Cell& get(int x, int y);
    Cell& getOld(int x, int y);

    void initCell(int x, int y, Cell::Type type);
    void setCell(int x, int y, Cell::Type type);

    void init();
    void step();

    explicit CA(int width);
    ~CA();
};

inline int CA::size()
{
    return X;
}

inline Cell& CA::get(int x, int y)
{
    return board[x][y];
}

inline Cell& CA::getOld(int x, int y)
{
    return board_old[x][y];
}

inline void CA::initCell(int x, int y, Cell::Type type)
{
    board[x][y].type = board_old[x][y].type = type;
}

inline void CA::setCell(int x, int y, Cell::Type type)
{
    board[x][y].age = 0;
    board[x][y].type = type;
}

#endif // CA_H_

/******************************************
* END OF FILE: ca.h
*******************************************/

