/* ==============================================================================

	File: eaREAD.h
	Author: Brendan Thompson
	Updated: 11/26/17

	Description: Interface  READ handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO

#include "../SymbolTable.h"
#include "../ProgramLineTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* ==============================================================================
	eaREAD Class Interface
============================================================================== */

class eaREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eaREAD();
	~eaREAD();

	// Connects local pointer to ParentMemoryManager
	void prepareAREAD(SymbolTable *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the read command
	void handleAREAD(ProgramLineObject *currentLine);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	ProgramLineObject *globalCurrentLine;

	SymbolTable *ParentMemoryManager; // pointer to the Executor's (parent's) SymbolTable

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// Executes the Command
	void executeAREADCommand(int arrayMemoryLocation, int startIndex, int endIndex);
};