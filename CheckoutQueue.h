/*
 * Quinn Pham
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 * Interface of the CheckoutQueue class
 * Built by implementing a linked list
 */

#ifndef CHECKOUTQUEUE_H
#define CHECKOUTQUEUE_H

#include "shopper.h"
#include <iostream>
using namespace std;

class CheckoutQueue
{
public:
	CheckoutQueue();
	~CheckoutQueue();

	bool isEmpty();
	int size(); // get length
	int totalItems(); // total items
	void enqueue(Shopper); // insert
	Shopper &front(); // return front
	void dequeue(); // remove

private:
	struct Node {
		Shopper s;
		Node *next;
	};

	int length;
	Node *head;
	Node *tail;


 	// void print(ostream &); move to public to use with testCheckoutQueue
	
};

#endif