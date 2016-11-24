/**********************************
 * FILE NAME: Server.h
 *
 * DESCRIPTION:
 **********************************/
#pragma once

#include "stdincludes.h"
#include "Container.h"

// Marcos
#define SERVER_CORE	16
#define SERVER_MMRY	10240
#define SERVER_BAND	1024

enum hardwareResource {
	hw_Core = 0, hw_Memory = 1, hw_Bandwidth = 2
};
enum serverStatus {
	svr_idle, svr_normal, svr_overload
};

/**
 * CLASS NAME: Server
 *
 * DESCRIPTION:
 */
class Server {
public:	
	Server() : Server(SERVER_CORE, SERVER_MMRY, SERVER_BAND) {};
	Server(unsigned int cores, unsigned int memory, unsigned int bandwidth);	
	/* fetch server information */
	void getCurrUsage(double &uCore, double &uMemory, double &uBandwidth);
	bool getResourceRemain(tuple<unsigned int, unsigned int, unsigned> &rem_resource);
	void getTotalResource(tuple<unsigned int, unsigned int, unsigned> &resource);
	int getStatus();
	/* assign target container to the server */
	void deployContainer(AppContainer* targetContainer);
	void distributeResource();
	/* update the resource usage of the server*/
	void updateUsage();

	unsigned int getLongestUpTime();

private:
	void updateStatus();	
	/* hardware resources */
	unsigned int total_Core;
	unsigned int total_Memory;
	unsigned int total_Bandwidth;
	/* resources required by the containers */
	unsigned int requested_Core = 0;
	unsigned int requested_Memory = 0;
	unsigned int requested_Bandwidth = 0;
	/* Server status */
	unsigned int status;
	/* hosting containers */
	vector<AppContainer*> containers;	
};
