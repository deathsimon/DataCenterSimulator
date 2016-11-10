/**********************************
 * FILE NAME: DataCenterSimulator.cpp
 *
 * DESCRIPTION: 
 **********************************/

#include "DataCenter.h"

 /**********************************
 * FUNCTION NAME: main
 *
 * DESCRIPTION: main function. Start from here
 **********************************/
int main() {

	DataCenter DC;

	DC.run();

	return 1;
}

/**
 * Constructor of the DataCenter class
 */
DataCenter::DataCenter(){	
	/* add a resource allocator*/
	resAllo = new ResAllocator();

	/* initialize server list */
	serverlist.clear();
	Server firstServer;
	serverlist.push_back(firstServer);

	printf("Hello World!\n");
}

/**
 * Destructor
 */
DataCenter::~DataCenter() {
	serverlist.clear();
}

void DataCenter::run() {
	// [TODO] for each time period:
	// First, update the requirement of each container
	
	// Then, update status of servers

	// Handle the newly created containers

	// Last, collect the performance and penalty from all containers
}

