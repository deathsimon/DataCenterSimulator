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
Clients::Clients(string filepath){
	containers.clear();
	newlyCreated.clear();
	workloads.clear();
	
	readWorkloads(filepath);
	// TODO : read and store the timestamp to create new container. How?
}

/**
 * FUNCTION NAME: getNewContainer
 *
 * DESCRIPTION: return a newly created container from the list for deployment
 *
 * RETURN: pointer to the newly created container
 */
AppContainer * Clients::getNewContainer() {
	AppContainer* cntr_ptr = nullptr;
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
/**
 * FUNCTION NAME: cleanSuspended
 *
 * DESCRIPTION: Remove the suspended container from list
 */
void Clients::cleanSuspended(){
	for (currContainer = containers.begin(); currContainer != containers.end();) {
		if (!(*currContainer)->isAlive()) {
			currContainer = containers.erase(currContainer);
			continue;
		}
		currContainer++;		
	}
}
/**
 * FUNCTION NAME: readWorkloads
 *
 * DESCRIPTION: Read and construct the workloads from target directory
 */
void Clients::readWorkloads(string dir) {
	// HACK : should parse all files in the directory
	string file_path = dir + "trace";
	string file_name;
	
	InputForVRChat *inputTrace;
	
	for (int num = 1; num <= NUMTRACE; num++) {
		file_name = file_path + to_string(num);
		/* for every file, create an instance and constuct inputs*/
		inputTrace = new InputForVRChat();
		inputTrace->setupInput(file_name);
		workloads.push_back(inputTrace);	
	}
}
