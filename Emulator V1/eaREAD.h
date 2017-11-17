/* ==============================================================================

	File: eaREAD.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing aREAD command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
#include <sstream> //std::stringstream str(" ")

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
#define INDEX_FIRST_CHAR_AFTER_AREAD_COMMAND 5

#define ARRAY_ID_CODE 0
#define START_INDEX_ID_CODE 1
#define END_INDEX_ID_CODE 2

const string AREAD_OP_CODE = "11";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eaREAD Class Interface
============================================================================== */

class eaREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eaREAD();
	~eaREAD();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to SymbolTable with the parent's (compiler's) versions
	void prepareAREAD(SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns number of errors
	int handleAREAD(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject globalArrayObject;
	memoryTableObject globalStartIndex;
	memoryTableObject globalEndIndex;

	string globalCurrentLine;
	unsigned int globalNumErrors;

	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// calls parseVariable() to get globalArrayName, and then parseIndex() twice to get the start & end indexes
	void parseParameters();

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseVariable(int *currentCharIterator, int parameterNumber);

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseConstant(int *currentCharIterator, int parameterNumber);

	// Ensures the globalArrayName already exists in the Symbol Table and gets the memory location
	void getMemoryLocation();



	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};