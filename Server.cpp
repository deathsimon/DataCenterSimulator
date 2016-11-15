#include "Server.h"

/**
 * Constructor of the Server class
 */
Server::Server(unsigned int cores, unsigned int memory, unsigned int bandwidth) {
	/* Set the upper-bounds */
	total_Core = cores;
	total_Memory = memory;
	total_Bandwidth = bandwidth;
	/* Set status */
	status = svr_idle;

	containers.clear();

	printf("Server up\n");
}

void Server::getCurrUsage(double *uCore, unsigned int *uMemory, double *uBandwidth){
	(*uCore) = usage_Core;
	(*uMemory) = usage_Memory;
	(*uBandwidth) = usage_Bandwidth;
}

double Server::getScore(AppContainer * targetContainer){
	// TODO : return the estimated score for accepting target container
	// -1.0 if cannot accomdate target container
	return 0.0;
}

/**
 * FUNCTION NAME: deployContainer
 *
 * DESCRIPTION: Add target container to the list. 
 *				Then re-distribute resources to all the hosted containers.
 */
void Server::deployContainer(AppContainer * targetContainer){
	containers.push_back(targetContainer);

	distributeResource();
}
/**
 * FUNCTION NAME: updateUsage
 *
 * DESCRIPTION: Update the resource usage of this server
 */
void Server::updateUsage(){
	usage_Core = 0.0;
	usage_Memory = 0;
	usage_Bandwidth = 0.0;

	/* Get the actual resource usage of each container */
	tuple<double, unsigned int, double> resources;
	for each (AppContainer* c in containers) {
		c->getResourceUsage(&resources);		
		usage_Core += std::get<hw_Core>(resources);
		usage_Memory += std::get<hw_Memory>(resources);
		usage_Bandwidth += std::get<hw_Bandwidth>(resources);
	}

	updateStatus();
}
/**
 * FUNCTION NAME: getStatus
 *
 * DESCRIPTION: Return the current status of this server
 *
 * RETURN: status
 */
int Server::getStatus() {
	return status;
}
/**
 * FUNCTION NAME: updateStatus
 *
 * DESCRIPTION: Change the status according to the current resource usage
 */
void Server::updateStatus() {
	if (containers.empty()) {
		status = svr_idle;
	}
	else if (usage_Core > total_Core 
		|| usage_Memory > total_Memory 
		|| usage_Bandwidth > total_Bandwidth) {
		status = svr_overload;
	}
	else {
		status = svr_normal;
	}
}

/**
 * FUNCTION NAME: distributeResource
 *
 * DESCRIPTION: Distribute resources to the hosted containers
 */
void Server::distributeResource(){	
	double usage_Core = 0.0;
	unsigned int usage_Memory = 0;
	double usage_Bandwidth = 0.0;

	/* First, get the actual resource usage of each container */
	tuple<double, unsigned int, double> resources;
	for each (AppContainer* c in containers)	{
		c->getResourceUsage(&resources);
		std::tie(usage_Core, usage_Memory, usage_Bandwidth) = resources;
		// TODO :
	}
	// TODO : assign resources to the containers
	// tuple<unsigned int, unsigned int, unsigned int> assignedResources = std::make_tuple(, , );
	// assignResource(assignedResources);
}

