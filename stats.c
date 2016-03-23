/*
 * stats.c
 * Brett Raible
 * CIS 361 - Project 2
 * 3/19/2016
*/

#include<stdio.h>
#include<stdlib.h>
#include"stats.h" 

static int totalCustomersServed = 0;
static double avgWaitTime = 0.0;
static int maxWaitTime = 0;
static double avgWaitSize = 0.0;
static int maxWaitSize = 0;

/*
 * Returns the total number of customers served.
*/ 
int getCustServed() {
	return totalCustomersServed;
}

/*
 * Returns the average wait time.
*/ 
double getAvgWaitTime() {
	if(totalCustomersServed > 0)
		return (avgWaitTime/((double)totalCustomersServed));
	return 0;
}

/*
 * Returns the maximum time time one customer waited.
*/ 
int getMaxWaitTime() {
	return maxWaitTime;
}

/*
 * Returns the average size of the wait queue.
*/ 
double getAvgWaitSize() {
	return (avgWaitSize/((double) MINUTES_IN_DAY));
}

/*
 * Returns the maximum size of the queue.
*/ 
int getMaxWaitSize() {
	return maxWaitSize;
}

/*
 * Adds the data given in the parameters to the variables.
 * The variables are then used for calculating numbers for
 * banks to use as data to determine how many tellers to use.
*/ 
void addCustData(int arrivalTime, int serviceTime) {
	totalCustomersServed++;
	int timeToService = serviceTime-arrivalTime;
	avgWaitTime += ((double)timeToService);
	if(timeToService > maxWaitTime)
		maxWaitTime = timeToService;
}

/*
 * Updates the variables for the average wait size and max wait
 * size (if necessary) by using the parameter, the number of
 * elements from the queue.
*/ 
void updateWaitQueue(int numElements) {
	if(numElements > maxWaitSize)
		maxWaitSize = numElements;
	avgWaitSize += numElements;
}

/*
 * Clears the stats to 0, for starting a new simulation.
*/ 
void clearStats() {
	totalCustomersServed = 0;
	avgWaitTime = 0.0;
	maxWaitTime = 0;
	avgWaitSize = 0.0;
	maxWaitSize = 0;
}
