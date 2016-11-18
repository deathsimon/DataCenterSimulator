#include "ResAllocator.h"

ResAllocator::ResAllocator(vector<Server*> *serverList) {
	svrList = serverList;
}

Server * ResAllocator::scheduleTo(AppContainer * targetContainer) {
	// TODO : return target server
	return nullptr;
}
