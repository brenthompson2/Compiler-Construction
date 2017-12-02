/* ==============================================================================

	File: LoopManager.cpp
	Author: Brendan Thompson
	Updated: 11/30/17

	Description: Interface for LoopManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- Handles loop & loopend commands
		- Manages the current loop
		- Handles nesting

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include "ProgramLineTable.h"
#include "SymbolTable.h"

#include <iostream>	// Console IO
#include <sstream> //std::stringstream str(" ")
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_NUM_LOOPS 7

/* ==============================================================================
	Type Definitions
============================================================================== */

struct loopObject {
	int lineNumber;
	int runnerAddress;
	int startIndexAddress;
	int endIndexAddress;
	float incrementAmountAddress;
};

/* ==============================================================================
	symbol Table Class Interface
============================================================================== */

class LoopManager {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	LoopManager();
	~LoopManager();

	// sets the global parentMemoryManager & parentProgramManager to point to the Compiler's
	void prepareLoopManager(SymbolTable *currentMemoryManager, ProgramLineTable *currentProgramManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Handles the loop command by adding the new loopObject to the globalLoopArray and conditionally entering the loop
	void handleLOOP(ProgramLineObject *currentLine, int *currentProgramCounter);

	// returns the next appropriate program counter given the conditional of the currentLoop and pops off the globalCurrentLoopIndex
	void handleLOOPEND(int *currentProgramCounter);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// prints out the value for every value in CoreMemory - For Executor
	void printLoopManager();

private:

	/* ==============================================================================
		Private Members
	============================================================================== */

	loopObject globalLoopArray[MAX_NUM_LOOPS];
	int globalIndexTopLoopObject;

	SymbolTable *parentMemoryManager;
	ProgramLineTable *parentProgramManager;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the new loop to the top of the globalLoopArray & sets globalCurrentLoopIndex to point to it
	void addNewLoop(int newLineNumber, int newRunnerAddress, int newStartIndexAddress, int newEndIndexAddress, int incrementAddress);

	// Decrements the pointer to the top loop
	void popOffTopLoop();

	// Adds the topIncrementAmount to the topRunnerValue
	void incrementTopRunner();

	// Returns the result of the conditional of the top loop
	bool checkConditionTopLoop();

	// Sets the RValues given the LValues
	void setConditionValues(int runnerLValue, float *runnerRValue,
							int startLValue, float *startRValue,
							int endLValue, float *endRValue,
							int incrementLValue, float *incrementRValue);

	// returns true if the condition succeeded given the direction represented by the increment amount
	bool getConditionResults(float topIncrementAmount, float topRunnerValue, float topEndValue);

	// returns true if the variable already exists in the LoopManager
	bool currentlyExists(int lineNumberOfLoop);

};