/* ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

	Description: Interface for SymbolTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages IDs (variables or Constants) and their associated values and virtual memory locations
		- sets all initial values to 0.123456789
		- coreMemoryArray[1000] = (bool) failedCompilation; (0 = success, 1 = failed)
		- calls on the FileManager to output .core file

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <sstream> // used in convertToFloat()
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

#define UNDEFINED_VALUE 0.123456789
const string UNDECLARED_VALUE = "_NA";

#define INDEX_COMPILATION_RESULT 1000
#define SUCCESSFULLY_COMPILED 0
#define FAILED_COMPILATION 1

/* ==============================================================================
	Type Definitions
============================================================================== */

struct memoryTableObject {
	string variableName;
	unsigned int memoryLocation;
	float value;
	bool isConstant;
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
	// adds a new line of core to the SymbolTable
	void loadLine(string newLine);

	// Sets the RValue at memoryLocation to newValue
	void setValue(int memoryLocation, string newValue);

	// if the variable doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentMemoryObject
	void manageMemoryTableObject(memoryTableObject *currentMemoryObject);

	// sets coreMemory boolean regarding the result of compilation
	void setCompilationResult(bool completedSuccessfully);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// returns true if the variable already exists in the SymbolTable
	bool currentlyExists(string variableName);

	// returns the memoryLocation for the variable
	int lookup(string variableName);

	// returns the value at the specified memoryLocation
	string getValue(int memoryLocation);

	// returns the lookup table index for the variable
	int getSymbolTableIndex(string variableNameToGet);

	// prints out the value for every value in CoreMemory
	void printCoreMemory();

	// prints out the Rvalue for every memoryLocation in CoreMemory from startIndex to endIndex
	void printCoreMemory(int startIndex, int endIndex);

	// iterates through the SymbolTable and prints the variableName & memoryLocation
	void printSymbolTable();

	// takes in currentString, sets the numberAsFloat, and returns if successful
	bool convertToFloat(string currentString, float &numberAsFloat);

private:

	/* ==============================================================================
		Private Members
	============================================================================== */

	string globalCoreMemoryArray[MAX_NUM_VARIABLES];
	int globalSizeCoreMemory;

	memoryTableObject symbolTableArray[MAX_NUM_VARIABLES]; // SymbolTable implemented as array of memoryTableObjects
	unsigned int numObjectsInArray;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the variable to the table and returns the index
	int insertInto(memoryTableObject *currentMemoryObject);

};