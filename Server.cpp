#include "Server.h"

/**
 * Constructor of the Server class
 */
Server::Server(unsigned int cores, unsigned int memory, unsigned int bandwidth) {
	/* Set the upper-bounds */
	total_Core = cores;
	total_Memory = memory;
	total_Bandwidth = bandwidth;

	containers.clear();
}
/**
 * Destructor
 */
Server::~Server() {
	containers.clear();

	printf("Server shutdown\n");
}

void Server::getCurrUsage(double *uCore, unsigned int *uMemory, double *uBandwidth){
	(*uCore) = usage_Core;
	(*uMemory) = usage_Memory;
	(*uBandwidth) = usage_Bandwidth;
}

double Server::getScore(AppContainer * targetContainer){
	// [TODO] return the estimated score for accepting target container
	// -1.0 if cannot accomdate target container
	return 0.0;
}

void Server::deployContainer(AppContainer * targetContainer){
	containers.push_back(targetContainer);

	distributeResource();
}

void Server::update(){
	distributeResource();
}

void Server::distributeResource(){
	// [TODO] distribute resources to the hosting containers
	// update the current resource usage
	for each (AppContainer* c in containers)	{

	}
}

