/*
  ==============================================================================

	File: tREAD.h
	Author: Brendan Thompson
	Updated: 09/25/17

	Description: Interface for Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "LookupTable.h"
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
#define MAX_VARIABLE_NAME_LENGTH 128	// need to use in variable names instead of using string
#define MAX_ARGUMENTS 7

const char READ_OP_CODE = '1';

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tREAD Class Interface
============================================================================== */

class tREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tREAD();
	void shutdown();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	void prepareREAD(FileManager *parentFileManager, LookupTable *parentMemoryManager); // Link up FileManager & LookupTable
	bool newREAD(string currentLine); // handles a READ command

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject variableArray[MAX_ARGUMENTS];
	unsigned int numVariablesInArray;
	string globalCurrentLine;
	bool validSyntax;
	unsigned int globalNumErrors;

	FileManager *currentFileManager;
	LookupTable *currentMemoryManager;


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	void parseVariables();

	// returns the number of errors in the line
		// changes the index to the currentChar
		// changes
		// calls addToVariableArray()
		// manipulates the status of compilation given pointers to a bunch of status information
	unsigned int analyzeCharacter(char currentChar,
										string currentVariableName,
										unsigned int numCharactersInVarName, unsigned int *currentLineIterator,
										bool *continueParsingParameters, bool *continueParsingVariable);

	void addToVariableArray(string currentVariableName);
	void addVariableArrayToLookupTable();
	void outputReadCommand();




	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	void printVariableArray();
};