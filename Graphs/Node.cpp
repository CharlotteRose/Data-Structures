#include "Node.h"
#include <iostream>

Node::Node(char newValue){

    isVisited = false;
    letter = newValue;
}

void Node::addAdjacent(Node* adjacentNode){

    adjacentList.push_back(adjacentNode);
}


void Node::removeAdjacent(Node* adjacentNode){
    int i = 0; //counter
    for(it = adjacentList.begin(); it < adjacentList.end(); it++, i++){
        if(adjacentNode->letter == adjacentList[i]->letter){
            adjacentList.erase(it);
        }
    }
}

void Node::printNode(){
    std::cout << std::endl << letter << " - ";
    int i = 0;
    for(it = adjacentList.begin(); it < adjacentList.end(); it++, i++){
        std::cout << adjacentList[i]->letter << " ";
    }
    std::cout << std::endl;

}
