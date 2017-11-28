/* ==============================================================================

	File: eSUBP.h
	Author: Brendan Thompson
	Updated: 11/26/17

	Description: Interface  SUBP handler for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <cmath> // All Math Commands

#include "../SymbolTable.h"
#include "../ProgramLineTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

const int SIN_CODE = -10;
const int COS_CODE = -11;
const int EXP_CODE = -12;
const int ABS_CODE = -13;
const int ALG_CODE = -14;
const int ALN_CODE = -15;
const int LOG_CODE = -16;
const int SQR_CODE = -17;

/* ==============================================================================
	eSUBP Class Interface
============================================================================== */

class eSUBP {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eSUBP();
	~eSUBP();

	// Connects local pointer to ParentMemoryManager
	void prepareSUBP(SymbolTable *currentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to execute the SUBP command
	void handleSUBP(ProgramLineObject *currentLine);

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
	void executeSUBPCommand(int operationCode, int variableMemLocation, int variableValue, int IdValue);
};