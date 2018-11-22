
#ifndef RISC_RISCEMULATORLIBRARY_H
#define RISC_RISCEMULATORLIBRARY_H

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using  namespace std;
//instruction structure
class RISC {
public:
    struct instruction;
    typedef struct instruction instruction;

//Еrror processing functions
    void error_processing(int code);

//File parsing functions
    int parse_file(FILE *in, char *name, int *args);

    void text_parameters(string& in, int *maxPC, int *num_of_commands);

//Writing program to memory
    void memory_write(int memory[65536][16], instruction command);

//program execution
    void exec_program(string& inpName, string& outName, vector<vector<int>>& reg,  vector<vector<int>>& memory);

//program_debugging
    void debug_program(FILE *in, FILE *out, int reg[8][16], int memory[4096][16]);

//operations
    void run_instruction(int reg[8][16], int memory[4096][16], int *PC, int *maxAcessAdress);
};
#endif //RISC_RISCEMULATORLIBRARY_H
