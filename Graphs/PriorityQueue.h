#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include "PriorityNode.h"
#include "Node.h"

class PriorityQueue{
public:
    PriorityQueue();
    Node* front();
    int frontPriority();

    Node* frontPriorNode();
    void push(Node*, int, Node*);
    void pop();
    void sort();

    void printQueue();
    bool isEmpty();


private:
    PriorityNode* head;
    int numberOfNodes;

};



#endif // PRIORITY_QUEUE
