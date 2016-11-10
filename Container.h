/**********************************
* FILE NAME: Container.h
*
* DESCRIPTION:
**********************************/

#include "stdincludes.h"

// Marcos
#define CONTAINER_CORE	4
#define CONTAINER_MMRY	1024
#define CONTAINER_BAND	256

/**
 * CLASS NAME: AppContainer
 *
 * DESCRIPTION: the abstract class for container
 */
class AppContainer {
public:
	AppContainer() : AppContainer(CONTAINER_CORE, CONTAINER_MMRY, CONTAINER_BAND) {};
	AppContainer(unsigned int cores, unsigned int memory, unsigned int bandwidth);
	~AppContainer();

	void update(int usrs, int objs);
	void updateUsr(int usrs);
	void updateObj(int objs);

	virtual void updateStatus() = 0;
private:
	/* Upper-bound of resources */
	unsigned int bound_Core;
	unsigned int bound_Memory;
	unsigned int bound_Bandwidth;
	/* Actual usage of resources */
	double usage_Core;
	unsigned int usage_Memory;
	double usage_Bandwidth;
	/* Number of users and objects in the container */
	unsigned int _usrs;
	unsigned int _objs;
};

/**
 * CLASS NAME: VRChatroom
 *
 * DESCRIPTION:
 */
class VRChatroom : public AppContainer {
public:
	void updateStatus();
};
