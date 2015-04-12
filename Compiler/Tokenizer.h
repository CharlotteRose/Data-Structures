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

    void getTokens(std::string tokenFile, std::list<Token*>*& tokenList);
    void initializeLists();
    TokenType lookUpKeyword(std::string curToken);
    TokenType lookUpNonID(char firstChar);



private:
    std::list<std::string> keywordList;
    std::list<char> symbolList;

    bool validIDchar(char curChar, ID_RULE idRule);
    void testID();
    void testIDLookup();
    void testNonIDLookup();
};
