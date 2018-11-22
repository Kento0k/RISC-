#include"RiscEmulatorLibrary.h"
using namespace std;
void RISC::exec_program(string& inpName, string& outName, vector<vector<int>>& reg,  vector<vector<int>>& memory){
    //maxAcessAdress является максимальным адресом памяти, куда совершалось обращение. Используется для печати, начиная с адреса maxAcessAdress+1 ячейки памяти не выводятся, т.к. они не были использованы.
    int PC=1, maxPC=4096, maxAcessAdress=0;
    string text;
    ifstream in(inpName);
    vector<instruction> program;
    if(!in.is_open())
        error_processing(20);
    //Заполняем массив команд, присваиваем командам параметры, записываем программу в память
    getline(in, text, '\0');
    text_align(text);
    parse_file(text, program);
    for(int i=0; i<program.size(); i++) {
        memory_write(memory, program[i]);
    }
    maxAcessAdress= program.size();
    //Выполняем программу
    while(PC<=maxPC&&PC!=0) {
        run_instruction(reg, memory, &PC, &maxAcessAdress);
    }
    ofstream out(outName);
    //Печатаем содержимое памяти и регистров в выходной файл
    out<<"Registers:\n";
    for (int z = 0; z < 8; z++) {
        out<<"register["<<z<<"]= ";
        for(int k=0; k<16; k++)
            out<<reg[z][k];
        out<<"\n";
    }
    cout<<"\n";
    out<<"Memory:\n";;
    for(int i=0; i<=maxAcessAdress;i++){
        out<<"memory["<<i<<"]= ";
        for(int k=0; k<16; k++)
            out<<memory[i][k];
        out<<"\n";
    }
    out<<endl;
    out.close();
}
