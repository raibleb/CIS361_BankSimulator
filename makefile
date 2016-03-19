all:
	gcc -Wall queue.h
	gcc -Wall -fsyntax-only queue.c
	gcc -Wall stats.h
	gcc -Wall -fsyntax-only stats.c
