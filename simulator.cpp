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
#define SIMUTIME	1

/**********************************
 * FUNCTION NAME: main
 *
 * DESCRIPTION: main function. Start from here
 **********************************/
int main(int argc, char* argv[]) {

	if (argc < 2) {
		fprintf(stderr, "Workload directory required\n");
		return FAILURE;
	}
	
	DataCenter DC;
	Clients client(argv[1]);
		
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

		/* Update the resource distribution of servers */
		DC.updateResourceDistribution();

		/* Remove the suspended containers from list */
		client.cleanSuspended();

	}

	return SUCCESS;
}