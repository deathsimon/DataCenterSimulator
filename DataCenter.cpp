/**********************************
 * FILE NAME: DataCenter.cpp
 *
 * DESCRIPTION: 
 **********************************/

#include "DataCenter.h"

/**
 * Constructor of the class DataCenter
 */
DataCenter::DataCenter(){	
	/* initialize server list */
	serverlist.clear();
	Server* firstServer = new Server();
	serverlist.push_back(firstServer);

	/* add a resource allocator*/
	resAllo = new NextFit(serverlist);

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
	Server* newServer = new Server;
	serverlist.push_back(newServer);
	return newServer;
}
/**
 * FUNCTION NAME: updateServerResReq
 *
 * DESCRIPTION: Update the resource requirement of each server
 */
void DataCenter::updateServerResReq(){
	for each (Server *s in serverlist) {
		s->updateUsage();
	}
}
/**
 * FUNCTION NAME: DistributeResource
 *
 * DESCRIPTION: Ask servers to distibute their resources to containers
 */
void DataCenter::DistributeResource() {
	for each (Server* s in serverlist) {
		if (s->getStatus() != svr_idle)	{
			s->distributeResource();
		}		
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
	return false;
}


