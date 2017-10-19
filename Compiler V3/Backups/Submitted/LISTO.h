/*
  ==============================================================================

	File: LISTO.h
	Author: Brendan Thompson
	Updated: 10/12/17

	Description: Interface for Functions for processing LISTO command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

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

#define INDEX_FIRST_CHAR_AFTER_LISTO_COMMAND 5
const char LISTO_OP_CODE = '6';

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	LISTO Class Interface
============================================================================== */

class LISTO {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	LISTO();
	~LISTO();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareLISTO(FileManager *parentFileManager);

	// calls the functions necessary to parse the line and print the object code to the file while counting errors
	// returns num errors
	int handleLISTO(string currentLine, int correspondingLineNumber);

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

	// checks to see if LISTO command is immediately followed by end of string character
	void checkSyntax();

	// tells the FileManager to print the object code for the command, which includes the command op code
	void outputLISTOCommand();

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};