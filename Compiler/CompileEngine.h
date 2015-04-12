#include <list>
#include "Token.h"

class CompileEngine{

public:
    CompileEngine();
    ~CompileEngine();

    void recieveTokens(std::list<Token*>*& newTokenList);
    void recursiveParse();

private:
    std::list<Token*>* tokenList;
    std::list<Token*>::iterator curToken;
    std::list<Token*>::iterator nextToken;

    bool noError;

    void advanceToken();
    void getNextToken();
    void outputToken();
    bool checkType();

    void compileClass();
    bool compileClassVarDec();
    bool compileSubroutineDec();
    bool compileType();
    void compileSubBody();
    bool compileVarDec();
    void compileParameterList();

    void compileExpression();
    void compileTerm();
    bool checkTerm();
    bool checkOP();
    void compileSubroutineCall();
    void compileExpressionList();


    void compileStatements();
    bool compileLetStatement();
    bool compileIfStatement();
    bool compileWhileStatement();
    bool compileDoStatement();
    bool compileReturnStatement();

    bool staticOrField();
    bool constructFuncOrMeth();

    Token* currentToken;
    Token* tokenNext;

};
