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
	Clients client;

	DC.linkClient(&client);

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

void DataCenter::linkClient(Clients * cle){
	clients = cle;
}

void DataCenter::run() {
	// TODO : for each time period

	/* Update the requirement of each container */
	clients->updateRequirement();
	
	/* Update status of servers */
	for each (Server s in serverlist) {
		s.update();
	}

	/* Estimate the performance / penalty of each container */
	clients->estimatePerf();
	
	/* Deploy the newly created container to server */
	AppContainer* newContainer = NULL;
	while ((newContainer = clients->getNewContainer()) != NULL) {		
		// TODO : finish resAllo
		// resAllo->
	};

	/* Remove the suspended containers from list */
	clients->cleanSuspended();
}

