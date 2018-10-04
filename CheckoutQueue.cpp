/*
 * Quinn Pham
 * CheckoutQueue.cpp
 * COMP15
 * Fall 2018
 * Implementation of the CheckoutQueue class
 * Note: Includes print to be used with testCheckoutQueue.cpp
 */

#include <iostream>
#include "CheckoutQueue.h"

using namespace std;

/*
 * Function: constructor
 * Input: none
 * Returns: none
 * Does: initializes an empty queue
 */
CheckoutQueue::CheckoutQueue()
{
	 length = 0;
	 head = NULL;
	 tail = NULL;
}

/*
 * Function: destructor
 * Input: none
 * Returns: none
 * Does: deletes the queue, liberates space
 */ 
CheckoutQueue::~CheckoutQueue()
{
	 Node *to_del = NULL;
	 Node *temp = head;

	 while (temp != NULL) {
	 	to_del = temp;
	 	temp = temp->next;
	 	delete to_del;
	 }
}

/*
 * Function: isEmpty
 * Input: none
 * Returns: boolean
 * Does: returns true if queue is empty
 */ 
bool CheckoutQueue::isEmpty()
{
	return (length == 0);
}

/*
 * Function: size
 * Input: none
 * Returns: int 
 * Does: returns the number of shoppers in the queue
 */ 
int CheckoutQueue::size()
{
	return length;
}

/*
 * Function: totalItems
 * Input: none
 * Returns: int
 * Does: returns total number of items left for all shoppers in the queue
 */ 
int CheckoutQueue::totalItems()
{
	int total = 0;
	Node *temp = head;

	while (temp != NULL) {
		total = total + temp->s.items_left;
		temp = temp->next;
	}
	
	return total;
}

/*
 * Function: enqueue
 * Input: a shopper
 * Returns: none
 * Does: adds a shopper at the end of the queue
 */ 
void CheckoutQueue::enqueue(Shopper toAdd)	
{
	// adding to the back of queue

	Node *shopper = new Node;
	shopper->s = toAdd;
	shopper->next = NULL;

	if (isEmpty()) {
		head = shopper;
		tail = shopper;
		length++;
		return;
	}

	tail->next = shopper;
	tail = shopper;
	length++;
}

/*
 * Function: front
 * Input: none
 * Returns: reference
 * Does: returns a reference to the front shopper in the queue
 * 		 throws a runtime error with "empty_queue" if queue is empty
 */ 
Shopper &CheckoutQueue::front()
{
	if (isEmpty()) {
		throw std::runtime_error("empty_queue");
	}

	return head->s;
}

/*
 * Function: dequeue
 * Input: none
 * Returns: none
 * Does: removes the front-most element of the queue
 *		 throws a runtime error with "empty_queue" if queue is empty
 */ 
void CheckoutQueue::dequeue()
{
	if (isEmpty()) {
		throw std::runtime_error("empty_queue");
	}

	Node *temp = head;
	head = head->next;
	delete temp;
	length--;	 
}

/* 
 * Function: print
 * Input: a reference to the ostream
 * Returns: nothing
 * Does: prints the queue to the ostream
 */

/*void CheckoutQueue::print(std::ostream &out)
{
    if (isEmpty()) {
        out << "List is empty!" << endl;
        return;
    }
    
    Node *to_print = head;
    int count = 1;

    while (to_print != NULL) {
    	out << count << ". ";
        out << to_print->s.id << endl;
        to_print = to_print->next;
        count++;
    }
*/



