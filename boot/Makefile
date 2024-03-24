# This Makefile is just for testing now 


all:
	/usr/local/i386elfgcc/bin/i386-elf-as  -I ../include entry.s -o boot.o
	/usr/local/i386elfgcc/bin/i386-elf-gcc -I ../include/ -Wno-implicit-fallthrough -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	/usr/local/i386elfgcc/bin/i386-elf-gcc -I ../include -c ../src/console.c -o ../src/console.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	/usr/local/i386elfgcc/bin/i386-elf-gcc -I ../include -c ../src/string.c -o ../src/string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	/usr/local/i386elfgcc/bin/i386-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o ../src/console.o  ../src/string.o -lgcc
remove:
	rm -f boot.o
	rm -f kernel.o
	rm -f ../src/console.o
	rm -f ../src/string.o
	rm -f myos.bin
test:
	qemu-system-i386 -kernel myos.bin
