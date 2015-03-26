#include <list>
#include "Token.h"
#include <string>

enum ID_RULE{
    FIRST,
    NOT_FIRST
};

class Tokenizer{
public:
    Tokenizer();

    void getTokens(std::string tokenFile, std::list<Token>*& tokenList);
    void initializeLists();

private:
    std::list<std::string> keywordList;
    std::list<char> symbolList;

};
