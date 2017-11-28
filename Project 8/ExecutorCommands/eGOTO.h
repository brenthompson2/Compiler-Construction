/*
  ==============================================================================

	File: eGOTO.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing GOTO command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "../LineLabelTable.h"

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
#define INDEX_FIRST_CHAR_AFTER_GOTO_COMMAND 4

const string GOTO_OP_CODE = "8";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eGOTO Class Interface
============================================================================== */

class eGOTO {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eGOTO();
	~eGOTO();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to LineLabelTable with the parent's (compiler's) versions
	void prepareGOTO(LineLabelTable *parentLineManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns number of errors
	int handleGOTO(string currentLine, int actualLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	string globalLineLabelName;
	int globalLineLabelLineNumber;
	int globalNumErrors;

	LineLabelTable *currentLineManager; // pointer to the Compiler's (parent's) SymbolTable

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */


	// calls parseLineLabelName until no more variable to parse
	void parseParameters();

	// parses through a line one character at a time, sets globalLineLabelName, and returns whether or not there are any more variables to parse
	bool parseLineLabelName(int *currentCharIterator);

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputGOTOCommand();
};