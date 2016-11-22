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
void Server::getCurrUsage(double &uCore, double &uMemory, double &uBandwidth){
	uCore = (double) requested_Core / (double) total_Core;
	if (uCore > 1.0) { uCore = 1.0; }
	uMemory = (double) requested_Memory / (double) total_Memory;
	if (uMemory > 1.0) { uMemory = 1.0; }
	uBandwidth = (double) requested_Bandwidth / (double) total_Bandwidth;
	if (uBandwidth > 1.0) { uBandwidth = 1.0; }
}
/**
 * FUNCTION NAME: deployContainer
 *
 * DESCRIPTION: Add target container to the list. 
 *				Then re-distribute resources to all the hosted containers.
 */
void Server::deployContainer(AppContainer * targetContainer){
	containers.push_back(targetContainer);

	tuple<unsigned int, unsigned int, unsigned int> req_resources;
	targetContainer->getResourceRequirement(req_resources);
	requested_Core += get<hw_Core>(req_resources);
	requested_Memory += get<hw_Memory>(req_resources);
	requested_Bandwidth += get<hw_Bandwidth>(req_resources);

	updateStatus();
}
/**
 * FUNCTION NAME: updateUsage
 *
 * DESCRIPTION: Update the resource usage of this server
 */
void Server::updateUsage(){
	requested_Core = 0;
	requested_Memory = 0;
	requested_Bandwidth = 0;

	/* Get the resource assigned to each container */
	tuple<unsigned int, unsigned int, unsigned int> resources;
	for each (AppContainer* c in containers) {
		c->getResourceAssigned(resources);
		requested_Core += get<hw_Core>(resources);
		requested_Memory += get<hw_Memory>(resources);
		requested_Bandwidth += get<hw_Bandwidth>(resources);
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
	else if (requested_Core > total_Core
		|| requested_Memory > total_Memory
		|| requested_Bandwidth > total_Bandwidth) {
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
	unsigned int used_Core = 0;
	unsigned int used_Memory = 0;
	unsigned int used_Bandwidth = 0;

	(requested_Core >= total_Core) ? (used_Core = total_Core) : (used_Core = requested_Core);
	(requested_Memory >= total_Memory) ? (used_Memory = total_Memory) : (used_Memory = requested_Memory);
	(requested_Bandwidth >= total_Bandwidth) ? (used_Bandwidth = total_Bandwidth) : (used_Bandwidth = requested_Bandwidth);

	/* Assign resources to containers evenly */
	unsigned int assignCore = 0;
	unsigned int assignMemory = 0;
	unsigned int assignBandWidth = 0;
	tuple<unsigned int, unsigned int, unsigned int> req_resources;
	for each (AppContainer* c in containers) {		
		c->getResourceRequirement(req_resources);
		assignCore = round(get<hw_Core>(req_resources) * (used_Core / requested_Core));
		assignMemory = round(get<hw_Memory>(req_resources) * (used_Memory / requested_Memory));
		assignBandWidth = round(get<hw_Bandwidth>(req_resources) * (used_Bandwidth / requested_Bandwidth));

		tuple<unsigned int, unsigned int, unsigned int> assignedResources = std::make_tuple(assignCore, assignMemory, assignBandWidth);
		c->assignResource(assignedResources);
	}
}

