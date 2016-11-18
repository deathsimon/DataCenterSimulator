#pragma once
#include "stdincludes.h"
#include "Server.h"
#include "Container.h"

class ResAllocator {
public:
	ResAllocator(vector<Server*> *serverList);
	Server* scheduleTo(AppContainer* targetContainer);
private:
	vector<Server*> *svrList;
};
