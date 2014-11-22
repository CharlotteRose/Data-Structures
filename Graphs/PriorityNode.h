#ifndef PRIORITY_NODE
#define PRIORITY_NODE
#include "Node.h"

class PriorityNode{
public:
    PriorityNode(Node*, int, Node*);
    int priority;
    Node* graphNode;
    Node* priorGraphNode;
    PriorityNode* nextNode;
};





#endif // PRIORITY_NODE
