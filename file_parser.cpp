#include "RiscEmulatorLibrary.h"
using namespace std;
//Парсер
//Проверяем входную программу на правильность. Заполняем вектор команд
void RISC:: parse_file(string& text, vector<instruction>& program) {
    cmatch match;
    string command;
    string word;
    instruction operation;
    int operAddress=1;
    regex add_comm("add [0-9]+ [0-9]+ [0-9]+ ?");
    regex addi_comm("addi [0-9]+ [0-9]+ -?[0-9]+ ?");
    regex nand_comm("nand [0-9]+ [0-9]+ [0-9]+ ?");
    regex lui_comm("lui [0-9]+ [0-9]+ ?");
    regex sw_comm("sw [0-9]+ [0-9]+ -?[0-9]+ ?");
    regex lw_comm("lw [0-9]+ [0-9]+ -?[0-9]+ ?");
    regex beq_comm("beq [0-9]+ [0-9]+ -?[0-9]+ ?");
    regex jalr_comm("jalr [0-9]+ [0-9]+ ?");
    for(int i=0; i<text.length(); i++){
        if(text[i]!='\n')
            command+=text[i];
        else{
            if(regex_match(command.c_str(), match, add_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<3; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, addi_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<3; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, nand_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<3; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, lui_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<2; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, sw_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<3; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, lw_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<3; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, beq_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<3; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else if(regex_match(command.c_str(), match, jalr_comm)){
                stringstream ss(command);
                ss>>word;
                operation.name=word;
                for(int k=0; k<2; k++) {
                    ss >> word;
                    operation.args.push_back(stoi(word));
                }
            }
            else {
                cout<<command<<endl;
                error_processing(70);
            }
            operation.address= operAddress;
            program.push_back(operation);
            operation.name.clear();
            operation.args.clear();
            command.clear();
            operAddress++;
        }
    }
}
//Убираем комментарии, проверяем на недопустимые символы, приводим буквы к нижнему регистру
void RISC::text_align(string& text) {
    string newText;
    string allowed_symbols = ("abdehijlnqrstuw0123456789,-# \n");
    for (int i=0; i<text.length(); i++) {
        if(isupper(text[i]))
           text[i]= (char)tolower(text[i]);
        if(allowed_symbols.find(text[i])==-1)
           error_processing(50);
        if(text[i]=='#'){
           if(text[i+1]!='\n')
               text[i+1]='#';
        }
        if(text[i]==',')
            text[i]=' ';
        if(text[i]=='\n' && text[i-1]=='\n')
            continue;
        if(text[i]!='#'){
            newText+= text[i];
        }
    }
    text.clear();
    text+=newText;
}