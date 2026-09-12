#!/bin/bash
gcc greet.c
strace -o LOG ./a.out Vladyslav
wc -l LOG

gcc -static greet.c -o a
strace -o LOG ./a Vladyslav
wc -l LOG
