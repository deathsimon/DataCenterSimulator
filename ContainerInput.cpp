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

InputForVRChat & InputForVRChat::operator=(InputForVRChat & anotherInput) {	
	for each (tuple<unsigned int, unsigned int>* t in anotherInput.inputSeq) {
		tuple<unsigned int, unsigned int>* newTuple = t;
		this->inputSeq.push_back(newTuple);
	}	
	return *this;
}

void InputForVRChat::setupInput(){
	// TODO : read from file and make tuples
	//
	// std::make_tuple(,);
}

bool InputForVRChat::getNext() {
	tuple<unsigned int, unsigned int> next;
	return getNext(&next);
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

