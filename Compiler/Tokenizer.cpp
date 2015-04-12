#include "Tokenizer.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Tokenizer::Tokenizer(){
    //testID();

    initializeLists();
    //testIDLookup();
    //testNonIDLookup();

}


void Tokenizer::getTokens(std::string tokenFile, std::list<Token*>*& tokenList){
    //open ifstream with tokenFile + ".token"
    std::ifstream fin(tokenFile.c_str());
    char firstChar;
    bool validIDcharacter = false;
    std::string currentToken;
    TokenType tokenType;
    Token* newToken;

    if(fin.is_open()){
    //parse the first char
    while(fin.get(firstChar)){
        newToken = new Token();
        tokenType = ERROR;

        currentToken = ""; //resets the token building string


        validIDcharacter = validIDchar(firstChar, FIRST);
        if(validIDcharacter){
            currentToken += firstChar;
            while(validIDcharacter){
                //builds string until invalid char is found
                tokenType = lookUpKeyword(currentToken);
                if(tokenType == KEYWORD){
                    newToken->keyword = currentToken;
                    break;
                }

                //check if currentToken is a keyword, if so, say so and break
                firstChar = fin.peek();
                validIDcharacter = validIDchar(firstChar, NOT_FIRST);
                if(validIDcharacter){
                    fin.get(firstChar);
                    currentToken += firstChar;
                }
            }

            if(tokenType == IDENTIFIER){
                newToken->identifier = currentToken;
            }

        }else{
            //do the stuff for symbols here

            tokenType = lookUpNonID(firstChar);

            //check symbol
            if(tokenType == SYMBOL){
                newToken->symbol = firstChar;
            }else if(tokenType == INT_CONST){
                bool stillDigit = true;
                while(stillDigit){
                    firstChar = fin.peek();
                    if(isdigit(firstChar)){
                        fin.get(firstChar);
                        currentToken += firstChar;
                    }else{
                       stillDigit = false;
                    }
                }
                newToken->intVal = atoi(currentToken.c_str());
            }else if(tokenType == STRING_CONST){
                bool stillString = true;
                while(stillString){
                    fin.get(firstChar);

                    if(firstChar == '"'){
                        stillString = false;

                    }else{
                        currentToken += firstChar;
                    }
                }
                newToken->stringVal = currentToken;
            }
        }

        newToken->tokenType = tokenType;
        if(newToken->tokenType != ERROR){
            //add to the list
            tokenList->push_back(newToken);
        }else{
            delete newToken;
            newToken = NULL;
        }

    }


    //while not EoF

    //also test for EoF during smaller cases

    //first test if it's an identifier legal character.

    //if it is, build until you hit an illegal character or EOF

    //test built string against keywords, if not, then identifier
        fin.close();
    }else{
        std::cout << "fail" << std::endl;
    }





    //if an illegal character is first, first check type of token


    //symbol

    //int const

    //string constant

    //add the created token to the tokenList


}

void Tokenizer::initializeLists(){
    keywordList.push_back("class");
    keywordList.push_back("constructor");
    keywordList.push_back("function");
    keywordList.push_back("method");
    keywordList.push_back("field");
    keywordList.push_back("static");
    keywordList.push_back("var");
    keywordList.push_back("int");
    keywordList.push_back("char");
    keywordList.push_back("boolean");
    keywordList.push_back("void");
    keywordList.push_back("true");
    keywordList.push_back("false");
    keywordList.push_back("null");
    keywordList.push_back("this");
    keywordList.push_back("let");
    keywordList.push_back("do");
    keywordList.push_back("if");
    keywordList.push_back("else");
    keywordList.push_back("while");
    keywordList.push_back("return");

    symbolList.push_back('{');
    symbolList.push_back('}');
    symbolList.push_back('(');
    symbolList.push_back(')');
    symbolList.push_back('[');
    symbolList.push_back(']');
    symbolList.push_back('.');
    symbolList.push_back(',');
    symbolList.push_back(';');
    symbolList.push_back('+');
    symbolList.push_back('-');
    symbolList.push_back('*');
    symbolList.push_back('/');
    symbolList.push_back('&');
    symbolList.push_back('|');
    symbolList.push_back('<');
    symbolList.push_back('>');
    symbolList.push_back('=');
    symbolList.push_back('~');
}

void Tokenizer::testNonIDLookup(){
    Token testToken;
    testToken.tokenType = lookUpNonID('(');

    std::cout << "(" << std::endl;
    if(testToken.tokenType == SYMBOL){
        std::cout << "SYMBOL" << std::endl;
    }

    if(testToken.tokenType == INT_CONST){
        std::cout << "DIGIT" << std::endl;
    }

    if(testToken.tokenType == STRING_CONST){
        std::cout << "QUOTE" << std::endl;
    }


    testToken.tokenType = lookUpNonID('8');

    std::cout << "8" << std::endl;
    if(testToken.tokenType == SYMBOL){
        std::cout << "SYMBOL" << std::endl;
    }

    if(testToken.tokenType == INT_CONST){
        std::cout << "DIGIT" << std::endl;
    }

    if(testToken.tokenType == STRING_CONST){
        std::cout << "QUOTE" << std::endl;
    }


    testToken.tokenType = lookUpNonID('"');

    std::cout << '"' << std::endl;
    if(testToken.tokenType == SYMBOL){
        std::cout << "SYMBOL" << std::endl;
    }

    if(testToken.tokenType == INT_CONST){
        std::cout << "DIGIT" << std::endl;
    }

    if(testToken.tokenType == STRING_CONST){
        std::cout << "QUOTE" << std::endl;
    }
}

void Tokenizer::testIDLookup(){

    Token testToken;
    testToken.tokenType = lookUpKeyword("boolean");

    std::cout << "booleaan" << std::endl;
    if(testToken.tokenType == KEYWORD){
        std::cout << "KEYWORD" << std::endl;
    }

    if(testToken.tokenType == IDENTIFIER){
        std::cout << "IDENTIFIER" << std::endl;
    }

    testToken.tokenType = lookUpKeyword("boolean");
    std::cout << "boolean" << std::endl;
    if(testToken.tokenType == KEYWORD){
        std::cout << "KEYWORD" << std::endl;
    }

    if(testToken.tokenType == IDENTIFIER){
        std::cout << "IDENTIFIER" << std::endl;
    }
}

TokenType Tokenizer::lookUpKeyword(std::string curToken){
    TokenType tokenType = IDENTIFIER;
    //lookup keyword
    std::list<std::string>::iterator it;

    for(it = keywordList.begin();
        it != keywordList.end(); it++){
        if(curToken == *it){
            tokenType = KEYWORD;
            return tokenType;
        }
    }
    return tokenType;
}

TokenType Tokenizer::lookUpNonID(char firstChar){
    TokenType tokenType = ERROR;

    //if token found in symbols, set to symbol
    std::list<char>::iterator it;

    for(it = symbolList.begin();
        it != symbolList.end(); it++){
        if(firstChar == *it){
            tokenType = SYMBOL;
            return tokenType;
        }
    }

    //else if first char is a digit, set to digit
    if(isdigit(firstChar)){
        tokenType = INT_CONST;
        return tokenType;
    }

    //else if first char is quotes, set to quotes
    if(firstChar == '"'){
        tokenType = STRING_CONST;
        return tokenType;
    }

    return tokenType;
}

void Tokenizer::testID(){
    bool test = false;
    ID_RULE id_rule = FIRST;

    test = this->validIDchar('5', id_rule);
    std::cout << "Testing 5, first " << test << std::endl;

    test = validIDchar('_', id_rule);
    std::cout << "Testing _, first " << test << std::endl;

    test = validIDchar('a', id_rule);
    std::cout << "Testing a, first " << test << std::endl;

    test = validIDchar('?', id_rule);
    std::cout << "Testing ?, first " << test << std::endl;

    id_rule = NOT_FIRST;

    test = validIDchar('5', id_rule);
    std::cout << "Testing 5, second " << test << std::endl;

    test = validIDchar('_', id_rule);
    std::cout << "Testing _, second " << test << std::endl;

    test = validIDchar('a', id_rule);
    std::cout << "Testing a, second " << test << std::endl;

    test = validIDchar('?', id_rule);
    std::cout << "Testing ?, second " << test << std::endl;
}

bool Tokenizer::validIDchar(char curChar, ID_RULE idRule){


    if(idRule == FIRST){
        //if digit, then false
        if(isdigit(curChar)){
            return false;
        }
        //if letter true
        if(isalpha(curChar)){
            return true;
        }

        //if underscore true
        if(curChar == '_'){
            return true;
        }
    }else if(idRule == NOT_FIRST){
        //if letter, true
        if(isalpha(curChar)){
            return true;
        }
        //if underscore, true
        if(curChar == '_'){
            return true;
        }

        //if digit, true
        if(isdigit(curChar)){
            return true;
        }
    }
    return false;
}
