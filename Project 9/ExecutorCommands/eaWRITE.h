/* ==============================================================================

	File: eaWRITE.h
	Author: Brendan Thompson
	Updated: 11/26/17

	Description: Interface  WRITE handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO

#include "../CoreMemory.h"
#include "../ProgramLineTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* ==============================================================================
	eaWRITE Class Interface
============================================================================== */

class eaWRITE {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eaWRITE();
	~eaWRITE();

	// Connects local pointer to ParentMemoryManager
	void prepareAWRITE(CoreMemory *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the WRITE command
	void handleAWRITE(ProgramLineObject *currentLine);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	ProgramLineObject *globalCurrentLine;

	CoreMemory *ParentMemoryManager; // pointer to the Executor's (parent's) CoreMemory

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// Executes the Command
	void executeAWRITECommand(int arrayMemoryLocation, int startIndex, int endIndex);
};