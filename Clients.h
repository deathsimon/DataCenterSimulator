/**********************************
 * FILE NAME: Clients.h
 *
 * DESCRIPTION:
 **********************************/
#pragma once

#include "stdincludes.h"
#include "Container.h"

 /**
  * CLASS NAME: Clients
  *
  * DESCRIPTION: the class that manages the containers.
  */
class Clients {
public:
	Clients();
	AppContainer* getNewContainer();
	void updateWorkload();
	void estimatePerf();
	void cleanSuspended();
private:
	vector<AppContainer*> containers;
	vector<AppContainer*>::iterator currContainer;
	vector<AppContainer*> newlyCreated;
};
