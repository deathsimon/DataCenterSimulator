/**********************************
* FILE NAME: DataCenterSimulator.cpp
*
* DESCRIPTION: 
**********************************/

#include "DataCenter.h"


/**********************************
* FUNCTION NAME: main
*
* DESCRIPTION: main function. Start from here
**********************************/
int main() {

	DataCenter DC;

	return 1;
}

/**
* Constructor of the DataCenter class
*/

DataCenter::DataCenter(){	
	resAllo = new ResAllocator();
	serverlist.clear();

	printf("Hello World!\n");
}

/**
* Destructor
*/
DataCenter::~DataCenter() {
	
}

void DataCenter::run() {
	// First, update status of servers

	// Then, create and deploy new containers

}

