/*
  ==============================================================================

	File: LiteralTable.cpp
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Interface for LiteralTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
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
const string UNDEFINED_LITERAL = "";

/* ==============================================================================
	Type Definitions
============================================================================== */

struct literalTableObject {
	string variableName;
	string literalString;
	unsigned int memoryLocation;
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

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// if the Literal doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentLiteralObject
	void manageLiteralObject(literalTableObject *currentLiteralObject);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// iterates through the LiteralTable and prints the literalString & memoryLocation
	void printLiteralTable();

	// returns true if the variable already exists in the LiteralTable
	bool currentlyExists(string currentVariableName);

	// returns the memoryLocation for the variable
	int lookup(string currentVariableName);

	// returns the lookup table index for the variable
	int getLiteralTableIndex(string literalToFind);

protected:

	/* ==============================================================================
		Private Members
	============================================================================== */
	literalTableObject LiteralTableArray[MAX_NUM_LITERALS]; // LiteralTable implemented as array of memoryTableObjects
	unsigned int numObjectsInArray;


	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the variable to the table (HAVE NOT YET IMPLEMENTED SORT)
	int insertInto(literalTableObject *currentMemoryObject);

};