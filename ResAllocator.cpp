#include "ResAllocator.h"

ResAllocator::ResAllocator(vector<Server*> *serverList) {
	svrList = serverList;
}

Server * ResAllocator::scheduleTo(AppContainer * targetContainer) {
	// TODO : return target server
	return nullptr;
}

/*
double Server::getScore(AppContainer * targetContainer) {
	// TODO : return the estimated score for accepting target container
	// -1.0 if cannot accomdate target container
	return 0.0;
}
*/