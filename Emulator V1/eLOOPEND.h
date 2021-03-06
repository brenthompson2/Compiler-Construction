/*
  ==============================================================================

	File: eLOOPEND.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing LOOPEND command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

const string LOOPEND_OP_CODE = "15";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eLOOPEND Class Interface
============================================================================== */

class eLOOPEND {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eLOOPEND();
	~eLOOPEND();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareLOOPEND();

	// calls the functions necessary to parse the line and print the object code to the file while counting errors
	// returns num errors
	int handleLOOPEND(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	unsigned int globalNumErrors;

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// checks to see if LOOPEND command is immediately followed by end of string character
	void checkSyntax();

	// tells the FileManager to print the object code for the command, which includes the command op code
	void outputLOOPENDCommand();

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};