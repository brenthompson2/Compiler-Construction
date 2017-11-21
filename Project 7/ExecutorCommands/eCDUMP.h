/*
  ==============================================================================

	File: eCDUMP.h
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Functions for processing CDUMP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- NOT BEING USED: EXECUTOR IS HANDLING THIS COMMAND

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
// #include <stdlib.h>	// Exit()
// #include <string.h> // strcpy & strcat
#include <sstream> //std::stringstream str(" ")

#include "../SymbolTable.h"
#include "../ProgramLineTable.h"

// using std::cin;
using std::cout;
// using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eCDUMP Class Interface
============================================================================== */

class eCDUMP {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eCDUMP();
	~eCDUMP();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to SymbolTable with the parent's (compiler's) versions
	void prepareCDUMP(SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	void handleCDUMP(ProgramLineObject *currentLine);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	ProgramLineObject *globalCurrentLine;

	// Parent's Objects
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable


	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// Outputs All Core Memory Values Between the start and the end indexes
	 void coreDump(int startIndex, int endIndex);

};