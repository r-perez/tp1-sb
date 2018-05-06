prog: main.o file.o symbols.o translator.o utility.o
	gcc -o prog main.o file.o symbols.o translator.o utility.o -Wall -ggdb3

main.o: main.c
	gcc -c main.c

file.o: file.c
	gcc -c file.c

symbols.o: symbols.c
	gcc -c symbols.c

translator.o: translator.c
	gcc -c translator.c

utility.o: utility.c
	gcc -c utility.c

clean:
	rm *.o *.gch *~ vgcore*; echo "Done cleaning."
