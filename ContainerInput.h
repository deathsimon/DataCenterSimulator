/**********************************
 * FILE NAME: ContainerInput.h
 *
 * DESCRIPTION:
 **********************************/
#pragma once

#include "stdincludes.h"

class ContainerInput {
public:
	ContainerInput() {};
	virtual void setupInput(string filename) = 0;	
};

class InputForVRChat : public ContainerInput {
public:
	InputForVRChat();
	InputForVRChat& operator = (InputForVRChat &anotherInput);		

	bool hasNext();
	void getNext(tuple<unsigned int, unsigned int> &nxtTuple);

	virtual void setupInput(string filename);	

private:	
	deque<tuple<unsigned int, unsigned int>*> inputSeq;
};