#ifndef NODE
#define NODE
#include <string>
#include <vector>

class Node{
public:
    Node(char);

    void addChild(Node*);
    Node* matchChild(char);
    std::string value;
    Node* childListHead;
    Node* nextChild;
    Node* childListTail;
};

#endif // NODE
