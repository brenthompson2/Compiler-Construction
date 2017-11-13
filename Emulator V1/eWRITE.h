/* ==============================================================================

	File: eWRITE.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing WRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "SymbolTable.h"
#include "FileManager.h"

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
#define INDEX_FIRST_CHAR_AFTER_WRITE_COMMAND 5

const string WRITE_OP_CODE = "2";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eWRITE Class Interface
============================================================================== */

class eWRITE {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eWRITE();
	~eWRITE();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareWRITE(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns number of errors
	int handleWRITE(string currentLine, int actualLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject variableArray[MAX_ARGUMENTS]; // memoryTableObject declared in SymbolTable
	unsigned int numVariablesInArray;
	string globalCurrentLine;
	unsigned int globalNumErrors;

	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */


	// calls parseVariable until no more variable to parse
	void parseParameters();

	// parses through a line one character at a time, adds complete variables to VariableArray, and returns whether or not there are any more variables to parse
	bool parseVariable(int *currentCharIterator);

	// adds the currentVariableName to the variableArray and increments numVariablesInArray
	void addToVariableArray(string currentVariableName);

	// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
	void syncVariableArrayToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputWRITECommand();




	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// prints the variableArray to the console
	void printVariableArray();
};