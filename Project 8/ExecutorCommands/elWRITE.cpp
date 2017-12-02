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

// executes the command (prepared to handle multiple literals on one line)
void elWRITE::executeLWRITECommand(){
	int currentMemoryLocation;
	string currentLiteral;
	char currentChar;
	int currentLiteralIterator;
	// cout << "\t\t[elWRITE]: Attempting to Execute Object Code...\n";

	for (int i = 1; i < (*globalCurrentLine).numElementsInLine; i++){
		currentMemoryLocation = (*globalCurrentLine).lineOfCodeArray[i];
		currentLiteral = (*ParentLiteralManager).getValue(currentMemoryLocation);
		currentLiteralIterator = 0;
		currentChar = currentLiteral[currentLiteralIterator];

		// Print line one character at a time
		while (currentChar != '\0'){
			if ((currentChar == '\\') && (currentLiteral[currentLiteralIterator + 1] == 'n')){
				cout << endl;
				currentLiteralIterator = currentLiteralIterator + 2;
			}
			else {
				cout << currentChar;
				currentLiteralIterator++;
			}
			currentChar = currentLiteral[currentLiteralIterator];
		}
	}

	return;
}