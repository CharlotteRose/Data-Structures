#ifndef GAME_BOARD
#define GAME_BOARD
#include <string>
#include <vector>

class GameBoard{
public:
    GameBoard();

    void setup();
    void runGame();
    void printGame();

private:
    bool createBoard();
    void checkGameRules();

    std::vector <Cell*> masterList;

    unsigned int maxWidth;
    unsigned int maxHeight;
};

#endif // GAME_BOARD
