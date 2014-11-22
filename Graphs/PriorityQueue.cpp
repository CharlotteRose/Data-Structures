#include "PriorityQueue.h"
#include <stdlib.h>
#include <iostream>

PriorityQueue::PriorityQueue(){
    head = NULL;
    numberOfNodes = 0;
}

Node* PriorityQueue::front(){
    //std::cout << "Popping " << head->graphNode->letter << std::endl;
    return head->graphNode;
}

int PriorityQueue::frontPriority(){

    //std::cout << "Popping " << head->priority << std::endl;
    return head->priority;
}

Node* PriorityQueue::frontPriorNode(){

    return head->priorGraphNode;
}

void PriorityQueue::printQueue(){
    PriorityNode* temp = head;

    while(temp != NULL){
        //std::cout << "Node is " << temp->graphNode->letter << " -> " <<temp->priorGraphNode->letter << std::endl;

        temp = temp->nextNode;
    }

}


void PriorityQueue::push(Node* graphNode, int newPriority, Node* priorNode){

    //std::cout << "Pushing " << graphNode->letter << newPriority << "  prior is "
    //          << priorNode->letter << std::endl;
    PriorityNode* placeholder = new PriorityNode(graphNode, newPriority, priorNode);
    PriorityNode* temp = head;

    numberOfNodes++;

    //std::cout << std::endl << std::endl;
    if(head == NULL){
        head = placeholder;
        placeholder = NULL;
    }else{
        if(placeholder->priority < head->priority){
            placeholder->nextNode = head;
            head = placeholder;
            placeholder = NULL;
            temp = NULL;
            //std::cout << "NEW HEAD is " << head->graphNode->letter << head->priority << std::endl;
        }else{
            while(temp->nextNode != NULL){
                if(placeholder->priority < temp->nextNode->priority){
                    placeholder->nextNode = temp->nextNode;
                    temp->nextNode = placeholder;
                    break;
                }

                temp = temp->nextNode;
            }

            if(temp->nextNode == NULL){
                temp->nextNode = placeholder;
                placeholder = NULL;
                temp = NULL;
            }
        }

    }
}

void PriorityQueue::pop(){
    PriorityNode* temp;

    if(head != NULL){
        temp = head;
        head = head->nextNode;
        delete temp;
        temp = NULL;
        numberOfNodes--;
    }
}

bool PriorityQueue::isEmpty(){
    if(numberOfNodes == 0){
        return true;
    }
    return false;
}
