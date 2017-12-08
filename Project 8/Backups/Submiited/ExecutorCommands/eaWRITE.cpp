/* ==============================================================================

	File: eaWRITE.cpp
	Author: Brendan Thompson
	Updated: 11/26/17

	Description: Implementation of Functions for processing aWRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eaWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eaWRITE::eaWRITE(){
	return;
}

eaWRITE::~eaWRITE(){
	return;
}

// Connects global pointer to ParentMemoryManager
void eaWRITE::prepareAWRITE(SymbolTable *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;

}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the aWRITE command
void eaWRITE::handleAWRITE(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;

	string arrayMemoryLocation_string, startIndexValue_string, endIndexValue_string, startIndexMemLocation_string, endIndexMemLocation_string;
	int arrayMemoryLocation_int, startIndexValue_int, endIndexValue_int, startIndexMemLocation_int, endIndexMemLocation_int;

	arrayMemoryLocation_int = ((*globalCurrentLine).lineOfCodeArray)[1];
	startIndexMemLocation_int = ((*globalCurrentLine).lineOfCodeArray)[2];
	endIndexMemLocation_int = ((*globalCurrentLine).lineOfCodeArray)[3];
	// cout << "\t\t[aWRITE]: Executing aWRITE command for array at " << arrayMemoryLocation_int << " between indexes from mem locations " << startIndexMemLocation_int << " to " << endIndexMemLocation_int << endl;

	startIndexValue_string = (*ParentMemoryManager).getValue(startIndexMemLocation_int);
	endIndexValue_string = (*ParentMemoryManager).getValue(endIndexMemLocation_int);

	// cout << "\t\t[aWRITE]: Executing aWRITE command for array at " << arrayMemoryLocation_int << " for indexes " << startIndexValue_string << " to " << endIndexValue_string << endl;

	std::stringstream str0(startIndexValue_string);
	str0 >> startIndexValue_int;
	std::stringstream str1(endIndexValue_string);
	str1 >> endIndexValue_int;

	if ((*ParentMemoryManager).rangeChecksOut(arrayMemoryLocation_int, startIndexValue_int, endIndexValue_int)){
		// cout << "\t\t[aWRITE]: Executing aWRITE command for array at " << arrayMemoryLocation_int << " for indexes " << startIndexValue_int << " to " << endIndexValue_int << endl;
		executeAWRITECommand(arrayMemoryLocation_int, startIndexValue_int, endIndexValue_int);
	}
	else {
		cout << "\t\t[aWRITE]: Boundary Error for array at " << arrayMemoryLocation_int << " for indexes " << startIndexValue_int << " to " << endIndexValue_int << endl;
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void eaWRITE::executeAWRITECommand(int arrayMemoryLocation, int startIndex, int endIndex){
	// cout << "\t\t[eaWRITE]: Attempting to Execute Object Code...\n";
	string tempValue;
	int currentIndexIntoCoreMemory = arrayMemoryLocation + startIndex;

	for (int i = startIndex; i <= endIndex; i++){
		tempValue = (*ParentMemoryManager).getValue(currentIndexIntoCoreMemory);
		cout << tempValue << " ";
		currentIndexIntoCoreMemory++;
	}
	cout << endl;
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */