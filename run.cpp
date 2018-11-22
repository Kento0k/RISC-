#include "RiscEmulatorLibrary.h"
#include"instruction.h"
void run_instruction(int reg[8][16], int memory[4096][16], int *PC, int *maxAcessAdress) {
    //Определяем операцию по коду
    //ADD. reg[a]= reg[b]+reg[c]
    if (memory[*PC][0] == 0 && memory[*PC][1] == 0 && memory[*PC][2] == 0) {
        int regA, regB, regC, carry = 0;
        //Переводим номера регистров в десятичную систему счисления
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        regC = memory[*PC][13] * 4 + memory[*PC][14] * 2 + memory[*PC][15];
        //Если регистр А ненулевой, то записываем в него сумму содержимого регистров Б и С в двоичной системе счисления, инкрементируем РС
        if(regA!=0) {
            for (int i = 15; i >= 0; i--) {
                reg[regA][i] = reg[regB][i] + reg[regC][i] + carry;
                if (reg[regA][i] == 2) {
                    reg[regA][i] = 0;
                    carry = 1;
                } else if (reg[regA][i] == 3) {
                    reg[regA][i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
        }
        *PC+=1;
    }
        //ADDI. reg[a]=reg[b]+imm
    else if (memory[*PC][0] == 0 && memory[*PC][1] == 0 && memory[*PC][2] == 1) {
        int regA, regB, carry = 0, imm[16] = {0};
        //Переводим номера регистров в десятичную систему счисления
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        //Если регистр А ненулевой, то записываем в него сумму регистра B и immediate в двоичной системе счисления, инкрементируем PC
        if(regA!=0) {
            for (int i = 15; i > 8; i--)
                imm[i] = memory[*PC][i];
            if (imm[9] == 1) {
                for (int i = 8; i >= 0; i--)
                    imm[i] = 1;
            }
            for (int i = 15; i >= 0; i--) {
                reg[regA][i] = reg[regB][i] + imm[i] + carry;
                if (reg[regA][i] == 2) {
                    reg[regA][i] = 0;
                    carry = 1;
                } else if (reg[regA][i] == 3) {
                    reg[regA][i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
        }
        *PC+=1;
    }
        //NAND. reg[a]=~(reg[a]&reg[b])
    else if (memory[*PC][0] == 0 && memory[*PC][1] == 1 && memory[*PC][2] == 0) {
        int regA, regB, regC;
        //Переводим номера регистров в десятичную систему счисления, производим побитовую операцию "и-не" над содержимым регистров B и С, записываем результат в двоичной системе счисления в регистр А, если он ненулевой, инкрементируем РС
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        regC = memory[*PC][13] * 4 + memory[*PC][14] * 2 + memory[*PC][15];
        if(regA!=0) {
            for (int i = 0; i < 16; i++) {
                if (reg[regB][i] == 1 && reg[regC][i] == 1)
                    reg[regA][i] = 0;
                else
                    reg[regA][i] = 1;
            }
        }
        *PC+=1;
    }
        //LUI. place 10 bits of imm from the 16-th bit of reg[a]. The lower 6 bits of reg[a] become 0
    else if (memory[*PC][0] == 0 && memory[*PC][1] == 1 && memory[*PC][2] == 1) {
        int regA;
        //Переводим номер регистра А в десятичную систему счисления. Если он ненулевой, то, начиная со старшего бита, записываем в него immediate в двоичной системе счисления. Младшие 6 бит регистра А обнуляем. Инкрементируем PC/
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        if(regA!=0) {
            for (int i = 6; i < 16; i++) {
                reg[regA][i - 6] = memory[*PC][i];
            }
            for (int i = 10; i < 16; i++)
                reg[regA][i] = 0;
        }
        *PC+=1;
    }
        //SW. store reg[a] in the memory with address= reg[b]+imm
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 0 && memory[*PC][2] == 0) {
        int regA, regB, carry = 0, imm[16] = {0}, address[16] = {0}, intAddress = 0, deg = 1;
        //Переводим номера регистров в десятичную систему счисления, получаем immediate
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        for (int i = 15; i > 8; i--)
            imm[i] = memory[*PC][i];
        if (imm[9] == 1) {
            for (int i = 8; i >= 0; i--)
                imm[i] = 1;
        }
        //Получаем адрес назначения и переводим его в десятичную систему счисления
        for (int i = 15; i >= 0; i--) {
            address[i] = reg[regB][i] + imm[i] + carry;
            if (address[i] == 2) {
                address[i] = 0;
                carry = 1;
            } else if (address[i] == 3) {
                address[i] = 1;
                carry = 1;
            } else
                carry = 0;
        }
        for (int i = 15; i >= 0; i--) {
            intAddress += address[i] * deg;
            deg *= 2;
        }
        //Проверяем адрез назначения на существование
        if (intAddress > 4095)
            error_processing(120);
        //Если адрес назначения был максимальным, обновляем maxAcessAdress
        if(intAddress>*maxAcessAdress)
            *maxAcessAdress=intAddress;
        //Если адрес ненулевой, записываем в него содержимое регистра А
        if (intAddress != 0) {
            for (int i = 0; i < 16; i++)
                memory[intAddress][i] = reg[regA][i];
        }
        //Инкрементируем PC
        *PC+=1;
    }
        //LW. place to reg[a] a value from the memory with address= reg[b]+imm
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 0 && memory[*PC][2] == 1) {
        //Переводим номера регистров в десятичную систему счисления, получаем immediate
        int regA, regB, carry = 0, imm[16] = {0}, address[16] = {0}, intAddress = 0, deg = 1;
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        //Если регистр А ненулевой,записываем в него значение, расположенное по полученному адресу, при условии его существования. При необходимости обновляем maxAccessAddress. Инкрементируем PC
        if(regA!=0) {
            for (int i = 15; i > 8; i--)
                imm[i] = memory[*PC][i];
            if (imm[9] == 1) {
                for (int i = 8; i >= 0; i--)
                    imm[i] = 1;
            }
            for (int i = 15; i >= 0; i--) {
                address[i] = reg[regB][i] + imm[i] + carry;
                if (address[i] == 2) {
                    address[i] = 0;
                    carry = 1;
                } else if (address[i] == 3) {
                    address[i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
            for (int i = 15; i >= 0; i--) {
                intAddress += address[i] * deg;
                deg *= 2;
            }
            if (intAddress > 4095)
                error_processing(120);
            if(intAddress>*maxAcessAdress)
                *maxAcessAdress=intAddress;
            for (int i = 0; i < 16; i++)
                reg[regA][i] = memory[intAddress][i];
        }
        *PC+=1;
    }
        //BEQ. if reg[a]==reg[b] go to memory address PC+1+imm. PC is the address of beq
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 1 && memory[*PC][2] == 0) {
        int regA, regB, carry = 0, imm[16] = {0}, address[16] = {0}, intAddress = *PC, deg = 1, cnt = 15, isEqual = 1;
        //Переводим номера регистров в десятичную систему счисления
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        //Проверяем на равенство их содержимые
        for (int i = 0; i < 16; i++) {
            if (reg[regA][i] != reg[regB][i]) {
                isEqual = 0;
                break;
            }
        }
        //Если содержимые равны между собой
        if (isEqual == 1) {
            //Получаем адрес назначения
            for (int i = 15; i > 8; i--)
                imm[i] = memory[*PC][i];
            if (imm[9] == 1) {
                for (int i = 8; i >= 0; i--)
                    imm[i] = 1;
            }
            while (intAddress != 0) {
                address[cnt] = intAddress % 2;
                intAddress /= 2;
                cnt--;
            }
            for (int i = 15; i >= 0; i--) {
                address[i] = address[i] + imm[i] + carry;
                if (address[i] == 2) {
                    address[i] = 0;
                    carry = 1;
                } else if (address[i] == 3) {
                    address[i] = 1;
                    carry = 1;
                } else
                    carry = 0;
            }
            cnt=15;
            carry=0;
            address[cnt]+=1;
            if(address[cnt]==2){
                address[cnt]=0;
                carry++;
            }
            cnt--;
            while(carry!=0&&cnt>=0){
                address[cnt]+=carry;
                if (address[cnt] == 2) {
                    address[cnt] = 0;
                    carry = 1;
                    cnt--;
                } else
                    carry = 0;
            }
            for (int i = 15; i >= 0; i--) {
                intAddress += address[i] * deg;
                deg *= 2;
            }
            //Проверяем адрес на существование
            if (intAddress > 4095)
                error_processing(120);
            //Если адрес нулевой, инкрементируем его, чтобы избежать останова.
            if(intAddress==0) {
                intAddress++;
            }
            //При необходимости обновляем maxAccessAddress
            if(intAddress>*maxAcessAdress)
                *maxAcessAdress=intAddress+1;
            //Присваиваем РС адрес назначения, т.е совершаем прыжок в памяти
            *PC = intAddress;
        }
            //Если условие равенства не было выполнено, просто инкрементируем PC.
        else
            *PC+=1;
    }
        //JALR. go to program address which contains in reg[b]. reg[a]=PC+1.PC is the address of jalr
    else if (memory[*PC][0] == 1 && memory[*PC][1] == 1 && memory[*PC][2] == 1) {
        int regA, regB, address=0, jalrAddress = *PC + 1, cnt = 15, deg = 1;
        //Получаем номера регистров в десятичной системе счисления
        regA = memory[*PC][3] * 4 + memory[*PC][4] * 2 + memory[*PC][5];
        regB = memory[*PC][6] * 4 + memory[*PC][7] * 2 + memory[*PC][8];
        //Получаем адрес назначения
        for (int i = 15; i >= 0; i--) {
            address += reg[regB][i] * deg;
            deg *= 2;
        }
        //Проверяем адрес на существование
        if (address > 4095)
            error_processing(120);
        //При необходимости обновляем maxAcessAdress
        if(address>*maxAcessAdress)
            *maxAcessAdress=address;
        //Совершаем прыжок
        *PC = address;
        //Если хотя бы один из регистров ненулевой, избегаем останова. Если оба регистра нулевые, то, согласно документации, происходит останов
        if(regA!=0||regB!=0) {
            //Если регистр А ненулевой, записываем в него адрес
            if (regA != 0) {
                while (jalrAddress != 0) {
                    reg[regA][cnt] = jalrAddress % 2;
                    jalrAddress /= 2;
                    cnt--;
                }
                while (cnt >= 0) {
                    reg[regA][cnt] = 0;
                    cnt--;
                }
            }
            if(*PC==0)
                *PC+=1;
        }
    }
}

