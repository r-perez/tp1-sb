prog: main.o hash.o translator.o
	gcc -o a main.o hash.o translator.o

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

translator.o: translator.c
	gcc -c translator.c

clean:
	rm *.o *.gch *~; echo "Done cleaning."
