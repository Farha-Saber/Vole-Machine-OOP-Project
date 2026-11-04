// Date: 6 Oct 1973
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

// /*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*

bool ProgramLoader::readProgram(const string& filePath, vector<uint16_t>& instructions){
    
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filePath << endl;
        return false;
    }


    string line;
    while(getline(file, line)){
        if (line.empty() || line[0] == ';') {
        continue;
        }

        string word = line.substr(0, 4);

        if (word.size() !=4 || !isHexString(word)) {
            cout << "Bad word: [" << word << "] size=" << word.size() << endl;
      
            return false;
        }


    
        int value = stoi(word ,nullptr , 16);

        Instructionfields f;
         f.opcode =(value >> 12) & 0xF;
         f.r = (value >> 8) & 0xF;
         f.x = (value >> 4) & 0xF;
         f.y = (value & 0xF);
         if(!InstructionValidator::validate(f)){
            cout << "Invalid instruction: " << word << endl;
            return false;
         }


         instructions.push_back(value);

    

    }
    return true;
}
