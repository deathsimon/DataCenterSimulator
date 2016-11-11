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
	virtual void setupInput() = 0;
	virtual bool getNext() = 0;
};

class InputForVRChat : public ContainerInput {
public:
	InputForVRChat();
	virtual void setupInput();
	virtual bool getNext(tuple<unsigned int, unsigned int>* nxtTuple);

private:
	deque<tuple<unsigned int, unsigned int>*> inputSeq;
};