/**********************************
* FILE NAME: DataCenterSimulator.h
*
* DESCRIPTION: 
**********************************/

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
	void run();

private:
	ResAllocator *resAllo;
	vector<Server> serverlist;
	vector<Server>::iterator currServer;
};
