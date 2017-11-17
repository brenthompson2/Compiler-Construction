/*
  ==============================================================================

	File: eDIM.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing DIM command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

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
#define INDEX_FIRST_CHAR_AFTER_DIM_COMMAND 3

const string DIM_OP_CODE = "0";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eDIM Class Interface
============================================================================== */

class eDIM {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eDIM();
	~eDIM();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to SymbolTable with the parent's (compiler's) versions
	void prepareDIM(SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns num errors
	int handleDIM(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject variableArray[MAX_ARGUMENTS]; // memoryTableObject declared in SymbolTable
	unsigned int numVariablesInArray;
	string globalCurrentLine;
	unsigned int globalNumErrors;

	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the dimensions
	void parseParameters();

	// parses through a line one character at a time, manages arrayName pointer, and returns whether or not there are any more parameters to parse
	bool parseVariable(int *currentCharIterator, string *arrayName);

	// parses through a line one character at a time, manages arraySize pointer, and returns whether or not there are any more parameters to parse
	bool parseSize(int *currentCharIterator, int *arraySize);

	// adds the currentArrayName to the variableArray and increments numVariablesInArray
	void addToVariableArray(string currentArrayName, int currentArraySize);

	// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
	void syncVariableArrayToSymbolTable();

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// prints the variableArray to the console
	void printVariableArray();
};