/* ==============================================================================

	File: eWRITE.h
	Author: Brendan Thompson
	Updated: 11/20/17

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
	eWRITE Class Interface
============================================================================== */

class eWRITE {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eWRITE();
	~eWRITE();

	// Connects global pointer to ParentMemoryManager
	void prepareWRITE(SymbolTable *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the command
	void handleWRITE(ProgramLineObject *currentLine, int correspondingLineNumber);

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
	void executeWRITECommand();
};