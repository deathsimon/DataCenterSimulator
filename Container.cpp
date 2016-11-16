/**********************************
 * FILE NAME: Container.cpp
 *
 * DESCRIPTION:
 **********************************/

#include "Container.h"

/**
 * Constructor of class AppContainer
 */
AppContainer::AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth) {
	/* Set the upper-bounds */
	bound_Core = cores;
	bound_Memory = memory;
	bound_Bandwidth = bandwidth;	
	/* set the status */
	state = CNTR_ALIVE;
	_id = -1;
}
AppContainer::~AppContainer(){
	printf("Container id %d is closing after up for %ud seconds.\n", _id, upTime);
}
/**
 * FUNCTION NAME: setID, getID
 *
 * DESCRIPTION: Set / Get the id of the container
 */
void AppContainer::setID(int id){
	_id = id;
}
int AppContainer::getID() {
	return _id;
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
 * FUNCTION NAME: assignResource
 *
 * DESCRIPTION: Amount of resources assigned by the hosting server
 */
void AppContainer::assignResource(tuple<unsigned int, unsigned int, unsigned int> resource) {
	std::tie(assigned_Core, assigned_Memory, assigned_Bandwidth) = resource;
}
/**
 * FUNCTION NAME: getResourceUsage
 *
 * DESCRIPTION: return the current usage of each resource in tuple format
 */
void AppContainer::getResourceUsage(tuple<double, unsigned int, double>* resources) {
	(*resources) = std::make_tuple(usage_Core, usage_Memory, usage_Bandwidth);
}
/**
 * Constructor of class VRChatroom
 */
VRChatroom::VRChatroom(unsigned int usr, unsigned int obj) {
	/* Set the number of users and objects */
	update(usr, obj);
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
 * FUNCTION NAME: updateWorkload
 *
 * DESCRIPTION: Update the workload of the container
 */
void VRChatroom::updateWorkload() {
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
 * FUNCTION NAME: getPerformance
 *
 * DESCRIPTION: 
 *
 * RETURN: performance score
 */
double VRChatroom::getPerformance() {
	// TODO : calculate the performance / penalty according to the resource requirement and assigned
	return 0.0;
}
/**
 * FUNCTION NAME: update
 *
 * DESCRIPTION: First, update the number of users and objects of the container.
 *				Then update the container's resource requirements accordingly.
 */
void VRChatroom::update(unsigned int usrs, unsigned int objs) {
	updateUsr(usrs);
	updateObj(objs);

	updateRequirements();
}
/**
 * FUNCTION NAME: updateUsr, UpdateObj
 *
 * DESCRIPTION: Update the number of user / objects of the container
 */
void VRChatroom::updateUsr(unsigned int usrs) {
	_usrs = usrs;
}
void VRChatroom::updateObj(unsigned int objs) {
	_objs = objs;
}
/**
 * FUNCTION NAME: updateRequirements
 *
 * DESCRIPTION: Update the resource requirement of the container according to current _usrs and _objs
 */
void VRChatroom::updateRequirements() {
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
