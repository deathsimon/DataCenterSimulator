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
	void updateServerResReq();
	void DistributeResource();
	bool newContainerRequest(AppContainer* newCntr);
	void statusReport();
	void CountServer();
	void CalculateUsage();
	void cleanSuspended();

private:

	void getUsage(vector<double> &seq, enum hardwareResource r);
	void getStatics(vector<double> &seq, tuple<double, double, double> &statics);

	ResAllocator *resAllo;
	vector<Server*> serverlist;
	vector<Server*>::iterator currServer;	
};
