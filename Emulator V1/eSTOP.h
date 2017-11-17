/* ==============================================================================

	File: eSTOP.h
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Interface for Functions for processing STOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

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

#define INDEX_FIRST_CHAR_AFTER_STOP_COMMAND 4
const string STOP_OP_CODE = "3";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eSTOP Class Interface
============================================================================== */

class eSTOP {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eSTOP();
	~eSTOP();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to parse the line and print the object code to the file while counting errors
	// returns num errors
	int handleSTOP(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	unsigned int globalNumErrors;


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// checks to see if stop command is immediately followed by end of string character
	void checkSyntax();




	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};