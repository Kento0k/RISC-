#include"RiscEmulatorLibrary.h"
void RISC::debug_program(string& inpName, string& outName, vector<vector<int>>& reg,  vector<vector<int>>& memory){
    printf("Debug mode.\nPrint '1' to do the next step.\nPrint'2'to run to the end\nPrint'3'to stop running\n");
    //maxAcessAdress является максимальным адресом памяти, куда совершалось обращение. Используется для печати, начиная с адреса maxAcessAdress+1 ячейки памяти не выводятся, т.к. они не были использованы.
    int PC=1, maxPC=4096, maxAcessAdress=0;
    string command;
    string text;
    string allowedCommand= "123";
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
    //Пока не дошли до конца программы
    while(PC<=maxPC&&PC!=0) {
        cin>>command;
        if (allowedCommand.find(command)==-1) {
            printf("Wrong command\n");
            continue;
        }
            //Делаем один шаг
        else if (command=="1") {
            run_instruction(reg, memory, &PC, &maxAcessAdress);
            //Выводим содержимое памяти и регистров на экран
            cout<<"Registers:\n";
            for (int z = 0; z < 8; z++) {
                cout<<"register["<<z<<"]= ";
                for(int k=0; k<16; k++)
                    cout<<reg[z][k];
                cout<<"\n";
            }
            cout<<"\n";
            cout<<("Memory:\n");
            for(int i=0; i<=maxAcessAdress;i++){
                cout<<"memory["<<i<<"]= ";
                for(int k=0; k<16; k++)
                    cout<<memory[i][k];
                cout<<"\n";
            }
        }
            //Завершаем до конца
        else if(command=="2"){
            while(PC<=maxPC&&PC!=0){
                run_instruction(reg, memory, &PC, &maxAcessAdress);
                //Выводим содержимое регистров и памяти на экран
                cout<<"Registers:\n";
                for (int z = 0; z < 8; z++) {
                    cout<<"register["<<z<<"]= ";
                    for(int k=0; k<16; k++)
                        cout<<reg[z][k];
                    cout<<"\n";
                }
                cout<<"\n";
                cout<<("Memory:\n");
                for(int i=0; i<=maxAcessAdress;i++){
                    cout<<"memory["<<i<<"]= ";
                    for(int k=0; k<16; k++)
                        cout<<memory[i][k];
                    cout<<"\n";
                }
            }
        }
        else if(command=="3")
            break;
    }
    //Выводим содержимое регистров и памяти в выходной файл
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

