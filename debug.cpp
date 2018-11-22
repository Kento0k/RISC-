#include"RiscEmulatorLibrary.h"
#include"instruction.c"
void debug_program(FILE *in, FILE *out, int reg[8][16], int memory[4096][16]){
    printf("Debug mode.\nPrint '1' to do the next step.\nPrint'2'to run to the end\nPrint'3'to stop running\n");
    //maxAcessAdress является максимальным адресом памяти, куда совершалось обращение. Используется для печати, начиная с адреса maxAcessAdress+1 ячейки памяти не выводятся, т.к. они не были использованы.
    int maxLine=0, num_of_commands=0, command_count=0, address=1, PC=1, maxPC=4096, maxAcessAdress=0;
    char command[20];
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
    //Пока не дошли до конца программы
    while(PC<=maxPC&&PC!=0) {
        scanf("%s", command);
        if (strcmp("1", command) != 0 && strcmp("2", command) != 0 && strcmp("3", command) != 0) {
            printf("Wrong command\n");
            continue;
        }
            //Делаем один шаг
        else if (strcmp("1", command) == 0) {
            run_instruction(reg, memory, &PC, &maxAcessAdress);
            //Выводим содержимое памяти и регистров на экран
            printf("Registers:\n");
            for (int z = 0; z < 8; z++) {
                printf("register[%d]=  ", z);
                for(int k=0; k<16; k++)
                    printf("%d", reg[z][k]);
                printf("\n");
            }
            printf("\n");
            printf("Memory:\n");
            for(int i=0; i<=maxAcessAdress;i++){
                printf("memory[%d]=  ", i);
                for(int k=0; k<16; k++)
                    printf("%d", memory[i][k]);
                printf("\n");
            }
        }
            //Завершаем до конца
        else if(strcmp("2", command) == 0){
            while(PC<=maxPC&&PC!=0){
                run_instruction(reg, memory, &PC, &maxAcessAdress);
                //Выводим содержимое регистров и памяти на экран
                printf("Registers:\n");
                for (int z = 0; z < 8; z++) {
                    printf("register[%d]=  ", z);
                    for(int k=0; k<16; k++)
                        printf("%d", reg[z][k]);
                    printf("\n");
                }
                printf("\n");
                printf("Memory:\n");
                for(int i=0; i<=maxAcessAdress;i++){
                    printf("memory[%d]=  ", i);
                    for(int k=0; k<16; k++)
                        printf("%d", memory[i][k]);
                    printf("\n");
                }
            }
        }
        else if(strcmp("3", command) == 0)
            break;
    }
    //Выводим содержимое регистров и памяти в выходной файл
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

