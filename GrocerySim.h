/*
 * Quinn Pham
 * CheckoutQueue.h
 * COMP15
 * Fall 2018
 * Interface of the GrocerySim class
 * Uses two dynamic arrays to store standard/ express queues
 */

#ifndef GROCERYSIM_H
#define GROCERYSIM_H
#include <istream>
#include <string>
#include <cstdio>
#include "shopper.h"
#include "CheckoutQueue.h"

using namespace std;

class GrocerySim
{
public:
	GrocerySim(int num_standard_queue, int num_express, int max_express);
	~GrocerySim();
	void run (istream &infile);

private:
	CheckoutQueue *std_lanes;
	CheckoutQueue *exp_lanes;
	int std; // number of standard lanes
	int exp; // number of express lanes
	int max; // max number of items for express
	int curr_time; // current time

	bool isQualified(Shopper); // if the shopper is qualified for express
	void processing(); // process item for first shopper
	void print(Shopper); // print out finished shopper
	void allocate(Shopper, int, int, int); // allocates a shopper
	void addStdShopper(Shopper); // puts the shopper in a line
	void addExpShopper(Shopper);
	bool allEmpty(); // if all lanes are empty

};

#endif