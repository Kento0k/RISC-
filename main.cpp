#include "RiscEmulatorLibrary.h"
using namespace std;
int main(int argc, char *argv[]){
    vector<vector<int>> reg(8, vector<int>(16));
    vector<vector<int>> memory(4096, vector<int>(16));
    string inpName;
    string outName;
    string debug;
    inpName= argv[1];
    outName= argv[2];
    RISC processor;
    if(argc<3 || argc>4) {
        cout<<"############################################################\n"
            <<"#                                                          #\n"
            <<"# The RISC-16 machine emulator                             #\n"
            <<"#                                                          #\n"
            <<"# Example of command line:                                 #\n"
            <<"# ...\\RISC.exe ...\\in.txt ...\\out.txt [debug]              #\n"
            <<"# ...\\RISC.exe- path to executable file                    #\n"
            <<"# ...\\in.exe- path to input file                           #\n"
            <<"# ...\\RISC.exe- path to output file                        #\n"
            <<"# Print '[debug]' key if you want to enter to debug mode   #\n"
            <<"#                                                          #\n"
            <<"# Example of an input file:                                #\n"
            <<"# SW R1,R2,15                                              #\n"
            <<"# ADD R3,R5,R7                                             #\n"
            <<"# ADDI R4,R2,23                                            #\n"
            <<"#                                                          #\n"
            <<"############################################################\n"
        <<endl;
        processor.error_processing(10);
    }
    else{
            if(argc==3) {
                processor.exec_program(inpName, outName, reg, memory);
            }
            /*else if(argc==4){
                if(debug=="[debug]")
                    processor.debug_program(in,out, reg, memory);
                else
                    processor.error_processing(30);
            }*/
    }
    return 0;
}