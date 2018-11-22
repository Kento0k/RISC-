.PHONY: all clean

all: RISC.exe

RISC.exe : main.o errors.o file_parser.o execute.o write_to_memory.o run.o debug.o
	g++ -o RISC main.o errors.o file_parser.o execute.o write_to_memory.o run.o debug.o

main.o : main.cpp
	g++ -c -o main.o main.cpp

errors.o : errors.cpp
	g++ -c -o errors.o errors.cpp

file_parser.o : file_parser.cpp   
	g++ -c -o file_parser.o file_parser.cpp

write_to_memory.o : write_to_memory.cpp   
	g++ -c -o write_to_memory.o write_to_memory.cpp

run.o : run.cpp
	g++ -c -o run.o run.cpp

debug.o : debug.cpp
	g++ -c -o debug.o debug.cpp

clean :
	del *.o