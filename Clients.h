/**********************************
 * FILE NAME: Clients.h
 *
 * DESCRIPTION:
 **********************************/

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
	void updateRequirement();
	void estimatePerf();
	void cleanSuspended();
private:
	vector<AppContainer*> containers;
	vector<AppContainer*>::iterator currContainer;
	vector<AppContainer*> newlyCreated;
};
