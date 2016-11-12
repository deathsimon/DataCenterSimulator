/**********************************
 * FILE NAME: DataCenter.cpp
 *
 * DESCRIPTION: 
 **********************************/

#include "DataCenter.h"

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

void DataCenter::updateServerStatus(){
	for each (Server s in serverlist) {
		s.update();
	}
}

bool DataCenter::newContainerRequest(AppContainer * newCntr) {
	// TODO : add the container to the server chosen by resource allocator
	return false;
}


