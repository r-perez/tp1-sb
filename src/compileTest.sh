#!/bin/bash

gcc -o prog -g -Wall File.c  File.h  Main.c  TableOfSymbols.c  TableOfSymbols.h  Translator.c  Translator.h  Converter.c  Converter.h;
valgrind --leak-check=full ./prog test.a --keepBinary;
