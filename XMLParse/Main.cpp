
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <list>


struct Student{
    std::string firstName;
    std::string lastName;
    std::string degree;
};

enum STUDENT_DATA{
    FIRST,
    LAST,
    DEGREE
};

int main(){
    std::ifstream fin;
    std::ofstream fout;

    fin.open("data-set.xml");
    fout.open("data-out.txt");

    if(fin.is_open() && fout.is_open()){
        std::string currentLine = "";
        STUDENT_DATA currentData = LAST;
        bool newStudent = true;

        std::getline(fin, currentLine);
        std::getline(fin, currentLine);

        Student* tempStudent;

        while(!fin.eof()){
            if(newStudent == true){
                tempStudent = new Student();
            }

            currentLine = "";
            std::getline(fin, currentLine);

            //strips tabs out of strings for preparsing
            currentLine.erase(std::remove(currentLine.begin(), currentLine.end(), '\t'), currentLine.end());

            if(currentLine == "<record>"){
               newStudent = false;
            } else if(currentLine == "</record>"){
                fout << std::endl;
                newStudent = true;
            }else{
                int firstPos = -1;
                int secondPos = -1;
                for(int i = 0; i < currentLine.length(); i++){
                    if(currentLine[i] == '>' && firstPos == -1){
                        firstPos = i + 1;
                    }
                    if(currentLine[i] == '<' && firstPos >= 0){
                        secondPos = i;
                    }
                }

                std::string str2 = currentLine.substr (firstPos, secondPos - firstPos);

                if(currentData == LAST){
                    tempStudent->lastName = str2;
                    currentData = FIRST;
                }else if(currentData == FIRST){
                    tempStudent->firstName = str2;
                    currentData = DEGREE;
                }else if(currentData == DEGREE){
                    tempStudent->degree = str2;


                    fout << tempStudent->firstName << " " << tempStudent->lastName << std::endl;
                    fout << tempStudent->degree << std::endl;
                    currentData = LAST;
                }
            }
        }


        fin.close();
        fout.close();
    }
}
