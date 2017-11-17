/* ==============================================================================

	File: eREAD.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

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

// Connects local pointer to ParentMemoryManager
void eREAD::prepareREAD(SymbolTable *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to parse and execute the read command
void eREAD::handleREAD(ProgramLineObject *currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[READ]: Executing Line " << correspondingLineNumber << "...\n";

	globalNumErrors = 0;

	executeREADCommand();
	(*ParentMemoryManager).printCoreMemory(0, 3);

	if (globalNumErrors == 0){
		// cout << "\t\t[READ]: Successfully completed READ command\n";
	}
	else {
		cout << "\t\t[READ]: Failed to complete READ command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
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