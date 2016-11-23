/**********************************
 * FILE NAME: simulator.h
 *
 * DESCRIPTION: 
 **********************************/
#include "stdincludes.h"
#include "DataCenter.h"
#include "Clients.h"

#define	SUCCESS	0
#define FAILURE	-1
#define SIMUTIME	10

/**********************************
 * FUNCTION NAME: main
 *
 * DESCRIPTION: main function. Start from here
 **********************************/
int main(int argc, char* argv[]) {

	if (argc < 3) {
		fprintf(stderr, "Not enough arguments\n");
		return FAILURE;
	}
	
	DataCenter DC;
	Clients client(argv[1], argv[2]);
		
	// HACK : improvement required
	for (int time = 1; time < SIMUTIME; time++) {
		/* Update the workload of each container */
		client.updateWorkload();
						
		/* Update the resource requirement of each server */
		DC.updateServerResReq();

		/* Distribution resources of each server to the containers*/
		DC.DistributeResource();

		/* Estimate the performance / penalty of each container */
		client.estimatePerf();

		/* Check if there are new container requests */
		if (client.hasNewContainerRequest(time)) {
			/* Deploy the newly created container to server */
			AppContainer* newCntr = nullptr;
			while ((newCntr = client.getNewContainer()) != nullptr) {
				DC.newContainerRequest(newCntr);
			};
		}
				
		/* Remove the suspended containers from list */
		client.cleanSuspended();

	}

	return SUCCESS;
 }