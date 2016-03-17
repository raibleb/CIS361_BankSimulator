#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Customer {
	int cid;		//Customer ID
	int arrivalTime;	//Time entered queue
	int serviceTime;	//Time left queue
	int leaveTime;		//Time done serviced
	int totalTime;		//Total time at the bank
	struct Customer* next;	//Next customer in line
} Customer;

typedef struct Queue {
	Customer* head;		//Customer at the front of the queue
	int numElements;	//Number of customers in queue
} Queue;

void addElement(Customer c, Queue q);		//Add a customer to the queue
Customer removeElement(Queue q);		//Remove & return the head
int queueSize(Queue q);				//Return size of the given queue
