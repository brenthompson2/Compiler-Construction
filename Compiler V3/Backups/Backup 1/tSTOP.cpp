/*
  ==============================================================================

	File: tSTOP.cpp
	Author: Brendan Thompson
	Updated: 10/09/17

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
// returns num errors
int tSTOP::handleSTOP(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[tSTOP]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	checkSyntax();

	if (globalNumErrors == 0){
		outputSTOPCommand();
		cout << "\t\t[tSTOP]: Successfully completed tSTOP command\n";
	}
	else {
		cout << "\t\t[tSTOP]: Failed to complete tSTOP command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if stop command is immediately followed by end of string character
void tSTOP::checkSyntax(){
	char currentChar = globalCurrentLine[4];
	if(!currentChar == '\0'){
		cout << "\t\t[tSTOP]: Syntax Error: Expected end of line after STOP command: " << globalCurrentLine << endl;
		globalNumErrors++;
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