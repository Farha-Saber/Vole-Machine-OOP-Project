#include "InstructionValidator.h"
#include "ProgramLoader.h"
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

bool ProgramLoader::isHexString(const string& text) {
    for(int i=0; i< text.size(); i++){
        if (!isxdigit(text[i])) {
            return false;
        }
    }
    return true;
}


bool ProgramLoader::readProgram(const string& filePath, vector<uint16_t>& instructions){
    
    ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }


    string line;
    while(getline(file, line)){
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == string::npos || line[first] == ';') {
             continue;
        }


        string word = line.substr(first, 4);
       
        if (word.size() !=4 || !isHexString(word)) {
      
            return false;
        }


    
        int value = stoi(word ,nullptr , 16);

        InstructionFields f;
         f.opcode =(value >> 12) & 0xF;
         f.r = (value >> 8) & 0xF;
         f.x = (value >> 4) & 0xF;
         f.y = (value & 0xF);
         if(!InstructionValidator::validate(f)){
            return false;
         }


         instructions.push_back(value);

    

    }
    return true;
}
