/*==============================================================================

	File: tASSIGNMENT.h
	Author: Brendan Thompson
	Updated: 11/09/17

	Description: Interface for Functions for processing ASSIGNMENT command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

==============================================================================*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <string.h> // strcpy & strcat

#include "SymbolTable.h"
#include "FileManager.h"
#include "ExpressionFixConverter.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define OBJ_VALUE_EQUALS -1
#define OBJ_VALUE_LEFT_BRACKET -2
#define OBJ_VALUE_EXPONENT -3
#define OBJ_VALUE_TIMES -4
#define OBJ_VALUE_DIVIDE -5
#define OBJ_VALUE_PLUS -6
#define OBJ_VALUE_MINUS -7

const string ASSIGNMENT_OP_CODE = "14";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	tASSIGNMENT Class Interface
============================================================================== */

class tASSIGNMENT {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	tASSIGNMENT();
	~tASSIGNMENT();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
	void prepareASSIGNMENT(FileManager *parentFileManager, SymbolTable *parentMemoryManager);

	// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
	// returns num errors
	int handleASSIGNMENT(string currentLine, int correspondingLineNumber);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	int globalNumErrors;

	// Infix to Postfix Conversion
	ExpressionFixConverter mainExpressionConverter;

	// Arguments
	memoryTableObject globalVariableArray[MAX_NUM_INPUT_VALUES]; // memoryTableObject declared in SymbolTable
	unsigned int globalNumVariablesInArray;

	// Parent's Objects
	FileManager *currentFileManager; // pointer to the Compiler's (parent's) FileManager
	SymbolTable *currentMemoryManager; // pointer to the Compiler's (parent's) SymbolTable

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	// Conditionally adds the postfix input values to the globalVariableArray
	void syncExpressionToVariableArray(string newExpression[], int numValsInNewExpression);

	// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
	void syncVariablesToSymbolTable();

	// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
	void outputASSIGNMENTCommand(string newExpression[], int numValsInNewExpression);

	// Takes in an operator and returns the appropriate token for the obj file
	int getObjectCodeMapping(string currentInputValue);

	// Prints out the postfix array
	void printPostfixExpression(string newExpression[], int numValsInNewExpression);
};