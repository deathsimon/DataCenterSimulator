#pragma once
#include "stdincludes.h"
#include "Server.h"
#include "Container.h"

class ResAllocator {
public:
	ResAllocator(vector<Server*> &serverList);
	virtual Server* scheduleTo(AppContainer* targetContainer) = 0;
protected:
	//virtual double getScore(Server* s, AppContainer* target) = 0;
	vector<Server*> *svrList;
	unsigned int currSvr = 0;
};

class  NextFit : public ResAllocator{
public:	
	NextFit(vector<Server*> &serverList) : ResAllocator(serverList) {};
	virtual Server* scheduleTo(AppContainer* targetContainer);
private:
	double getScore(Server* s, AppContainer* target);	
	unsigned int anchor = 0;
};

class  BestFit : public ResAllocator {
public:
	BestFit(vector<Server*> &serverList) : ResAllocator(serverList) {};
	virtual Server* scheduleTo(AppContainer* targetContainer);
private:
	double getScore(Server* s, AppContainer* target);
	double remain_ratio(unsigned int r, unsigned int c, unsigned int t);
};
