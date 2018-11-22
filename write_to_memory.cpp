#include "RISCEmulatorLibrary.h"
#include "instruction.c"
void memory_write(int memory[4096][16], instruction step){
    //Переводим инструкции в машинный код и записываем в память
    int address=step.adress;
    int memcnt;
    int neg=0;
    int carry=0;
    //ADD
    if(strcmp(step.name, "add")==0){
        //Проверяем правильность аргументов
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        //Назначаем аргументы инструкции
        int regA= step.args[0];
        int regB= step.args[1];
        int regC= step.args[2];
        //Задаем код инструкции
        memory[address][0]=0;
        memory[address][1]=0;
        memory[address][2]=0;
        //Записываем аргументы в двоичной системе счисления в соответствующие биты памяти
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        memcnt=9;
        for(int i=memcnt; i<4; i++)
            memory[address][i] = 0;
        memcnt=15;
        while(regC!=0){
            memory[address][memcnt]=regC%2;
            regC/=2;
            memcnt--;
        }
    }
        //ADDI
    else if(strcmp(step.name, "addi")==0){
        //Проверяем и записываем в биты памяти регистры в двоичной системе счисления
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-64||step.args[2]>63)
            error_processing(110);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=0;
        memory[address][1]=0;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        //Проверяем, отрицательное ли immediate
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
            neg=1;
        }
        //Если immediate отрицательно, то переводим в дополнительный код. Записываем в соответствующие биты памяти
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
        if(neg==1) {
            memcnt = 15;
            for(int i=memcnt; i>9; i--){
                if(memory[address][i]==0)
                    memory[address][i]=1;
                else
                    memory[address][i]=0;
            }
            memcnt=15;
            memory[address][memcnt] += 1;
            if (memory[address][memcnt] == 2) {
                memory[address][memcnt] = 0;
                carry++;
            }
            memcnt--;
            while (carry != 0 && memcnt != 9) {
                memory[address][memcnt] += carry;
                if (memory[address][memcnt] == 2) {
                    memory[address][memcnt] = 0;
                    carry = 1;
                    memcnt--;
                } else
                    carry = 0;
            }
        }
    }
        //NAND
    else if(strcmp(step.name, "nand")==0){
        //Проверяем аргументы, переводим в двоичную систему, записываем в соответствующие биты памяти
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7||step.args[2]<0||step.args[2]>7)
            error_processing(100);
        int regA= step.args[0];
        int regB= step.args[1];
        int regC= step.args[2];
        memory[address][0]=0;
        memory[address][1]=1;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        for(int i=memcnt; i<4; i++)
            memory[address][i] = 0;
        memcnt=15;
        while(regC!=0){
            memory[address][memcnt]=regC%2;
            regC/=2;
            memcnt--;
        }

    }
        //LUI
    else if(strcmp(step.name, "lui")==0){
        //Проверяем аргументы, переводим в двоичную систему, записываем в соответствующие биты памяти
        if(step.args[0]<0||step.args[0]>7)
            error_processing(100);
        if(step.args[1]<0||step.args[1]>1023)
            error_processing(110);
        int regA= step.args[0];
        int imm=step.args[1];
        memory[address][0]=0;
        memory[address][1]=1;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
    }
        //SW
    else if(strcmp(step.name, "sw")==0){
        //Проверяем аргументы, переводим в двоичную систему, при необходимости переводим immediate в дополнительный код, записываем в соответствующие биты памяти
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-64||step.args[2]>63)
            error_processing(110);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=1;
        memory[address][1]=0;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
            neg=1;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
        if(neg==1) {
            memcnt = 15;
            for(int i=memcnt; i>9; i--){
                if(memory[address][i]==0)
                    memory[address][i]=1;
                else
                    memory[address][i]=0;
            }
            memcnt=15;
            memory[address][memcnt] += 1;
            if (memory[address][memcnt] == 2) {
                memory[address][memcnt] = 0;
                carry++;
            }
            memcnt--;
            while (carry != 0 && memcnt != 9) {
                memory[address][memcnt] += carry;
                if (memory[address][memcnt] == 2) {
                    memory[address][memcnt] = 0;
                    carry = 1;
                    memcnt--;
                } else
                    carry = 0;
            }
        }

    }
        //LW.
    else if(strcmp(step.name, "lw")==0){
        //Проверяем аргументы, переводим в двоичную систему, при необходимости переводим immediate в дополнительный код, записываем в соответствующие биты памяти
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-64||step.args[2]>63)
            error_processing(110);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=1;
        memory[address][1]=0;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
            neg=1;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
        if(neg==1) {
            memcnt = 15;
            for(int i=memcnt; i>9; i--){
                if(memory[address][i]==0)
                    memory[address][i]=1;
                else
                    memory[address][i]=0;
            }
            memcnt=15;
            memory[address][memcnt] += 1;
            if (memory[address][memcnt] == 2) {
                memory[address][memcnt] = 0;
                carry++;
            }
            memcnt--;
            while (carry != 0 && memcnt != 9) {
                memory[address][memcnt] += carry;
                if (memory[address][memcnt] == 2) {
                    memory[address][memcnt] = 0;
                    carry = 1;
                    memcnt--;
                } else
                    carry = 0;
            }
        }
    }
        //BEQ.
    else if(strcmp(step.name, "beq")==0){
        //Проверяем аргументы, переводим в двоичную систему, при необходимости переводим immediate в дополнительный код, записываем в соответствующие биты памяти
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        if(step.args[2]<-64||step.args[2]>63)
            error_processing(110);
        int regA= step.args[0];
        int regB= step.args[1];
        int imm= step.args[2];
        memory[address][0]=1;
        memory[address][1]=1;
        memory[address][2]=0;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
        if(imm<0){
            memory[address][9]=1;
            imm=-imm;
            neg=1;
        }
        memcnt=15;
        while(imm!=0){
            memory[address][memcnt]=imm%2;
            imm/=2;
            memcnt--;
        }
        if(neg==1) {
            memcnt = 15;
            for(int i=memcnt; i>9; i--){
                if(memory[address][i]==0)
                    memory[address][i]=1;
                else
                    memory[address][i]=0;
            }
            memcnt=15;
            memory[address][memcnt] += 1;
            if (memory[address][memcnt] == 2) {
                memory[address][memcnt] = 0;
                carry++;
            }
            memcnt--;
            while (carry != 0 && memcnt != 9) {
                memory[address][memcnt] += carry;
                if (memory[address][memcnt] == 2) {
                    memory[address][memcnt] = 0;
                    carry = 1;
                    memcnt--;
                } else
                    carry = 0;
            }
        }
    }
        //JALR.
    else if(strcmp(step.name, "jalr")==0){
        //Проверяем аргументы, переводим в двоичную систему, записываем в соответствующие биты памяти
        if(step.args[0]<0||step.args[0]>7||step.args[1]<0||step.args[1]>7)
            error_processing(100);
        int regA= step.args[0];
        int regB= step.args[1];
        memory[address][0]=1;
        memory[address][1]=1;
        memory[address][2]=1;
        memcnt=5;
        while(regA!=0){
            memory[address][memcnt]=regA%2;
            regA/=2;
            memcnt--;
        }
        memcnt=8;
        while(regB!=0){
            memory[address][memcnt]=regB%2;
            regB/=2;
            memcnt--;
        }
    }

}



