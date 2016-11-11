/**********************************
* FILE NAME: DataCenterSimulator.h
*
* DESCRIPTION: 
**********************************/
#pragma once

#include "stdincludes.h"
#include "Clients.h"
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
	void linkClient(Clients *cle);
	void run();

private:
	Clients *clients;
	ResAllocator *resAllo;
	vector<Server> serverlist;
	vector<Server>::iterator currServer;
};
