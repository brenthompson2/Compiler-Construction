/* ==============================================================================

	File: eREAD.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Implementation of Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eREAD.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eREAD::eREAD(){
	return;
}

eREAD::~eREAD(){
	return;
}

// Connects global pointer to ParentMemoryManager
void eREAD::prepareREAD(CoreMemory *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the read command
void eREAD::handleREAD(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;
	executeREADCommand();
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void eREAD::executeREADCommand(){
	int currentMemoryLocation;
	string tempValue;
	// cout << "\t\t[eREAD]: Attempting to Execute Object Code...\n";

	for (int i = 1; i < (*globalCurrentLine).numElementsInLine; i++){
		cin >> tempValue;
		currentMemoryLocation = (*globalCurrentLine).lineOfCodeArray[i];
		(*ParentMemoryManager).setValue(currentMemoryLocation, tempValue);
		// cout << "\t\t[eREAD]: Saved \"" << tempValue << "\" to location " << currentMemoryLocation << endl;
	}

	return;
}