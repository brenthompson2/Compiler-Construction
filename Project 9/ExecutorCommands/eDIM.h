/* ==============================================================================

	File: eDIM.h
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Interface  DIM handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

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
	eDIM Class Interface
============================================================================== */

class eDIM {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eDIM();
	~eDIM();

	// Connects local pointer to ParentMemoryManager
	void prepareDIM(CoreMemory *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the DIM command
	void handleDIM(ProgramLineObject *currentLine);

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
	void executeDIMCommand();
};