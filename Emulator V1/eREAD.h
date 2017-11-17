/* ==============================================================================

	File: eREAD.h
	Author: Brendan Thompson
	Updated: 11/16/17

	Description: Interface  READ handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "SymbolTable.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_STRING_LENGTH 50
#define MAX_VARIABLE_NAME_LENGTH 128	// currently using strings which may or may not allow for 128 characters
#define MAX_ARGUMENTS 7
#define INDEX_FIRST_CHAR_AFTER_READ_COMMAND 2

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eREAD Class Interface
============================================================================== */

class eREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eREAD();
	~eREAD();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to ParentMemoryManager
	void prepareREAD(SymbolTable *currentMemoryManager);

	// calls the functions necessary to parse and execute the read command
	void handleREAD(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	int variableArray[MAX_ARGUMENTS];
	int globalNumVariablesInArray;
	string globalCurrentLine;
	int globalNumErrors;

	SymbolTable *ParentMemoryManager; // pointer to the Executor's (parent's) SymbolTable

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	void parseParameters();

	// adds the currentVariableName to the variableArray and increments globalNumVariablesInArray
	void addToVariableArray(string currentVariableName);

	// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
	void syncVariableArrayToSymbolTable();

	// Executes the Command
	void executeREADCommand();

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// prints the variableArray to the console
	void printVariableArray();
};