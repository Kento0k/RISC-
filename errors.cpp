#include "RiscEmulatorLibrary.h"
using namespace std;
void RISC::error_processing(int code){
    printf("Error %d: ", code);
    if (code==10){
        cout<<"Wrong number of arguments in command line"<<endl;
    }
    else if (code==20){
        cout<<"File doesn`t exist"<<endl;
    }
    else if (code==30){
        cout<<"Wrong command"<<endl;
    }
    else if (code==40){
        cout<<"Cannot allocate memory"<<endl;
    }
    else if (code==50){
        cout<<"Unacceptable symbol in line"<<endl;
    }
    else if (code==60){
        cout<<"Line is too long"<<endl;
    }
    else if (code==70){
        cout<<"Unacceptable command in line"<<endl;
    }
    else if (code==80){
        cout<<"Unacceptable argument in line\n"<<endl;
    }
    else if (code==90){
        cout<<"Unacceptable number of arguments in line"<<endl;
    }
    else if (code==100){
        cout<<"Unacceptable register"<<endl;
    }
    else if (code==110){
        cout<<"Unacceptable immediate"<<endl;
    }
    else if (code==120){
        cout<<"Out of bounds memory"<<endl;
    }
    else if (code==130){
        cout<<"Out of bounds adress"<<endl;
    }
    else if (code==140){
        cout<<"File is empty"<<endl;
    }
    cout<<"Press any button..."<<endl;
    getchar();
    exit(code);
}





