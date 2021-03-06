#include <fstream>
#include <string>
#include "CompileEngine.h"
#include "Tokenizer.h"
#include "Token.h"
#include <List>

class Compiler{
public:
    Compiler();
    void compileFile(std::string);

private:
    std::string stripFile(std::string); //pre pass to remove comments and whitespace

    Tokenizer tokenizer; //makes tokens then adds to list for parser to parse
    CompileEngine compileEngine;

    std::list<Token*>* tokenList;
};
