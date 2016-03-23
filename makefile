all:
	gcc -Wall queue.h
	gcc -Wall -fsyntax-only queue.c
	gcc -Wall stats.h
	gcc -Wall -fsyntax-only stats.c
	gcc -Wall proj2.c queue.c stats.c -o proj2.o -lm
