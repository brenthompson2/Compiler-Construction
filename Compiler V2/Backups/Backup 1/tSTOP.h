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

const char STOP_OP_CODE = '3';

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
	bool newSTOP(string currentLine, int *numErrors); // handles a STOP command

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	bool validSyntax;
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