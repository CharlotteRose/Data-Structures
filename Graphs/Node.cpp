#include "Node.h"
#include <iostream>

Node::Node(char newValue){

    isVisited = false;
    infTimeCheck = false;
    letter = newValue;
    nodeNumber = 0;
    pathSum = 0;
    infPathSum = 0;
    priorNode = NULL;
    infPriorNode = NULL;
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
    std::cout << std::endl << letter << " " << " - ";
    int i = 0;
    for(it = adjacentList.begin(); it < adjacentList.end(); it++, i++){
        std::cout << adjacentList[i]->letter << weight[i] << " ";
    }
    std::cout << std::endl;

}
