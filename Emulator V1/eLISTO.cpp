/*
  ==============================================================================

	File: eLISTO.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing LISTO command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "eLISTO.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eLISTO::eLISTO(){
	return;
}

eLISTO::~eLISTO(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void eLISTO::prepareLISTO(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
// returns num errors
int eLISTO::handleLISTO(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[LISTO]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	checkSyntax();

	if (globalNumErrors == 0){
		outputLISTOCommand();
		cout << "\t\t[LISTO]: Successfully compiled LISTO command\n";
	}
	else {
		cout << "\t\t[LISTO]: Failed to compile LISTO command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if LISTO command is immediately followed by end of string character
void eLISTO::checkSyntax(){
	char currentChar = globalCurrentLine[INDEX_FIRST_CHAR_AFTER_LISTO_COMMAND];
	if(!currentChar == '\0'){
		cout << "\t\t[LISTO]: Syntax Error: Expected end of line after LISTO command: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void eLISTO::outputLISTOCommand(){
	// cout << "\t\t[LISTO]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(LISTO_OP_CODE);
	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */