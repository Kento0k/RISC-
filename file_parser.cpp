#include "RISCEmulatorLibrary.h"
#include "instruction.c"
//Убираем комментарии, проверяем на недопустимые символы, приводим буквы к нижнему регистру
void clear_text(char *text, int length) {
    char *allowed_symbols = ("abdehijlnqrstuw0123456789,-# ");
    int k=0;
    while(k<length) {
        if (text[k] == '#') {
            do {
                text[k] = '#';
                k++;
            } while (text[k] != '\n' && k != length&&text[k]!=EOF);
            continue;
        }
        if (text[k] == '\n'||text[k]==EOF) {
            k++;
            continue;
        }
        text[k] = (char)tolower(text[k]);
        if (strchr(allowed_symbols, text[k]) == NULL)
            error_processing(50);
        k++;
    }
}
//Парсер
int parse_file(FILE *in, char *name, int *args) {
    const char *command[9];
    command[0] = "addi";
    command[1] = "nand";
    command[2] = "jalr";
    command[3] = "add";
    command[4] = "lui";
    command[5] = "beq";
    command[6] = "sw";
    command[7] = "lw" ;
    command[8] = "halt" ;
    int symbol=0, strlen=0, argcnt=0, flag=0;
    char *str=(char*)malloc(0);
    //Считываем строку из файла
    while(symbol!='\n'&&symbol!=EOF&&symbol!='#'){
        strlen++;
        str= (char*)realloc(str, strlen*sizeof(char));
        symbol=fgetc(in);
        str[strlen-1]= (char)symbol;
    }
    clear_text(str, strlen);
    while(symbol!='\n'&&symbol!=EOF)
        symbol=fgetc(in);
    if(strlen==1) {
        return 0;
    }
    str[strlen-1]='\0';
    //Получаем имя операции и проверяем строку на правильность
    char *oper=strtok(str, " ,");
    strcpy(name, oper);
    for(int i=0; i<9; i++){
        if (strcmp(name, command[i])==0)
            flag=1;
    }
    if(flag==0)
        error_processing(70);
    //Получаем операнды и проверяем их
    while(oper!=NULL){
        oper=strtok(NULL, ",");
        if(oper!=NULL) {
            if(argcnt==3)
                error_processing(70);
            args[argcnt] = atoi(oper);
            argcnt++;
        }
    }
    if(strcmp(name, command[0])==0||strcmp(name, command[1])==0||strcmp(name, command[3])==0||strcmp(name, command[5])==0||strcmp(name, command[6])==0||strcmp(name, command[7])==0){
        if(argcnt!=3)
            error_processing(80);
    }
    if(strcmp(name, command[2])==0||strcmp(name, command[4])==0){
        if(argcnt!=2)
            error_processing(80);
    }
    if(strcmp(name, command[8])==0){
        if(argcnt!=0)
            error_processing(80);
    }
    free(str);
    return 1;
}
//Количество строк и количество команд
void text_parameters(FILE* in, int *maxLine, int *num_of_commands){
    int symbol;
    while(!feof(in)){
        if(fgetc(in)=='\n')
            *maxLine+=1;
    }
    fseek(in, 0, SEEK_SET);
    for(int i=0; i<=*maxLine; i++){
        symbol=fgetc(in);
        if(symbol!='#' && symbol!=' ' &&symbol!='\n')
            *num_of_commands+=1;
        while(symbol!='\n' && symbol!=EOF)
            symbol=fgetc(in);
    }
    fseek(in, 0, SEEK_SET);
}