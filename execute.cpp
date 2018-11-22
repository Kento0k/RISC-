#include"RiscEmulatorLibrary.h"
using namespace std;
void RISC::exec_program(string& inpName, string& outName, vector<vector<int>>& reg,  vector<vector<int>>& memory){
    //maxAcessAdress является максимальным адресом памяти, куда совершалось обращение. Используется для печати, начиная с адреса maxAcessAdress+1 ячейки памяти не выводятся, т.к. они не были использованы.
    int maxLine=0, num_of_commands=0, command_count=0, address=1, PC=1, maxPC=4096, maxAcessAdress=0;
    string text;
    ifstream in(inpName);
    vector<instruction> program;
    if(!in.is_open())
        error_processing(20);
    getline(in, text, '\0');
    text_parameters(text, &maxLine, &num_of_commands);
    parse_file(text, program);
    //Заполняем массив команд, присваиваем командам параметры, записываем программу в память
    for(int i=0; i<program.size(); i++) {
        memory_write(memory, program[i]);
    }
    /*//Выполняем программу
    while(PC<=maxPC&&PC!=0) {
        run_instruction(reg, memory, &PC, &maxAcessAdress);
    }
    //Печатаем содержимое памяти и регистров в выходной файл
    fprintf(out, "Registers:\n");
    for (int z = 0; z < 8; z++) {
        fprintf(out, "register[%d]=  ", z);
        for(int k=0; k<16; k++)
            fprintf(out, "%d", reg[z][k]);
        fprintf(out, "\n");
    }
    fprintf(out, "\n");
    fprintf(out, "Memory:\n");
    for(int i=0; i<=maxAcessAdress;i++){
        fprintf(out, "memory[%d]=  ", i);
        for(int k=0; k<16; k++)
            fprintf(out, "%d", memory[i][k]);
        fprintf(out, "\n");
    }*/
}
