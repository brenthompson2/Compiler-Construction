/* ==============================================================================

	File: elREAD.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Implementation of Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "elREAD.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

elREAD::elREAD(){
	return;
}

elREAD::~elREAD(){
	return;
}

// Connects global pointer to ParentLiteralManager
void elREAD::prepareLREAD(LiteralTable *currentLiteralManager){
	ParentLiteralManager = currentLiteralManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the read command
void elREAD::handleLREAD(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;
	executeLREADCommand();
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void elREAD::executeLREADCommand(){
	int currentMemoryLocation;
	string tempValue;
	// cout << "\t\t[elREAD]: Attempting to Execute Object Code...\n";

	for (int i = 1; i < (*globalCurrentLine).numElementsInLine; i++){
		cin >> tempValue;
		currentMemoryLocation = (*globalCurrentLine).lineOfCodeArray[i];
		(*ParentLiteralManager).setValue(currentMemoryLocation, tempValue);
		// cout << "\t\t[elREAD]: Saved \"" << tempValue << "\" to location " << currentMemoryLocation << endl;
	}

	return;
}