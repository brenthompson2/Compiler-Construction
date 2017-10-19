/*
  ==============================================================================

	File: tSTOP.h
	Author: Brendan Thompson
	Updated: 09/25/17

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

#include "LookupTable.h"
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
	void shutdown();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	void prepareSTOP(FileManager *parentFileManager);
	bool newSTOP(string currentLine); // handles a STOP command

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalCurrentLine;
	bool validSyntax;
	unsigned int globalNumErrors;

	FileManager *currentFileManager;


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	void checkSyntax();// checks to see if stop command is immediately followed by end of string character
	void outputSTOPCommand();




	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};