# This Makefile is just for testing now 


all :
	i386 i386-elf-as entry.s -o boot.o
	i386-elf-gcc -I ../include/ -Wno-implicit-fallthrough -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i386-elf-gcc -I ../include -c ../src/string.c -o ../src/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i386-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o ../src/string.o -lgcc