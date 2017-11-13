/* ==============================================================================

	File: eNOP.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing NOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eNOP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eNOP::eNOP(){
	return;
}

eNOP::~eNOP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void eNOP::prepareNOP(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
// returns num errors
int eNOP::handleNOP(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[NOP]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	checkSyntax();

	if (globalNumErrors == 0){
		outputNOPCommand();
		cout << "\t\t[NOP]: Successfully compiled NOP command\n";
	}
	else {
		cout << "\t\t[NOP]: Failed to compile NOP command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if NOP command is immediately followed by end of string character
void eNOP::checkSyntax(){
	char currentChar = globalCurrentLine[INDEX_FIRST_CHAR_AFTER_NOP_COMMAND];
	if(!currentChar == '\0'){
		cout << "\t\t[NOP]: Syntax Error: Expected end of line after NOP command: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void eNOP::outputNOPCommand(){
	// cout << "\t\t[NOP]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(NOP_OP_CODE);
	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */