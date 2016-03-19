/*
 * proj2.c
 * Brett Raible
 * CIS 361 - Project 2
 * 3/17/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stats.h"
#include "queue.h" 

#define AVG_SERVICE 2.0

int main() {
	printf("Beginning simulation.\n");
	return 0;
}

double expdist (double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

void simulation(int numOfTellers) {
	Queue myQueue;
	myQueue.numElements = 0;
}
