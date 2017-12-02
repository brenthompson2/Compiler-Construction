/*
  ==============================================================================

	File: tCLS.cpp
	Author: Brendan Thompson
	Updated: 10/23/17

	Description: Implementation of Functions for processing CLS command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tCLS.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tCLS::tCLS(){
	return;
}

tCLS::~tCLS(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tCLS::prepareCLS(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
// returns num errors
int tCLS::handleCLS(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	// cout << "\t\t[CLS]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	checkSyntax();

	if (globalNumErrors == 0){
		outputCLSCommand();
		// cout << "\t\t[CLS]: Successfully completed CLS command\n";
	}
	else {
		cout << "\t\t[CLS]: Failed to complete CLS command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if tCLS command is immediately followed by end of string character
void tCLS::checkSyntax(){
	char currentChar = globalCurrentLine[INDEX_FIRST_CHAR_AFTER_CLS_COMMAND];
	if(!currentChar == '\0'){
		cout << "\t\t[CLS]: Syntax Error: Expected end of line after CLS command: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void tCLS::outputCLSCommand(){
	// cout << "\t\t[CLS]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(CLS_OP_CODE);
	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */