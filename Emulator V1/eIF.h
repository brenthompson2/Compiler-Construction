/*
  ==============================================================================

	File: eIF.h
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Interface for Functions for processing IF command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

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

#include "FileManager.h"
#include "LineLabelTable.h"
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
#define INDEX_FIRST_CHAR_AFTER_IF_COMMAND 2

const string IF_OP_CODE = "18";

const int FIRST_ID_CODE = 1;
const int SECOND_ID_CODE = 2;

const int LESS_CODE = -1;
const int LESS_EQUAL_CODE = -2;
const int EQUAL_CODE = -3;
const int GREATER_CODE = -4;
const int GREATER_EQUAL_CODE = -5;
const int NOT_EQUAL_CODE = -6;

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eIF Class Interface
============================================================================== */

class eIF {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eIF();
	~eIF();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager, SymbolTable, and LineLabelTable with the parent's (compiler's) versions
	void prepareIF(FileManager *parentFileManager, SymbolTable *parentMemoryManager, LineLabelTable *parentLineManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns num errors
	int handleIF(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	int globalNumErrors;

	// Arguments
	memoryTableObject firstID;
	int testCondition;
	memoryTableObject secondID;
	memoryTableObject globalLineLabel;

	// Parent's Objects
	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable
	LineLabelTable *currentLineManager; // pointer to the Compiler's (parent's) LineLabelTable


	/* ==============================================================================
		Private Methods
	============================================================================== */

	// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
	void syncVariablesToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputIFCommand();

	/* ==============================================================================
		Private Parsing Methods
	============================================================================== */

	// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the IFAensions
	void parseParameters();

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseVariable(int *currentCharIterator, int parameterNumber);

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseConstant(int *currentCharIterator, int parameterNumber);

	// parses through a line one character at a time, sets global Line Label Name, and returns whether or not there are any more variables to parse
	bool parseLineLabelName(int *currentCharIterator);

	// parses through a line one character at a time, manages the global testCondition
	void parseTestCond(int *currentCharIterator);

	// parses through a line one character at a time and returns whether or not there are any more parameters to parse
	bool checkForThen(int *currentCharIterator);


	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};