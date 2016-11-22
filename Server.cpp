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
/**
 * FUNCTION NAME: getCurrUsage
 *
 * DESCRIPTION: Compute the current usage (in percentage) of each resource
 */
void Server::getCurrUsage(double *uCore, double *uMemory, double *uBandwidth){
	(*uCore) = (double) assigned_Core / (double) total_Core;
	(*uMemory) = (double) assigned_Memory / (double) total_Memory;
	(*uBandwidth) = (double) assigned_Bandwidth / (double) total_Bandwidth;
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
	assigned_Core = 0;
	assigned_Memory = 0;
	assigned_Bandwidth = 0;

	/* Get the resource assigned to each container */
	tuple<unsigned int, unsigned int, unsigned int> resources;
	for each (AppContainer* c in containers) {
		c->getResourceAssigned(resources);
		assigned_Core += std::get<hw_Core>(resources);
		assigned_Memory += std::get<hw_Memory>(resources);
		assigned_Bandwidth += std::get<hw_Bandwidth>(resources);
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
	else if (assigned_Core > total_Core 
		|| assigned_Memory > total_Memory
		|| assigned_Bandwidth > total_Bandwidth) {
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
	unsigned int require_Core = 0;
	unsigned int require_Memory = 0;
	unsigned int require_BandWidth = 0;

	/* First, get the resource requirement of each container */
	tuple<unsigned int, unsigned int, unsigned int> req_resources;
	for each (AppContainer* c in containers)	{
		c->getResourceRequirement(req_resources);
		std::tie(require_Core, require_Memory, require_BandWidth) = req_resources;
		// TODO :
	}
	// TODO : assign resources to the containers
	// tuple<unsigned int, unsigned int, unsigned int> assignedResources = std::make_tuple(, , );
	// assignResource(assignedResources);
}

