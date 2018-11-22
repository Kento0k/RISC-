#include"RISCEmulatorLibrary.h"
#include"instruction.c"
using namespace std;
void RISC::exec_program(std::ifstream in, FILE *out, vector<vector<int>> reg(8, vector<int>(16)),  vector<vector<int>> memory(4096, vector<int>(16));){
    //maxAcessAdress является максимальным адресом памяти, куда совершалось обращение. Используется для печати, начиная с адреса maxAcessAdress+1 ячейки памяти не выводятся, т.к. они не были использованы.
    int maxLine=0, num_of_commands=0, command_count=0, address=1, PC=1, maxPC=4096, maxAcessAdress=0;
    text_parameters(in, &maxLine, &num_of_commands);
    //Создаем массив команд
    instruction *program= (instruction*)malloc(num_of_commands * sizeof(instruction));
    int flag[num_of_commands];
    //Заполняем массив команд, присваиваем командам параметры, записываем программу в память
    for(int i=0; i<=maxLine; i++) {
        flag[i]= parse_file(in, program[command_count].name, program[command_count].args);
        if(flag[i]==1) {
            program[command_count].adress = address;
            memory_write(memory, program[command_count]);
            address++;
            maxAcessAdress++;
        }
        command_count++;
    }
    //Выполняем программу
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
    }
}
