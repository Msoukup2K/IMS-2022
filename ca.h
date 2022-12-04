/******************************************
* FILE: ca.h
*
* IMS 2022/23 -- 11. Model pomocí celulárního automatu
*
* authors:   Vojtech Kucera (xkucer0h),
*            Martin Soukup (xsouku15)
*
* date:     2022-12-04
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
        US = 4, // unstable state
        IC = 5, // immune cell
        DC = 6, // dead cell as a result of immune system or therapy
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
    
    // cell count differents
    int nT_diff = 0;
    int nPC_diff = 0;
    int nIC_diff = 0;

    // cell counts
    int nT = 0; // number of tumor cells
    int nPC = 0; // number of PCs
    int nIC = 0; // number of ICs
    int nVic = 0; // number of IC victories over PCs
    int nDef = 0; // number of IC defeats by PCs

    int time_step = 0; // number of the current step

    // constatns:
    const double bp_0 = 0.7; // base probability of division of PC
    const double a_p = 0.42; // base living tumor thickness
    const double b_n = 0.53; // base necrotic thickness
    const double R_max = 37.5; // maximum tumor extent
    const double p_dT = 0.5; // tumor death constant
    const double p_dI = 0.2; // immune death constant
    const double k_PC = 0.8; // PC death rate due to treatment
    const double k_QC = 0.4; // QC death rate due to treatment
    const double k_IC = 0.6; // IC death rate due to treatment
    const double PK = 1.0; // pharmacokinetics

    // calculated every step:
    double R_t{}; // average radius of the tumor, rough approximation (error around 1)
    double W_p{}; // thickness of proliferating cancerous cells
    double R_n{}; // thickness of necrotic cells

    // parameters:
    int age_threshold = 10; // influences how fast PCs change to QCs
    int n_dead = 5; // influences how fast USs change to DCs
    double K_c = 0.0 - R_max / 2.0; // chemotherapy effect on the division
    double gamma_PC = 0.55; // up to 0.95; PC resistance to treatment
    double gamma_QC = 0.0; // up to 0.4; QC resistance to treatment
    double gamma_IC = 0.0; // up to 0.7; IC resistance to treatment
    double p_0 = bp_0; // probability of division of PC

    // turn on cell death due to treatment, not really reflecting reality
    bool treatment_TRIVIAL_IMPLEMENTATION = false;

    // functions calculating certain values:
    double r(int x, int y); // distance from center
    double br(int x, int y); // probability of diviion of PC
    void R_t_calc(); // calculate R_t for the current step (tumor radius)
    void W_p_calc(); // calculate W_p for the current step (prolif. thickness)
    void R_n_calc(); // calculate R_n for the current step (necro. thickness)

    // rules:
    void rulePC(int x, int y);
    void ruleQC(int x, int y);
    void ruleIC(int x, int y);
    void ruleUS(int x, int y);
    void ruleDC(int x, int y);

    // set neighborhood to the neighbors of the cell at (x, y)
    void neighbors(int x, int y);

public:
    int size();
    
    Cell& get(int x, int y);
    Cell& getOld(int x, int y);

    void initCell(int x, int y, Cell::Type type);
    void setCell(int x, int y, Cell::Type type);
    void moveCell(int x0, int y0, int x1, int y1);
    void moveCellToCenter(int x, int y);

    void init();
    void step();

    double upTTCC(); // upper limit of therapy tumor carrying capacity

    // change the age threshold
    bool setCellAgeThreshold(int threshold);
    // change the length of USs' lifespan
    bool setNDead(int ndead);
    // change division probability to reflect therapy effects
    bool setTherapyDivisionProbability(int doses);
    // change tumor carrying capacity to reflect therapy effects
    bool setTherapyTumorCarryingCapacity(int capacity);

    // set resistances; QC and IC only have effect when simulating cell death by treatment
    bool setTherapyResistancePC(double res);
    bool setTherapyResistanceQC(double res);
    bool setTherapyResistanceIC(double res);

    void setTherapyCellDeath();

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
    board[x][y].age = board_old[x][y].age = 0;
    board[x][y].type = board_old[x][y].type = type;
}

inline void CA::setCell(int x, int y, Cell::Type type)
{
    board[x][y].age = 0;
    board[x][y].type = type;
}

inline void CA::moveCell(int x0, int y0, int x1, int y1)
{
    if (get(x1, y1).type == Cell::ES)
    {
        board[x1][y1] = board[x0][y0];
        board[x0][y0] = Cell{};
    }
}

inline double CA::upTTCC()
{
    return R_max / 2.0;
}

#endif // CA_H_

/******************************************
* END OF FILE: ca.h
*******************************************/

