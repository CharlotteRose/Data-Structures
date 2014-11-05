#include "Node.h"

Node::Node(char newValue){

    isVisited = false;
    letter = newValue;
}

void Node::addAdjacent(Node* adjacentNode){

    //could check for duplicate nodes here and prevent them from being added
    //however, that may cause more overhead than just doing a depth/breadth search
    //and checking the flag

    adjacentList.push_back(adjacentNode);
}
