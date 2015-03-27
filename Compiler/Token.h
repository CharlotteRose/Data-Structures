#ifndef TOKEN
#define TOKEN

#include <string>

enum TokenType{
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST,
    ERROR
};

class Token{
public:
    Token();

    TokenType tokenType;
    std::string keyword;
    char symbol;
    std::string identifier;
    int intVal;
    std::string stringVal;
};

#endif // TOKEN
