/*
 * Quinn Pham
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 * Interface of the GrocerySim class
 */


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include "GrocerySim.h"
#include "CheckoutQueue.h"
#include "shopper.h"

using namespace std;

/*
 * Function: parametized constructor
 * Input: int standard checkout lines
 *		  int express checkout lines
 *		  int max items
 * Returns: none
 * Does: initializes the object to the provided values
 */ 
GrocerySim::GrocerySim(int num_std, int num_express, int max_express)
{
	std = num_std;
	exp = num_express;
	max = max_express;

	std_lanes = new CheckoutQueue[std];
	exp_lanes = new CheckoutQueue[exp];

	curr_time = 1;
}

/*
 * Function: destructor
 * Input: none
 * Returns: none
 * Does: deletes the structures and liberates memory
 */ 
GrocerySim::~GrocerySim()
{
	 delete [] std_lanes;
	 delete [] exp_lanes;
}

/*
 * Function: run
 * Input: reference to an istream
 * Returns: none
 * Does: reads the shopper details, assigns them to lanes, and
 *		 runs the simulated lanes
 */ 
void GrocerySim::run(istream &infile)
{	
	 int time, items;
	 int count = 1;
	 // var for whether a new shopper has arrived yet
	 bool buffer = false; // true if curr_time != time

	 while (infile) {
	 	processing(); 
	 	if (buffer == false) {
	 		infile >> time >> items;
	 		if (curr_time == time) {
	 			Shopper s;
	 			allocate(s, count, time, items);
	 			count++;
	 		}
	 		else {
	 			buffer = true;
	 		}
	 	}
	 	else { //buffer == true 
	 		if (curr_time == time) { // check again
	 			buffer = false;
	 			Shopper s;
	 			allocate(s, count, time, items);
	 			count++; 
	 		} // else buffer still true
	 	}
	 	curr_time++;
	 }

	 while (not allEmpty()) { // all shoppers are in lines
	 	processing();		  // but input has ended
	 	curr_time++;
	 }
}

/*
 * Function: isQualified
 * Input: none
 * Returns: boolean value
 * Does: checks whether the shopper is qualified for express
 */ 
bool GrocerySim::isQualified(Shopper s) {
	return (s.num_items <= max);
}

/*
 * Function: processing
 * Input: none
 * Returns: none
 * Does: process one item for the first shopper in each lane
 * 		 prints the shopper if no more items remaining
 */ 
void GrocerySim::processing() {
	for (int i = 0; i < std; i++) {
		if (not std_lanes[i].isEmpty()) {
			Shopper &s = std_lanes[i].front();
			s.items_left = s.items_left - 1;
			if (s.items_left == 0) {
				print(s);
				std_lanes[i].dequeue();
			}
		}
	}

	for (int i = 0; i < exp; i++) {
		if (not exp_lanes[i].isEmpty()) {
			Shopper &s = exp_lanes[i].front();
			s.items_left = s.items_left - 1;
			if (s.items_left == 0) {
				print(s);
				exp_lanes[i].dequeue();
			}
		}
	}
}

/*
 * Function: print
 * Input: a Shopper
 * Returns: none
 * Does: prints the finished shopper
 */ 
void GrocerySim::print(Shopper s) {
	cout << "Shopper " << s.id << " arrived at " << s.arrival_time << 
		 " with " << s.num_items << ", took " 
         << curr_time - s.arrival_time << " units" << endl;
}

/*
 * Function: allocate
 * Input: a Shopper, an int (count, and int (time) and an int (items)
 * Returns: none
 * Does: adds info to the shopper and allocates them
 */ 
void GrocerySim::allocate(Shopper s, int x, int y, int z) {
	s = {x, y, z, z};
	// check where to put shopper
	if (isQualified(s)) {
		addExpShopper(s);
 	}
	else {
		addStdShopper(s);
	}
}
/*
 * Function: addStdShopper
 * Input: a Shopper
 * Returns: none
 * Does: adds a standard shopper to the shortest standard line
 */ 
 void GrocerySim::addStdShopper(Shopper s) {
 	int min_pos = 0;
 	for (int i = 1; i < std; i++) {
 		if (std_lanes[i].totalItems() 
 			< std_lanes[min_pos].totalItems()) {
			min_pos = i;
		}
	}		
	std_lanes[min_pos].enqueue(s);
}

/*
 * Function: addExpShopper
 * Input: a Shopper
 * Returns: none
 * Does: adds an express shopper to the shortest line
 */ 
 void GrocerySim::addExpShopper(Shopper s) {
	int min_std = 0;
 	for (int i = 1; i < std; i++) {
		if (std_lanes[i].totalItems() 
			< std_lanes[min_std].totalItems()) {
			min_std = i;
		}
	}
	int min_exp = 0;
	for (int i = 1; i < exp; i++) {
		if (exp_lanes[i].totalItems() 
			< exp_lanes[min_exp].totalItems()) {
			min_exp = i;
		}
	}

	if (exp_lanes[min_exp].totalItems() 
		< std_lanes[min_std].totalItems()) {
		exp_lanes[min_exp].enqueue(s);
	}
	else {
		std_lanes[min_std].enqueue(s);
	}
 }

/*
 * Function: allEmpty
 * Input: none
 * Returns: a boolean value
 * Does: checks if all lanes are empty
 */ 
 bool GrocerySim::allEmpty() {
 	for (int i = 0; i < std; i++) {
		if (not std_lanes[i].isEmpty()) {
			return false;
		}
	}

	for (int i = 0; i < exp; i++) {
		if (not exp_lanes[i].isEmpty()) {
			return false;
		}
	}

	return true;
}
