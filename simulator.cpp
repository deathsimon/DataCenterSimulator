/**********************************
 * FILE NAME: simulator.h
 *
 * DESCRIPTION: 
 **********************************/
#include "stdincludes.h"
#include "DataCenter.h"
#include "Clients.h"

#define	SUCCESS	1

/**********************************
 * FUNCTION NAME: main
 *
 * DESCRIPTION: main function. Start from here
 **********************************/
int main() {

	DataCenter DC;
	Clients client;

	// TODO : for each time period

	/* Update the requirement of each container */
	client.updateRequirement();

	/* Update status of servers */
	DC.updateServerStatus();	

	/* Estimate the performance / penalty of each container */
	client.estimatePerf();

	/* Deploy the newly created container to server */
	AppContainer* newCntr = NULL;
	while ((newCntr = client.getNewContainer()) != NULL) {		
		DC.newContainerRequest(newCntr);
	};

	/* Remove the suspended containers from list */
	client.cleanSuspended();
	

	return SUCCESS;
}