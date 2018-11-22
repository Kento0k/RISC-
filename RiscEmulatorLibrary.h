
#ifndef RISC_RISCEMULATORLIBRARY_H
#define RISC_RISCEMULATORLIBRARY_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<regex>
using  namespace std;
//instruction structure
class RISC {
public:
    struct instruction{
        vector<int> args;
        int address;
        string name;
    };
    typedef struct instruction instruction;

//Еrror processing functions
    void error_processing(int code);

//File parsing functions
    void parse_file(string& text, vector<instruction>& program);

    void text_align(string& in);

//Writing program to memory
    void memory_write(vector<vector<int>>& memory, RISC::instruction step);

//program execution
    void exec_program(string& inpName, string& outName, vector<vector<int>>& reg,  vector<vector<int>>& memory);

//program_debugging
    void debug_program(string& inpName, string& outName, vector<vector<int>>& reg,  vector<vector<int>>& memory);

//operations
    void run_instruction(vector<vector<int>>& reg, vector<vector<int>>& memory, int *PC, int *maxAcessAdress);
};
#endif //RISC_RISCEMULATORLIBRARY_H
