/**********************************
 * FILE NAME: DataCenter.cpp
 *
 * DESCRIPTION: 
 **********************************/

#include "DataCenter.h"

/**
 * Constructor of the class DataCenter
 */
DataCenter::DataCenter(){	
	/* initialize server list */
	serverlist.clear();
	Server* firstServer = new Server();
	serverlist.push_back(firstServer);

	/* add a resource allocator*/
	//resAllo = new NextFit(serverlist);
	//resAllo = new BestFit(serverlist);
	//resAllo = new WorstFit(serverlist);
	resAllo = new AgeBased(serverlist);
	
	printf("Hello World!\n");
}

/**
 * Destructor
 */
DataCenter::~DataCenter() {
	serverlist.clear();
}
/**
 * FUNCTION NAME: bootServer
 *
 * DESCRIPTION: Create a new server and add to server list
 *
 * RETURN: address of the newly created server
 */
Server* DataCenter::bootServer() {
	Server* newServer = new Server;
	serverlist.push_back(newServer);
	return newServer;
}
/**
 * FUNCTION NAME: updateServerResReq
 *
 * DESCRIPTION: Update the resource requirement of each server
 */
void DataCenter::updateServerResReq(){
	for each (Server *s in serverlist) {
		s->updateUsage();
	}
}
/**
 * FUNCTION NAME: DistributeResource
 *
 * DESCRIPTION: Ask servers to distibute their resources to containers
 */
void DataCenter::DistributeResource() {
	for each (Server* s in serverlist) {
		if (s->getStatus() != svr_idle)	{
			s->distributeResource();
		}		
	}
}
/**
 * FUNCTION NAME: newContainerRequest
 *
 * DESCRIPTION: Deploy the newly created container to target server chosen by the resource allocator
 */
bool DataCenter::newContainerRequest(AppContainer * newCntr) {
	Server *targetServer = resAllo->scheduleTo(newCntr);
	if(targetServer == nullptr){
		/* boot a new server */
		targetServer = bootServer();		
	}
	targetServer->deployContainer(newCntr);		
	return false;
}

void DataCenter::statusReport() {
	CountServer();
	CalculateUsage();
}

void DataCenter::CountServer() {
	unsigned int idleServers = 0;
	for each (Server* s in serverlist) {
		if (s->getStatus() == svr_idle) {
			idleServers++;
		}
	}
	unsigned int nonIdleServer = serverlist.size() - idleServers;
	fprintf(stdout, "Servers\t%d %d %d\n", serverlist.size(), nonIdleServer, idleServers);
}

void DataCenter::CalculateUsage() {
	vector<double> seq;
	tuple<double, double, double> statics;
		
	// HACK
	seq.clear();
	getUsage(seq, hw_Core);
	getStatics(seq, statics);
	fprintf(stdout, "CPU\t%.2lf\t%.2lf\t%.2lf\n", std::get<0>(statics), std::get<1>(statics), std::get<2>(statics));

	seq.clear();
	getUsage(seq, hw_Memory);
	getStatics(seq, statics);
	fprintf(stdout, "Memory\t%.2lf\t%.2lf\t%.2lf\n", std::get<0>(statics), std::get<1>(statics), std::get<2>(statics));

	seq.clear();
	getUsage(seq, hw_Bandwidth);
	getStatics(seq, statics);
	fprintf(stdout, "Network\t%.2lf\t%.2lf\t%.2lf\n", std::get<0>(statics), std::get<1>(statics), std::get<2>(statics));
}

void DataCenter::getUsage(vector<double> &seq, hardwareResource r){
	tuple<double, double, double> resource;
	double tmp;	

	for each (Server* s in serverlist) {
		if (s->getStatus() != svr_idle) {
			s->getCurrUsage(resource);
			// HACK
			switch (r) {
			case hw_Core:
				tmp = std::get<hw_Core>(resource);
				break;
			case hw_Memory:
				tmp = std::get<hw_Memory>(resource);
				break;
			case hw_Bandwidth:
				tmp = std::get<hw_Bandwidth>(resource);
				break;
			default:
				tmp = -1;
				break;
			}
			seq.push_back(tmp);
		}
	}	
}

void DataCenter::getStatics(vector<double> &seq, tuple<double, double, double>& statics) {
	double sum = 0.0;
	double avg = 0.0;
	double var = 0.0;
	double std = 0.0;

	if (seq.size() != 0) {
		for each (double num in seq) {
			sum += num;
		}
		avg = sum / seq.size();

		for each (double num in seq) {
			var += ((num - avg) * (num - avg));
		}
		var /= seq.size();
		std = sqrt(var);
	}
	statics = std::make_tuple(avg, var, std);
}




