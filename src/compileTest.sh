#!/bin/bash

gcc -o prog -g -Wall file.c  file.h  main.c  symbols.c  symbols.h  translator.c  translator.h  utility.c  utility.h;
valgrind --leak-check=full ./prog;
