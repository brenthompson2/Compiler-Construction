/*
  ==============================================================================

	File: tSTOP.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Implementation of Functions for processing STOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tSTOP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tSTOP::tSTOP(){
	return;
}

tSTOP::~tSTOP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tSTOP::prepareSTOP(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
bool tSTOP::newSTOP(string currentLine, int *numErrors){
	globalCurrentLine = currentLine;
	cout << "\t\t[tSTOP]: Compiling Line: " << globalCurrentLine << endl;

	globalNumErrors = 0;
	validSyntax = true;

	checkSyntax();

	outputSTOPCommand();

	if (!validSyntax){
		cout << "\t\t[tSTOP]: " << globalNumErrors << " Syntax Errors in STOP Command: " << globalCurrentLine << endl;
	}

	// cout << "\t\t[tSTOP]: Valid Syntax: " << validSyntax << endl;

	*numErrors += globalNumErrors;
	return validSyntax;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if stop command is immediately followed by end of string character
void tSTOP::checkSyntax(){
	char currentChar = globalCurrentLine[4];
	if(!currentChar == '\0'){
		cout << "\t\t[tSTOP]: Syntax Error: Expected end of line after STOP command: " << globalCurrentLine << endl;
		validSyntax = false;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void tSTOP::outputSTOPCommand(){
	// cout << "\t\t[tSTOP]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeCharToObj(STOP_OP_CODE);
	(*currentFileManager).writeCharToObj('\n');
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */