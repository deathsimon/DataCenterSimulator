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
Clients::Clients(string tracePath, string seqFileName){
	containers.clear();
	newlyCreated.clear();
	traces.clear();
	sequence.clear();
	
	readTraces(tracePath);	
	readSequence(seqFileName);
}
/**
 * FUNCTION NAME: hasNewContainerRequest
 *
 * DESCRIPTION: Check if there are container requests at time t.
 *				If so, create containers and put into newlyCreated.
 *
 * RETURN: True if there are creation requests; else, false.
 */
bool Clients::hasNewContainerRequest(unsigned int time){
	if (get<0>(*sequence.front()) != time) {
		return false;
	}
	tuple<unsigned int, vector<unsigned int>*>* currTuple = sequence.front();
	sequence.pop_front();
	vector<unsigned int>* inputTrace = get<1>(*currTuple);
	VRChatroom *newContainer;
	for each (unsigned int t in *inputTrace) {
		newContainer = new VRChatroom();
		newContainer->setupInputs(traces[t]);
		newlyCreated.push_back(newContainer);
	}
	return true;
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
		containers.push_back(cntr_ptr);
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
 * FUNCTION NAME: readTraces
 *
 * DESCRIPTION: Read and construct the workload traces from target directory
 */
void Clients::readTraces(string dir) {
	// HACK : should parse all files in the directory
	string file_path = dir + "trace";
	string file_name;
	
	InputForVRChat *inputTrace;
	
	for (int num = 0; num < NUMTRACE; num++) {
		file_name = file_path + to_string(num);
		/* for every file, create an instance and constuct inputs*/
		inputTrace = new InputForVRChat();
		inputTrace->setupInput(file_name);
		traces.push_back(inputTrace);
	}
}

void Clients::readSequence(string filename){	
	unsigned int timestamp;
	
	vector<unsigned int>* t;
	tuple<unsigned int, vector<unsigned int>*>* workload;

	/* read workloads from file */
	ifstream infile(filename.c_str(), ios::in);
	string line;
	unsigned int w;
	while (getline(infile, line)) {
		t = new vector<unsigned int>();
			
		std::istringstream iss (line);
		iss >> timestamp;
		while (iss >> w){
			t->push_back(w);
		};		
		workload = new tuple<unsigned int, vector<unsigned int>*>(timestamp, t);
		sequence.push_back(workload);
		
	};
	infile.close();
}
