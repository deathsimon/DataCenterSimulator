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
private:
	ResAllocator *resAllo;
	vector<Server> serverlist;
public:
	DataCenter();
	~DataCenter();
	void run();
};
