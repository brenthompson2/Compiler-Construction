/* ==============================================================================

	File: eWRITE.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Implementation of Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eWRITE::eWRITE(){
	return;
}

eWRITE::~eWRITE(){
	return;
}

// Connects local pointer to ParentMemoryManager
void eWRITE::prepareWRITE(SymbolTable *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the command
void eWRITE::handleWRITE(ProgramLineObject *currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[eWRITE]: Executing Line " << correspondingLineNumber << "...\n";

	executeWRITECommand();

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void eWRITE::executeWRITECommand(){
	int currentMemoryLocation;
	string tempValue;
	cout << "\t\t[eWRITE]: Attempting to Execute Object Code...\n";

	for (int i = 1; i < (*globalCurrentLine).numElementsInLine; i++){
		currentMemoryLocation = (*globalCurrentLine).lineOfCodeArray[i];
		tempValue = (*ParentMemoryManager).getValue(currentMemoryLocation);
		cout << tempValue << " ";
	}
	cout << endl;

	return;
}