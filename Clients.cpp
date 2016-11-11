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

void Clients::updateRequirement(){
	for each (AppContainer *c in containers)	{
		c->run();
	}
}

void Clients::estimatePerf() {
	// estimate the performance / penalty of each container
	for each (AppContainer* c in containers) {
		// TODO : collect the perfomance. How?
		// c->
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
