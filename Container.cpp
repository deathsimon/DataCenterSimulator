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
}
AppContainer::~AppContainer(){
	printf("Container close\n");
};
void AppContainer::run(){
	// TODO : fetch information from eventHandler
	// update(u, o);

	/* if no more work, suspend */
	// state = CNTR_SUSP;
}
void AppContainer::update(unsigned int usrs, unsigned int objs) {
	updateUsr(usrs);
	updateObj(objs);
	
	updateStatus();
}
void AppContainer::updateUsr(unsigned int usrs) {
	_usrs = usrs;
}
void AppContainer::updateObj(unsigned int objs) {
	_objs = objs;
}

bool AppContainer::isAlive(){	
	return (state == CNTR_ALIVE)?1:0;
}

/**
 * Constructor of the VRChatroom class
 */
void VRChatroom::updateStatus() {
	/* update resource requirement according to current _usrs and _objs */
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
