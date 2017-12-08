/* ==============================================================================

	File: eIF.h
	Author: Brendan Thompson
	Updated: 11/30/17

	Description: Interface for IF handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

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

const int LESS_CODE = -1;
const int LESS_EQUAL_CODE = -2;
const int EQUAL_CODE = -3;
const int GREATER_CODE = -4;
const int GREATER_EQUAL_CODE = -5;
const int NOT_EQUAL_CODE = -6;

/* ==============================================================================
	eIF Class Interface
============================================================================== */

class eIF {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eIF();
	~eIF();

	// Connects local pointer to parentMemoryManager
	void prepareIF(CoreMemory *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to test the IF and sets the currentProgramLine accordingly
	void handleIF(ProgramLineObject *currentLine, int *currentProgramLine);

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
	void getValuesForConditional(float *firstValue, float *secondValue, int *testCondition, int *destinationLine);

	// Returns the value of the tested condition
	bool getResultOfCondition(float firstOperand, float secondOperand, int testCondition);
};