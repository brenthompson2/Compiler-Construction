/*==============================================================================

	File: eASSIGNMENT.h
	Author: Brendan Thompson
	Updated: 12/10/17

	Description: Interface for Functions for handling ASSIGNMENT command for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

==============================================================================*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <cmath> // pow(double, double)

#include "../CoreMemory.h"
#include "../ProgramLineTable.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_NUM_ELEMENTS 40 // Same as ExpressionFixConverter
#define OPERATOR_NOT_FOUND -1 // Same as ExpressionFixConverter

#define OBJ_VALUE_EQUALS -1
#define OBJ_VALUE_LEFT_BRACKET -2
#define OBJ_VALUE_EXPONENT -3
#define OBJ_VALUE_TIMES -4
#define OBJ_VALUE_DIVIDE -5
#define OBJ_VALUE_PLUS -6
#define OBJ_VALUE_MINUS -7

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	eASSIGNMENT Class Interface
============================================================================== */

class eASSIGNMENT {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	eASSIGNMENT();
	~eASSIGNMENT();

	// Connects local pointer to CoreMemory with the parent's (executor's) versions
	void prepareASSIGNMENT(CoreMemory *parentMemoryManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// calls the functions necessary to parse the line, sync the variables with the CoreMemory, and print the object code to the file while counting errors
	// returns num errors
	int handleASSIGNMENT(ProgramLineObject *currentLine);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	int globalNumErrors;
	ProgramLineObject *globalCurrentLine;
	int globalNumElements;
	int globalArrayOfElements[MAX_NUM_ELEMENTS];

	// Parent's Objects
	CoreMemory *currentMemoryManager; // pointer to the Compiler's (parent's) CoreMemory

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	void setGlobals(ProgramLineObject *currentLine);

	void handleOperation(int indexOfOperator);

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	int getIndexFirstOperator();

	// Prints out the postfix expression array
	void printCurrentExpression();
};