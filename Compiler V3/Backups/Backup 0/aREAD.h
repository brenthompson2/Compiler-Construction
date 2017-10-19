/*
  ==============================================================================

	File: aREAD.h
	Author: Brendan Thompson
	Updated: 10/01/17

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

const string AREAD_OP_CODE = "11";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	aREAD Class Interface
============================================================================== */

class aREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	aREAD();
	~aREAD();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareAREAD(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	bool newAREAD(string currentLine, int *MainNumErrors);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject currentMemoryTableObject;
	string globalVariableName;
	string globalStartIndex;
	string globalEndIndex;

	string globalCurrentLine;
	bool validSyntax;
	unsigned int globalNumErrors;

	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */


	// iterates through the parameters passed to the command one character at a time and inserts them into variableArray
	void parseParameters();

// analyzeCharInVarName =
	// manipulates globalNumErrors
	// changes the index to the currentChar
	// calls addToVariableArray(string currentVariableName)
	// manipulates the status of parsing given pointers to status information
	void analyzeCharInVarName(	char currentChar,
								string currentVariableName,
								unsigned int numCharactersInVarName,
								bool *continueParsingVariable);

// analyzeCharInIndex =
	// manipulates globalNumErrors
	// changes the index to the currentChar
	// calls addToVariableArray(string currentVariableName)
	// manipulates the status of parsing given pointers to status information
	void analyzeCharInIndex(char currentChar,
							string currentVariableName,
							unsigned int numCharactersInVarName,
							bool *continueParsingVariable,
							bool isEndIndex);

	// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
	void syncVariableArrayToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputAREADCommand();



	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};