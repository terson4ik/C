#!/bin/bash
gcc common/greet.c
strace -o LOG ./a.out Vladyslav
wc -l LOG

gcc -static common/greet.c
strace -o LOG ./a.out Vladyslav
wc -l LOG

gcc -static common/greet2.c
strace -o LOG ./a.out Vladyslav
wc -l LOG

nasm -f elf start.asm
nasm -f elf calls.asm
gcc -m32 -Wall -c greet3.c
ld -m elf_i386 start.o calls.o greet3.o -o greet3
strace -o LOG ./greet3 Vladyslav
wc -l LOG

rm -f LOG *.o a.out
