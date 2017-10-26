/* ==============================================================================

	File: tLOOPEND.cpp
	Author: Brendan Thompson
	Updated: 10/12/17

	Description: Implementation of Functions for processing LOOPEND command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "tLOOPEND.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tLOOPEND::tLOOPEND(){
	return;
}

tLOOPEND::~tLOOPEND(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tLOOPEND::prepareLOOPEND(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

// calls the functions necessary to parse the line and print the object code to the file while counting errors
// returns num errors
int tLOOPEND::handleLOOPEND(string currentLine, int correspondingLineNumber){
	cout << "\t\t[LOOPEND]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;
	globalNumErrors = 0;

	globalCurrentLine = currentLine;

	checkSyntax();

	if (globalNumErrors == 0){
		outputLOOPENDCommand();
		cout << "\t\t[LOOPEND]: Successfully compiled LOOP-END command\n";
	}
	else {
		cout << "\t\t[LOOPEND]: Failed to compile LOOP-END command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// checks to see if LOOPEND command is immediately followed by end of string character
void tLOOPEND::checkSyntax(){
	char currentChar;
	currentChar = globalCurrentLine[8];
	if(!(globalCurrentLine[8] == '\0')){
		cout << "\t\t[LOOPEND]: Syntax Error: Expected end of line instead of " << currentChar << " after LOOP-END command: " << globalCurrentLine << "<--\n";
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code
void tLOOPEND::outputLOOPENDCommand(){
	// cout << "\t\t[LOOPEND]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(LOOPEND_OP_CODE);
	(*currentFileManager).writeCharToObj('\n');
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */