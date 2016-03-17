#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void addElement(Customer c, Queue q) {	
	if (queueSize(q) <= 0) {
		q.head = &c;
	} else {
		Customer* temp = q.head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = &c;
	}
	q.numElements++;
}

Customer removeElement(Queue q) {
	if (queueSize(q) > 0 && q.head != '\0') {
		Customer* temp = q.head;
		q.head = temp->next;
		q.numElements--;
		return *temp;
	}
	printf("Tried removing from empty queue. Exiting.");
	exit(1);
}

int queueSize(Queue q) {
	return q.numElements;
}
