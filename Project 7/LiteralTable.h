/* ==============================================================================

	File: LiteralTable.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Interface for LiteralTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages literal phrases and their associated virtual memory locations

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO

#include "FileManager.h"

// using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

// #define MAX_STRING_LENGTH 50
// #define MAX_VARIABLE_NAME_LENGTH 128
#define MAX_NUM_LITERALS 1000
#define NOT_FOUND_IN_ARRAY -1

const string UNNAMED_LITERAL = "_NA";
const string UNDEFINED_LITERAL = "0.123456789";

/* ==============================================================================
	Type Definitions
============================================================================== */

struct literalTableObject {
	string variableName;
	string literalString;
	unsigned int memoryLocation; // currently same as index
};

/* ==============================================================================
	Literal Table Class Interface
============================================================================== */

class LiteralTable {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	LiteralTable();
	~LiteralTable();

	// sets the global currentFileManager to point to the Compiler's parentFileManager
	void linkWithParentFileManager(FileManager *parentFileManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// adds a new line of core to the LiteralTable - For Executor
	void loadLine(string newLine);

	// Sets the RValue at memoryLocation to newValue - For Executor
	void setValue(int memoryLocation, string newValue);

	// if the Literal doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentLiteralObject
	void manageLiteralObject(literalTableObject *currentLiteralObject);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// returns true if the variable already exists in the LiteralTable
	bool currentlyExists_Variable(string currentVariableName);

	// returns true if the literal already exists in the LiteralTable
	bool currentlyExists_Literal(string currentLiteralString);

	// returns the rvalue pointed to by the memoryLocation - For Executor
	string getValue(int memoryLocation);

	// returns the memoryLocation for the variable
	int lookup(string literalToFind);

	// returns the memoryLocation for the literalToFind
	int lookup_Literal(string literalToFind);

	// returns the lookup table index for the variable
	int getLiteralTableIndex(string literalVariableToFind);

	// iterates through the LiteralTable and prints the literalString & memoryLocation
	void ePrintLiteralTable();

	// iterates through the LiteralTable and prints the literalString & memoryLocation
	void printLiteralTable();

	// iterates through the LiteralTable and outputs the literalString & memoryLocation to .literal file
	void outputLiteralFile();

protected:

	/* ==============================================================================
		Private Members
	============================================================================== */
	string globalLiteralArray[MAX_NUM_LITERALS]; // - For Executor
	int globalSizeLiteralArray; // - For Executor

	literalTableObject LiteralTableArray[MAX_NUM_LITERALS]; // LiteralTable implemented as array of memoryTableObjects
	unsigned int numObjectsInArray;

	FileManager *currentFileManager;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the variable to the table (HAVE NOT YET IMPLEMENTED SORT)
	int insertInto(literalTableObject *currentMemoryObject);

};