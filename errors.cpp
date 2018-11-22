#include "RISCEmulatorLibrary.h"

void RISC::error_processing(int code){
    printf("Error %d: ", code);
    if (code==10){
        printf("Wrong number of arguments in command line\n");
    }
    else if (code==20){
        printf("File doesn`t exist\n");
    }
    else if (code==30){
        printf("Wrong command\n");
    }
    else if (code==40){
        printf("Cannot allocate memory\n");
    }
    else if (code==50){
        printf("Unacceptable symbol in line\n");
    }
    else if (code==60){
        printf("Line is too long\n");
    }
    else if (code==70){
        printf("Unacceptable command in line\n");
    }
    else if (code==80){
        printf("Unacceptable argument in line\n");
    }
    else if (code==90){
        printf("Unacceptable number of arguments in line\n");
    }
    else if (code==100){
        printf("Unacceptable register\n");
    }
    else if (code==110){
        printf("Unacceptable immediate\n");
    }
    else if (code==120){
        printf("Out of bounds memory\n");
    }
    else if (code==130){
        printf("Out of bounds adress\n");
    }
    else if (code==140){
        printf("File is empty\n");
    }
    printf("Press any button...\n");
    getchar();
    exit(code);
}





