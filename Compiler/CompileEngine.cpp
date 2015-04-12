#include "CompileEngine.h"
#include <iterator>
#include <iostream>

CompileEngine::CompileEngine(){
}



void CompileEngine::recieveTokens(std::list<Token*>*& newTokenList){
    //grabs the tokens and sets the current token iterator to the beginning
    this->tokenList = newTokenList;
    curToken = tokenList->begin();

    noError = true;
    currentToken = *curToken;
    compileClass();
}


CompileEngine::~CompileEngine(){
    tokenList = NULL;
}


void CompileEngine::compileClass(){
    bool loopCompile = true;

    if(noError){
        //first verify that the token is a keyword
        if(currentToken->tokenType == KEYWORD){
            std::cout << "<CLASS>" << std::endl;
            outputToken();
            if(currentToken->tokenType == IDENTIFIER){
                outputToken();
                if(currentToken->tokenType == SYMBOL){
                    if(currentToken->symbol == '{'){
                        outputToken();


                        while(loopCompile == true){
                            loopCompile = compileClassVarDec();
                        }

                        loopCompile = true;
                        while(loopCompile == true){
                            loopCompile = compileSubroutineDec();
                        }

                        if(currentToken->tokenType == SYMBOL){
                            if(currentToken->symbol == '}'){
                                outputToken();
                                std::cout << "</CLASS>" << std::endl;
                            }else{
                               std::cout << "ERROR: EXPECTED } symbol" << std::endl;
                            }

                        }else{
                           std::cout << "ERROR: EXPECTED symbol" << std::endl;
                        }
                    }else{
                       std::cout << "ERROR: EXPECTED { symbol" << std::endl;
                    }

                }else{
                  std::cout << "ERROR: EXPECTED symbol" << std::endl;
                }

            }else{
               noError = false;
               std::cout << "ERROR: EXPECTED class name" << std::endl;
            }


        }else{
            noError = false;
            std::cout << "ERROR: EXPECTED class keyword" << std::endl;
        }
    }
}

void CompileEngine::advanceToken(){
    if(curToken != tokenList->end()){
        this->curToken++;
        currentToken = *curToken;
    }
}

void CompileEngine::getNextToken(){
    nextToken = curToken;
    std::advance(nextToken, 1);
    tokenNext = *nextToken;
}

void CompileEngine::outputToken(){
    if(currentToken->tokenType == KEYWORD){
        std::cout << "<KEYWORD>" << currentToken->keyword << "</KEYWORD>" << std::endl;
    }

    if(currentToken->tokenType == SYMBOL){
        std::cout << "<SYMBOL>" << currentToken->symbol << "</SYMBOL>" << std::endl;
    }

    if(currentToken->tokenType == IDENTIFIER){
        std::cout << "<IDENTIFIER>" << currentToken->identifier << "</IDENTIFIER>" << std::endl;
    }

    if(currentToken->tokenType == INT_CONST){
        std::cout << "<INT_CONST>" << currentToken->intVal << "</INT_CONST>" << std::endl;
    }

    if(currentToken->tokenType == STRING_CONST){
        std::cout << "<STRING_CONST>" << currentToken->stringVal << "</STRING_CONST>" << std::endl;
    }

    advanceToken();
}


bool CompileEngine::compileClassVarDec(){
    if(noError){

        if(staticOrField()){
            std::cout << "<CLASS_VAR_DEC>" << std::endl;
            outputToken();
            compileType();
            if(currentToken->tokenType == IDENTIFIER){
                outputToken();

                //check if there is a comma for more variable declarations
                bool moreVars = false;
                if(currentToken->tokenType == SYMBOL){
                    if(currentToken->symbol == ','){
                        moreVars = true;
                    }
                }

                //if so, check syntax

                while(moreVars){
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ','){
                            outputToken();
                            if(currentToken->tokenType == IDENTIFIER){
                                outputToken();
                                if(currentToken->tokenType == SYMBOL){
                                    if(currentToken->symbol == ','){
                                        moreVars = true;
                                    }else{
                                        moreVars = false;
                                    }
                                }else{
                                    noError = true;
                                    std::cout << "ERROR: EXPECTED , or ; symbol" << std::endl;
                                }


                            }else{
                              noError = true;
                              std::cout << "ERROR: EXPECTED variable name" << std::endl;
                            }


                        }else{
                            noError = false;
                            std::cout << "ERROR: INVALID symbol for multiple variables" << std::endl;
                        }
                    }

                    //check for semicolon
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ';'){
                            outputToken();
                            std::cout << "</CLASS_VAR_DEC>" << std::endl;
                        }else{
                            noError = false;
                            std::cout << "ERROR: EXPECTED ;" << std::endl;
                        }
                    }else{
                        noError = false;
                        std::cout << "ERROR: EXPECTED ;" << std::endl;
                    }

                }




            }else{
                std::cout << "ERROR: EXPECTED variable name" << std::endl;
            }


        }
    }
    return false;
}

bool CompileEngine::compileSubroutineDec(){
    if(noError){
        if(constructFuncOrMeth()){
            std::cout << "<SUBROUTINE_DEC>" << std::endl;
            outputToken();
            if(currentToken->tokenType == KEYWORD){
                if(currentToken->keyword == "void"){
                    outputToken();
                }else{
                    compileType();
                }
            }else if (currentToken->tokenType == IDENTIFIER){
                compileType();
            }

            if(noError){
                //either void or a valid type was discovered
                if(currentToken->tokenType == IDENTIFIER){
                    outputToken();
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == '('){
                            outputToken();
                            compileParameterList();

                            if(currentToken->tokenType == SYMBOL){
                                if(currentToken->symbol == ')'){
                                    outputToken();
                                    compileSubBody();

                                }else{
                                    std::cout << "ERROR: EXPECTED ( symbol" << std::endl;
                                }
                            }else{
                              std::cout << "ERROR: EXPECTED ) symbol" << std::endl;
                            }

                        }else{
                           std::cout << "ERROR: EXPECTED ( symbol" << std::endl;
                        }
                    }else{
                        noError = false;
                        std::cout << "ERROR: EXPECTED ( symbol" << std::endl;
                    }


                }else{
                    noError = false;
                    std::cout << "ERROR: EXPECTED subroutine name" << std::endl;
                }
            }

        }
    }

    return false;
}

bool CompileEngine::staticOrField(){
    if(currentToken->tokenType == KEYWORD){
        if(currentToken->keyword == "static"){
            return true;
        }

        if(currentToken->keyword == "field"){
            return true;
        }
        return false;
    }else{
        noError = false;
        std::cout << "ERROR: EXPECTED keyword" << std::endl;
        return false;
    }
}

bool CompileEngine::checkType(){
    if(currentToken->tokenType == KEYWORD){
        if(currentToken->keyword == "int" ||
           currentToken->keyword == "char" ||
           currentToken->keyword == "boolean"){
            return true;
        }//end if
    }else if(currentToken->tokenType == IDENTIFIER){
        return true;
    }else{
        return false;
    }
}


void CompileEngine::compileParameterList(){
    if(noError){
        //first we need to see if we have zero or one parameter lists

        bool isAList = checkType();

        if(isAList == true){
            std::cout << "<PARAMETER_LIST>" << std::endl;
            compileType();
            if(noError){
                if(currentToken->tokenType == IDENTIFIER){
                    outputToken();

                    //check that the next token is a comma
                    bool moreVars = false;
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ','){
                            moreVars = true;
                        }
                    }

                    //if so, check syntax

                    while(moreVars){
                        if(currentToken->tokenType == SYMBOL){
                            if(currentToken->symbol == ','){
                                outputToken();
                                compileType();
                                if(noError){
                                    if(currentToken->tokenType == IDENTIFIER){
                                        outputToken();
                                        if(currentToken->tokenType == SYMBOL){
                                            if(currentToken->symbol == ','){
                                                moreVars = true;
                                            }else{
                                                moreVars = false;
                                            }
                                        }else{
                                            noError = true;
                                            std::cout << "ERROR: EXPECTED , or ; symbol" << std::endl;
                                        }
                                    }else{
                                      noError = true;
                                      std::cout << "ERROR: EXPECTED variable name" << std::endl;
                                      moreVars = false;
                                    }
                                }
                            }else{
                                noError = false;
                                std::cout << "ERROR: INVALID symbol for multiple variables" << std::endl;
                            }
                        }
                    }//end while
                    std::cout << "</PARAMETER_LIST>" << std::endl << std::endl;

                }else{
                  std::cout << "ERROR: EXPECTED variable name in declaration" << std::endl;
                }//end else


            }//end error check
        }//end list check
    }//end error check
}//end function

void CompileEngine::compileSubBody(){
    if(noError){
        if(currentToken->tokenType == SYMBOL){
            if(currentToken->symbol == '{'){
                outputToken();
                bool checkAgain = compileVarDec();
                while(checkAgain){
                    checkAgain = compileVarDec();
                }

                if(noError){
                    compileStatements();
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == '}'){
                            outputToken();
                            std::cout << "</SUBROUTINE_DEC>" << std::endl << std::endl;
                        }else{
                            noError = false;
                            std::cout << "ERROR: EXPECTED } in sub body" << std::endl;
                        }
                    }else{
                        noError = false;
                        std::cout << "ERROR: EXPECTED } in sub body" << std::endl;
                    }
                }
            }else{
                noError = false;
                std::cout << "ERROR: EXPECTED { in sub body" << std::endl;
            }

        }else{
            noError = false;
            std::cout << "ERROR: EXPECTED { in sub body" << std::endl;
        }
    }
}

bool CompileEngine::compileVarDec(){
    if(noError){
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "var"){
                std::cout << "<VAR_DEC>" << std::endl;
                outputToken();
                compileType();
                if(currentToken->tokenType == IDENTIFIER){
                    outputToken();
                    if(noError){
                        bool moreVars = false;
                        if(currentToken->tokenType == SYMBOL){
                            if(currentToken->symbol == ','){
                                moreVars = true;
                            }

                        }


                        //if so, check syntax

                        while(moreVars){
                            if(currentToken->tokenType == SYMBOL){
                                if(currentToken->symbol == ','){
                                    outputToken();
                                    if(currentToken->tokenType == IDENTIFIER){
                                        outputToken();
                                        if(currentToken->tokenType == SYMBOL){
                                            if(currentToken->symbol == ','){
                                                moreVars = true;
                                            }else{
                                                moreVars = false;
                                            }
                                        }else{
                                            noError = true;
                                            std::cout << "ERROR: EXPECTED , or ; symbol" << std::endl;
                                        }


                                    }else{
                                      noError = true;
                                      std::cout << "ERROR: EXPECTED variable name" << std::endl;
                                    }


                                }else{
                                    noError = false;
                                    std::cout << "ERROR: INVALID symbol for multiple variables" << std::endl;
                                }
                            }
                        }

                            //check for semicolon
                            if(currentToken->tokenType == SYMBOL){
                                if(currentToken->symbol == ';'){
                                    outputToken();
                                    std::cout << "</VAR_DEC>" << std::endl;
                                }else{
                                    noError = false;
                                    std::cout << "ERROR: EXPECTED ;" << std::endl;
                                }
                            }else{
                                noError = false;
                                std::cout << "ERROR: EXPECTED ;" << std::endl;
                            }

                    }
                }else{
                  noError = false;
                  std::cout << "ERROR: EXPECTED variable name but no identifier was found" << std::endl;
                }

            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool CompileEngine::compileLetStatement(){
    if(noError){
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "let"){
                std::cout << "<LET_STATEMENT>" << std::endl;
                outputToken();
                if(currentToken->tokenType == IDENTIFIER){
                    outputToken();

                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == '['){
                            outputToken();
                            if(noError){
                                compileExpression();
                                if(currentToken->tokenType == SYMBOL){
                                    if(currentToken->symbol == ']'){
                                        outputToken();
                                    }else{
                                        noError = false;
                                        std::cout << "ERROR in let optional syntax" << std::endl;
                                        return true;
                                    }
                                }else{
                                    noError = false;
                                    std::cout << "ERROR in let syntax" << std::endl;
                                    return true;
                                }
                            }else{
                                noError = false;
                                std::cout << "ERROR in let syntax" << std::endl;
                                return true;
                            }
                        }

                        if(currentToken->symbol == '='){
                            outputToken();
                            if(noError){
                                compileExpression();

                                if(currentToken->tokenType == SYMBOL){
                                    if(currentToken->symbol == ';'){
                                        outputToken();
                                        std::cout << "</LET_STATEMENT>" << std::endl << std::endl;
                                    }else{
                                        noError = false;
                                        std::cout << "ERROR in let ; syntax" << std::endl;
                                        return true;
                                    }
                                }else{
                                    noError = false;
                                    std::cout << "ERROR in let symbol syntax" << std::endl;
                                    return true;
                                }
                            }else{
                                noError = false;
                                std::cout << "ERROR in let syntax" << std::endl;
                                return true;
                            }
                        }else{
                            noError = false;
                            std::cout << "ERROR in let syntax" << std::endl;
                            return true;
                        }
                    }else{
                        noError = false;
                        std::cout << "ERROR in let syntax" << std::endl;
                        return true;
                    }

                }else{
                    noError = false;
                    std::cout << "ERROR in let syntax" << std::endl;
                    return true;
                }


            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool CompileEngine::compileIfStatement(){
    if(noError){
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "if"){
                std::cout << "<IF_STATEMENT>" << std::endl;
                outputToken();
                if(currentToken->tokenType == SYMBOL){
                    if(currentToken->symbol == '('){
                        outputToken();
                        compileExpression();
                        if(noError){
                            if(currentToken->tokenType == SYMBOL){
                                if(currentToken->symbol == ')'){
                                    outputToken();
                                    if(currentToken->tokenType == SYMBOL){
                                    if(currentToken->symbol == '{'){
                                        outputToken();
                                        compileStatements();
                                        if(noError){
                                            if(currentToken->tokenType == SYMBOL){
                                            if(currentToken->symbol == '}'){
                                                outputToken();

                                                //else statement code goes here
                                                if(currentToken->tokenType == KEYWORD){
                                                    if(currentToken->keyword == "else"){
                                                    outputToken();
                                                    if(currentToken->tokenType == SYMBOL){
                                                    if(currentToken->symbol == '{'){
                                                        outputToken();
                                                        compileStatements();
                                                        if(noError){
                                                        if(currentToken->tokenType == SYMBOL){
                                                        if(currentToken->symbol == '}'){
                                                        outputToken();
                                                        std::cout << "</IF_STATEMENT>" << std::endl << std::endl;
                                                        return true;

                                                        }else{
                                                        noError = false;
                                                        std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                                        return true;
                                                        }

                                                        }else{
                                                        noError = false;
                                                        std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                                        return true;
                                                        }

                                                        }else{
                                                            noError = false;
                                                            std::cout << "ERROR IN else SYNTAX (" << std::endl;
                                                            return true;
                                                        }


                                                    }else{
                                                    noError = false;
                                                    std::cout << "ERROR IN else SYNTAX (" << std::endl;
                                                    return true;
                                                    }


                                                    }else{
                                                    noError = false;
                                                    std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                                    return true;
                                                    }


                                                    }else{
                                                        std::cout << "</IF_STATEMENT>" << std::endl << std::endl;
                                                        return true;
                                                    }
                                                }
                                                std::cout << "</IF_STATEMENT>" << std::endl << std::endl;
                                                return true;
                                            }else{
                                                noError = false;
                                                std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                                return true;
                                            }
                                            }else{
                                                noError = false;
                                                std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                                return true;
                                            }
                                        }else{
                                            noError = false;
                                            std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                            return true;
                                        }

                                    }else{
                                        noError = false;
                                        std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                        return true;
                                    }

                                    }
                                    else{
                                        noError = false;
                                        std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                        return true;
                                    }

                                }else{
                                    noError = false;
                                    std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                    return true;
                                }

                            }else{
                                noError = false;
                                std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                                return true;
                            }
                        }else{
                            noError = false;
                            std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                            return true;
                        }

                    }else{
                        noError = false;
                        std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                        return true;
                    }
                }else{
                    noError = false;
                    std::cout << "ERROR IN IF SYNTAX (" << std::endl;
                    return true;
                }

            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool CompileEngine::compileWhileStatement(){
    if(noError){
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "while"){
                std::cout << "<WHILE_STATEMENT>" << std::endl;
                outputToken();
                if(currentToken->tokenType == SYMBOL){
                    if(currentToken->symbol == '('){
                       outputToken();
                       compileExpression();

                       if(noError){
                           if(currentToken->tokenType == SYMBOL){
                               if(currentToken->symbol == ')'){
                                    outputToken();
                                    if(currentToken->tokenType == SYMBOL){
                                        if(currentToken->symbol == '{'){
                                            outputToken();
                                            compileExpression();

                                            if(noError){
                                                if(currentToken->tokenType == SYMBOL){
                                                    if(currentToken->symbol == '}'){
                                                        outputToken();
                                                        std::cout << "</WHILE_STATEMENT>" << std::endl << std::endl;
                                                        return true;
                                                    }else{
                                                        noError = false;
                                                        std::cout << "ERROR IN WHILE STATEMENT, expected }" << std::endl;
                                                        return true;
                                                    }
                                                }else{
                                                noError = false;
                                                std::cout << "ERROR IN WHILE STATEMENT, expected }" << std::endl;
                                                return true;
                                                }
                                            }else{
                                                return true;
                                            }

                                        }else{
                                            noError = false;
                                            std::cout << "ERROR IN WHILE STATEMENT, expected {" << std::endl;
                                            return true;
                                        }
                                    }else{
                                        noError = false;
                                        std::cout << "ERROR IN WHILE STATEMENT, expected symbol" << std::endl;
                                        return true;
                                    }
                               }else{
                                    noError = false;
                                    std::cout << "ERROR IN WHILE STATEMENT, expected )" << std::endl;
                                    return true;
                               }
                           }else{
                                noError = false;
                                std::cout << "ERROR IN WHILE STATEMENT" << std::endl;
                                return true;
                           }
                       }else{
                           return false;
                       }


                    }else{
                        noError = false;
                        std::cout << "ERROR IN WHILE STATEMENT" << std::endl;
                        return true;
                    }

                }else{
                    noError = false;
                    std::cout << "ERROR IN WHILE STATEMENT" << std::endl;
                    return true;
                }


            }else{
                return false;
            }
        }else{
            return false;
        }

    }else{
        return false;
    }
}


void CompileEngine::compileSubroutineCall(){
    if(noError){
        std::cout << "<SUBROUTINE_CALL>" << std::endl;
        outputToken();
        if(currentToken->tokenType == SYMBOL){
            if(currentToken->symbol == '('){
                outputToken();
                compileExpressionList();
                if(noError){
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ')'){
                            outputToken();
                            std::cout << "</SUBROUTINE_CALL>" << std::endl << std::endl;
                        }else{
                            noError = false;
                        std::cout << "ERROR in subroutine call, expected )" << std::endl;
                        }
                    }else{
                        noError = false;
                        std::cout << "ERROR in subroutine call, expected )" << std::endl;
                    }
                }else{
                    std::cout << "ERROR in subroutine call" << std::endl;
                }

            }else if(currentToken->symbol == '.'){
               outputToken();
               if(currentToken->tokenType == IDENTIFIER){
                  outputToken();
                  if(currentToken->tokenType == SYMBOL){
                    if(currentToken->symbol == '('){
                        outputToken();
                        compileExpressionList();
                        if(noError){
                            if(currentToken->tokenType == SYMBOL){
                                if(currentToken->symbol == ')'){
                                    outputToken();
                                    std::cout << "</SUBROUTINE_CALL>" << std::endl << std::endl;
                                }else{
                                    noError = false;
                                std::cout << "ERROR in subroutine call, expected )" << std::endl;
                                }
                            }else{
                                noError = false;
                                std::cout << "ERROR in subroutine call, expected )" << std::endl;
                            }
                        }else{
                            std::cout << "ERROR in subroutine call" << std::endl;
                        }


                    }else{
                         noError = false;
                         std::cout << "ERROR expected ( in subroutine name" << std::endl;
                    }
                  }else{
                     noError = false;
                     std::cout << "ERROR expected ( in subroutine name" << std::endl;
                  }

               }else{
                   noError = false;
                   std::cout << "ERROR expected subroutine name" << std::endl;
               }

            }else{
                noError = false;
                std::cout << "ERROR expected ( or . in subroutine" << std::endl;
            }

        }else{
            noError = false;
            std::cout << "ERROR expected ( or . in subroutine" << std::endl;
        }
    }
}

bool CompileEngine::compileDoStatement(){
    if(noError){
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "do"){
                std::cout << "<DO_STATEMENT>" << std::endl;
                outputToken();
                compileSubroutineCall();
                if(noError){
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ';'){
                            outputToken();
                            std::cout << "</LET_STATEMENT>" << std::endl << std::endl;
                            return true;
                        }
                    }else{
                        noError = false;
                        return true;
                    }
                }else{
                    return true;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }

    }else{
        return false;
    }
}


bool CompileEngine::compileReturnStatement(){
    if(noError){
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "return"){
                std::cout << "<RETURN_STATEMENT>" << std::endl;
                outputToken();

                //check if next token is a term
                bool isTerm = checkTerm();
                if(isTerm){
                    compileExpression();
                }

                if(noError == false){
                    std::cout << "ERROR IN RETURN SYNTAX" << std::endl;
                    return true;
                }

                if(currentToken->tokenType == SYMBOL){
                    if(currentToken->symbol == ';'){
                        outputToken();
                        std::cout << "</RETURN_STATEMENT>" << std::endl << std::endl;
                        return true;
                    }
                }else{
                    noError = false;
                    std::cout << "ERROR: EXPECTED ; in return" << std::endl;
                    return false;
                }

            }else{
                return false;
            }
        }else{
            return false;
        }

    }else{
        return false;
    }
}

void CompileEngine::compileStatements(){
    if(noError){
        std::cout << "<STATEMENTS>" << std::endl;
        bool moreStatements = true;
        while(moreStatements){
            moreStatements = false;
            bool anotherStatement = false;

            anotherStatement = compileLetStatement();
            if(anotherStatement == true){
                moreStatements = true;
            }

            anotherStatement = compileWhileStatement();
            if(anotherStatement == true){
                moreStatements = true;
            }

            anotherStatement = compileReturnStatement();
            if(anotherStatement == true){
                moreStatements = true;
            }

            anotherStatement = compileDoStatement();
            if(anotherStatement == true){
                moreStatements = true;
            }

            anotherStatement = compileIfStatement();
            if(anotherStatement == true){
                moreStatements = true;
            }
        }
        std::cout << "</STATEMENTS>" << std::endl << std::endl;
    }
}

void CompileEngine::compileExpression(){
    if(noError){
        std::cout << "<EXPRESSIONS>" << std::endl;
        bool moreTerms = false;
        compileTerm();
        if(checkOP()){
            moreTerms = true;
        }


        while(moreTerms){
            outputToken();
            compileTerm();

            if(noError){
                moreTerms = checkOP();
            }else{
                break;
            }
        }
        std::cout << "</EXPRESSIONS>" << std::endl << std::endl;
    }
}


bool CompileEngine::constructFuncOrMeth(){
    if(currentToken->tokenType == KEYWORD){
        if(currentToken->keyword == "constructor"){
            return true;
        }

        if(currentToken->keyword == "function"){
            return true;
        }

        if(currentToken->keyword == "method"){
            return true;
        }

        return false;
    }
}

bool CompileEngine::compileType(){
    if(noError){
        std::cout << "<TYPE>" << std::endl;
        if(currentToken->tokenType == KEYWORD ||
           currentToken->tokenType == IDENTIFIER){
           if(currentToken->tokenType == KEYWORD){
              if(currentToken->keyword == "int" ||
                 currentToken->keyword == "char" ||
                 currentToken->keyword == "boolean"){

                 outputToken();
              }else{
                  noError = false;
                  std::cout << "ERROR: EXPECTED keyword int/char/boolean" << std::endl;
              }

           }else if(currentToken->tokenType == IDENTIFIER){
               outputToken();
           }
           std::cout << "</TYPE>" << std::endl << std::endl;
        }else{
            noError = false;
            std::cout << "ERROR: EXPECTED a type but none found" << std::endl;
        }
    }
}

void CompileEngine::compileTerm(){

    if(noError){
        std::cout << "<TERM>" << std::endl;
        if(currentToken->tokenType == KEYWORD){
            if(currentToken->keyword == "true" ||
               currentToken->keyword == "false" ||
               currentToken->keyword == "null" ||
               currentToken->keyword == "this" )
               {
                   outputToken();
               }
        }

        if(currentToken->tokenType == INT_CONST){
            outputToken();
        }

        if(currentToken->tokenType == STRING_CONST){
            outputToken();
        }

        //check for unary term
        if(currentToken->tokenType == SYMBOL){
            if(currentToken->symbol == '~' ||
               currentToken->symbol == '-'){
                outputToken();
                compileTerm();
            }else if(currentToken->symbol == '('){
                outputToken();
                compileExpression();
                if(noError){
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ')'){
                            outputToken();
                        }else{
                          noError = false;
                          std::cout << "ERROR expected a ) in term expression" << std::endl;
                        }
                    }else{
                        noError = false;
                        std::cout << "ERROR in term expression" << std::endl;
                    }
                }
            }
        }

        if(currentToken->tokenType == IDENTIFIER){
            //if identifier peek ahead to see if variable name
            //subroutine call, or array style declaration
            getNextToken();
            if(tokenNext->tokenType == SYMBOL){
                if(tokenNext->symbol == '['){
                    outputToken();
                    outputToken();
                    compileExpression();
                    if(noError){
                        if(currentToken->tokenType == SYMBOL){
                            if(currentToken->symbol == ']'){
                                outputToken();
                            }else{
                                noError = true;
                                std::cout << "ERROR EXPECTED ] in array syntax" << std::endl;
                            }
                        }else{
                            noError = true;
                            std::cout << "ERROR EXPECTED ] in array syntax" << std::endl;

                        }
                    }else{
                        std::cout << "ERROR in array syntax" << std::endl;
                    }

                }else if(tokenNext->symbol == '(' ||
                         tokenNext->symbol == '.'){
                    compileSubroutineCall();
                }else{
                    noError = false;
                }
            }else{
                outputToken();
            }

        }
        std::cout << "</TERM>" << std::endl;
    }
}


bool CompileEngine::checkTerm(){

    if(currentToken->tokenType == KEYWORD){
        if(currentToken->keyword == "true" ||
           currentToken->keyword == "false" ||
           currentToken->keyword == "null" ||
           currentToken->keyword == "this" )
           {
               return true;
           }
    }

    if(currentToken->tokenType == INT_CONST){
        return true;
    }

    if(currentToken->tokenType == STRING_CONST){
        return true;
    }

    //check for unary term
    if(currentToken->tokenType == SYMBOL){
        if(currentToken->symbol == '~' ||
           currentToken->symbol == '-'){
            return true;
        }else if(currentToken->symbol == '('){
            return true;
        }
    }

    if(currentToken->tokenType == IDENTIFIER){
        return true;
    }
    return false;
}

bool CompileEngine::checkOP(){

    if(currentToken->tokenType == SYMBOL){
        if(currentToken->symbol == '+'||
           currentToken->symbol == '_'||
           currentToken->symbol == '*'||
           currentToken->symbol == '/'||
           currentToken->symbol == '&'||
           currentToken->symbol == '|'||
           currentToken->symbol == '<'||
           currentToken->symbol == '>'||
           currentToken->symbol == '='){
                return true;
        }
    }
    return false;
}


void CompileEngine::compileExpressionList(){
    if(noError){
        std::cout << "<EXPRESSION_LIST>" << std::endl;
        bool moreExpressions = false;

        if(checkTerm()){
            compileExpression();
            if(currentToken->tokenType == SYMBOL){
                if(currentToken->symbol == ','){
                    moreExpressions = true;
                }
            }

            while(moreExpressions){
                moreExpressions = false;
                outputToken();
                compileExpression();

                if(noError){
                    if(currentToken->tokenType == SYMBOL){
                        if(currentToken->symbol == ','){
                            moreExpressions = true;
                        }
                    }
                }else{
                    std::cout << "ERROR: wrong syntax for multiple expressions in list" << std::endl;
                    break;
                }

            }
        }
        std::cout << "</EXPRESSION_LIST>" << std::endl << std::endl;
    }
}
