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
void Server::getCurrUsage(tuple<double, double, double>& resource){	
	double uCore = (double) requested_Core / (double) total_Core;
	if (uCore > 1.0) { uCore = 1.0; }
	double uMemory = (double) requested_Memory / (double) total_Memory;
	if (uMemory > 1.0) { uMemory = 1.0; }
	double uBandwidth = (double) requested_Bandwidth / (double) total_Bandwidth;
	if (uBandwidth > 1.0) { uBandwidth = 1.0; }

	resource = std::make_tuple(uCore, uMemory, uBandwidth);
}
/**
 * FUNCTION NAME: getResourceRemain
 *
 * DESCRIPTION: Get the amount of the remaining resources on the server
 *
 * RETURN: True if all the resources have remaining; else, False.
 */
bool Server::getResourceRemain(tuple<unsigned int, unsigned int, unsigned>& rem_resource){
	unsigned int rem_core = 0;
	unsigned int rem_memory = 0;
	unsigned int rem_bandwidth = 0;
	bool hasRemaining = true;

	(requested_Core < total_Core) ? (rem_core = total_Core - requested_Core) : (hasRemaining &= false);
	(requested_Memory < total_Memory) ? (rem_memory = total_Memory - requested_Memory) : (hasRemaining &= false);
	(requested_Bandwidth < total_Bandwidth) ? (rem_bandwidth = total_Bandwidth - requested_Bandwidth) : (hasRemaining &= false);

	rem_resource = std::make_tuple(rem_core, rem_memory, rem_bandwidth);

	return hasRemaining;
}
/**
 * FUNCTION NAME : getTotalResource
 *
 * DESCRIPTION : Get the total amount of each resource
 */
 void Server::getTotalResource(tuple<unsigned int, unsigned int, unsigned>& resource) {
	 resource = std::make_tuple(total_Core, total_Memory, total_Bandwidth);
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

	/* Get the resource requested by the containers */
	tuple<unsigned int, unsigned int, unsigned int> resources;
	for each (AppContainer* c in containers) {
		c->getResourceRequirement(resources);
		requested_Core += get<hw_Core>(resources);
		requested_Memory += get<hw_Memory>(resources);
		requested_Bandwidth += get<hw_Bandwidth>(resources);
	}
	updateStatus();
}

bool Server::removeSuspend() {
	bool removed = false;
	vector<AppContainer*>::iterator it;
	for (it = containers.begin(); it != containers.end();) {
		if (!(*it)->isAlive()) {
			it = containers.erase(it);
			removed = true;
			continue;
		}
		it++;
	}

	return removed;
}
/**
 * FUNCTION NAME: getLongestUpTime
 *
 * DESCRIPTION: Return the exsisting time of the earliest started container on the server
 *
 * RETURN: time t
 */
 unsigned int Server::getLongestUpTime() {
	 unsigned int t = 0;
	 for each (AppContainer* c in containers) {
		 if ( t < c->getUpTime() ) {
			 t = c->getUpTime();
		 }
	 }
	 return t;
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
		assignCore = (unsigned int)lround(get<hw_Core>(req_resources) * (used_Core / requested_Core));
		assignMemory = (unsigned int)lround(get<hw_Memory>(req_resources) * (used_Memory / requested_Memory));
		assignBandWidth = (unsigned int)lround(get<hw_Bandwidth>(req_resources) * (used_Bandwidth / requested_Bandwidth));

		tuple<unsigned int, unsigned int, unsigned int> assignedResources = std::make_tuple(assignCore, assignMemory, assignBandWidth);
		c->assignResource(assignedResources);
	}
}

