/*
  ==============================================================================

	File: tSTOP.h
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Interface for Functions for processing STOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "FileManager.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define INDEX_FIRST_CHAR_AFTER_STOP_COMMAND 4
const string STOP_OP_CODE = "3";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tSTOP Class Interface
============================================================================== */

class tSTOP {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tSTOP();
	~tSTOP();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareSTOP(FileManager *parentFileManager);

	// calls the functions necessary to parse the line and print the object code to the file while counting errors
	// returns num errors
	int handleSTOP(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	unsigned int globalNumErrors;

	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// checks to see if stop command is immediately followed by end of string character
	void checkSyntax();

	// tells the FileManager to print the object code for the command, which includes the command op code
	void outputSTOPCommand();




	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};