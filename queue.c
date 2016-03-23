#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

/*
 * Adds an element to the end of the queue (linked list).
 * Increments the numElements of the queue.
*/ 
void addElement(Customer* c, Queue* q) {	
	if (queueSize(q) <= 0) {
		q->head = c;
	} else {
		Customer* temp = q->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = c;
	}
	q->numElements++;
}

/*
 * Remove the head element from the queue and return
 * that element. The original head element's next
 * pointer becomes the new head element.
*/ 
Customer* removeElement(Queue* q) {
	if (queueSize(q) > 0 && q->head != '\0') {
		Customer* temp = q->head;
		q->head = temp->next;
		q->numElements--;
		return temp;
	}
	printf("Tried removing from empty queue. Exiting.");
	exit(1);
}

/*
 * Returns the size of the queue given.
*/ 
int queueSize(Queue* q) {
	return q->numElements;
}
