#include "Node.h"
#include <string>

Node::Node(char newChar){
    value = toupper(newChar);
    childListHead = NULL;
    childListTail = childListHead;
    nextChild = NULL;
}

void Node::addChild(Node* newChild){

    if(childListHead == NULL){
        childListHead = newChild;
        childListTail = childListHead;
    }else{
        childListTail->nextChild = newChild;
        childListTail = childListTail->nextChild;
    }

}

Node* Node::matchChild(char newChar){
    Node* tempChild = NULL;
    char charToCheck = toupper(newChar);

    if(isalpha(charToCheck) == true){
        //only check letters
        tempChild = childListHead;

        while(tempChild != NULL){
            if(charToCheck == tempChild->value){
                break;
            }
            tempChild = tempChild->nextChild;
        }
    }

    return tempChild;
}
