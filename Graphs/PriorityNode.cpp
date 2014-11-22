#include "PriorityNode.h"
#include <stdlib.h>

PriorityNode::PriorityNode(Node* newGraphNode, int newPriority, Node* newPriorGraphNode){
    graphNode = newGraphNode;
    priority = newPriority;
    nextNode = NULL;
    priorGraphNode = newPriorGraphNode;

}
