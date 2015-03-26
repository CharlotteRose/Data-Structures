#include "Tokenizer.h"

Tokenizer::Tokenizer(){
}


void Tokenizer::getTokens(std::string tokenFile, std::list<Token>*& tokenList){
    //open ifstream with tokenFile + ".token"

    //parse the first char

    //while not EoF

    //also test for EoF during smaller cases

    //first test if it's an identifier legal character.

    //if it is, build until you hit an illegal character or EOF

    //test built string against keywords, if not, then identifier



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

TokenType Tokenizer::lookUpKeyword(std::string curToken){
    TokenType tokenType = ERROR;

    //lookup keyword

    //lookup symbol

    //check for int const

    //check for strings


    //if it's none of these, it's an identifier


    return tokenType;
}

TokenType Tokenizer::lookUpNonID(char firstChar){
    TokenType tokenType = ERROR;

    //if token found in symbols, set to symbol

    //else if first char is a digit, set to digit

    //else if first char is quotes, set to quotes

    return false;
}

bool validIDchar(char curChar, ID_RULE idRule){
    bool isValid = false;

    if(idRule == FIRST){
        //if digit, then false

        //if letter true

        //if underscore true

    }else if(idRule == NOT_FIRST){
        //if letter, true

        //if underscore, true

        //if digit, true

    }

    return isValid;
}
