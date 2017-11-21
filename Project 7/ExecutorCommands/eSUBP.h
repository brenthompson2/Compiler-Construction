/* ==============================================================================

	File: eSUBP.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing SUBP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
#include <sstream> //std::stringstream str(" ")

#include "../SymbolTable.h"

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
#define INDEX_FIRST_CHAR_AFTER_SUBP_COMMAND 4

const string SUBP_OP_CODE = "13";

const int VARIABLE_ID_CODE = 1;
const int OTHER_ID_CODE = 2;

const int SIN_CODE = -10;
const int COS_CODE = -11;
const int EXP_CODE = -12;
const int ABS_CODE = -13;
const int ALG_CODE = -14;
const int ALN_CODE = -15;
const int LOG_CODE = -16;
const int SQR_CODE = -17;

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eSUBP Class Interface
============================================================================== */

class eSUBP {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eSUBP();
	~eSUBP();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to SymbolTable with the parent's (compiler's) versions
	void prepareSUBP(SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns num errors
	int handleSUBP(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	int globalNumErrors;

	// Arguments
	memoryTableObject globalVariable;
	float globalOperation;
	memoryTableObject secondID;

	// Parent's Objects
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Methods
	============================================================================== */

	// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
	void syncVariablesToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputSUBPCommand();

	/* ==============================================================================
		Private Parsing Methods
	============================================================================== */

	// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the SUBPAensions
	void parseParameters();

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseVariable(int *currentCharIterator, int parameterNumber);

	// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
	bool parseConstant(int *currentCharIterator, int parameterNumber);

	// parses through a line one character at a time, manages the global testCondition
	void parseOperation(int *currentCharIterator);


	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};