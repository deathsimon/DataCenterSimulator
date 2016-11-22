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
	Clients(string tracePath, string seqFileName);
	bool hasNewContainerRequest(unsigned int time);
	AppContainer* getNewContainer();
	void updateWorkload();
	void estimatePerf();
	void cleanSuspended();
private:
	void readTraces(string dir);
	void readSequence(string filename);
	vector<AppContainer*> containers;
	vector<AppContainer*>::iterator currContainer;
	vector<AppContainer*> newlyCreated;

	vector<InputForVRChat*> traces;
	deque<tuple<unsigned int, vector<unsigned int>*>*> sequence;
	unsigned int container_id = 0;
};
