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

/**
 * CLASS NAME: Server
 *
 * DESCRIPTION:
 */
class Server {
public:	
	Server() : Server(SERVER_CORE, SERVER_MMRY, SERVER_BAND) {};
	Server(unsigned int cores, unsigned int memory, unsigned int bandwidth);	
	~Server();	
	/* fetch server information */
	void getCurrUsage(double *uCore, unsigned int *uMemory, double *uBandwidth);
	double getScore(AppContainer* targetContainer);
	/* assign target container to the server */
	void deployContainer(AppContainer* targetContainer);
	/* update the resource usage of the server*/
	void update();
	
private:
	void distributeResource();
	/* hardeare resources */
	unsigned int total_Core;
	unsigned int total_Memory;
	unsigned int total_Bandwidth;
	/* Actual usage of resources */
	double usage_Core;
	unsigned int usage_Memory;
	double usage_Bandwidth;
	/* hosting containers */
	vector<AppContainer*> containers;	
};
