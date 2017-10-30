/*
  ==============================================================================

	File: tlWRITE.h
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Interface for Functions for processing lWRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "LiteralTable.h"
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
#define INDEX_FIRST_CHAR_AFTER_LWRITE_COMMAND 6

const string LWRITE_OP_CODE = "17";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tlWRITE Class Interface
============================================================================== */

class tlWRITE {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tlWRITE();
	~tlWRITE();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & LiteralTable with the parent's (compiler's) versions
	void prepareLWRITE(FileManager *parentFileManager, LiteralTable *parentLiteralManager);

	// calls the functions necessary to parse the line, sync the literal with the LiteralTable, and print the object code to the file while counting errors
	// returns number of errors
	int handleLWRITE(string currentLine, int actualLineNumber);

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
	void parseLiteral(int *currentCharIterator);

	// asks the literalManager to conditionally add the globalLiteralString to the Literal table and gets the globalLiteralAddress
	void syncLiteralToLiteralTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputLWRITECommand();


	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};