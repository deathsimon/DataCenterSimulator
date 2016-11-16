/**********************************
 * FILE NAME: Container.h
 *
 * DESCRIPTION:
 **********************************/
#pragma once

#include "stdincludes.h"
#include "ContainerInput.h"

// Marcos
#define CONTAINER_CORE	4
#define CONTAINER_MMRY	1024
#define CONTAINER_BAND	256

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
	AppContainer() : AppContainer(CONTAINER_CORE, CONTAINER_MMRY, CONTAINER_BAND, 0, 0) {};
	AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth) : AppContainer(cores, memory, bandwidth, 0, 0) {};
	AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth, unsigned int usr, unsigned int obj);
	~AppContainer();
	
	void setID(int);
	void assignResource(tuple<unsigned int, unsigned int, unsigned int> resource);

	void update(unsigned int usrs, unsigned int objs);
	void updateUsr(unsigned int usrs);
	void updateObj(unsigned int objs);

	bool isAlive();
	unsigned int getUpTime();
	void getResourceUsage(tuple<double, unsigned int, double>* resources);	

	virtual void updateWorkload() = 0;
	virtual void updateRequirements() = 0;
	virtual double getPerformance() = 0;
protected:
	int _id;
	unsigned int upTime;
	int state;
	/* Upper-bound of resources */
	unsigned int bound_Core;
	unsigned int bound_Memory;
	unsigned int bound_Bandwidth;
	/* Amount of resources assigned */
	unsigned int assigned_Core = 0;
	unsigned int assigned_Memory = 0;
	unsigned int assigned_Bandwidth = 0;
	/* Actual usage of resources */
	double usage_Core = 0.0;
	unsigned int usage_Memory = 0;
	double usage_Bandwidth = 0.0;
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
	VRChatroom() {};
	void setupInputs(InputForVRChat *workloads);
	virtual void updateWorkload();
	virtual void updateRequirements();
	virtual double getPerformance();
private:
	void updateCPU();
	void updateMem();
	void updateBDW();

	InputForVRChat *inputs = NULL;
};
