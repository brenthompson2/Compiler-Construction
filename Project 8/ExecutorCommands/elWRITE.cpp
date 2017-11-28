/* ==============================================================================

	File: elWRITE.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Implementation of Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "elWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

elWRITE::elWRITE(){
	return;
}

elWRITE::~elWRITE(){
	return;
}

// Connects local pointer to ParentLiteralManager
void elWRITE::prepareLWRITE(LiteralTable *currentLiteralManager){
	ParentLiteralManager = currentLiteralManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the command
void elWRITE::handleLWRITE(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;
	executeLWRITECommand();
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void elWRITE::executeLWRITECommand(){
	int currentMemoryLocation;
	string tempValue;
	// cout << "\t\t[elWRITE]: Attempting to Execute Object Code...\n";

	for (int i = 1; i < (*globalCurrentLine).numElementsInLine; i++){
		currentMemoryLocation = (*globalCurrentLine).lineOfCodeArray[i];
		tempValue = (*ParentLiteralManager).getValue(currentMemoryLocation);
		cout << tempValue << " ";
	}

	return;
}