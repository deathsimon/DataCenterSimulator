/**********************************
 * FILE NAME: Container.h
 *
 * DESCRIPTION:
 **********************************/
#pragma once

#include "stdincludes.h"
#include "ContainerInput.h"

// Marcos
#define SPEC_CORE	4
#define SPEC_MMRY	1024
#define SPEC_BAND	256

#define BASIC_CPU	1
#define BASIC_MMRY	128
#define BASIC_BAND	32

enum cntrState {
	CNTR_SUSP, CNTR_ALIVE
};

/**
 * CLASS NAME: AppContainer
 *
 * DESCRIPTION: the abstract class for container
 */
class AppContainer {
public:
	AppContainer() : AppContainer(SPEC_CORE, SPEC_MMRY, SPEC_BAND) {};	
	AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth);
	~AppContainer();
	/* set properties */
	void setID(int);
	/* get properties */
	int getID();
	bool isAlive();
	unsigned int getUpTime();
	/* Resource related methods */
	void assignResource(tuple<unsigned int, unsigned int, unsigned int> resource);
	void getResourceAssigned(tuple<unsigned int, unsigned int, unsigned int> &resources);
	void getResourceRequirement(tuple<unsigned int, unsigned int, unsigned int> &resources);
	
	virtual void updateWorkload() = 0;
	virtual double getPerformance() = 0;
protected:
	virtual void updateRequirements() = 0;

	int _id;
	unsigned int upTime;
	int state;
	/* Resource Specifications of the container */
	unsigned int bound_Core;
	unsigned int bound_Memory;
	unsigned int bound_Bandwidth;
	/* Amount of resources assigned */
	unsigned int assigned_Core = 0;
	unsigned int assigned_Memory = 0;
	unsigned int assigned_Bandwidth = 0;
	/* Requirement of resources */
	unsigned int require_Core = 0;
	unsigned int require_Memory = 0;
	unsigned int require_BandWidth = 0;
	//double usage_Core = 0.0;		// percentage
	//unsigned int usage_Memory = 0;	// amount
	//double usage_Bandwidth = 0.0;	// percentage
	/* Number of users and objects in the container */
	unsigned int _usrs = 0;
	unsigned int _objs = 0;	
};

/**
 * CLASS NAME: VRChatroom
 *
 * DESCRIPTION:
 */
class VRChatroom : public AppContainer {
public:	
	VRChatroom() : VRChatroom(0, 0) {};
	VRChatroom(unsigned int usr, unsigned int obj);

	void setupInputs(InputForVRChat *workloads);

	virtual void updateWorkload();	
	virtual double getPerformance();
private:
	/* workload update related */
	void update(unsigned int usrs, unsigned int objs);
	void updateUsr(unsigned int usrs);
	void updateObj(unsigned int objs);

	virtual void updateRequirements();

	void updateCPU();
	void updateMem();
	void updateBDW();
	/* Amount of based resources required with no workload */
	unsigned int basicCore;
	unsigned int basicMemory;
	unsigned int basicBandwidth;

	InputForVRChat *inputs = NULL;
};
