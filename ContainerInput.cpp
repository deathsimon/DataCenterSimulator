/**********************************
 * FILE NAME: ContainerInput.cpp
 *
 * DESCRIPTION:
 **********************************/

#include "ContainerInput.h"

 /**
  * Constructor of class InputForVRChat
  */
InputForVRChat::InputForVRChat() {
	inputSeq.clear();
}	
/**
 * Assignment operator overloading
 */
InputForVRChat & InputForVRChat::operator=(InputForVRChat & anotherInput) {	
	for each (tuple<unsigned int, unsigned int>* t in anotherInput.inputSeq) {
		tuple<unsigned int, unsigned int>* newTuple = t;
		this->inputSeq.push_back(newTuple);
	}	
	return *this;
}
/**
 * FUNCTION NAME: setupInput
 *
 * DESCRIPTION: Read workloads from file and construct an input sequence
 */
void InputForVRChat::setupInput(string filename){
	unsigned int numData;
	unsigned int usr;
	unsigned int obj;
	tuple<unsigned int, unsigned int> *workload;

	/* read workloads from file */
	ifstream infile(filename.c_str(),ios::in);
	infile >> numData;
	while (numData) {
		infile >> usr >> obj;
		workload = new tuple<unsigned int, unsigned int>(usr, obj);
		inputSeq.push_back(workload);
		numData--;
	};
	infile.close();
}
/**
 * FUNCTION NAME: getNext
 *
 * DESCRIPTION: Get the next pair of (usr, obj) and return True.
 *				If no more workloads, return False.
 *
 * RETURN : hasNext
 */
bool InputForVRChat::getNext() {
	tuple<unsigned int, unsigned int> next;
	return getNext(next);
}
bool InputForVRChat::getNext(tuple<unsigned int, unsigned int> &nxtTuple){
	bool hasNext = false;
	if (!inputSeq.empty()) {
		nxtTuple = *inputSeq.front();
		inputSeq.pop_front();
		hasNext = true;
	}
	return hasNext;
}

