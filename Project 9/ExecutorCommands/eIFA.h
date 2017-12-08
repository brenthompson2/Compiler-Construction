/* ==============================================================================

	File: eIFA.h
	Author: Brendan Thompson
	Updated: 11/30/17

	Description: Interface for IFA handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

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
	Symbolic Constants
============================================================================== */

/* ==============================================================================
	eIFA Class Interface
============================================================================== */

class eIFA {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eIFA();
	~eIFA();

	// Connects local pointer to parentMemoryManager
	void prepareIFA(CoreMemory *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to test the IFA and sets the currentProgramLine accordingly
	void handleIFA(ProgramLineObject *currentLine, int *currentProgramLine);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	ProgramLineObject *globalCurrentLine;

	CoreMemory *parentMemoryManager; // pointer to the Executor's (parent's) CoreMemory

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// Sets the values by looking up the memoryLocations and values provided by globalCurrentLine
	void getValueForConditional(float *valueOfID, int *negativeLine, int *zeroLine, int *positiveLine);
};