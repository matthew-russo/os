#!/bin/bash

./compiler/run/i686-elf/bin/as boot.s -o boot.o
./compiler/run/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
./compiler/run/bin/i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
