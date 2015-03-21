#include "VirtualMachine.h"
#include <cstdlib>
#include <sstream>

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
    labelName = "";
}

void VirtualMachine::parseLine(std::string currentLine){
    resetStrings();
    //breaks string into substrings, starting indexes
    int pos = 0;
    int span = 0;
    int i = 0;
    COMMAND_TYPE currentCommand;
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
    currentCommand = checkCommand(command);

    if(currentCommand == MEM_COMMAND){
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
        if(location == "local"){
            location = "LCL";
        }

        if(location == "argument"){
            location = "ARG";
        }

        if(location == "this"){
            location = "THIS";
        }

        if(location == "that"){
            location = "THAT";
        }

        if(location == "temp"){
            location = "TEMP";
        }

        outputMemoryCommand();
    }else if (currentCommand == ARITH_COMMAND){
        //parse arithmetic function
        outputArithmetic();
    }else if (currentCommand == LABEL_COMMAND){
        pos = i;
        labelName = currentLine.substr(pos, currentLine.length());
        if(location == "local"){
            location = "LCL";
        }

        if(location == "argument"){
            location = "ARG";
        }

        if(location == "this"){
            location = "THIS";
        }

        if(location == "that"){
            location = "THAT";
        }

        if(location == "temp"){
            location = "5";
        }

        std::cout << labelName << std::endl;
        outputLabelCommand();
    }else if (currentCommand == FUNC_COMMAND){
        if(command != "return"){
            //grabs function name if not a return statement
            pos = i;
            for(i; i < currentLine.length(); i++){
                if(currentLine[i] == ' '){
                    span = i - pos;
                    functionName = currentLine.substr(pos, span);
                    i++; //skips the whitespace
                    break;
                }
            }

            //grabs k or n for functions
            pos = i;
            span = currentLine.length() - i;
            numberIn = currentLine.substr(pos, span);
        }
        outputFunctionCommand();
    }

    //check if the command is an arithmetic function
    std::cout << "command is " << command << std::endl;

}

COMMAND_TYPE VirtualMachine::checkCommand(std::string command){
    COMMAND_TYPE tempCommand = INVALID_COMMAND;
    if(command == "push")
        tempCommand = MEM_COMMAND;
    if(command == "pop")
        tempCommand = MEM_COMMAND;
    if(command == "add")
        tempCommand = ARITH_COMMAND;
    if(command == "sub")
        tempCommand = ARITH_COMMAND;
    if(command == "neg")
        tempCommand = ARITH_COMMAND;
    if(command == "eq")
        tempCommand = ARITH_COMMAND;
    if(command == "lt")
        tempCommand = ARITH_COMMAND;
    if(command == "gt")
        tempCommand = ARITH_COMMAND;
    if(command == "and")
        tempCommand = ARITH_COMMAND;
    if(command == "or")
        tempCommand = ARITH_COMMAND;
    if(command == "not")
        tempCommand = ARITH_COMMAND;
    if(command == "label")
        tempCommand = LABEL_COMMAND;
    if(command == "goto")
        tempCommand = LABEL_COMMAND;
    if(command == "if-goto")
        tempCommand = LABEL_COMMAND;
    if(command == "function")
        tempCommand = FUNC_COMMAND;
    if(command == "call")
        tempCommand = FUNC_COMMAND;
    if(command == "return")
        tempCommand = FUNC_COMMAND;
    return tempCommand;
}

void VirtualMachine::outputLabelCommand(){
    if(command == "label"){
        if(functionMode){
            labelName = functionName + "$" + labelName;
        }

        oStr << "(" << labelName << ")\n" << '\n';
        std::cout << "Label outputted" << std::endl;
    }

    if(command == "goto"){
        if(functionMode){
            labelName = functionName + "$" + labelName;
        }
        oStr << "@" << labelName << '\n' << "0;JMP\n" << '\n';
    }

    if(command == "if-goto")
    {
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" << "@" << labelName << '\n'
             << "D;JGT\n" << '\n';
    }
}

void VirtualMachine::outputFunctionCommand(){
    if(command == "function"){
        //convert k to int
        oStr << "(" << functionName << ")\n" << '\n';
        functionMode = true;
        numericValue = atoi(numberIn.c_str());
        std::cout << command << " " << functionName << " " << numericValue << std::endl;

        for(int i = 0; i < numericValue; i++){
            oStr << "@0"  << '\n' << "D=A\n";
            oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n" << '\n';
        }
    }else if(command == "call"){
        //convert call value to string and then create a unique call return label
        std::string callValue = NumberToString(callNumber);
        std::string returnAddress = "return-address" + callValue;

        numericValue = atoi(numberIn.c_str());
        std::cout << command << " " << functionName << " " << numericValue << std::endl;

        //push return address
        oStr << "@" << returnAddress << '\n' << "D=A\n";
        oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n" << '\n';
        //push LCL
        oStr << "@LCL" << '\n' << "D=M\n";
        oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n" << '\n';

        //push ARG
        oStr << "@ARG" << '\n' << "D=M\n";
        oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n" << '\n';

        //push THIS
        oStr << "@THIS" << '\n' << "D=M\n";
        oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n" << '\n';

        //push THAT
        oStr << "@THAT" << '\n' << "D=M\n";
        oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n" << '\n';


        //point ARG to SP-numeric value-5
        oStr << "@" << numberIn << '\n' << "D=A\n" << "@5\n" << "D=D+A\n"
             << "@SP\n" << "D=M-D\n" << "@ARG\n" << "M=D\n" << '\n';
        //point local to SP
        oStr << "@SP\n" << "D=M\n" << "@LCL\n" << "M=D\n" << '\n';

        //goto function
        oStr << "@" << functionName << '\n' << "0;JMP\n" << '\n';

        //declare return label
        oStr << "(" << returnAddress << ")\n" << '\n';


        //increment call number
        callNumber++;
    }

    if(command == "return"){

        //Frame = LCL
        oStr << "@LCL\n" << "D=M\n" << "@FRAME\n" << "M=D\n";

        //stores return address in temp variable RET
        oStr << "@5\n" << "D=D-A\n" << "A=D\n" << "D=M\n" << "@RET\n" << "M=D\n";

        //pop return value to Arg0 location
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" << "@ARG\n"
             << "A=M\n" << "M=D\n";

        //restore SP

        oStr << "@ARG\n" << "D=M\n" << "@1\n" << "D=D+A\n" << "@SP\n"
             << "M=D\n";

        //restore THAT
        oStr << "@FRAME\n" << "D=M\n" << "@1\n" << "D=D-A\n" << "A=D\n" << "D=M\n"
             << "@THAT\n" << "M=D\n";
        //restore THIS
        oStr << "@FRAME\n" << "D=M\n" << "@2\n" << "D=D-A\n" << "A=D\n" << "D=M\n"
             << "@THIS\n" << "M=D\n";
        //restore ARG
        oStr << "@FRAME\n" << "D=M\n" << "@3\n" << "D=D-A\n" << "A=D\n" << "D=M\n"
             << "@ARG\n" << "M=D\n";
        //restore LCL
        oStr << "@FRAME\n" << "D=M\n" << "@4\n" << "D=D-A\n" << "A=D\n" << "D=M\n"
             << "@LCL\n" << "M=D\n";

        //Access RET to get return address, then jump
        oStr << "@RET\n" << "A=M\n" << "0;JMP\n" << '\n';

        functionMode = false;
    }
}

void VirtualMachine::outputMemoryCommand(){

    if(location == "LCL" || location == "ARG" ||
       location == "THIS"|| location == "THAT" ){


        if(command == "push"){
            oStr << "@" << index << '\n' << "D=A\n";
            oStr << "@" << location << '\n' << "A=M\n" << "A=A+D\n" << "D=M\n";
            oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n";
        }

        if(command == "pop"){
            oStr << "@" << index << '\n' << "D=A\n" << "@R13\n" << "M=D\n"
                 << "@" << location << '\n' << "D=M\n" << "@R13\n" << "M=M+D\n"
                 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "@R13\n" << "A=M\n"
                 << "M=D\n";
        }


    }else{
     //handles generic commands
        if(location == "TEMP"){
            location = "5";
        }

        if(command == "push"){
            oStr << "@" << index << '\n' << "D=A\n";
            if(location != "constant"){
                oStr << "@" << location << '\n' << "A=A+D\n" << "D=M\n";
            }
            oStr << "@SP\n" << "A=M\n" << "M=D\n" << "@SP\n" << "AM=M+1\n";
        }

        if(command == "pop"){
            oStr << "@" << index << '\n' << "D=A\n" << "@R13\n" << "M=D\n"
                 << "@" << location << '\n' << "D=A\n" << "@R13\n" << "M=M+D\n"
                 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "@R13\n" << "A=M\n"
                 << "M=D\n";
        }

        oStr << '\n';
    }
}

void VirtualMachine::outputArithmetic(){
    bool labelCreated = false;
    if(command == "add"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=M+D\n";
    }

    if(command == "sub"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n" <<
        "A=A-1\n" << "M=M-D\n";
    }

    if(command == "neg"){
        oStr << "@SP\n" << "A=M-1\n" << "M=-M\n";
    }

    if(command == "eq"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n"
             << "A=A-1\n" << "D=M-D\n" << "@EQUAL" << labelNumber << '\n'  << "D;JEQ\n"
             << "@NOT_EQUAL" << labelNumber << '\n'  << "D;JNE\n" << "(EQUAL" << labelNumber
             << ')' << '\n'
             << "@SP\n" << "A=M-1\n" << "M=-1\n" << "@END" << labelNumber  << '\n'
             << "0;JMP\n" << "(NOT_EQUAL" << labelNumber << ')' << '\n'<< "@SP\n"
             << "A=M-1\n" << "M=0\n" << "(END" << labelNumber << ')' << '\n' ;
             labelCreated = true;
    }

    if(command == "lt"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n"
             << "A=A-1\n" << "D=M-D\n" << "@LT" << labelNumber << '\n'  << "D;JLT\n"
             << "@NOT_LT" << labelNumber << '\n' << "D;JGE\n" << "(LT" << labelNumber << ')'
             << '\n'
             << "@SP\n" << "A=M-1\n" << "M=-1\n" << "@END" << labelNumber << '\n'
             << "0;JMP\n" << "(NOT_LT" << labelNumber << ')' << '\n' << "@SP\n"
             << "A=M-1\n" << "M=0\n" << "(END" << labelNumber << ')' << '\n';
             labelCreated = true;
    }

    if(command == "gt"){
        oStr << "@SP\n" << "AM=M-1\n" << "D=M\n"
             << "A=A-1\n" << "D=M-D\n" << "@GT" << labelNumber << '\n' << "D;JGT\n"
             << "@NOT_GT" << labelNumber << '\n' << "D;JLE\n" << "(GT" << labelNumber << ')'
             << '\n'
             << "@SP\n" << "A=M-1\n" << "M=-1\n" << "@END" << labelNumber  << '\n'
             << "0;JMP\n" << "(NOT_GT" << labelNumber << ')' << '\n' << "@SP\n"
             << "A=M-1\n" << "M=0\n" << "(END" << labelNumber << ')' << '\n' ;
             labelCreated = true;
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
        oStr << "@SP\n" << "AM=M-1\n" << "M=!M\n" << "@SP\n" << "AM=M+1\n";
    }

    if(labelCreated){
        labelNumber++;
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

std::string VirtualMachine::NumberToString ( int Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}
