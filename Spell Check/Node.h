#ifndef NODE
#define NODE
#include <string>

class Node{
public:
    Node(char);

    void addChild(Node*);
    Node* matchChild(std::string);
    std::string value;
    Node* childListHead;
    Node* nextChild;
    Node* childListTail;
    int numChildren;
};

#endif // NODE
