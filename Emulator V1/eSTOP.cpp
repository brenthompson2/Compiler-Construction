/* ==============================================================================

	File: eSTOP.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing STOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eSTOP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eSTOP::eSTOP(){
	return;
}

eSTOP::~eSTOP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void eSTOP::prepareSTOP(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
// returns num errors
int eSTOP::handleSTOP(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[STOP]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	checkSyntax();

	if (globalNumErrors == 0){
		outputSTOPCommand();
		cout << "\t\t[STOP]: Successfully completed STOP command\n";
	}
	else {
		cout << "\t\t[STOP]: Failed to complete STOP command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if stop command is immediately followed by end of string character
void eSTOP::checkSyntax(){
	char currentChar = globalCurrentLine[INDEX_FIRST_CHAR_AFTER_STOP_COMMAND];
	if(!currentChar == '\0'){
		cout << "\t\t[STOP]: Syntax Error: Expected end of line after STOP command: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void eSTOP::outputSTOPCommand(){
	// cout << "\t\t[STOP]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(STOP_OP_CODE);
	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */