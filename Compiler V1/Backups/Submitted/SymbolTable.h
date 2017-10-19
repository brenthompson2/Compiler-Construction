/*
  ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 09/26/17

	Description: Interface for SymbolTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

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
	symbol Table Class Interface
============================================================================== */

class SymbolTable {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	SymbolTable();
	void SymbolTable_shutdown();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// if the variable doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentMemoryObject
	void manageMemoryTableObject(memoryTableObject *currentMemoryObject);

	// if the variable exists, removes it from the table (NOT YET IMPLEMENTED)
	void removeVariable(string variableName);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// iterates through the SymbolTable and prints the variableName & memoryLocation
	void printSymbolTable();

	// returns true if the variable already exists in the SymbolTable
	bool currentlyExists(string variableName);

	// returns the memoryLocation for the variable
	int lookup(string variableName);

	// returns the lookup table index for the variable
	int getSymbolTableIndex(string variableName);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject sortedTableArray[MAX_NUM_VARIABLES]; // SymbolTable implemented as array of memoryTableObjects
	unsigned int numObjectsInArray;
	unsigned int totalMemorySpacesUsed;


	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the variable to the table (HAVE NOT YET IMPLEMENTED SORT)
	int insertInto(string variableName);

};