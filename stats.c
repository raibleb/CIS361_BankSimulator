/*
 * stats.c
 * Brett Raible
 * CIS 361 - Project 2
 * 3/19/2016
*/

#include<stdio.h>
#include<stdlib.h>
#include"stats.h" 

int totalCustomersServed = 0;
double avgWaitTime = 0.0;
int maxWaitTime = 0;
double avgWaitSize = 0.0;
int maxWaitSize = 0;

int custServed() {
	return totalCustomersServed;
}

double getAvgWaitTime() {
	if(totalCustomersServed > 0)
		return (avgWaitTime/((double)totalCustomersServed));
	return 0;
}

int getMaxWaitTime() {
	return maxWaitTime;
}

double getAvgWaitSize() {
	return (avgWaitSize/((double) MINUTES_IN_DAY));
}

int getMaxWaitSize() {
	return maxWaitSize;
}

void addCustData(int arrivalTime, int serviceTime) {
	totalCustomersServed++;
	int timeToService = serviceTime-arrivalTime;
	avgWaitTime += ((double)timeToService);
	if(timeToService > maxWaitTime)
		maxWaitTime = timeToService;
}

void updateWaitQueue(int numElements) {
	if(numElements > maxWaitSize)
		maxWaitSize = numElements;
	avgWaitSize += numElements;
}
