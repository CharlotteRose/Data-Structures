#include <vector>
#include <iostream>

GameBoard::GameBoard(){
    setup();
}

void GameBoard::setup();

void GameBoard::runGame(){
    std::vector <Cell*> iterator it;
    int i = 0;

    for(it = masterList.begin(); it < masterList.end(); it++, i++){
        masterList[i]->checkNeighbors();
    }

    i = 0;

    for(it = masterList.begin(); it < masterList.end(); it++, i++){
        masterList[i]->updateCell();
    }




}
void GameBoard::printGame();

bool GameBoard::createBoard();
void GameBoard::checkGameRules();
