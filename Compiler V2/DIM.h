/*
  ==============================================================================

	File: DIM.h
	Author: Brendan Thompson
	Updated: 10/01/17

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

const char DIM_OP_CODE = '0';

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	DIM Class Interface
============================================================================== */

class DIM {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	DIM();
	~DIM();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareDIM(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	bool newDIM(string currentLine, int *numErrors);

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


	// iterates through the parameters passed to the command one character at a time and inserts them into variableArray
	void parseParameters();

// analyzeCharacter =
	// changes the globalNumErrors
	// changes the index to the currentChar
	// manipulates the status of parsing given pointers to status information
	void analyzeCharacter(	char currentChar,
							string currentArrayName,
							unsigned int numCharactersInVarName, unsigned int *currentLineIterator,
							bool *continueParsingParameters, bool *continueParsingVariable);

	// continues parsing down the line in order to get the size of the designated array
		// manipulates currentLineIterator and continueParsingParameters
		// calls addToVariableArray()
	void parseSize(string currentArrayName, unsigned int *currentLineIterator, bool *continueParsingParameters);

	// analyzeCharacter =
		// changes the globalNumErrors
		// changes currentLineIterator
		// manipulates the status of parsing given pointers to status information
	void analyzeSize(char currentChar, unsigned int numCharsInSize, unsigned int *currentLineIterator, bool *continueParsingSize, bool *continueParsingParameters);

	// adds the currentArrayName to the variableArray and increments numVariablesInArray
	void addToVariableArray(string currentArrayName, unsigned int currentArraySize);

	// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
	void syncVariableArrayToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outpuDIMCommand();



	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// prints the variableArray to the console
	void printVariableArray();
};