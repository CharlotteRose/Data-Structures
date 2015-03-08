#include "VirtualMachine.h"

bool VirtualMachine::convertFile(std::fstream& fStr){
    std::string currentLine;
    while(!fStr.eof()){
        std::getline(fStr, currentLine);
        currentLine = cleanString(currentLine);
        if(!currentLine.empty()){
            //stripped file to parse easier
            //first reset fields
            if(currentLine[0] != '('){
                parseLine(currentLine);
            }
        }
        else{

        }
    }
}

void VirtualMachine::resetStrings(){
    command = "";
    location = "";
    index = "";
}

void VirtualMachine::parseLine(std::string currentLine){
    resetStrings();
    //breaks string into substrings, starting indexes
    int pos = 0;
    int span = 0;
    int i = 0;
    bool memoryCommand = false;

    for(i; i < currentLine.length(); i++){
        if(currentLine[i] == ' '){
            span = i - pos;
            command = currentLine.substr(pos, span);
            i++; //skips the whitespace
            break;
        }
    }

    //grabs one liner commands
    if(span == 0){
        command = currentLine;
    }

    //checks if command is push or pop
    memoryCommand = checkCommand(command);

    if(memoryCommand){
        pos = i;
        for(i; i < currentLine.length(); i++){
            if(currentLine[i] == ' '){
                span = i - pos;
                location = currentLine.substr(pos, span);
                i++; //skips the whitespace
                break;
            }
        }

        pos = i;
        span = currentLine.length() - i;
        index = currentLine.substr(pos, span);

        outputMemoryCommand();
    }else{
        //parse arithmetic function
        outputArithmetic();
    }

    //check if the command is an arithmetic function
    std::cout << "command is " << command << std::endl;

}

bool VirtualMachine::checkCommand(std::string command){
    if(command == "push")
        return true;
    if(command == "pop")
        return true;

    return false;
}

void VirtualMachine::outputMemoryCommand(){
    if(command == "push"){
        oStr << "@" << index << '\n' << "D=A\n";
        if(location != "constant"){
            oStr << "@" << location << '\n' << "A=A+D\n" << "D=M\n";
        }
        oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n";
    }

    if(command == "pop"){
        oStr << "@" << index << '\n' << "D=M\n" << "@R13\n" << "M=D\n"
             << "@" << location << '\n' << "D=M\n" << "@R13\n" << "M=M+D\n"
             << "@SP\n" << "AM=M-1\n" << "D=M\n" << "@R13\n" << "A=M\n"
             << "M=D\n";
    }

    oStr << '\n';
}

void VirtualMachine::outputArithmetic(){
    if(command == "add"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=M+D\n";
    }

    if(command == "sub"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=M-D\n";
    }

    if(command == "neg"){
        oStr << "@SP\n" << "A=A-1\n" << "M=-M\n";
    }

    if(command == "eq"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n"
             << "A=A-1\n" << "M=M-D\n" << "@EQUAL\n" << "D;JEQ\n"
             << "@NOT_EQUAL\n" << "D;JNE\n" << "(EQUAL)\n"
             << "@SP\n" << "A=M-1\n" << "M=-1\n" << "@END\n"
             << "0;JMP\n" << "(NOT_EQUAL)\n" << "@SP\n"
             << "A=M-1\n" << "M=0\n" << "(END)\n";
    }

    if(command == "lt"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n"
             << "A=A-1\n" << "M=M-D\n" << "@LT\n" << "D;JLT\n"
             << "@NOT_LT\n" << "D;JGE\n" << "(LT)\n"
             << "@SP\n" << "A=M-1\n" << "M=-1\n" << "@END\n"
             << "0;JMP\n" << "(NOT_LT)\n" << "@SP\n"
             << "A=M-1\n" << "M=0\n" << "(END)\n";
    }

    if(command == "gt"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n"
             << "A=A-1\n" << "M=M-D\n" << "@GT\n" << "D;JGT\n"
             << "@NOT_GT\n" << "D;JLE\n" << "(GT)\n"
             << "@SP\n" << "A=M-1\n" << "M=-1\n" << "@END\n"
             << "0;JMP\n" << "(NOT_GT)\n" << "@SP\n"
             << "A=M-1\n" << "M=0\n" << "(END)\n";
    }


    if(command == "and"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=D&M\n";
    }

    if(command == "or"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=D|M\n";
    }

    if(command == "not"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=D!M\n";
    }

     oStr << '\n';
}


std::string VirtualMachine::cleanString(std::string& input){
  //parses out comments in the line
  std::string::iterator comment;
  int i = 0;
  for ( std::string::iterator it = input.begin(); it != input.end(); ++it, i++){

        if(input[i] == '/'){
            //if(!input.empty()){
              if( i + 1 < input.length()){
                  if(input[i + 1] == '/'){
                      comment = it;
                      break;
                  }
              }
            //}
        }
  }
  input.erase(i, input.length());
  return input;
}
