/**********************************
 * FILE NAME: ContainerInput.cpp
 *
 * DESCRIPTION:
 **********************************/

#include "ContainerInput.h"

 /**
  * Constructor of the InputForVRChat class
  */
InputForVRChat::InputForVRChat() {
	inputSeq.clear();
}

void InputForVRChat::setupInput(){
	// TODO : read from file and make tuples
	//
	// std::make_tuple(,);
}

bool InputForVRChat::getNext(tuple<unsigned int, unsigned int>* nxtTuple){
	bool hasNext = false;
	if (!inputSeq.empty()) {
		nxtTuple = inputSeq.front();
		inputSeq.pop_front();
		hasNext = true;
	}
	return hasNext;
}

