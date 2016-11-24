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
 *				Next-Fit find the next server in the server list that can accommodate target server.
 * 
 * RETURN:	target server if found; else, a nutllptr is returned.
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
 * RETURN:	1.0 or -1.0
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

/**
 * FUNCTION NAME: scheduleTo
 *
 * DESCRIPTION: choose the server for target container using Best-Fit.
 *				Best-Fit find the server that minimize the remaining resource.
 *
 * RETURN:	target server if found; else, a nutllptr is returned.
 */
Server * BestFit::scheduleTo(AppContainer * targetContainer){
	Server *targetServer = nullptr;
	double score = 0.0;
	double max_score = 0.0;

	for each (Server* s in *svrList)	{
		score = getScore(s, targetContainer);
		if (score > max_score) {
			targetServer = s;
			max_score = score;
		}
	}
	return targetServer;
}
/**
 * FUNCTION NAME: getScore
 *
 * DESCRIPTION: the score of the server for target container.
 *				the score is calculated by function remain_ratio().
 *
 * RETURN: score; -1.0 if cannot accomodate.
 */
double BestFit::getScore(Server * s, AppContainer * target) {
	double score = -1.0;
	double tmp;
	std::tuple<unsigned int, unsigned int, unsigned int> remain_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> total_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> request_resource;
	s->getResourceRemain(remain_resource);
	s->getTotalResource(total_resource);
	target->getResourceRequirement(request_resource);
	
	if (std::get<hw_Core>(remain_resource) >= std::get<hw_Core>(request_resource)
		&& std::get<hw_Memory>(remain_resource) >= std::get<hw_Memory>(request_resource)
		&& std::get<hw_Bandwidth>(remain_resource) >= std::get<hw_Bandwidth>(request_resource)) {
		if (score < (tmp = remain_ratio(std::get<hw_Core>(remain_resource), 
			std::get<hw_Core>(request_resource), std::get<hw_Core>(total_resource)))) {
			score = tmp;
		}
		if (score < (tmp = remain_ratio(std::get<hw_Memory>(remain_resource),
			std::get<hw_Memory>(request_resource), std::get<hw_Memory>(total_resource)))) {
			score = tmp;
		}
		if (score < (tmp = remain_ratio(std::get<hw_Bandwidth>(remain_resource),
			std::get<hw_Bandwidth>(request_resource), std::get<hw_Bandwidth>(total_resource)))) {
			score = tmp;
		}
		score++;	// avoid (score == 0)
	}
	return 1/score;
}
double BestFit::remain_ratio(unsigned int r, unsigned int c, unsigned int t) {
	return (double)(r - c) / (double)t;
}

/**
 * FUNCTION NAME: scheduleTo
 *
 * DESCRIPTION: choose the server for target container using Worst-Fit.
 *				Worst-Fit find the server that maximize the remaining resource.
 *
 * RETURN:	target server if found; else, a nutllptr is returned.
 */
Server * WorstFit::scheduleTo(AppContainer * targetContainer) {
	Server *targetServer = nullptr;
	double score = 0.0;
	double max_score = 0.0;

	for each (Server* s in *svrList) {
		score = getScore(s, targetContainer);
		if (score > max_score) {
			targetServer = s;
			max_score = score;
		}
	}
	return targetServer;
}
/**
 * FUNCTION NAME: getScore
 *
 * DESCRIPTION: the score of the server for target container.
 *				the score is calculated by function remain_ratio().
 *
 * RETURN: score; -1.0 if cannot accomodate.
 */
double WorstFit::getScore(Server * s, AppContainer * target) {
	double score = -1.0;
	std::tuple<unsigned int, unsigned int, unsigned int> remain_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> total_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> request_resource;
	s->getResourceRemain(remain_resource);
	s->getTotalResource(total_resource);
	target->getResourceRequirement(request_resource);

	if (std::get<hw_Core>(remain_resource) >= std::get<hw_Core>(request_resource)
		&& std::get<hw_Memory>(remain_resource) >= std::get<hw_Memory>(request_resource)
		&& std::get<hw_Bandwidth>(remain_resource) >= std::get<hw_Bandwidth>(request_resource)) {
		score = 1.0;
		double tmp = score;
		if (score > (tmp = remain_ratio(std::get<hw_Core>(remain_resource),
			std::get<hw_Core>(request_resource), std::get<hw_Core>(total_resource)))) {
			score = tmp;
		}
		if (score > (tmp = remain_ratio(std::get<hw_Memory>(remain_resource),
			std::get<hw_Memory>(request_resource), std::get<hw_Memory>(total_resource)))) {
			score = tmp;
		}
		if (score > (tmp = remain_ratio(std::get<hw_Bandwidth>(remain_resource),
			std::get<hw_Bandwidth>(request_resource), std::get<hw_Bandwidth>(total_resource)))) {
			score = tmp;
		}
	}
	return score;
}
double WorstFit::remain_ratio(unsigned int r, unsigned int c, unsigned int t) {
	return (double)(r - c) / (double)t;
}

/**
 * FUNCTION NAME: scheduleTo
 *
 * DESCRIPTION: choose the server for target container using Age-Based.
 *				Age-Based find the server with longevity containers.
 *
 * RETURN:	target server if found; else, a nutllptr is returned.
 */
Server * AgeBased::scheduleTo(AppContainer * targetContainer) {
	Server* targetServer = nullptr;
	double score = 0.0;
	double max_score = 0.0;

	for each (Server* s in *svrList) {
		score = getScore(s, targetContainer);
		if (score > max_score) {
			targetServer = s;
			max_score = score;
		}
	}

	return targetServer;
}
/**
 * FUNCTION NAME: getScore
 *
 * DESCRIPTION: the score of the server for target container.
 *				the score equals to the longest up time t.
 *
 * RETURN: time t as score; -1.0 if cannot accomodate.
 */
double AgeBased::getScore(Server * s, AppContainer * target) {
	double score = -1.0;
	std::tuple<unsigned int, unsigned int, unsigned int> remain_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> total_resource;
	std::tuple<unsigned int, unsigned int, unsigned int> request_resource;
	s->getResourceRemain(remain_resource);
	s->getTotalResource(total_resource);
	target->getResourceRequirement(request_resource);

	if (std::get<hw_Core>(remain_resource) >= std::get<hw_Core>(request_resource)
		&& std::get<hw_Memory>(remain_resource) >= std::get<hw_Memory>(request_resource)
		&& std::get<hw_Bandwidth>(remain_resource) >= std::get<hw_Bandwidth>(request_resource)) {
		score = s->getLongestUpTime() + 1;
	}

	return score;
}
