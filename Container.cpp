/**********************************
 * FILE NAME: Container.cpp
 *
 * DESCRIPTION:
 **********************************/

#include "Container.h"

/**
 * Constructor of the AppContainer class
 */
AppContainer::AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth, unsigned int usr, unsigned int obj) {
	/* Set the upper-bounds */
	bound_Core = cores;
	bound_Memory = memory;
	bound_Bandwidth = bandwidth;
	/* Set the number of users and objects */
	update(usr, obj);
	/* set the status */
	state = CNTR_ALIVE;
	_id = -1;
}
AppContainer::~AppContainer(){
	printf("Container id %d is closing after up for %ud seconds.\n", _id, upTime);
}
/**
 * FUNCTION NAME: setID
 *
 * DESCRIPTION: Set the id of the container
 */
void AppContainer::setID(int id){
	_id = id;
}
/**
 * FUNCTION NAME: update
 *
 * DESCRIPTION: First, update the number of users and objects of the container.
 *				Then update the container status accordingly.
 */
void AppContainer::update(unsigned int usrs, unsigned int objs) {
	updateUsr(usrs);
	updateObj(objs);
	
	updateStatus();
}
/**
 * FUNCTION NAME: updateUsr
 *
 * DESCRIPTION: Update the number of user of the container
 */
void AppContainer::updateUsr(unsigned int usrs) {
	_usrs = usrs;
}
/**
 * FUNCTION NAME: updateObj
 *
 * DESCRIPTION: Update the number of objects of the container
 */
void AppContainer::updateObj(unsigned int objs) {
	_objs = objs;
}
/**
 * FUNCTION NAME: isAlive
 *
 * DESCRIPTION: check if the container still has workload remains
 * 
 * RETURN: True / False
 */
bool AppContainer::isAlive(){	
	return (state == CNTR_ALIVE)?true:false;
}
/**
 * FUNCTION NAME: getUpTime
 *
 * DESCRIPTION: return the amount of time this container has been running
 *
 * RETURN: upTime
 */
unsigned int AppContainer::getUpTime() {
	return upTime;
}
/**
 * FUNCTION NAME: setupInputs
 *
 * DESCRIPTION: Copy the input workload sequence from target workload.
 */
void VRChatroom::setupInputs(InputForVRChat *workloads) {
	inputs = new InputForVRChat();
	/* copy from target */
	*inputs = (*workloads);
}
/**
 * FUNCTION NAME: updateRequirement
 *
 * DESCRIPTION: Update the resource requirement of the container
 */
void VRChatroom::updateRequirement() {
	tuple<unsigned int, unsigned int> next;
	unsigned int newUsr;
	unsigned int newObj;
	/* fetch information from eventHandler */
	if (inputs->getNext(&next)) {
		/* get the number of user and objests from the tuple */
		std::tie(newUsr, newObj) = next;
		update(newUsr, newObj);

		upTime++;
	}
	else {
		/* no more inputs, suspend the container */
		update(0, 0);
		state = CNTR_SUSP;	
	}
}
/**
 * FUNCTION NAME: updateStatus
 *
 * DESCRIPTION: Update the requirement of the three major resources according to current _usrs and _objs
 */
void VRChatroom::updateStatus() {	
	updateCPU();
	updateMem();
	updateBDW();	
}

void VRChatroom::updateCPU() {
	// TODO
	// usage_Core = ;
}

void VRChatroom::updateMem() {
	// TODO
	// usage_Memory = ;
}

void VRChatroom::updateBDW() {
	// TODO
	// usage_Bandwidth = ;
}
