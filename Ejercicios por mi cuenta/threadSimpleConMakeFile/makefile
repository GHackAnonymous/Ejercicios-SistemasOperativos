all: main

main: main.o
	gcc main.o -l pthread -o mainExe

main.o:main.c
	gcc -c -Wall main.c

clean: 
	rm -f *.o

cleanAll: clean
	rm -f mainExe
