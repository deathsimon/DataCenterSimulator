#include "ResAllocator.h"

/**
 * Constructor of the class ResAllocator
 */
ResAllocator::ResAllocator(vector<Server*> &serverList) {
	svrList = &serverList;	
}
/**
 * FUNCTION NAME: scheduleTo
 *
 * DESCRIPTION: choose the server for target container using Next-Fit.
 *				Next-Fit find the next server in the server lis that can accommodate target server.
 * 
 * RETRUNE:	target server if found; else, a nutllptr is returned.
 */
Server * NextFit::scheduleTo(AppContainer * targetContainer) {
	Server *targetServer = nullptr;

	if (!svrList->empty()) {
		anchor = currSvr;
		while (true) {
			if (getScore((*svrList)[currSvr], targetContainer) > 0) {
				targetServer = (*svrList)[currSvr];
				break;
			}
			currSvr = (currSvr + 1) % svrList->size();
			if (anchor == currSvr) {
				// cannot find a feasible server
				break;
			}
		};
	}
	return targetServer;
}
/**
 * FUNCTION NAME: getScore
 *
 * DESCRIPTION: the score of the server for target container.
 *				1.0 if the server can accommodate target container; otherwise, -1.0.
 *
 * RETRUNE:	1.0 or -1.0
 */
double NextFit::getScore(Server * s, AppContainer * target) {
	double score = -1.0;
	std::tuple<unsigned int, unsigned int, unsigned int> remain_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> request_resource;
	s->getResourceRemain(remain_resource);
	target->getResourceRequirement(request_resource);
	if (std::get<hw_Core>(remain_resource) >= std::get<hw_Core>(request_resource)
		&& std::get<hw_Memory>(remain_resource) >= std::get<hw_Memory>(request_resource)
		&& std::get<hw_Bandwidth>(remain_resource) >= std::get<hw_Bandwidth>(request_resource)) {
		score = 1.0;	
	}
	return score;
}
