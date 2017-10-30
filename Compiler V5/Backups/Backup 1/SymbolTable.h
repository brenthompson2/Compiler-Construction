/*
  ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 10/29/17

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
#define MAX_NUM_VARIABLES 1001
#define NOT_FOUND_IN_ARRAY -1

#define INDEX_COMPILATION_RESULT 1000
#define SUCCESSFULLY_COMPILED 0
#define FAILED_COMPILATION 1

/* ==============================================================================
	Type Definitions
============================================================================== */

struct memoryTableObject {
	string variableName;
	unsigned int memoryLocation;
	int integerValue;
	bool booleanValue;
	bool stringValue;
	bool isArray;
	unsigned int size;
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
	~SymbolTable();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// if the variable doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentMemoryObject
	void manageMemoryTableObject(memoryTableObject *currentMemoryObject);

	// sets coreMemory boolean regarding the result of compilation
	void setCompilationResult(bool completedSuccessfully);

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

protected:

	/* ==============================================================================
		Private Members
	============================================================================== */
	memoryTableObject symbolTableArray[MAX_NUM_VARIABLES]; // SymbolTable implemented as array of memoryTableObjects
	unsigned int numObjectsInArray;
	unsigned int numUsedMemory;


	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the variable to the table (HAVE NOT YET IMPLEMENTED SORT)
	int insertInto(memoryTableObject *currentMemoryObject);

};