prog: Main.o File.o TableOfSymbols.o Translator.o Converter.o
	gcc -o prog Main.o File.o TableOfSymbols.o Translator.o Converter.o -Wall

Main.o: Main.c
	gcc -c Main.c

Converter.o: Converter.c
	gcc -c Converter.c

File.o: File.c
	gcc -c File.c

TableOfSymbols.o: TableOfSymbols.c
	gcc -c TableOfSymbols.c

Translator.o: Translator.c
	gcc -c Translator.c

clean:
	rm *.o *.gch *~ vgcore*; echo "Done cleaning."
