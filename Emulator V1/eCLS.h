/*
  ==============================================================================

	File: eCLS.h
	Author: Brendan Thompson
	Updated: 10/23/17

	Description: Interface for Functions for processing eCLS command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

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

#define INDEX_FIRST_CHAR_AFTER_CLS_COMMAND 3
const string CLS_OP_CODE = "19";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eCLS Class Interface
============================================================================== */

class eCLS {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eCLS();
	~eCLS();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareCLS(FileManager *parentFileManager);

	// calls the functions necessary to parse the line and print the object code to the file while counting errors
	// returns num errors
	int handleCLS(string currentLine, int correspondingLineNumber);

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

	// checks to see if eCLS command is immediately followed by end of string character
	void checkSyntax();

	// tells the FileManager to print the object code for the command, which includes the command op code
	void outputCLSCommand();




	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};