/* ==============================================================================

	File: elREAD.h
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
	elREAD Class Interface
============================================================================== */

class elREAD {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	elREAD();
	~elREAD();

	// Connects local pointer to ParentLiteralManager
	void prepareLREAD(LiteralTable *currentLiteralManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the read command
	void handleLREAD(ProgramLineObject *currentLine);

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
	void executeLREADCommand();
};