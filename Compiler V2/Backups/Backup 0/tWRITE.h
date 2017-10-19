/*
  ==============================================================================

	File: tWRITE.h
	Author: Brendan Thompson
	Updated: 09/26/17

	Description: Interface for Functions for processing WRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

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

const char WRITE_OP_CODE = '2';

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tWRITE Class Interface
============================================================================== */

class tWRITE {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tWRITE();
	void shutdown();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareWRITE(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	bool newWRITE(string currentLine, int *numErrors);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject variableArray[MAX_ARGUMENTS]; // memoryTableObject declared in SymbolTable
	unsigned int numVariablesInArray;
	string globalCurrentLine;
	bool validSyntax;
	unsigned int globalNumErrors;

	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// iterates through the variables passed to the command one character at a time and inserts them into variableArray
	void parseVariables();

	// analyzeCharacter = returns the number of errors in the line
		// changes the index to the currentChar
		// calls addToVariableArray(string currentVariableName)
		// manipulates the status of parsing given pointers to status information
	unsigned int analyzeCharacter(char currentChar,
										string currentVariableName,
										unsigned int numCharactersInVarName, unsigned int *currentLineIterator,
										bool *continueParsingParameters, bool *continueParsingVariable);

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