#ifndef CELL
#define CELL
#include <vector>

enum Cell_State{
    DEAD,
    ALIVE
};


class Cell{
public:
    Cell(bool);
    void checkNeighbors();
    void updateCell();
    void addNeighbor(Cell*);

    void testCell();


private:
    Cell_State currentState;
    Cell_State nextState;
    int neighborsAlive();
    int maxNeighbors;
    std::vector <Cell*> neighborList;



};

#endif // CELL
