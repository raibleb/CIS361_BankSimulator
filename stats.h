/*
 * stats.h
 * Brett Raible
 * CIS 361 - Project 2
 * 3/17/2016
*/

#include<stdio.h>
#include<stdlib.h>

#define MINUTES_IN_DAY	480

int getCustServed();		//Return the number of customers served
double getAvgWaitTime();	//Return the average time a customer waited in line
int getMaxWaitTime();		//Return the max time a customer waited in line
double  getAvgWaitSize();	//Return the average size of the queue
int getMaxWaitSize();		//Return the max size of the queue;

void addCustData(int arrivalTime, int serviceTime);	
void updateWaitQueue(int numElements);
