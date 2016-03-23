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

/*
 * Main function. Opens the data file and calls the simulation function.
*/ 
int main() {
	printf("Beginning simulation.\n");
	data = fopen("proj2.dat", "r");
	int i;
	for(i = 4; i < 8; i++) {
		custID = 0;
		simulation(i);
	}
	//Free anythign left in the queue (if any)
	while(queueSize(&myQueue) > 0) {
		Customer* c = removeElement(&myQueue);
		free(c);
		printf("Had to free\n");
	}
	fclose(data);
	return 0;
}

/*
 * The simulation function operates as the main function of the program.
 * It takes the number of tellers as a parameter, sets up necessary variables
 * such as the array of tellers, loop integers, and the number of available
 * tellers.
*/ 
void simulation(int numTellers) {
	currentTime = 0;			//Start at time 0
	double tellers[numTellers];		//"Tellers" for the simulation
	int i;
	for(i = 0; i < numTellers; i++) {
		tellers[i] = 0.0;		//Initialize each teller to 0
	}
	int availTellers = numTellers;		//All tellers available initially
	
	/*
 	* The loop will keep going untile the 'day' is over and nobody is
 	* in the queue and only adds customers until the end of the day.
 	*/ 
	while(currentTime < MINUTES_IN_DAY || queueSize(&myQueue) > 0) {
		//Do the if only while the doors of the bank are open
		if (currentTime < MINUTES_IN_DAY) newMinute();
		for(i = 0; i < numTellers; i++) {
			if (tellers[i] > 0.0) {
				tellers[i]--;	//As a minute goes by, subtract 1
				if(tellers[i] <= 0.0)
					availTellers++;
					//Teller available if their time is <= 0
			}
		}
		if(availTellers > 0) {
			for(i = 0;i < numTellers; i++) {
				if(tellers[i] <= 0.0 && queueSize(&myQueue) > 0){
					//Add a time to the teller and remove
					//the customer
					tellers[i] = expdist(AVG_SERVICE);
					Customer* temp = removeElement(&myQueue);
					temp->serviceTime = currentTime;
					//Add the cutomer data to the statistics
					addCustData(temp->arrivalTime, temp->serviceTime);
					free(temp); //FREE THE MEMORY
					availTellers--;//Teller is no longer free
				}
			}
		}
		//Update the number of elements in the queue to the stats
		updateWaitQueue(myQueue.numElements);
		currentTime++; //One minute passed.
	}

	//After while loop (day), report stats for that day.
	printf("Completed simulation with number of tellers: %d\n", numTellers);
	printf("Number of Customers served:\t%d\n", getCustServed());
	printf("Average wait time:\t%f\n", getAvgWaitTime());
	printf("Max wait time:\t\t%d\n", getMaxWaitTime());
	printf("Average wait size:\t%f\n", getAvgWaitSize());
	printf("Max wait size:\t\t%d\n", getMaxWaitSize());
	printf("Time took to service everyone: %d\n", currentTime);
	clearStats(); //Clear stats for next simulation.

}
/*
 * newMinute() adds a number of customers to the queue depending on rand()
 * and the data file that was loaded and pointed to by fp.
*/ 
void newMinute() {
	int r = rand() % 100; //Get a number between 1 & 100
	int chance = 0;
	int numCust = 0;
	char* delim = "\t";
	char* line = malloc(sizeof(char*));
	char* token;
	while(r > chance) {	//While the number is > the chance of having
				//that many customers come in this minute
		fgets(line, 100, data);
		token = strtok(line, delim);
		numCust = atoi(token);
		token = strtok(NULL, delim);
		chance += atoi(token);	//Re-assign chance to the new chance
	}
	rewind(data);	//Go back to the start of the file for the next minute.
	int i;
	for(i = 0; i < numCust; i++) {
		cust = malloc(sizeof(Customer));	//Make a new customer
		if(cust == NULL) {
			printf("Couldn't malloc\n");
			exit(0);
		}
		cust->cid = custID;			//Give them an ID
		custID++;
		cust->arrivalTime = currentTime;	//Set their arrival time
		cust->next = NULL;
		addElement(cust, &myQueue);		//Add them to the queue
	}
	free(line);	//Free the line
}

/*
 * Created by Professor Yonglei Tao.
 * Return a different random number than just rand().
*/
double expdist (double mean) {
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}
