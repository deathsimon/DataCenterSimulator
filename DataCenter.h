/**********************************
 * FILE NAME: DataCenter.h
 *
 * DESCRIPTION: 
 **********************************/
#pragma once

#include "stdincludes.h"
#include "ResAllocator.h"
#include "Server.h"

/**
 * CLASS NAME: DataCenter
 *
 * DESCRIPTION: 
 */
class DataCenter {
public:
	DataCenter();
	~DataCenter();
	Server* bootServer();
	void updateServerStatus();
	void updateResourceDistribution();
	bool newContainerRequest(AppContainer* newCntr);

private:
	ResAllocator *resAllo;
	vector<Server> serverlist;
	vector<Server>::iterator currServer;
};
