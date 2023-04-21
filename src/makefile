# This makefile first converts the assembly project to a library, and then the c project is compiled with this library.

all: program

generateBuffer.o: generateBuffer.asm
	nasm -f elf64 -o generateBuffer.o generateBuffer.asm

libassembly.so: generateBuffer.o
	gcc -shared -o libassembly.so generateBuffer.o

program: socket.c libassembly.so
	gcc -o program socket.c -L. -lassembly 

.PHONY: clean
clean:
	rm -f generateBuffer.o libassembly.so program

.PHONY: run
run:
	export LD_LIBRARY_PATH=./