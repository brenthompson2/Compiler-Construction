/*
  ==============================================================================

	File: STOP.cpp
	Author: Brendan Thompson
	Updated: 10/09/17

	Description: Implementation of Functions for processing STOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "STOP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

STOP::STOP(){
	return;
}

STOP::~STOP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void STOP::prepareSTOP(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
// returns num errors
int STOP::handleSTOP(string currentLine, int correspondingLineNumber){
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
void STOP::checkSyntax(){
	char currentChar = globalCurrentLine[INDEX_FIRST_CHAR_AFTER_STOP_COMMAND];
	if(!currentChar == '\0'){
		cout << "\t\t[STOP]: Syntax Error: Expected end of line after STOP command: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void STOP::outputSTOPCommand(){
	// cout << "\t\t[STOP]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeCharToObj(STOP_OP_CODE);
	(*currentFileManager).writeCharToObj('\n');
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */