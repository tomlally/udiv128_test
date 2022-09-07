#!/bin/bash

nasm nasm.asm -g -Fdwarf -f elf64
g++ -O3 -c main.cpp
g++ main.o nasm.o
