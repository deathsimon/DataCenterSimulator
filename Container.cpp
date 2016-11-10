/**********************************
 * FILE NAME: Container.cpp
 *
 * DESCRIPTION:
 **********************************/

#include "Container.h"

/**
 * Constructor of the AppContainer class
 */
AppContainer::AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth) {
	/* Set the upper-bounds */
	bound_Core = cores;
	bound_Memory = memory;
	bound_Bandwidth = bandwidth;
	/* Set the number of users and objects */
	update(0, 0);
}
AppContainer::~AppContainer(){
	printf("Container close\n");
};
void AppContainer::update(int usrs, int objs) {
	updateUsr(usrs);
	updateObj(objs);
	
	updateStatus();
}
void AppContainer::updateUsr(int usrs) {
	_usrs = usrs;
}
void AppContainer::updateObj(int objs) {
	_objs = objs;
}

/**
 * Constructor of the VRChatroom class
 */
void VRChatroom::updateStatus() {
	// [TODO] update resource requirement according to current _usrs and _objs
	/*
	usage_Core = ;
	usage_Memory = ;
	usage_Bandwidth = ;
	*/
}