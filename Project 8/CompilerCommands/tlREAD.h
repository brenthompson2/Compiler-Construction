/*
  ==============================================================================

	File: tlREAD.h
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Interface for Functions for processing LREAD command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "../LiteralTable.h"
#include "../FileManager.h"

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
#define INDEX_FIRST_CHAR_AFTER_LREAD_COMMAND 5

const string LREAD_OP_CODE = "16";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tlREAD Class Interface
============================================================================== */

class tlREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tlREAD();
	~tlREAD();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & LiteralTable with the parent's (compiler's) versions
	void prepareLREAD(FileManager *parentFileManager, LiteralTable *parentLiteralManager);

	// calls the functions necessary to parse the line, sync the variables with the LiteralTable, and print the object code to the file while counting errors
	// returns number of errors
	int handleLREAD(string currentLine, int actualLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	literalTableObject globalLiteralObject;
	string globalCurrentLine;
	int globalNumErrors;

	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	LiteralTable *currentliteralManager; // pointer to the Compiler's (parent's) LiteralTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */


	// calls parseLiteral
	void parseParameters();

	// parses through a line one character at a time, adds complete variables to VariableArray, and returns whether or not there are any more variables to parse
	bool parseVariable(int *currentCharIterator);

	// asks the literalManager to conditionally add the globalLiteralString to the Literal table and gets the globalLiteralAddress
	void syncLiteralToLiteralTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputLREADCommand();


	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};