/* ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 11/26/17

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

#include "FileManager.h"

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

	// sets the global currentFileManager to point to the Compiler's parentFileManager
	void linkWithParentFileManager(FileManager *parentFileManager);

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */
	// loads the new line of core into the SymbolTable - For Executor
	void loadLine(string newLine);

	// Sets the RValue at memoryLocation to newValue - For Executor
	void setValue(int memoryLocation, string newValue);

	// Sets the RValue of the destinationAddress to the RValue of the sourceAddress
	void deepCopy(int destinationAddress, int sourceAddress);

	// Adds a new array to the globalArrayofArrayDimensions
	void addNewArray(int memoryLocationOfNewArray, int sizeOfNewArray);

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

	// returns the value at the specified memoryLocation - For Executor
	string getValue(int memoryLocation);

	// returns the lookup table index for the variable
	int getSymbolTableIndex(string variableNameToGet);

	// Returns true if the start & end indexes are within the range of the array
	bool rangeChecksOut(int arrayMemoryLocation, int startIndex, int endIndex);

	// prints out the value for every value in CoreMemory - For Executor
	void printCoreMemory();

	// prints out the Rvalue for every memoryLocation in CoreMemory from startIndex to endIndex - For Executor
	void printCoreMemory(int startIndex, int endIndex);

	// prints out the globalArrayofArrayDimensions
	void printArrayDimension();

	// iterates through the SymbolTable and prints the variableName & memoryLocation
	void printSymbolTable();

	// iterates through the SymbolTable and outputs the variableName & memoryLocation to .core file
	void outputCoreFile();

	// takes in currentString, sets the numberAsFloat, and returns if successful
	bool convertToFloat(string currentString, float &numberAsFloat);

protected:

	/* ==============================================================================
		Private Members
	============================================================================== */

	// Core memory Array of Variables for Execution
	string globalCoreMemoryArray[MAX_NUM_VARIABLES];
	int globalSizeCoreMemory; // - For Executor

	// Array Of Arrays for Execution
	memoryTableObject globalArrayofArrayDimensions[MAX_NUM_VARIABLES];
	int globalNumArrayDimension;

	// Array Of memoryTableObjects for Compilation
	memoryTableObject symbolTableArray[MAX_NUM_VARIABLES]; // SymbolTable implemented as array of memoryTableObjects
	unsigned int numObjectsInArray;

	FileManager *currentFileManager;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// adds the variable to the table and returns the index
	int insertInto(memoryTableObject *currentMemoryObject);

};