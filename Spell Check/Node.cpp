#include "Node.h"
#include <string>
#include <iostream>

Node::Node(char newChar){
    value = toupper(newChar);
    childListHead = NULL;
    childListTail = childListHead;
    nextChild = NULL;
    numChildren = 0;
}

void Node::addChild(Node* newChild){

    if(childListHead == NULL){
        childListHead = newChild;
        childListTail = childListHead;
    }else{
        childListTail->nextChild = newChild;
        childListTail = childListTail->nextChild;
    }
    numChildren++;
}

Node* Node::matchChild(std::string newChar){
    Node* tempChild = NULL;
    if(isalpha(toupper(newChar[0])) == true){
        //only check letters
        tempChild = childListHead;

        while(tempChild != NULL){
            if(newChar[0] == tempChild->value[0]){
                break;
            }
            tempChild = tempChild->nextChild;
        }
    }

    return tempChild;
}
