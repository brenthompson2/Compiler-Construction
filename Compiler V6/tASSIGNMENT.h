/*
  ==============================================================================

	File: tASSIGNMENT.h
	Author: Brendan Thompson
	Updated: 11/05/17

	Description: Interface for Functions for processing LOOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
// #include <sstream> // std::stringstream str(" ")

#include "SymbolTable.h"
#include "FileManager.h"
#include "ExpressionParsingMatrix.h"

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
#define INDEX_FIRST_CHAR_AFTER_ASSIGNMENT_COMMAND 4

#define MAX_NUM_OPERATORS 40
#define MAX_NUM_ID 20

const string ASSIGNMENT_OP_CODE = "14";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tASSIGNMENT Class Interface
============================================================================== */

class tASSIGNMENT {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tASSIGNMENT();
	~tASSIGNMENT();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareASSIGNMENT(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns num errors
	int handleASSIGNMENT(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	int globalNumErrors;

	// Arguments
	int globalNumIDs;
	int globalNumOperators;
	memoryTableObject *globalIDArray[MAX_NUM_OPERATORS];
	int *globalOperatorArray[MAX_NUM_ID];

	// Parent's Objects
	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable

	InputObject objectForTesting;


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the ASSIGNMENTensions
	void parseParameters();

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseVariable(int *currentCharIterator, int parameterNumber);

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseConstant(int *currentCharIterator, int parameterNumber);

	// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
	void syncVariablesToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputASSIGNMENTCommand();



	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};