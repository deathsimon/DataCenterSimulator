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
	resAllo = new ResAllocator(&serverlist);

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
/**
 * FUNCTION NAME: bootServer
 *
 * DESCRIPTION: Create a new server and add to server list
 *
 * RETURN: address of the newly created server
 */
Server* DataCenter::bootServer() {
	Server* newServer = new Server();
	serverlist.push_back(*newServer);
	return newServer;
}
/**
 * FUNCTION NAME: updateServerStatus
 *
 * DESCRIPTION: Update the resource usage of each server
 */
void DataCenter::updateServerStatus(){
	for each (Server s in serverlist) {
		s.updateUsage();
	}
}
/**
 * FUNCTION NAME: updateResourceDistribution
 *
 * DESCRIPTION: Ask servers to redistibute their resources to containers
 */
void DataCenter::updateResourceDistribution() {
	for each (Server s in serverlist) {
		s.distributeResource();
	}
}
/**
 * FUNCTION NAME: newContainerRequest
 *
 * DESCRIPTION: Deploy the newly created container to target server chosen by the resource allocator
 */
bool DataCenter::newContainerRequest(AppContainer * newCntr) {
	Server *targetServer = resAllo->scheduleTo(newCntr);
	if(targetServer == nullptr){
		/* boot a new server */
		targetServer = bootServer();
	}
	targetServer->deployContainer(newCntr);
	targetServer->updateUsage();
	return false;
}


