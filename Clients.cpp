/**********************************
 * FILE NAME: Clients.cpp
 *
 * DESCRIPTION:
 **********************************/

#include "Clients.h"
#include "Container.h"

/**
 * Constructor of the Clients class
 */
Clients::Clients(){
	containers.clear();
	newlyCreated.clear();

	// TODO : read and store the timestamp to create new container. How?
}

AppContainer * Clients::getNewContainer() {
	AppContainer* cntr_ptr = NULL;
	if (!newlyCreated.empty()) {
		cntr_ptr = newlyCreated.back();
		newlyCreated.pop_back();
	}
	return cntr_ptr;
}


/**
 * FUNCTION NAME: updateWorkload
 *
 * DESCRIPTION: Update the workload of each container
 */
void Clients::updateWorkload(){
	for each (AppContainer *c in containers)	{
		c->updateWorkload();
	}
}
/**
 * FUNCTION NAME: estimatePerf
 *
 * DESCRIPTION: Estimate the performance / penalty of each container
 */
void Clients::estimatePerf() {	
	double peformance = 0.0;
	for each (AppContainer* c in containers) {
		peformance = c->getPerformance();
		// TODO : what do to with the performance ?
	}
}

void Clients::cleanSuspended(){
	for (currContainer = containers.begin(); currContainer != containers.end();) {
		if (!(*currContainer)->isAlive()) {
			currContainer = containers.erase(currContainer);
			continue;
		}
		currContainer++;		
	}
}
