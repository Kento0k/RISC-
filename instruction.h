#ifndef RISC_INSTRUCTION_H
#define RISC_INSTRUCTION_H
#include"RISCEmulatorLibrary.h"
using namespace std;
struct instruction{
    vector<int> args;
    int adress;
    string name;
};
#endif //RISC_INSTRUCTION_H
