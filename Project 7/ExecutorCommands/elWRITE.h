/* ==============================================================================

	File: elWRITE.h
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Interface  READ handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO

#include "../LiteralTable.h"
#include "../ProgramLineTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* ==============================================================================
	elWRITE Class Interface
============================================================================== */

class elWRITE {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	elWRITE();
	~elWRITE();

	// Connects global pointer to ParentLiteralManager
	void prepareLWRITE(LiteralTable *currentLiteralManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the command
	void handleLWRITE(ProgramLineObject *currentLine);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	ProgramLineObject *globalCurrentLine;

	LiteralTable *ParentLiteralManager; // pointer to the Executor's (parent's) LiteralTable

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// Executes the Command
	void executeLWRITECommand();
};