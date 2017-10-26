/*
  ==============================================================================

	File: taREAD.h
	Author: Brendan Thompson
	Updated: 10/09/17

	Description: Interface for Functions for processing aREAD command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

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
#define INDEX_FIRST_CHAR_AFTER_AREAD_COMMAND 5

const string AREAD_OP_CODE = "11";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	taREAD Class Interface
============================================================================== */

class taREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	taREAD();
	~taREAD();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareAREAD(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns number of errors
	int handleAREAD(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject currentArrayObject;
	string globalArrayName;
	string globalStartIndex;
	string globalEndIndex;

	string globalCurrentLine;
	unsigned int globalNumErrors;

	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// calls parseVariable() to get globalArrayName, and then parseIndex() twice to get the start & end indexes
	void parseParameters();

	// parses through a line one character at a time, adds complete currentVariableName to globalArrayName, and returns whether or not there are any more parameters to parse
	bool parseVariable(int *currentCharIterator);

	// parses through a line one character at a time, conditionally adds complete currentIndexString to globalStartIndex or globalEndIndex, and returns whether or not there are any more parameters to parse
	bool parseIndex(int *currentCharIterator, bool gettingStartIndex);

	// Ensures the globalArrayName already exists in the Symbol Table and gets the memory location
	void getMemoryLocation();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputAREADCommand();



	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};