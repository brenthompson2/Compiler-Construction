/*
  ==============================================================================

	File: LookupTable.cpp
	Author: Brendan Thompson
	Updated: 09/25/17

	Description: Interface for LookupTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_STRING_LENGTH 50
#define MAX_VARIABLE_NAME_LENGTH 128
#define MAX_NUM_VARIABLES 1000
#define NOT_FOUND_IN_ARRAY -1

/* ==============================================================================
	Type Definitions
============================================================================== */

struct memoryTableObject {
	string variableName;
	unsigned int memoryLocation;
};

/* ==============================================================================
	Lookup Table Class Interface
============================================================================== */

class LookupTable {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	LookupTable();
	void LookupTable_shutdown();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	void manageMemoryTableObject(memoryTableObject *currentMemoryObject); // if the variable doesn't already exist, the function adds the variable to the table in the appropriately sorted spot and assigns it a memory location
	void removeVariable(string variableName); // if the variable exists, removes it from the table

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	void printLookupTable();

	bool currentlyExists(string variableName); // returns true if the variable already exists in the table
	int getMemoryLocation(string variableName); // returns the memoryLocation for the variable
	int getLookupTableIndex(string variableName); // returns the lookup table index for the variable

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject sortedTableArray[MAX_NUM_VARIABLES];
	unsigned int numObjectsInArray;


	/* ==============================================================================
		Private Methods
	============================================================================== */
	int addVariable(string variableName); // if the variable doesn't already exist, the function adds the variable to the table in the appropriately sorted spot

};