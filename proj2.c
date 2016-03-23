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

void simulation(int numTellers);
void newMinute();
double expdist(double mean);

FILE* data;
Queue myQueue;
Customer* cust;
int custID, currentTime;

int main() {
	printf("Beginning simulation.\n");
	data = fopen("proj2.dat", "r");
	int i;
	for(i = 4; i < 8; i++) {
		custID = 0;
		simulation(i);
	}
	while(queueSize(&myQueue) > 0) {
		Customer* c = removeElement(&myQueue);
		free(c);
		printf("Had to free\n");
	}
	fclose(data);
	return 0;
}

void simulation(int numTellers) {
	currentTime = 0;
	double tellers[numTellers];
	int i;
	for(i = 0; i < numTellers; i++) {
		tellers[i] = 0.0;
	}
	int availTellers = numTellers;
	while(currentTime < MINUTES_IN_DAY || queueSize(&myQueue) > 0) {
		if (currentTime < MINUTES_IN_DAY) newMinute();
		for(i = 0; i < numTellers; i++) {
			if (tellers[i] > 0.0) {
				tellers[i]--;
				if(tellers[i] <= 0.0)
					availTellers++;
			}
		}
		if(availTellers > 0) {
			for(i = 0;i < numTellers; i++) {
				if(tellers[i] <= 0.0 && queueSize(&myQueue) > 0){
					tellers[i] = expdist(AVG_SERVICE);
					Customer* temp = removeElement(&myQueue);
					temp->serviceTime = currentTime;
					addCustData(temp->arrivalTime, temp->serviceTime);
					free(temp);
					availTellers--;
				}
			}
		}
		updateWaitQueue(myQueue.numElements);
		currentTime++;
	}

	printf("Completed simulation with number of tellers: %d\n", numTellers);
	printf("Number of Customers served:\t%d\n", getCustServed());
	printf("Average wait time:\t%f\n", getAvgWaitTime());
	printf("Max wait time:\t\t%d\n", getMaxWaitTime());
	printf("Average wait size:\t%f\n", getAvgWaitSize());
	printf("Max wait size:\t\t%d\n", getMaxWaitSize());
	clearStats();

}
/*
 * newMinute() adds a number of customers to the queue depending on rand()
 * and the data file that was loaded and pointed to by fp.
*/ 
void newMinute() {
	int r = rand() % 100;
	int chance = 0;
	int numCust = 0;
	char* delim = "\t";
	char* line = malloc(sizeof(char*));
	char* token;
	while(r > chance) {
		fgets(line, 100, data);
		token = strtok(line, delim);
		numCust = atoi(token);
		token = strtok(NULL, delim);
		chance += atoi(token);
	}
	rewind(data);
	int i;
	for(i = 0; i < numCust; i++) {
		cust = malloc(sizeof(Customer));
		if(cust == NULL) {
			printf("Couldn't malloc\n");
			exit(0);
		}
		cust->cid = custID;
		custID++;
		cust->arrivalTime = currentTime;
		cust->next = NULL;
		addElement(cust, &myQueue);
	}
}

double expdist (double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}
