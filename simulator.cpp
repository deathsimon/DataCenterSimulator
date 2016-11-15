/**********************************
 * FILE NAME: simulator.h
 *
 * DESCRIPTION: 
 **********************************/
#include "stdincludes.h"
#include "DataCenter.h"
#include "Clients.h"

#define	SUCCESS	1
#define SIMUTIME	1

/**********************************
 * FUNCTION NAME: main
 *
 * DESCRIPTION: main function. Start from here
 **********************************/
int main() {

	DataCenter DC;
	Clients client;
	
	// HACK : improvement required
	for (int time = 0; time < SIMUTIME; time++) {
		/* Update the workload of each container */
		client.updateWorkload();

		/* Estimate the performance / penalty of each container */
		client.estimatePerf();

		/* Update status of servers */
		DC.updateServerStatus();

		/* Deploy the newly created container to server */
		AppContainer* newCntr = NULL;
		while ((newCntr = client.getNewContainer()) != NULL) {
			DC.newContainerRequest(newCntr);
		};

		/* Remove the suspended containers from list */
		client.cleanSuspended();

	}

	return SUCCESS;
}