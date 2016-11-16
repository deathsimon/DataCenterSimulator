/**********************************
 * FILE NAME: Clients.h
 *
 * DESCRIPTION:
 **********************************/
#pragma once

#include "stdincludes.h"
#include "Container.h"

#define	NUMTRACE	2

 /**
  * CLASS NAME: Clients
  *
  * DESCRIPTION: the class that manages the containers.
  */
class Clients {
public:	
	Clients(string filepath);
	AppContainer* getNewContainer();
	void updateWorkload();
	void estimatePerf();
	void cleanSuspended();
private:
	void readWorkloads(string dir);
	vector<AppContainer*> containers;
	vector<AppContainer*>::iterator currContainer;
	vector<AppContainer*> newlyCreated;

	vector<ContainerInput*> workloads;
};
