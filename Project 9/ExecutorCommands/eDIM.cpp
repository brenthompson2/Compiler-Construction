/* ==============================================================================

	File: eDIM.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Implementation of Functions for processing DIM command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eDIM.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eDIM::eDIM(){
	return;
}

eDIM::~eDIM(){
	return;
}

// Connects global pointer to ParentMemoryManager
void eDIM::prepareDIM(CoreMemory *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the DIM command
void eDIM::handleDIM(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;
	executeDIMCommand();
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void eDIM::executeDIMCommand(){
	int newArrayLocation;
	int newArraySize;
	// cout << "\t\t[eDIM]: Attempting to Execute Object Code...\n";

	for (int i = 1; i < (*globalCurrentLine).numElementsInLine; i++){
		newArrayLocation = (*globalCurrentLine).lineOfCodeArray[i];
		newArraySize = (*globalCurrentLine).lineOfCodeArray[++i];
		(*ParentMemoryManager).addNewArray(newArrayLocation, newArraySize);
		// cout << "\t\t[eDIM]: Saved array at location " << newArrayLocation << " with array size " << newArraySize <<  endl;
	}

	return;
}